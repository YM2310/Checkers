#include "Header.h"
#define EATING_MOVE 2
#define OPEN_MOVE 1
#define BLOCKED_MOVE 0
#define TOP_RIGHT 0
#define TOP_LEFT 1
#define BOTTOM_RIGHT 2
#define BOTTOM_LEFT 3


int checkTopRight(Pos pos, char board[][8]);
int checkTopLeft(Pos pos, char board[][8]);
int checkBottomRight(Pos pos, char board[][8]);
int checkBottomLeft(Pos pos, char board[][8]);
void updateLegalMovesWhite(Piece* piece ,char board[][8]);
void updateLegalMovesBlack(Piece* piece, char board[][8]);
int howManyMoves(Pos* moves);
void updateLegalMovesKing(Piece* piece, char board[][8]);
int sameLetter(char c1, char c2);

int Piece:: updateLegalMoves(char board[][8]) {
	if (this->status == 'k') {
		updateLegalMovesKing(this, board);
		return howManyMoves(this->moves);
	}
	if (this->color == 'w')
		updateLegalMovesWhite(this,board);
	else
		updateLegalMovesBlack(this,board);
	return howManyMoves(this->moves);


}

int Piece::updateLegalMovesInRow(char board[][8])
{
	Pos enemy;
	if (checkTopRight(this->pos, board) == EATING_MOVE) {
		{
			enemy.row = this->pos.row - 1;
			enemy.col = this->pos.col + 1;
			if (checkTopRight(enemy, board) == 1) {
				this->moves[TOP_RIGHT].row = enemy.row - 1;
				this->moves[TOP_RIGHT].col = enemy.col + 1;
			}
			else {
				this->moves[TOP_RIGHT].row = -1;
				this->moves[TOP_RIGHT].col = -1;
			}
		}
	}
	else {
		this->moves[TOP_RIGHT].row = -1;
		this->moves[TOP_RIGHT].col = -1;
	}
	if (checkTopLeft(this->pos, board) == EATING_MOVE) {
		{
			enemy.row = this->pos.row - 1;
			enemy.col = this->pos.col - 1;
			if (checkTopLeft(enemy, board) == 1) {
				this->moves[TOP_LEFT].row = enemy.row - 1;
				this->moves[TOP_LEFT].col = enemy.col - 1;
			}
			else {
				this->moves[TOP_LEFT].row = -1;
				this->moves[TOP_LEFT].col = -1;
			}
		}
	}
	else {
		this->moves[TOP_LEFT].row = -1;
		this->moves[TOP_LEFT].col = -1;
	}
	if (checkBottomRight(this->pos, board) == EATING_MOVE) {
		{
			enemy.row = this->pos.row + 1;
			enemy.col = this->pos.col + 1;
			if (checkBottomRight(enemy, board) == 1) {
				this->moves[BOTTOM_RIGHT].row = enemy.row + 1;
				this->moves[BOTTOM_RIGHT].col = enemy.col + 1;
			}
			else {
				this->moves[BOTTOM_RIGHT].row = -1;
				this->moves[BOTTOM_RIGHT].col = -1;
			}
		}
	}
	else {
		this->moves[BOTTOM_RIGHT].row = -1;
		this->moves[BOTTOM_RIGHT].col = -1;
	}
	if (checkBottomLeft(this->pos, board) == EATING_MOVE) {
		{
			enemy.row = this->pos.row + 1;
			enemy.col = this->pos.col - 1;
			if (checkBottomLeft(enemy, board) == 1) {
				this->moves[BOTTOM_LEFT].row = enemy.row + 1;
				this->moves[BOTTOM_LEFT].col = enemy.col - 1;
			}
			else {
				this->moves[BOTTOM_LEFT].row = -1;
				this->moves[BOTTOM_LEFT].col = -1;
			}
		}
	}
	else {
		this->moves[BOTTOM_LEFT].row = -1;
		this->moves[BOTTOM_LEFT].col = -1;
	}
	if (this->status == 'k') {
		for (int i = 4; i < 16; i++) {
			this->moves[i].row = -1;
			this->moves[i].col = -1;
		}
	}
	return howManyMoves(this->moves);
}

int Piece::isLegal(Pos move)
{
	for (int i = 0; i < 16; i++) {
		if (move.row == this->moves[i].row && move.col == this->moves[i].col) {
			return 1;
		}
	}
	return 0;
}

