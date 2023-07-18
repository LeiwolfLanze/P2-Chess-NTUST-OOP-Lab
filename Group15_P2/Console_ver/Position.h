/*********************************************************************
 * Filename: Position.h
 * Author: 朱昱綸 (B11115022@mail.ntust.edu.tw)
 *         張庭嘉 (B11115027@mail.ntust.edu.tw)
 *         顏毓德 (B11115038@mail.ntust.edu.tw)
 *         黃雋祐 (B11115048@mail.ntust.edu.tw)
 * Cteate Date: May 5, 2023
 * Last Edit: May 6, 2023
 * Description: This program defines the structure Position.
 *********************************************************************/

#ifndef POSITION_H
#define POSITION_H

#include<iostream>

using namespace std;

struct Position {
	int x, y;

	Position() : x(0), y(0) {};
	Position(int x, int y) : x(x), y(y) {};

	static bool outOfBounds(const Position& pos);
	static Position getPos(const string& strPos);
	Position abs();

	bool operator==(const Position& pos);
	Position operator+(const Position& pos);
	Position operator-(const Position& pos);
};

#endif