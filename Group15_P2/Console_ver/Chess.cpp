/*********************************************************************
 * Filename: Chess.cpp
 * Author: 朱昱綸 (B11115022@mail.ntust.edu.tw)
 *         張庭嘉 (B11115027@mail.ntust.edu.tw)
 *         顏毓德 (B11115038@mail.ntust.edu.tw)
 *         黃雋祐 (B11115048@mail.ntust.edu.tw)
 * Cteate Date: May 5, 2023
 * Last Edit: May 12, 2023
 * Description: This program implements the game Chess in C++.
 *********************************************************************/

#include "GameBoard.h"

using namespace std;

// Intent: To print the start menu and take the inputs
// Pre: None.
// Post: The function prints the start menu and returns the input FEN code.
tuple<string, char> startMenu() {
	// Selection
	cout << "< Select a mode to start: (ng)New Game or (l)Load <FEN Code>\n> ";

	string mode, inputFEN = "";
	char side = '0';
	getline(cin, mode);

	// system("cls");
	if (!mode.compare(0, 2, "ng") || !mode.compare("New Game")) {
		cout << "< New a Game with Default GameBoard. Please select a color to go first.\n";
		cout << "< Type: (w)White or (b)Black\n> ";
		string color;
		getline(cin, color);
		if (tolower(color[0]) == 'w' || tolower(color[0]) == 'b') side = tolower(color[0]);
		else cout << "< [Error: Invalid Color] The default color (White) is set.\n";
	}
	else if (!mode.compare(0, 1, "l") || !mode.compare(0, 4, "Load")) {
		inputFEN = mode.substr(mode.find(' ') + 1);
		cout << "< Load from FEN: " << inputFEN << endl;
	}
	else cout << "< [Error: Invalid Mode] A default gameboard is set.\n";

	return { inputFEN , side };
}

int main() {

	bool exit = false;
	tuple<string, char> start = startMenu();
	string inputFEN = get<0>(start);
	char player = get<1>(start);

	// Execute until ESC
	while (!exit) {
		
		// Initialize the game
		GameBoard gameBoard(inputFEN);
		if (player != '0') gameBoard.setTurn(player);

		// Start the game
		int gameStatus;
		bool isMoveCommand = false;
		
		while ((gameStatus = gameBoard.isGameOver()) == 0) {

			cout << gameBoard << endl; // Print the gameboard
			Move move;
			do {
				isMoveCommand = false;

				// Take the execution and move command
				string command, firstCom, secondCom;
				cout << "< " << (gameBoard.isWhiteTurn() ? "White's" : "Black's") << " Turn. Type <src> <dest> to move\n> ";
				getline(cin, command);
				istringstream iss(command);

				iss >> firstCom;
				if (firstCom == "undo") {
					if (!gameBoard.undo()) cout << "< [Error: Empty Stack or Single Elemnent] Fail to undo." << endl;
				}
				else if (firstCom == "redo") {
					if (!gameBoard.redo()) cout << "< [Error: Empty Stack] Fail to redo." << endl;
				}
				else if (firstCom == "reset") {
					gameBoard.resetBoard(gameBoard.getDefaultFEN());
					cout << "< Game has been reset!" << endl;
				}
				else if (firstCom == "reload") {
					iss >> secondCom, gameBoard.resetBoard(secondCom);
					cout << "< Game has been reloaded!" << endl;
				}
				else if (firstCom == "getFEN") {
					cout << "< Current FEN Code: " << gameBoard.getFEN() << endl;
				}
				else if (firstCom == "capitulate") {
					gameBoard.capitulate();
				}
				else {
					isMoveCommand = true;
					iss >> secondCom;

					// Check move
					move = Move::getMove(firstCom, secondCom);
					if (Move::outOfBounds(move)) move.setIntent(15);
					else move.setIntent(gameBoard.checkIntent(move));
				}

			} while (!gameBoard.isValidMove(move) && isMoveCommand);

			// Move the piece
			if (isMoveCommand) gameBoard.movePiece(move);
		}

		// Display the result of the ended game
		cout << gameBoard << endl;
		switch (gameStatus) {
		case 1:
			cout << "< [Checkmate!] " << (!gameBoard.isWhiteTurn() ? "White" : "Black") << " won." << endl;
			break;
		case 2:
			cout << "< [Draw!] Stalemate for no moves left for " << (gameBoard.isWhiteTurn() ? "White" : "Black") << endl;
			break;
		case 3:
			cout << "< [Draw!] Stalemate for lack of material" << endl;
			break;
		case 4:
			cout << "< [Draw!] Threefold repetition reached" << endl;
			break;
		case 5:
			cout << "< [Draw!] Fifty-move rule" << endl;
			break;
		case 6:
			cout << "< [Captulation] " << (gameBoard.isWhiteTurn() ? "White" : "Black") << " captulated, so " 
				 << (!gameBoard.isWhiteTurn() ? "White" : "Black") << " won." << endl;
			break;
		default:
			cout << "< Game ended for unknown cause." << endl;
			break;
		}

		// Provide selections after a ended game
		cout << "< Wanna Play Again?" << endl;
		string decision;
		bool validDecision = false;
		do {
			cout << "< Type: (r)Restart, (b)Back to Menu or (e)Esc\n> ";
			getline(cin, decision);
			switch (tolower(decision[0])) {
			case 'r':
				inputFEN = "";
				validDecision = true;
				break;
			case 'b':
				start = startMenu();
				inputFEN = get<0>(start);
				player = get<1>(start);
				validDecision = true;
				break;
			case'e':
				exit = true;
				validDecision = true;
				break;
			default:
				cout << "< [Error: Invalid Decision] Re" << endl;
				break;
			}

		} while (!validDecision);
	}

	return 0;
}
