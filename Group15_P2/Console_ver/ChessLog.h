/*********************************************************************
 * Filename: GameBoard.h
 * Author: ���R�� (B11115022@mail.ntust.edu.tw)
 *         �i�x�� (B11115027@mail.ntust.edu.tw)
 *         �C���w (B11115038@mail.ntust.edu.tw)
 *         ���m�� (B11115048@mail.ntust.edu.tw)
 * Cteate Date: May 11, 2023
 * Last Edit: May 12, 2023
 * Description: This program defines the class GameBoard.
 *********************************************************************/

#ifndef CHESSLOG_H
#define CHESSLOG_H
#include<stack>
#include<string>
#include<iostream>

using namespace std;

class ChessLog {
protected:
	stack<string> boardHistory;
	stack<string> redoMoves;

public:
	void addLog(string strFEN);
	bool undoMove();
	bool redoMove();
};


#endif