/*********************************************************************
 * Filename: GameBoard.cpp
 * Author: 朱昱綸 (B11115022@mail.ntust.edu.tw)
 *         張庭嘉 (B11115027@mail.ntust.edu.tw)
 *         顏毓德 (B11115038@mail.ntust.edu.tw)
 *         黃雋祐 (B11115048@mail.ntust.edu.tw)
 * Cteate Date: May 5, 2023
 * Last Edit: May 12, 2023
 * Description: This program implements the class GameBoard defined in "GameBoard.h".
 *********************************************************************/

#include "GameBoard.h"

// Intent: To get the ANSI structed string
// Pre: The parameter fg, bg and bold must be given.
// Post: The function returns the string with ANSI.
string GameBoard::ANSI(ANSI_Code fg, ANSI_Code bg, bool bold) {
	const char* formatAttribute = bold ? "2" : "0";
	char _ansiHeader[]{ 0x1B,'[','\0' };
	return string(_ansiHeader) + formatAttribute + ";" + to_string(fg) + ";" + to_string(bg) + "m";
}

// Intent: To get the end of ANSI structed string
// Pre: None.
// Post: The function returns the string with ended ANSI.
string GameBoard::ANSI_END() {
	char _ansiReset[]{ 0x1B,'[','0','m','\0' };
	return string(_ansiReset);
}

// Intent: To split string str at spaces
// Pre: The parameter str must be given.
// Post: The function returns the vector of each string.
vector<string> splitSpacedString(string str) {
	vector<string> vec;
	string token;
	istringstream inputStringStream(str);
	while (inputStringStream >> token) {
		vec.push_back(token);
	}
	return vec;
}

// Intent: To analyze FEN code and the validity
// Pre: The parameter strFEN must be given.
// Post: The function returns a vector of analyed FEN strings if the code is valid.
vector<string> GameBoard::analyzeFormat_FEN(string strFEN) {

	// Returns a vector with analyzed FEN strings, if the FEN code is valid
	// Returns an empty vector, if the FEN code is invalid

	if (strFEN.empty()) return vector<string>();

	// Split each parameter into vecFEN
	vector<string> vecFEN = splitSpacedString(strFEN);
	if(vecFEN.size() > 6) return vector<string>();
	if (vecFEN.size() < 6) vecFEN.resize(6, "-");

	string piece_FEN = vecFEN[0]; // Piece Placement
	string nowTurn_FEN = vecFEN[1]; // Whose turn to move
	string castling_FEN = vecFEN[2]; // Castling Availability
	string enPassant_FEN = vecFEN[3]; // En passant
	string halfmove_FEN = vecFEN[4]; // Halfmove clock
	string fullmove_FEN = vecFEN[5]; // The number of fullmove

	// Check the code validity of the piece placement
	if (!piece_FEN.compare("-")) {
		return vector<string>();
	}
	else {
		// Check symbolic validity and both parties possess only one king respectively
		string availableSymbols = "PpRrNnBbKkQq12345678/";
		int whiteKing = 0, blackKing = 0;
		if (count_if(piece_FEN.begin(), piece_FEN.end(), [](char ch) { return ch == '/'; }) != 7) return vector<string>();
		else {
			for (auto it = piece_FEN.begin(); it != piece_FEN.end(); ++it) {
				if (availableSymbols.find(string(1, *it)) == availableSymbols.npos) return vector<string>();
				whiteKing += ((*it == 'K') ? 1 : 0), blackKing += ((*it == 'k') ? 1 : 0);
			}
			if (whiteKing != 1 || blackKing != 1) return vector<string>();
		}

		// Check if number of squares in a row is matched with 8
		piece_FEN += '/';
		int squares = 0;
		for (auto it = piece_FEN.begin(); it != piece_FEN.end(); ++it) {
			if (*it != '/') squares += (isalpha(*it) ? 1 : stoi(string(1, *it)));
			else {
				if (squares != 8) return vector<string>();
				else squares = 0;
			}
		}
	}
	
	// Check the code validity of the color to move
	if (nowTurn_FEN.compare("-")) {
		if (nowTurn_FEN.compare("w") && nowTurn_FEN.compare("b")) return vector<string>();
	}

	// Check the code validity of castling
	if (castling_FEN.compare("-")) {
		
		// Check symbolic validity
		string availableSymbols = "KQkq";
		if(castling_FEN.length() > 4) return vector<string>();
		else {
			for (auto it = castling_FEN.begin(); it != castling_FEN.end(); ++it)
				if (availableSymbols.find(string(1, *it)) == availableSymbols.npos) return vector<string>();
		}
	}

	// Check the code validity of possible en passant
	if (enPassant_FEN.compare("-")) {
		
		// Check symbolic validity
		string availablePosX = "12345678", availablePosY = "AaBbCcDdEeFfGg";
		if (availablePosY.find(string(1, enPassant_FEN[0])) == availablePosY.npos) return vector<string>();
		if (availablePosX.find(string(1, enPassant_FEN[1])) == availablePosX.npos) return vector<string>();
	}

	// Check the code validity of halfmove clock
	if (halfmove_FEN.compare("-")) {
		for(char c: halfmove_FEN) if(!isdigit(c)) return vector<string>();
	}

	// Check the code validity of fullmove number
	if (fullmove_FEN.compare("-")) {
		for (char c : fullmove_FEN) if (!isdigit(c)) return vector<string>();
	}

	// Return the vector if no any syntax error within
	return vecFEN;
}

