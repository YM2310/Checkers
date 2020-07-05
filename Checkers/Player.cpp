#include "Header.h"



void Player::initPlayer() {
	if (this->color == 'w') {
		int white_index = 0;
		
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 8; j += 2) {
				if (i % 2 == 0 && j == 0)
					j++;

				this->pieces[white_index] = new Piece(i, j, 'w');
				white_index++;
			}
		}
		return;
	}
	int black_index = 0;
		for (int i = 5; i < 8; i++) {
			for (int j = 0; j < 8; j += 2) {
				if (i % 2 == 0 && j == 0)
					j++;
				this->pieces[black_index] = new Piece(i, j, 'b');
				black_index++;
			}
		}
}

Piece* Player::isPiece(Pos pos)
{
	for (int i = 0; i < 12; i++) {
		if (this->pieces[i]->pos.col== pos.col&& this->pieces[i]->pos.row == pos.row) {
			return this->pieces[i];
		}
	}
	return NULL;
}

