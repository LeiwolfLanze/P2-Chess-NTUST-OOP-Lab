/*********************************************************************
 * Filename: Piece.cpp
 * Author: 朱昱綸 (B11115022@mail.ntust.edu.tw)
 *         張庭嘉 (B11115027@mail.ntust.edu.tw)
 *         顏毓德 (B11115038@mail.ntust.edu.tw)
 *         黃雋祐 (B11115048@mail.ntust.edu.tw)
 * Cteate Date: May 5, 2023
 * Last Edit: May 12, 2023
 * Description: This program implements the class Piece defined in "Piece.h".
 *********************************************************************/

#include"Piece.h"

// Intent: To get the icon of the piece
// Pre: None.
// Post: The function returns the icon of the piece.
char Piece::getIcon() {
	return this->_icon;
}

// Intent: To check if the piece is white
// Pre: None.
// Post: The function returns true if the piece is white.
bool Piece::isWhite() {
	return this->_isWhite;
}

// Intent: To get the position of the piece
// Pre: None.
// Post: The function returns the position of the piece.
Position Piece::getPos() {
	return this->_pos;
}

// Intent: To set the position of the piece
// Pre: The parameter pos must be given.
// Post: The function sets the position of the piece.
void Piece::setPos(const Position& pos) {
	this->_pos = pos;
}

// Intent: To check if the piece has moved
// Pre: None.
// Post: The function returns true if the piece has moved.
bool Piece::hasMoved() {
	return this->_hasMoved;
}

// Intent: To get the value of _2SquaresFlag
// Pre: None.
// Post: The function returns the flag for having moved 2 squares.
bool Piece::get2SquaresFlag() {
	return this->_2SquaresFlag;
}

// Intent: To set the flag _hasMoved of the piece
// Pre: The parameter mov must be given.
// Post: The function sets the flag _hasMoved of the piece.
void Piece::setHasMoved(bool mov) {
	this->_hasMoved = mov;
}

// Intent: To check if the move of the pawn is valid
// Pre: The parameter mov must be given.
// Post: The function check if the move of the pawn is valid.
bool Pawn::isValidMove(const Move& mov) {

	Position deltaMove = mov.getDest() - mov.getSrc();
	bool isAtDefaultPos = mov.getSrc().x == 1 || mov.getSrc().x == 6;

	// Basic Move
	if (mov.getIntent() == 0) {

		// Move 1 block
		if (deltaMove == Position(_isWhite ? 1 : -1, 0)) return true;

		// Move 2 blocks when it hasn't moved
		if ((deltaMove == Position(_isWhite ? 2 : -2, 0)) && !_hasMoved && isAtDefaultPos) {
			this->_2SquaresFlag = true;
			return true;
		}
	}

	if (mov.getIntent() == 1 && (deltaMove.x == (_isWhite ? 1 : -1)) && abs(deltaMove.y) == 1) return true;

	if (mov.getIntent() == 4) return true;

	return false;
}

// Intent: To check if the move of the rook is valid
// Pre: The parameter mov must be given.
// Post: The function check if the move of the rook is valid.
bool Rook::isValidMove(const Move& mov) {

	// Try jumping over a piece
	if (mov.getIntent() == 11) return false;

	Position deltaMove = (mov.getDest() - mov.getSrc()).abs();
	return !(deltaMove.x * deltaMove.y);
}

// Intent: To check if the move of the knight is valid
// Pre: The parameter mov must be given.
// Post: The function check if the move of the knight is valid.
bool Knight::isValidMove(const Move& mov) {

	Position deltaMove = (mov.getDest() - mov.getSrc()).abs();
	return (deltaMove.x * deltaMove.y) == 2;
}

// Intent: To check if the move of the bishop is valid
// Pre: The parameter mov must be given.
// Post: The function check if the move of the bishop is valid.
bool Bishop::isValidMove(const Move& mov) {

	// Try jumping over a piece
	if (mov.getIntent() == 12) return false;

	Position deltaMove = (mov.getDest() - mov.getSrc()).abs();
	return deltaMove.x == deltaMove.y;
}

// Intent: To check if the move of the king is valid
// Pre: The parameter mov must be given.
// Post: The function check if the move of the king is valid.
bool King::isValidMove(const Move& mov) {

	// Castling
	if (mov.getIntent() == 2 || mov.getIntent() == 3) return true;

	Position deltaMove = (mov.getDest() - mov.getSrc()).abs();
	return deltaMove.x < 2 && deltaMove.y < 2;
}

// Intent: To check if the move of the queen is valid
// Pre: The parameter mov must be given.
// Post: The function check if the move of the queen is valid.
bool Queen::isValidMove(const Move& mov) {

	// Try jumping over a piece
	if (mov.getIntent() == 11 || mov.getIntent() == 12) return false;

	Position deltaMove = (mov.getDest() - mov.getSrc()).abs();
	return !(deltaMove.x * deltaMove.y) || (deltaMove.x == deltaMove.y);
}