// Intent: To decode the piece-parted FEN code for initialization
// Pre: The parameter strPieceFEN must be given.
// Post: The function returns the decoded vector of strings.
vector<string> GameBoard::decodeToInit(string strPieceFEN) {

	// Create the decodedMap for setting pieces
	strPieceFEN += '/';
	vector<string> decodedMap;
	string rowElements = "";
	for (auto it = strPieceFEN.begin(); it != strPieceFEN.end(); ++it) {
		if (*it != '/') rowElements += (isalpha(*it) ? string(1, *it) : string(stoi(string(1, *it)), '0'));
		else {
			decodedMap.push_back(rowElements);
			rowElements = "";
		}
	}
	return decodedMap;
}

// Intent: To generate FEN code
// Pre: None.
// Post: The function returns generated FEN code.
string GameBoard::generateFEN() {

	string generatedFEN;

	for (int i = 7; i >=0; --i) {
		int nullCount = 0;
		for (int j = 0; j < 8; ++j) {
			if (_gameBoard[i][j] == nullptr) ++nullCount;
			else {
				if (nullCount > 0) generatedFEN += to_string(nullCount), nullCount = 0;
				generatedFEN += _gameBoard[i][j]->getIcon();
			}
		}
		if(nullCount > 0) generatedFEN += to_string(nullCount);
		if(i != 0) generatedFEN += '/';
	}

	generatedFEN += (_isWhiteTurn) ? " w " : " b ";
	
	string castling;
	for (const auto& [key, val] : _castlingAvailability) {
		if(val) castling += key;
	}
	if (castling.empty()) castling = "-";

	return generatedFEN += castling + " " + _PossibleEnPassantOfFEN + " " + to_string(_halfmove) + " " + to_string(_fullmove);
}

// Intent: To set the FEN code of this gameboard
// Pre: The parameter strFEN must be given.
// Post: The function sets the FEN code of this gameboard.
void GameBoard::setFEN(string strFEN) {
	this->_FEN = strFEN;
}

// Intent: To get the FEN code of this gameboard
// Pre: None.
// Post: The function returns the FEN code of this gameboard.
string GameBoard::getFEN() {
	return this->_FEN;
}

// Intent: To get the default FEN code
// Pre: None.
// Post: The function returns the default FEN code.
string GameBoard::getDefaultFEN() {
	return _defaultFEN;
}

