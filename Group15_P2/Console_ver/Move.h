/*********************************************************************
 * Filename: Move.h
 * Author: 朱昱綸 (B11115022@mail.ntust.edu.tw)
 *         張庭嘉 (B11115027@mail.ntust.edu.tw)
 *         顏毓德 (B11115038@mail.ntust.edu.tw)
 *         黃雋祐 (B11115048@mail.ntust.edu.tw)
 * Cteate Date: May 5, 2023
 * Last Edit: May 6, 2023
 * Description: This program defines the class Move.
 *********************************************************************/

#ifndef MOVE_H
#define MOVE_H

#include<iostream>
#include"Position.h"

using namespace std;

class Move {
private:
	Position _src, _dest;
	int _intent = 15;

public:
	Move() {};
	Move(const Position& src, const Position& dest) : _src(src), _dest(dest) {};

	static bool outOfBounds(const Move& mov);
	static Move getMove(const string& strSrc, const string& strDest);

	Position getSrc() const;
	Position getDest() const;
	int getIntent() const;

	void setIntent(int intent);
};

#endif