project(P2-Chess-NTUST-OOP)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/exe)

set(SrcFile "Chess.cpp"
			"GameBoard.h" "GameBoard.cpp"
			"Piece.h" "Piece.cpp"
			"Position.h" "Position.cpp"
			"Move.h" "Move.cpp"
			"ChessLog.h" "ChessLog.cpp"
 )

add_executable(Console_ver ${SrcFile})