// Intent: To set up the gameboard
// Pre: The parameter strFEN must be given.
// Post: The function sets up the gameboard.
void GameBoard::setBoard(vector<string> analyzedFEN) {
	
	string sPiece = analyzedFEN[0]; // Piece Placement
	string sTurn = analyzedFEN[1]; // Whose turn to move
	string sCastling = analyzedFEN[2]; // Castling Availability
	string sEnP = analyzedFEN[3]; // En passant
	string sHm = analyzedFEN[4]; // Halfmove clock
	string sFm = analyzedFEN[5]; // The number of fullmove

	// Initialize gameboard
	_gameBoard.resize(8);
	for (int i = 0; i < 8; ++i) _gameBoard[i].resize(8, nullptr);

	// Make shared pointers and map
	_whiteKing = make_shared<King>(true);
	_blackKing = make_shared<King>(false);
	map<char, function<shared_ptr<Piece>()>> availablePiece = { {'P', [&]() { return make_shared<Pawn>(true); } }, {'p', [&]() { return make_shared<Pawn>(false); } },
													{'R', [&]() { return make_shared<Rook>(true); } }, {'r', [&]() { return make_shared<Rook>(false); } },
													{'N', [&]() { return make_shared<Knight>(true); } }, {'n', [&]() { return make_shared<Knight>(false); } },
													{'B', [&]() { return make_shared<Bishop>(true); } }, {'b', [&]() { return make_shared<Bishop>(false); } },
													{'K', [&]() { return _whiteKing; } }, {'k', [&]() { return _blackKing; }},
													{'Q', [&]() { return make_shared<Queen>(true); } }, {'q', [&]() { return make_shared<Queen>(false); } } };

	// Decode FEN and set the pieces
	vector<string> decodedFEN_Map = decodeToInit(sPiece);
	
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			auto it = availablePiece.find(decodedFEN_Map[7 - i][j]);
			_gameBoard[i][j] = (it != availablePiece.end()) ? it->second() : nullptr;
		}
	}
	
	// Set the position of each piece and add to existing list
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (_gameBoard[i][j] != nullptr) {
				_gameBoard[i][j]->setPos({ i, j });
				insertPiece(_gameBoard[i][j]);
			}
		}
	}

	// Set the starter's turn if the FEN code provides
	this->_isWhiteTurn = (sTurn.compare("-")) ? (sTurn == "w") : 1;

	// Set the castling availability if the FEN code provides
	for_each(_castlingAvailability.begin(), _castlingAvailability.end(), [](auto& pair) { pair.second = false; });
	if (sCastling.compare("-")) for (auto c : sCastling) _castlingAvailability[c] = true;
	else for (auto c : string_view(_defaultCastling)) _castlingAvailability[c] = true;

	// Set the possible en passant to _PossibleEnPassantOfFEN
	this->_PossibleEnPassantOfFEN = sEnP;

	// Set the halfmove clock
	this->_halfmove = (sHm.compare("-")) ? stoi(sHm) : 0;

	// Set the number of fullmoves
	this->_fullmove = (sFm.compare("-")) ? stoi(sFm) : 1;
}

// Intent: To reset the gameboard
// Pre: The parameter strFEN must be given.
// Post: The function resets the gameboard.
void GameBoard::resetBoard(string strFEN) {

	// Analyze the FEN code and its validity
	vector<string> analyzedFEN = analyzeFormat_FEN(strFEN);
	if (analyzedFEN.empty()) {
		if (!strFEN.empty()) cout << "< [Error: Invalid FEN Format] Gameboard has been set to default." << endl;
		strFEN = this->_defaultFEN;
		analyzedFEN = analyzeFormat_FEN(strFEN);
	}

	// Set the FEN code of this gameboard
	this->_FEN = strFEN;

	// set gameboard
	setBoard(analyzedFEN);

	// Clear history
	while (!boardHistory.empty()) boardHistory.pop();
	while (!redoMoves.empty()) redoMoves.pop();

	// Push _FEN into boardHistory
	addLog(this->_FEN);

	// Set the board-rendered strings
	this->whiteBG = ANSI(FG_BLACK, BG_WHITE, false);
	this->blackBG = ANSI(FG_BLACK, BG_GRAY, false);
	this->whitePiece_whiteBG = ANSI(FG_GRAY, BG_WHITE, false);
	this->whitePiece_blackBG = ANSI(FG_WHITE, BG_GRAY, false);

	// Set _capitulationFlag
	this->_capitulationFlag = false;
}

