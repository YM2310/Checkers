#include "Header.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
using namespace std;

void Board::initBoard(Player* white, Player* black) {

	for (int i = 0; i < 12; i++) {
		this->board[white->pieces[i]->pos.row][white->pieces[i]->pos.col] = white->pieces[i]->color;
		this->board[black->pieces[i]->pos.row][black->pieces[i]->pos.col] = black->pieces[i]->color;
	}
}	


void Board::printBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << '|' << this->board[i][j];
		}
		cout << '|' << '\n';

	}
}

int isIn(Pos pos, Pos* arr) {
	for (int i = 0; i < 12; i++) {
		if (pos.col == arr[i].col && pos.row == arr[i].row)
			return i;
	}
	return -1;
}

Pos Board::select(vector<Pos> options) {
	vector<Pos>::iterator i = options.begin();
	Pos curser = options[0];
	char input = 0;
	while (input != '\r'&&input!='e') {
		flash(curser);
		switch (input = _getch())
		{
		case KEY_LEFT: {
			if (i != options.begin()) {
				i--;
				curser=*i;
			}
			else {
				i = options.end()-1;
				curser = *i;
			}
		}
					 break;
		case KEY_RIGHT: {
			if (i != options.end()-1) {
				i++;
				curser = *i;
			}
			else {
				i = options.begin();
				curser = *i;
			}
		}
					  break;
		default:
			break;
		}

	}
	if (input == 'e') {
		curser.row = -2;
		return curser;
	}

	flash(curser);
	return curser;
}

void Board:: flash(Pos pos) {
	gotoxy(pos.col*2+1,pos.row);
}
void Board::showMoves(Pos* moves) {
	for (int i = 0; i < 16; i++) {
		if (moves[i].col != -1 && moves[i].row != -1) {
			flash(moves[i]);
			cout << "_";
		}
	}
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Board::updateBoard(Piece* piece, Pos move) {
	if (piece->color == 'd') {
		this->board[piece->pos.row][piece->pos.col] = '\0';
		piece->pos.row = -1;
		piece->pos.col = -1;
		return;
	}
	this->board[piece->pos.row][piece->pos.col] = '\0';
	if (piece->status == 'k') {
		this->board[move.row][move.col] = piece->color - 32;
	}
	else {
		this->board[move.row][move.col] = piece->color;
	}
	
	piece->pos.row = move.row;
	piece->pos.col = move.col;
}