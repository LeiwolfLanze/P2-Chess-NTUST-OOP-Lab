/*********************************************************************
 * Filename: Move.cpp
 * Author: 朱昱綸 (B11115022@mail.ntust.edu.tw)
 *         張庭嘉 (B11115027@mail.ntust.edu.tw)
 *         顏毓德 (B11115038@mail.ntust.edu.tw)
 *         黃雋祐 (B11115048@mail.ntust.edu.tw)
 * Cteate Date: May 5, 2023
 * Last Edit: May 6, 2023
 * Description: This program implements the class Move defined in "Move.h".
 *********************************************************************/

#include"Move.h"

// Intent: To check if the move is out of bounds
// Pre: The parameter mov must be given.
// Post: The function checks if the move is out of bounds.
bool Move::outOfBounds(const Move& mov) {
	return Position::outOfBounds(mov._src) || Position::outOfBounds(mov._dest);
}

// Intent: To convert strings to move
// Pre: The parameter strSrc and strDest must be given.
// Post: The function converts the given strings to move.
Move Move::getMove(const string& strSrc, const string& strDest) {
	return Move(Position::getPos(strSrc), Position::getPos(strDest));
}

// Intent: To get the _src position
// Pre: None.
// Post: The function returns the _src position.
Position Move::getSrc() const {
	return this->_src;
}

// Intent: To get the _dest position
// Pre: None.
// Post: The function returns the _dest position.
Position Move::getDest() const {
	return this->_dest;
}

// Intent: To get the intention
// Pre: None.
// Post: The function returns the intention.
int Move::getIntent() const {
	return this->_intent;
}

// Intent: To set the intention
// Pre: The parameter intent must be given.
// Post: The function sets the intention.
void Move::setIntent(int intent) {
	this->_intent = intent;
}