// Intent: To undo
// Pre: None.
// Post: The function undoes.
bool GameBoard::undo() {
	if (!undoMove()) return false;
	setBoard(analyzeFormat_FEN(boardHistory.top()));
	return true;
}

// Intent: To redo
// Pre: None.
// Post: The function redoes.
bool GameBoard::redo() {
	if (!redoMove()) return false;
	setBoard(analyzeFormat_FEN(boardHistory.top()));
	return true;
}

// Intent: To capitulate
// Pre: None.
// Post: The function sets the capitulation flag to true.
void GameBoard::capitulate() {
	this->_capitulationFlag = true;
}

// Intent: To check if it's white's turn
// Pre: None.
// Post: The function returns true if it's white's turn.
bool GameBoard::isWhiteTurn() {
	return this->_isWhiteTurn;
}

// Intent: To set the turn of a color
// Pre: The parameter ch must be given.
// Post: The function sets the player's turn of given color.
bool GameBoard::setTurn(char ch) {
	if (ch != 'w' && ch != 'b') return false;
	this->_isWhiteTurn = (ch == 'w') ? 1 : 0;
	return true;
}

// Intent: To get the pointer of the peice at a given position
// Pre: The parameter pos must be given.
// Post: The function returns the pointer of the peice.
shared_ptr<Piece> GameBoard::getPieceAt(const Position& pos) const {
	return _gameBoard[pos.x][pos.y];
}

// Intent: To set the peice on gameboard
// Pre: The parameter pos and piece must be given.
// Post: The function sets the peice on gameboard.
void GameBoard::setPiece(const Position& pos, const shared_ptr<Piece>& piece) {
	
	_gameBoard[pos.x][pos.y] = piece;

	if (piece != nullptr) {
		piece->setPos(pos);
		piece->setHasMoved(true);
	}
}

// Intent: To get the pointer list of given-colored pieces that currently exist
// Pre: The parameter isWhite must be given.
// Post: The function returns the specific list of pieces.
vector<shared_ptr<Piece>> GameBoard::getPiecesList(bool isWhite) {
	return isWhite ? _whitePieces : _blackPieces;
}

// Intent: To get the pointer of given-colored King
// Pre: The parameter isWhite must be given.
// Post: The function returns the pointer of the specific King.
shared_ptr<King> GameBoard::getKingPtr(bool isWhite) {
	return isWhite ? _whiteKing : _blackKing;
}

// Intent: To get the render-formatted string at a position
// Pre: The parameter pos must be given.
// Post: The function returns the formatted string.
string GameBoard::getRenderFormatAt(const Position& pos) const {
	shared_ptr<Piece> piece = this->getPieceAt(pos);

	// Set plain(unshaded) squares when i + j is odd
	bool isPlainSquare = (pos.x + pos.y) % 2;
	string ch = isPlainSquare ? whiteBG : blackBG;

	if (piece == nullptr) return ch += "   " + ANSI_END();

	if (piece->isWhite() && isPlainSquare) ch += whitePiece_whiteBG;
	else if (piece->isWhite()) ch += whitePiece_blackBG;

	return ch += " " + string(1, piece->getIcon()) + " " + ANSI_END();
}

