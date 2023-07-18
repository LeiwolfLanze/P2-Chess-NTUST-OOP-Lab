/*********************************************************************
 * Filename: Piece.h
 * Author: 朱昱綸 (B11115022@mail.ntust.edu.tw)
 *         張庭嘉 (B11115027@mail.ntust.edu.tw)
 *         顏毓德 (B11115038@mail.ntust.edu.tw)
 *         黃雋祐 (B11115048@mail.ntust.edu.tw)
 * Cteate Date: May 5, 2023
 * Last Edit: May 12, 2023
 * Description: This program defines the class Piece.
 *********************************************************************/

#ifndef PIECE_H
#define PIECE_H

#include<string>
#include"Move.h"

using namespace std;

class Piece {
protected:
	char _icon;
	bool _isWhite, _hasMoved = false;
	bool _2SquaresFlag = false; // A flag for just moving 2 squares at first
	Position _pos;

public:

	Piece(char icon, bool isWhite) : _icon(icon), _isWhite(isWhite) {};

	char getIcon();
	bool isWhite();
	Position getPos();
	void setPos(const Position& pos);

	bool hasMoved();
	bool get2SquaresFlag();
	void setHasMoved(bool mov);

	virtual bool isValidMove(const Move& move) = 0;
	virtual bool isPromotable() = 0;

};

class Pawn : public Piece {
public:
	Pawn(bool isWhite) : Piece(isWhite ? 'P' : 'p', isWhite) {};
	bool isValidMove(const Move& mov) override;
	bool isPromotable() override { return (_pos.x == 0 || _pos.x == 7); }
};

class Rook : public Piece {
public:
	Rook(bool isWhite) : Piece(isWhite ? 'R' : 'r', isWhite) {};
	bool isValidMove(const Move& mov) override;
	bool isPromotable() override { return false; }
};

class Knight : public Piece {
public:
	Knight(bool isWhite) : Piece(isWhite ? 'N' : 'n', isWhite) {};
	bool isValidMove(const Move& mov) override;
	bool isPromotable() override { return false; }
};

class Bishop : public Piece {
public:
	Bishop(bool isWhite) : Piece(isWhite ? 'B' : 'b', isWhite) {};
	bool isValidMove(const Move& mov) override;
	bool isPromotable() override { return false; }
};

class King : public Piece {
public:
	King(bool isWhite) : Piece(isWhite ? 'K' : 'k', isWhite) {};
	bool isValidMove(const Move& mov) override;
	bool isPromotable() override { return false; }
};

class Queen : public Piece {
public:
	Queen(bool isWhite) : Piece(isWhite ? 'Q' : 'q', isWhite) {};
	bool isValidMove(const Move& mov) override;
	bool isPromotable() override { return false; }
};

#endif