int Piece::checkIfKing()
{
	if (this->color == 'w') {
		if (this->status == 's') {
			if (this->pos.row == 7) {
				this->status = 'k';
				return 1;
			}
		}
	}
	else{
		if (this->status == 's') {
			if (this->pos.row == 0) {
				this->status = 'k';
				return 1;
			}
		}
	}

	return 0;
}
int sameLetter(char c1, char c2) {
	if (c1 == c2)
		return 1;
	if (c1 + 32 == c2)
		return 1;
	if (c1 == c2 + 32)
		return 1;
	return 0;

}

int checkTopRight(Pos pos, char board[][8]) {
	if (pos.row - 1 < 0 || pos.col + 1 > 7)
		return BLOCKED_MOVE;
	if (board[pos.row - 1][pos.col + 1] == '\0')
		return OPEN_MOVE;
	if (sameLetter(board[pos.row - 1][pos.col + 1], board[pos.row][pos.col])==1)
		return BLOCKED_MOVE;
	else
		return EATING_MOVE;
}
int checkTopLeft(Pos pos, char board[][8]) {
	if (pos.row - 1 < 0 || pos.col - 1 < 0)
		return BLOCKED_MOVE;
	if (board[pos.row - 1][pos.col - 1] == '\0')
		return OPEN_MOVE;
	if (sameLetter(board[pos.row - 1][pos.col - 1], board[pos.row][pos.col])==1)
		return BLOCKED_MOVE;
	else
		return EATING_MOVE;
}
int checkBottomRight(Pos pos, char board[][8]) {
	if (pos.row + 1 > 7 || pos.col + 1 > 7)
		return BLOCKED_MOVE;
	if (board[pos.row + 1][pos.col + 1] == '\0')
		return OPEN_MOVE;
	if (sameLetter(board[pos.row + 1][pos.col + 1], board[pos.row][pos.col])==1)
		return BLOCKED_MOVE;
	else
		return EATING_MOVE;
}
int checkBottomLeft(Pos pos, char board[][8]) {
	if (pos.row + 1 > 7 || pos.col - 1 < 0)
		return BLOCKED_MOVE;
	if (board[pos.row + 1][pos.col - 1] == '\0')
		return OPEN_MOVE;
	if (sameLetter(board[pos.row + 1][pos.col - 1], board[pos.row][pos.col])==1)
		return BLOCKED_MOVE;
	else
		return EATING_MOVE;
}
int findEatingMoves(Piece* piece, char board[][8]) {
	Pos enemy;
	int moves_coutner = 0;
	if (checkTopRight(piece->pos, board) == EATING_MOVE) {
		enemy.row = piece->pos.row - 1;
		enemy.col = piece->pos.col + 1;
		if (checkTopRight(enemy, board) == 1) {
			piece->moves[TOP_RIGHT].row = enemy.row - 1;
			piece->moves[TOP_RIGHT].col = enemy.col + 1;
			moves_coutner++;
		}
		else {
			piece->moves[TOP_RIGHT].row = -1;
			piece->moves[TOP_RIGHT].col = -1;
		}
	}
	else {
		piece->moves[TOP_RIGHT].row = -1;
		piece->moves[TOP_RIGHT].col = -1;
	}
	if (checkTopLeft(piece->pos, board) == EATING_MOVE) {
		enemy.row = piece->pos.row - 1;
		enemy.col = piece->pos.col - 1;
		if (checkTopLeft(enemy, board) == 1) {
			piece->moves[TOP_LEFT].row = enemy.row - 1;
			piece->moves[TOP_LEFT].col = enemy.col - 1;
			moves_coutner++;
		}
		else {
			piece->moves[TOP_LEFT].row = -1;
			piece->moves[TOP_LEFT].col = -1;
		}
	}
	else {
		piece->moves[TOP_LEFT].row = -1;
		piece->moves[TOP_LEFT].col = -1;
	}
	if (checkBottomRight(piece->pos, board) == EATING_MOVE)
	{
		enemy.row = piece->pos.row + 1;
		enemy.col = piece->pos.col + 1;
		if (checkBottomRight(enemy, board) == 1) {
			piece->moves[BOTTOM_RIGHT].row = enemy.row + 1;
			piece->moves[BOTTOM_RIGHT].col = enemy.col + 1;
			moves_coutner++;
		}
		else {
			piece->moves[BOTTOM_RIGHT].row = -1;
			piece->moves[BOTTOM_RIGHT].col = -1;
		}
	}
	else {
		piece->moves[BOTTOM_RIGHT].row = -1;
		piece->moves[BOTTOM_RIGHT].col = -1;
	}
	if (checkBottomLeft(piece->pos, board) == EATING_MOVE) {
		enemy.row = piece->pos.row + 1;
		enemy.col = piece->pos.col - 1;
		if (checkBottomLeft(enemy, board) == 1) {
			piece->moves[BOTTOM_LEFT].row = enemy.row + 1;
			piece->moves[BOTTOM_LEFT].col = enemy.col - 1;
			moves_coutner++;
		}
		else {
			piece->moves[BOTTOM_LEFT].row = -1;
			piece->moves[BOTTOM_LEFT].col = -1;
		}
	}
	else {
		piece->moves[BOTTOM_LEFT].row = -1;
		piece->moves[BOTTOM_LEFT].col = -1;
	}
	return moves_coutner;
}