// Intent: To insert a piece into the list of existing pieces
// Pre: The parameter piece must be given.
// Post: The function inserts a piece into the list of existing pieces.
void GameBoard::insertPiece(const shared_ptr<Piece>& piece) {
	if (piece == nullptr) return;

	if (piece->isWhite()) _whitePieces.push_back(piece);
	else _blackPieces.push_back(piece);
}

// Intent: To remove a piece from the list of existing pieces
// Pre: The parameter piece must be given.
// Post: The function removes a piece from the list of existing pieces.
void GameBoard::removePiece(const shared_ptr<Piece>& piece) {
	if (piece == nullptr) return;

	if (piece->isWhite()) {
		auto it = find(_whitePieces.begin(), _whitePieces.end(), piece);
		_whitePieces.erase(it);
	}
	else {
		auto it = find(_blackPieces.begin(), _blackPieces.end(), piece);
		_blackPieces.erase(it);
	}
}

// Intent: To check if the king is in check
// Pre: The parameter kingColor must be given.
// Post: The function checks if the king is in check.
shared_ptr<Piece> GameBoard::isKingInCheck(bool kingColor) {

	// Check if any hostile piece can capture the king
	_isWhiteTurn = !_isWhiteTurn;

	for (shared_ptr<Piece> piece : getPiecesList(!kingColor)) {
		
		Move checkMove(piece->getPos(), getKingPtr(kingColor)->getPos());
		checkMove.setIntent(checkIntent(checkMove));
		if (isValidMove(checkMove)) {
			_isWhiteTurn = !_isWhiteTurn;
			return piece;
		}
	}
	
	_isWhiteTurn = !_isWhiteTurn;
	return nullptr;
}

// Intent: To move a piece
// Pre: The parameter mov must be given.
// Post: The function moves a piece.
void GameBoard::movePiece(const Move& mov) {

	shared_ptr<Piece> srcPiece = getPieceAt(mov.getSrc());
	shared_ptr<Piece> destPiece = getPieceAt(mov.getDest());

	// Move the piece to new position
	setPiece(mov.getDest(), srcPiece);
	setPiece(mov.getSrc(), nullptr);

	// Remove the original piece at destinated position from the pieces list if captured
	removePiece(destPiece);

	// Handle pawn promotion
	if (srcPiece->isPromotable()) {

		shared_ptr<Piece> promotedPiece;

		cout << "< Select a kind of piece to promote: (r)Rook, (k)Knight, (b)Bishop or (q)Queen\n> ";
		string strPromotion;
		cin >> strPromotion;

		map<char, function<shared_ptr<Piece>()>> availablePromotion = { {'r', [&]() { return make_shared<Rook>(srcPiece->isWhite()); } },
															{'k', [&]() { return make_shared<Knight>(srcPiece->isWhite()); } },
															{'b', [&]() { return make_shared<Bishop>(srcPiece->isWhite()); } },
															{'q', [&]() { return make_shared<Queen>(srcPiece->isWhite()); } } };
		auto it = availablePromotion.find(tolower(strPromotion[0]));
		if (it == availablePromotion.end()) cout << "< [Error: Invalid Input] Lose the chance to promote." << endl;
		else {
			promotedPiece = it->second();
			setPiece(mov.getDest(), promotedPiece);
			removePiece(srcPiece);
			insertPiece(promotedPiece);
		}
	}

	// Handle castling cases
	if (mov.getIntent() == 2 || mov.getIntent() == 3) {
		shared_ptr<Piece> targetRook = _gameBoard[srcPiece->isWhite() ? 0 : 7][mov.getIntent() == 3 ? 0 : 7];
		setPiece(targetRook->getPos(), nullptr);
		setPiece(mov.getDest() + Position(0, mov.getIntent() == 3 ? 1 : -1), targetRook);
	}

	// Handle en passant cases
	if (mov.getIntent() == 4) setPiece(Position(mov.getSrc().x, mov.getDest().y), nullptr);

	// Set the possible en passent of FEN
	Position deltaMove = mov.getDest() - mov.getSrc();
	if ((tolower(srcPiece->getIcon()) == 'p') && (deltaMove.abs() == Position(2, 0))) {
		this->_PossibleEnPassantOfFEN = string(1, 'a' + mov.getSrc().y) + string(1, '1' + mov.getDest().x + (srcPiece->isWhite() ? -1 : 1));
	}
	else this->_PossibleEnPassantOfFEN = _defaultEnPassant;
	

	// Set the halfmove clock
	if ((tolower(srcPiece->getIcon()) == 'p') || mov.getIntent() == 1) this->_halfmove = 0;
	else this->_halfmove++;

	// Set the the number of fullmove
	if (!_isWhiteTurn) this->_fullmove++;

	// Next turn
	_isWhiteTurn = !_isWhiteTurn;

	// Generate this FEN code and pushback into boardHistory
	this->_FEN = generateFEN();
	addLog(this->_FEN);
}

