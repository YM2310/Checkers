#pragma once
#include<stdio.h>
#include<iostream>
#include<conio.h>
#include <vector>
using namespace std;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
typedef struct position {
	int row;
	int col;
}Pos;
class Board;

class Piece {

public:
	Pos pos;
	char color;
	char status;
	Pos* moves = new Pos[16];
	Piece(int row, int col, char c) {
		pos.row = row;
		pos.col = col;
		color = c;
		status = 's';
		for (int i = 0; i < 16; i++)
		{
			moves[i].row = -1;
			moves[i].col = -1;

		}
	}
	int updateLegalMoves(char board[][8]);
	int updateLegalMovesInRow(char board[][8]);
	int isLegal(Pos move);
	int checkIfKing();
	//void move();

};

class Player {
public:
	char color;
	int score;

	Piece* pieces[12];
	Player() {

	}
	Player(char c) {
		color = c;
		score = 0;
		this->initPlayer();
	}

	void initPlayer();
	Piece* isPiece(Pos pos);
};

class Board {
public:
	char board[8][8]={""};
	Pos select(vector<Pos> options);
	void initBoard(Player* white, Player* black);
	void updateBoard(Piece* piece, Pos move);
	void printBoard();
	void flash(Pos pos);
	void showMoves(Pos* moves);
};



void gotoxy(int x, int y);