void updateLegalMovesWhite(Piece* piece,char board[][8])
{
	if (findEatingMoves(piece, board) != 0)
		return;
	Pos enemy;
	switch (checkTopRight(piece->pos, board))
	{
	case BLOCKED_MOVE: {
		piece->moves[TOP_RIGHT].row = -1;
		piece->moves[TOP_RIGHT].col = -1;
	}
		break;
	case OPEN_MOVE: {
		piece->moves[TOP_RIGHT].row = -1;
		piece->moves[TOP_RIGHT].col = -1;
	}
		break;

	
	default:
		break;
	}


	switch (checkTopLeft(piece->pos, board))
	{
	case BLOCKED_MOVE: {
		piece->moves[TOP_LEFT].row = -1;
		piece->moves[TOP_LEFT].col = -1;
	}
		  break;
	case OPEN_MOVE: {
		piece->moves[TOP_LEFT].row = -1;
		piece->moves[TOP_LEFT].col = -1;
	}
		  break;
	default:
		break;
	}


	switch (checkBottomRight(piece->pos, board))
	{
	case BLOCKED_MOVE: {
		piece->moves[BOTTOM_RIGHT].row = -1;
		piece->moves[BOTTOM_RIGHT].col = -1;
	}
		  break;
	case OPEN_MOVE: {
		piece->moves[BOTTOM_RIGHT].row = piece->pos.row + 1;
		piece->moves[BOTTOM_RIGHT].col = piece->pos.col + 1;
	}
		  break;
	default:
		break;
	}


	switch (checkBottomLeft(piece->pos, board))
	{
	case BLOCKED_MOVE: {
		piece->moves[BOTTOM_LEFT].row = -1;
		piece->moves[BOTTOM_LEFT].col = -1;
	}
		  break;
	case OPEN_MOVE: {
		piece->moves[BOTTOM_LEFT].row = piece->pos.row + 1;
		piece->moves[BOTTOM_LEFT].col = piece->pos.col - 1;
	}
		  break;
	default:
		break;
	}
}


void updateLegalMovesBlack(Piece* piece, char board[][8])
{
	Pos enemy;
	if (findEatingMoves(piece, board) != 0)
		return;

	switch (checkTopRight(piece->pos, board))
	{
	case BLOCKED_MOVE: {
		piece->moves[TOP_RIGHT].row = -1;
		piece->moves[TOP_RIGHT].col = -1;
	}
		  break;
	case OPEN_MOVE: {
		piece->moves[TOP_RIGHT].row = piece->pos.row - 1;
		piece->moves[TOP_RIGHT].col = piece->pos.col + 1;
	}
		  break;

	default:
		break;
	}


	switch (checkTopLeft(piece->pos, board))
	{
	case BLOCKED_MOVE: {
		piece->moves[TOP_LEFT].row = -1;
		piece->moves[TOP_LEFT].col = -1;
	}
		  break;
	case OPEN_MOVE: {
		piece->moves[TOP_LEFT].row = piece->pos.row - 1;
		piece->moves[TOP_LEFT].col = piece->pos.col - 1;
	}
		  break;

	default:
		break;
	}
	


	switch (checkBottomRight(piece->pos, board))
	{
	case BLOCKED_MOVE: {
		piece->moves[BOTTOM_RIGHT].row = -1;
		piece->moves[BOTTOM_RIGHT].col = -1;
	}
		  break;
	case OPEN_MOVE: {
		piece->moves[BOTTOM_RIGHT].row = -1;
		piece->moves[BOTTOM_RIGHT].col = -1;
	}
		  break;
	
	default:
		break;
	}
	


	switch (checkBottomLeft(piece->pos, board))
	{
	case BLOCKED_MOVE: {
		piece->moves[BOTTOM_LEFT].row = -1;
		piece->moves[BOTTOM_LEFT].col = -1;
	}
		  break;
	case OPEN_MOVE: {
		piece->moves[BOTTOM_LEFT].row = -1;
		piece->moves[BOTTOM_LEFT].col = -1;
	}
		  break;
	default:
		break;
	}
	}