// Intent: To check if the move is valid
// Pre: The parameter mov must be given.
// Post: The function checks if the move is valid.
bool GameBoard::isValidMove(const Move& mov) {
	
	if (mov.getIntent() == 15) return false;

	shared_ptr<Piece> srcPiece = getPieceAt(mov.getSrc());
	shared_ptr<Piece> destPiece = getPieceAt(mov.getDest());

	bool pieceColor = srcPiece->isWhite();

	// Try to move a hostile piece at self-round
	if (pieceColor != _isWhiteTurn) return false;

	// Check the move's validity based on piece's type
	if (!getPieceAt(mov.getSrc())->isValidMove(mov)) return false;

	// Ensure a king cannot tries to commit a suicide
	setPiece(mov.getDest(), srcPiece), setPiece(mov.getSrc(), nullptr);
	if (isKingInCheck(pieceColor) != nullptr) {
		setPiece(mov.getSrc(), srcPiece), setPiece(mov.getDest(), destPiece);
		return false;
	}
	setPiece(mov.getSrc(), srcPiece), setPiece(mov.getDest(), destPiece);

	// Check whether next move can save the king if currently left in check
	if (isKingInCheck(pieceColor) != nullptr) {

		// Try moving and see if still left in check
		setPiece(mov.getDest(), srcPiece), setPiece(mov.getSrc(), nullptr);

		bool stillInCheck = (isKingInCheck(pieceColor) != nullptr);
		setPiece(mov.getSrc(), srcPiece), setPiece(mov.getDest(), destPiece);

		// It's disallowed when a king tries to commit a suicide
		if (stillInCheck) return false; 
	}

	return true;
}

// Intent: To check the sign of a value
// Pre: The parameter val must be given.
// Post: The function returns -1 for negativity, 1 for positivity, and 0 for none.
int getSign(int val) {
	return (val > 0) - (val < 0);
}

