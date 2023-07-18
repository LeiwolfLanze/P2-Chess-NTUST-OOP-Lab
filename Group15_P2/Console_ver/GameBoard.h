/*********************************************************************
 * Filename: GameBoard.h
 * Author: 朱昱綸 (B11115022@mail.ntust.edu.tw)
 *         張庭嘉 (B11115027@mail.ntust.edu.tw)
 *         顏毓德 (B11115038@mail.ntust.edu.tw)
 *         黃雋祐 (B11115048@mail.ntust.edu.tw)
 * Cteate Date: May 5, 2023
 * Last Edit: May 12, 2023
 * Description: This program defines the class ChessLog.
 *********************************************************************/

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include<iostream>
#include<sstream>
#include<vector>
#include<map>
#include<string>
#include<string_view>
#include<memory>
#include<algorithm>
#include<functional>
#include<string_view>
#include"Piece.h"
#include"ChessLog.h"

using namespace std;

vector<string> splitSpacedString(string str);
int getSign(int val);

class GameBoard : ChessLog {
private:
	bool _isWhiteTurn = true;
	map<char, bool> _castlingAvailability = { {'K', false}, {'Q', false}, {'k', false}, {'q', false} };
	int _halfmove = 0, _fullmove = 1;
	bool _capitulationFlag = false;

	vector<vector<shared_ptr<Piece>>> _gameBoard;
	vector<shared_ptr<Piece>> _whitePieces, _blackPieces; // To record existing pieces on board
	shared_ptr<King> _whiteKing, _blackKing;

	string _FEN, _PossibleEnPassantOfFEN;
	constexpr static const char* _defaultFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	constexpr static const char* _defaultCastling = "KQkq";
	constexpr static const char* _defaultEnPassant = "-";

	// Use ANSI to render
	string whiteBG;
	string blackBG;
	string whitePiece_whiteBG;
	string whitePiece_blackBG;
	
	enum ANSI_Code {
		FG_BLACK = 30, BG_BLACK = 40,
		FG_RED = 31, BG_RED = 41,
		FG_GREEN = 32, BG_GREEN = 42,
		FG_BLUE = 34, BG_BLUE = 44,
		FG_MAGENTA = 35, BG_MAGENTA = 45,
		FG_CYAN = 36, BG_CYAN = 46,
		FG_GRAY = 90, BG_GRAY = 100,
		FG_YELLOW = 93, BG_YELLOW = 103,
		FG_WHITE = 97, BG_WHITE = 107,
	};

	static string ANSI(ANSI_Code fg, ANSI_Code bg, bool bold);
	static string ANSI_END();

	vector<string> analyzeFormat_FEN(string strFEN);
	vector<string> decodeToInit(string strPieceFEN);
	string generateFEN(); // Called after every move

public:
	void setFEN(string strFEN);
	string getFEN();
	string getDefaultFEN();

	void setBoard(vector<string> analyzedFEN);
	void resetBoard(string strFEN);
	bool undo();
	bool redo();
	void capitulate();

	GameBoard() : GameBoard(_defaultFEN) {};
	GameBoard(string strFEN) { resetBoard(strFEN); }
	bool isWhiteTurn();
	bool setTurn(char ch);

	shared_ptr<Piece> getPieceAt(const Position& pos) const;
	void setPiece(const Position& pos, const shared_ptr<Piece>& piece);
	vector<shared_ptr<Piece>> getPiecesList(bool isWhite);
	shared_ptr<King> getKingPtr(bool isWhite);

	string getRenderFormatAt(const Position& pos) const;

	void insertPiece(const shared_ptr<Piece>& piece);
	void removePiece(const shared_ptr<Piece>& piece);

	// This returns the hostile piece that made the king in check.
	shared_ptr<Piece> isKingInCheck(bool kingColor);

	void movePiece(const Move& mov);
	bool isValidMove(const Move& mov);
	int checkIntent(const Move& mov);

	bool isBlockable(const Move& moveToBlock, const shared_ptr<Piece>& blocker);
	int isGameOver();

	friend ostream& operator<<(ostream& strm, const GameBoard& gameboard);
};

#endif