int howManyMoves(Pos* moves)
{
	int movescounter = 0;
	for (int i = 0; i < 16; i++) {
		if (moves[i].col != -1 && moves[i].row != -1) {
			movescounter++;
		}
	}
	return movescounter;
}
	
void updateLegalMovesKing(Piece* piece, char board[][8]) {
	int moves_index = 0;
	Pos pos;
	Pos enemy;
	pos = piece->pos;
	while (checkTopRight(pos, board) == OPEN_MOVE) {

		pos.col++;
		pos.row--;
		piece->moves[moves_index] = pos;
		moves_index++;
	}
	if (checkTopRight(pos, board) == EATING_MOVE) {
		enemy.row = pos.row - 1;
		enemy.col = pos.col + 1;
		if (checkTopRight(enemy, board) == 1) {
			piece->moves[moves_index].row = enemy.row - 1;
			piece->moves[moves_index].col = enemy.col + 1;
			moves_index++;
		}
		else {
			piece->moves[moves_index].row = -1;
			piece->moves[moves_index].col = -1;
		}
	}
	pos = piece->pos;

	while (checkTopLeft(pos, board) == OPEN_MOVE) {

		pos.col--;
		pos.row--;
		piece->moves[moves_index] = pos;
		moves_index++;
	}
	if (checkTopLeft(pos, board) == EATING_MOVE) {
		enemy.row = pos.row - 1;
		enemy.col = pos.col - 1;
		if (checkTopLeft(enemy, board) == 1) {
			piece->moves[moves_index].row = enemy.row - 1;
			piece->moves[moves_index].col = enemy.col - 1;
			moves_index++;
		}
		else {
			piece->moves[moves_index].row = -1;
			piece->moves[moves_index].col = -1;
		}
	}
	pos = piece->pos;

	while (checkBottomRight(pos, board) == OPEN_MOVE) {

		pos.col++;
		pos.row++;
		piece->moves[moves_index] = pos;
		moves_index++;
	}
	if (checkBottomRight(pos, board) == EATING_MOVE) {
		enemy.row = pos.row + 1;
		enemy.col = pos.col + 1;
		if (checkBottomRight(enemy, board) == 1) {
			piece->moves[moves_index].row = enemy.row + 1;
			piece->moves[moves_index].col = enemy.col + 1;
			moves_index++;
		}
		else {
			piece->moves[moves_index].row = -1;
			piece->moves[moves_index].col = -1;
		}
	}
	pos.row = piece->pos.row;
	pos.col = piece->pos.col;

	while (checkBottomLeft(pos, board) == OPEN_MOVE) {

		pos.col--;
		pos.row++;
		piece->moves[moves_index] = pos;
		moves_index++;
	}
	if (checkBottomLeft(pos, board) == EATING_MOVE) {
		enemy.row = pos.row + 1;
		enemy.col = pos.col - 1;
		if (checkBottomLeft(enemy, board) == 1) {
			piece->moves[moves_index].row = enemy.row + 1;
			piece->moves[moves_index].col = enemy.col - 1;
			moves_index++;
		}
		else {
			piece->moves[moves_index].row = -1;
			piece->moves[moves_index].col = -1;
		}
	}
	pos = piece->pos;
	while (moves_index < 16) {
		piece->moves[moves_index].row = -1;
		piece->moves[moves_index].col = -1;
		moves_index++;
	}
}