// Intent: To check the intent of a move
// Pre: The parameter mov must be given.
// Post: The function checks and determines the intent of the move listed below.
int GameBoard::checkIntent(const Move& mov) {

	Position deltaMove = mov.getDest() - mov.getSrc();
	shared_ptr<Piece> srcPiece = getPieceAt(mov.getSrc());

	// Fail to move for moving an empty block
	if (srcPiece == nullptr) return 15;

	// Handle castling
	if ((srcPiece == _whiteKing || srcPiece == _blackKing) && (deltaMove.abs() == Position(0, 2)) && (!srcPiece->hasMoved())) {

		bool validCastling = true;
		shared_ptr<Piece> targetRook = _gameBoard[srcPiece->isWhite() ? 0 : 7][deltaMove.y < 0 ? 0 : 7];

		if (targetRook == nullptr) return 15; // Fail to find the targetRook

		if (targetRook->hasMoved()) validCastling = false;

		// Check there's no any piece between the king and the rook
		Position distance = targetRook->getPos() - srcPiece->getPos();
		int dir = getSign(distance.y); // Set a moving derection

		for (int i = dir; abs(i) < abs(distance.y); i += dir) {
			if (_gameBoard[mov.getSrc().x][mov.getSrc().y + i] != nullptr) validCastling = false;
		}

		// Check no any hostile piece is observing btw/at the king and the rook
		for (int i = 0; abs(i) < (abs(distance.y) + 1); i += dir) {
			Position currentPos = Position(mov.getSrc().x, mov.getSrc().y + i);
			for (shared_ptr<Piece> piece : getPiecesList(!srcPiece->isWhite())) {
				if (isValidMove(Move(piece->getPos(), currentPos))) validCastling = false;
			}
		}

		// Check the castling availability preset by FEN
		if(validCastling) {
			if (srcPiece == _whiteKing) validCastling = _castlingAvailability[(distance.y == 3) ? 'K' : 'Q'];
			else validCastling = _castlingAvailability[(distance.y == 3) ? 'k' : 'q'];
		}

		if (validCastling) return (distance.y == 3) ? 2 : 3;
	}

	// Handle any piece jumping over a hostile piece diagonally
	if (abs(deltaMove.x) == abs(deltaMove.y)) {
		int dirV = getSign(deltaMove.x), dirH = getSign(deltaMove.y);
		for (int i = dirV, j = dirH; abs(i) < abs(deltaMove.x); i += dirV, j += dirH) {
			if (_gameBoard[mov.getSrc().x + i][mov.getSrc().y + j] != nullptr) return 12;
		}
	}

	// Handle any piece jumping over a hostile piece vertically/horizontally
	if (!(deltaMove.x) || !(deltaMove.y)) {
		int dirV = getSign(deltaMove.x), dirH = getSign(deltaMove.y);
		for (int i = dirV, j = dirH; abs(i+j) < abs(deltaMove.x + deltaMove.y); i += dirV, j += dirH) {
			if (_gameBoard[mov.getSrc().x + i][mov.getSrc().y + j] != nullptr) return 11;
		}
	}

	// Handle en-passant capture move
	if ((tolower(srcPiece->getIcon()) == 'p') && deltaMove.abs() == Position(1, 1)) {
		shared_ptr<Piece> sidePiece = _gameBoard[mov.getSrc().x][mov.getDest().y];
		if(sidePiece != nullptr)
			if (tolower(sidePiece->getIcon()) == 'p' && sidePiece->get2SquaresFlag()) return 4;
	}

	// Handle simple moves
	if (getPieceAt(mov.getDest()) == nullptr) return 0; // Standard move

	if (srcPiece->isWhite() != getPieceAt(mov.getDest())->isWhite()) return 1; // Capture move

	return 15; // Invalid move

}

// Intent: To check if the the way of regicide is blockable
// Pre: The parameter regWay and blocker must be given.
// Post: The function checks if the the way of regicide is blockable.
bool GameBoard::isBlockable(const Move& regWay, const shared_ptr<Piece>& blocker) {

	// Check if the blocker can directly capture the regicide
	Move capMove = Move(blocker->getPos(), regWay.getSrc());
	capMove.setIntent(checkIntent(capMove));
	if (isValidMove(capMove)) return true;

	Position deltaRegWay = regWay.getDest() - regWay.getSrc();

	// Try to block when confronted with a regicide that moves diagonally
	if (abs(deltaRegWay.x) == abs(deltaRegWay.y)) {
		int dirV = getSign(deltaRegWay.x), dirH = getSign(deltaRegWay.y);
		for (int i = dirV, j = dirH; abs(i) < abs(deltaRegWay.x); i += dirV, j += dirH) {
			Position posToBlock(regWay.getSrc().x + i, regWay.getSrc().y + j);
			Move blockingMove = Move(blocker->getPos(), posToBlock);
			blockingMove.setIntent(checkIntent(blockingMove));
			if (isValidMove(blockingMove)) return true;
		}
	}
	
	// Try to block when confronted with a regicide that moves vertically/horizontally
	if (!(deltaRegWay.x) || !(deltaRegWay.y)) {
		int dirV = getSign(deltaRegWay.x), dirH = getSign(deltaRegWay.y);
		for (int i = dirV, j = dirH; abs(i+j) < abs(deltaRegWay.x + deltaRegWay.y); i += dirV, j += dirH) {
			Position posToBlock(regWay.getSrc().x + i, regWay.getSrc().y + j);
			Move blockingMove = Move(blocker->getPos(), posToBlock);
			blockingMove.setIntent(checkIntent(blockingMove));
			if (isValidMove(blockingMove)) return true;
		}
	}

	return false;
}

