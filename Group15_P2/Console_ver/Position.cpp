/*********************************************************************
 * Filename: Position.cpp
 * Author: 朱昱綸 (B11115022@mail.ntust.edu.tw)
 *         張庭嘉 (B11115027@mail.ntust.edu.tw)
 *         顏毓德 (B11115038@mail.ntust.edu.tw)
 *         黃雋祐 (B11115048@mail.ntust.edu.tw)
 * Cteate Date: May 5, 2023
 * Last Edit: May 6, 2023
 * Description: This program implements the structure Position defined in "Position.h".
 *********************************************************************/

#include"Position.h"

// Intent: To check if the position is out of bounds
// Pre: The parameter pos must be given.
// Post: The function checks if the position is out of bounds.
bool Position::outOfBounds(const Position& pos) {
	return (pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7);
}

// Intent: To convert string to position
// Pre: The parameter strPos must be given.
// Post: The function converts the given string to position.
Position Position::getPos(const string& strPos) {
	return Position(strPos[1] - '1', tolower(strPos[0]) - 'a');
}

// Intent: To get the absolute-valued position
// Pre: None.
// Post: The function returns the absolute-valued position.
Position Position::abs() {
	return Position(x < 0 ? -x : x, y < 0 ? -y : y);
}

// Intent: To overload the operator==
// Pre: The parameter pos must be given.
// Post: The function overloads the operator==.
bool Position::operator==(const Position& pos) {
	return (x == pos.x) && (y == pos.y);
}

// Intent: To overload the operator+
// Pre: The parameter pos must be given.
// Post: The function overloads the operator+.
Position Position::operator+(const Position& pos) {
	return Position(x + pos.x, y + pos.y);
}

// Intent: To overload the operator-
// Pre: The parameter pos must be given.
// Post: The function overloads the operator-.
Position Position::operator-(const Position& pos) {
	return Position(x - pos.x, y - pos.y);
}
