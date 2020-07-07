#include "Header.h"
#include <cstdlib>
#include <algorithm>   

Pos turn(Player* player,Player* not_player, Board* board);
void displayTurn(char color);
void displayScore(int white, int black);
Pos eatInRow(Player* player, Piece* piece,Board* board);
Pos isEaten(Pos origin, Pos targert);
vector<Pos> arrToVec(Pos* arr,int size);
int main() {
	Board board;
	Player white('w');
	Player black('b');
	white.initPlayer();
	black.initPlayer();
	board.initBoard(&white,&black);
	board.printBoard();
	Pos ate;
	Piece* eaten;
	Piece* selected;
	while (white.score<12&&black.score<12) {
		displayScore(white.score, black.score);
		ate=turn(&white,&black, &board);
		if (ate.row == -2)
			break;
		if (ate.row == -3) {
			black.score = 12;
			break;
		}
		system("CLS");
		board.printBoard();
		displayScore(white.score, black.score);

		ate=turn(&black,&white, &board);
		if (ate.row == -2)
			break;
		if (ate.row == -3) {
			white.score = 12;
			break;
		}
		system("CLS");
		board.printBoard();

	}
	system("CLS");
	if (white.score == 12) {

		cout << "WHITE WINS";
	}
	else if (black.score == 12) {
		cout << "BLACK WINS";

	}
	else {
		cout << "EXITED";
	}

}


Pos turn(Player* player,Player* not_player, Board* board) {
	displayTurn(player->color);

	Piece* selected=NULL;
	Piece* eaten;
	Pos to_move;
	to_move.col = -1;
	Pos ate;
	vector<Pos> moveables;
	ate.col = -1;
	ate.row = -1;
	do {
		moveables = player->generateMoveables(board);
		if (moveables.size() == 0) {
			ate.row = -3;
			return ate;
		}
		to_move = board->select(moveables);
		if (to_move.row == -2) {
			return to_move;
		}
		selected = player->isPiece(to_move);
	} while (selected == NULL);

	board->showMoves(selected->moves);

	do {
		to_move = board->select(arrToVec(selected->moves,16));
		if (to_move.row == -2) {
			return to_move;
		}
	} while (selected->isLegal(to_move) == 0);

	ate = isEaten(selected->pos, to_move);

	board->updateBoard(selected, to_move);
	if (selected->checkIfKing() == 1) {
		board->updateBoard(selected, selected->pos);
	}


	if (ate.row == -2)
		return ate;
	while (ate.row != -1) {
		eaten = not_player->isPiece(ate);
		if (eaten != NULL) {
			eaten->color = 'd';
			board->updateBoard(eaten, eaten->pos);
			player->score++;
			system("CLS");
			board->printBoard();
			ate = eatInRow(player, selected, board);

		}
		else {
			break;
		}
	}
	selected->can_eat = false;

	return ate;

	
}

Pos isEaten(Pos origin, Pos target) {
	Pos eaten;
	eaten.row = -1;
	eaten.col = -1;
	if (abs(origin.row - target.row) == 1) {
		return eaten;
	}
	if (origin.row > target.row) {
		eaten.row = target.row + 1;
		if (origin.col < target.col) {
			eaten.col = target.col - 1;
		}
		else {
			eaten.col = target.col + 1;
		}
		return eaten;
	}
	else {
		eaten.row = target.row - 1;
		if (origin.col < target.col) {
			eaten.col = target.col - 1;
		}
		else {
			eaten.col = target.col + 1;
		}
		return eaten;
	}
}

bool comparePos(Pos pos1, Pos pos2) {
	if (pos1.col == pos2.col) {
		return pos1.row < pos2.row;
	}
	else
		return pos1.col < pos2.col;
}

vector<Pos> arrToVec(Pos* arr, int size)
{
	vector<Pos> vec;
	for (int i = 0; i< size; i++) {
		if(arr[i].col!=-1)
		vec.push_back(arr[i]);
	}
	sort(vec.begin(), vec.end(), comparePos);
	return vec;
}

void displayTurn(char color)
{
	if (color == 'w') {
		gotoxy(20, 1);
		cout << "White Turn";
	}
	else {
		gotoxy(20, 1);
		cout << "Black Turn";
	}
}

void displayScore(int white, int black)
{
	gotoxy(7, 9);
	cout << "SCORE";
	gotoxy(1, 10);
	cout << "White:" << white << " | Black:" << black;
}

Pos eatInRow(Player* player, Piece* piece, Board* board)
{

	Pos to_move;
	Pos ate;
	ate.col = -1;
	ate.row = -1;

	if (piece->updateLegalMovesInRow(board->board) == 0)
		return ate;
		

	board->showMoves(piece->moves);

	do {
		to_move = board->select(arrToVec(piece->moves,16));
		if (to_move.row == -2) {
			return to_move;
		}
	} while (piece->isLegal(to_move) == 0);

	if (abs(to_move.row - piece->pos.row) != 1) {
		ate.col = (to_move.col + piece->pos.col) / 2;
		ate.row = (to_move.row + piece->pos.row) / 2;
	}
	board->updateBoard(piece, to_move);
	if(piece->checkIfKing())
		board->updateBoard(piece, piece->pos);
	return ate;
}