// Intent: To check if the game is over
// Pre: None.
// Post: The function checks if the game is over and returns the end code listed below.
int GameBoard::isGameOver() {

	if (this->_capitulationFlag) return 6;

	if (find(_whitePieces.begin(), _whitePieces.end(), _whiteKing) == _whitePieces.end() || find(_blackPieces.begin(), _blackPieces.end(), _blackKing) == _blackPieces.end()) return 1;

	shared_ptr<Piece> regicide = isKingInCheck(_isWhiteTurn);
	
	if (regicide != nullptr) {
		bool checkmate = true;
		
		// Check if the king could run away
		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				Position kingPos = getKingPtr(_isWhiteTurn)->getPos();
				Position runPos = Position(dx, dy) + kingPos;

				if (Position::outOfBounds(runPos)) continue;

				Move runMove = Move(kingPos, runPos);
				runMove.setIntent(checkIntent(runMove));
				if (isValidMove(runMove)) {
					checkmate = false;
					break;
				}
			}
		}
		
		// If the king cannot run away
		if (checkmate) {

			// Check if any friendly piece is able to block the way btw the king and the regicide
			for (shared_ptr<Piece> piece : getPiecesList(_isWhiteTurn)) {
				
				// Declare regWay as the way btw the king and the regicide
				Move regWay(regicide->getPos(), getKingPtr(_isWhiteTurn)->getPos());
				if (isBlockable(regWay, piece)) {
					checkmate = false;
					break;
				}
			}
		}
		if(checkmate) return 1;
	}
	
	// Check if stalemate due to no moves left
	bool hasValidMove = false;
	for (shared_ptr<Piece> piece : getPiecesList(_isWhiteTurn)) {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				Move move = Move(piece->getPos(), Position(i, j));
				move.setIntent(checkIntent(move));
				if (isValidMove(move)) {
					hasValidMove = true;
					break;
				}
			}
			if (hasValidMove) break;
		}
		if (hasValidMove) break;
	}
	if (!hasValidMove && regicide == nullptr) return 2;
	
	// Check if stalemate due to lack of material
	if (getPiecesList(_isWhiteTurn).size() == 1 && getPiecesList(!_isWhiteTurn).size() == 1) return 3;

	// Check for threefold repetition
	auto it_begin = begin(boardHistory._Get_container());
	auto it_end = end(boardHistory._Get_container());

	if (distance(it_begin, it_end) > 2) {
		if (count_if(it_begin, prev(it_end, 2), [&](const string& str) { return str == boardHistory.top(); }) >= 3)
			return 4;
	}
	
	// Check for fifty-move rule
	if (_halfmove >= 100) return 5;

	return 0;
}

// Intent: To overload the operator<<
// Pre: The parameter strm and gameboard must be given.
// Post: The function overloads the operator<<.
ostream& operator<<(ostream & strm, const GameBoard & gameboard) {
	strm << endl;
	for (int i = 0; i < 8; ++i) {
		int index = 8 - i;
		strm << "[" << index << "]";

		for (int j = 0; j < 8; ++j) {
			strm << gameboard.getRenderFormatAt(Position(7 - i, j));
		}
		strm << endl;
	}

	return strm << "   [A][B][C][D][E][F][G][H]\n";
}