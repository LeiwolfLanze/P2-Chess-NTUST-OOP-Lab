/*********************************************************************
 * Filename: Move.cpp
 * Author: ¦¶¬Rºú (B11115022@mail.ntust.edu.tw)
 *         ±i®x¹Å (B11115027@mail.ntust.edu.tw)
 *         ÃC·¶¼w (B11115038@mail.ntust.edu.tw)
 *         ¶À¹m¯§ (B11115048@mail.ntust.edu.tw)
 * Cteate Date: May 11, 2023
 * Last Edit: May 12, 2023
 * Description: This program implements the class ChessLog defined in "ChessLog.h".
 *********************************************************************/

#include"ChessLog.h"

// Intent: To add the FEN code to the log
// Pre: The parameter strFEN must be given.
// Post: The function adds the FEN to the history of the board.
void ChessLog::addLog(string strFEN) {
	boardHistory.push(strFEN);
	while (!redoMoves.empty()) redoMoves.pop();
}

// Intent: To undo the move
// Pre: None.
// Post: The function undoes the move.
bool ChessLog::undoMove() {
	if (!boardHistory.empty() && boardHistory.size() > 1) {
		string strFEN = boardHistory.top();
		boardHistory.pop();
		redoMoves.push(strFEN);
		return true;
	}
	return false;
}

// Intent: To redo the move
// Pre: None.
// Post: The function redoes the move.
bool ChessLog::redoMove() {
	if (!redoMoves.empty()) {
		string strFEN = redoMoves.top();
		redoMoves.pop();
		boardHistory.push(strFEN);
		return true;
	}
	return false;
}