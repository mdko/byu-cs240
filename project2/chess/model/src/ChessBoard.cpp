//ChessBoard.cpp

#include "ChessBoard.h"
#include "IChessPiece.h"	//Board.h has forward declaration of class to prevent circ. dep.
#include "UnitTest.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

ChessBoard::ChessBoard() {
	return;
}

ChessBoard::~ChessBoard() {
	clear();
}

void ChessBoard::clear() {
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			if (board[i][j] != NULL) {
				delete board[i][j];
				board[i][j] = NULL;
			}
		}
	}
	/*delete wKing;	wKing = NULL;
	delete wQueen; 	wQueen = NULL;
	delete wRook1;	wRook1 = NULL;
	delete wRook2;	wRook2 = NULL;
	delete wBishop1;	wBishop1 = NULL;
	delete wBishop2;	wBishop2 = NULL;
	delete wKnight1;	wKnight1 = NULL;
	delete wKnight2;	wKnight2 = NULL;
	delete wPawn1;	wPawn1 = NULL;
	delete wPawn2;	wPawn2 = NULL;
	delete wPawn3;	wPawn3 = NULL;
	delete wPawn4;	wPawn4 = NULL;
	delete wPawn5;	wPawn5 = NULL;
	delete wPawn6;	wPawn6 = NULL;
	delete wPawn7;	wPawn7 = NULL;
	delete wPawn8;	wPawn8 = NULL;
	
	delete bKing;	bKing = NULL;
	delete bQueen; 	bQueen = NULL;
	delete bRook1;	bRook1 = NULL;
	delete bRook2;	bRook2 = NULL;
	delete bBishop1;	bBishop1 = NULL;
	delete bBishop2;	bBishop2 = NULL;
	delete bKnight1;	bKnight1 = NULL;
	delete bKnight2;	bKnight2 = NULL;
	delete bPawn1;	bPawn1 = NULL;
	delete bPawn2;	bPawn2 = NULL;
	delete bPawn3;	bPawn3 = NULL;
	delete bPawn4;	bPawn4 = NULL;
	delete bPawn5;	bPawn5 = NULL;
	delete bPawn6;	bPawn6 = NULL;
	delete bPawn7;	bPawn7 = NULL;
	delete bPawn8;	bPawn8 = NULL;*/
}

void ChessBoard::initializeBoard() {
	//initialize elements in array to NULL
	//TODO a way to do this via incrementing a point to first element?
	for (int i=0; i<8; ++i)
		for (int j=0; j<8; ++j)
			board[i][j] = NULL;
	
	wKing = new King(WHITE, NA);
	wQueen = new Queen(WHITE, NA);
	wRook1 = new Rook(WHITE, NA);
	wRook2 = new Rook(WHITE, NA);
	wBishop1 = new Bishop(WHITE, NA);
	wBishop2 = new Bishop(WHITE, NA);
	wKnight1 = new Knight(WHITE, NA);
	wKnight2 = new Knight(WHITE, NA);
	wPawn1 = new Pawn(WHITE, UP);
	wPawn2 = new Pawn(WHITE, UP);
	wPawn3 = new Pawn(WHITE, UP);
	wPawn4 = new Pawn(WHITE, UP);
	wPawn5 = new Pawn(WHITE, UP);
	wPawn6 = new Pawn(WHITE, UP);
	wPawn7 = new Pawn(WHITE, UP);
	wPawn8 = new Pawn(WHITE, UP);

	bKing = new King(BLACK, NA);
	bQueen = new Queen(BLACK, NA);
	bRook1 = new Rook(BLACK, NA);
	bRook2 = new Rook(BLACK, NA);
	bBishop1 = new Bishop(BLACK, NA);
	bBishop2 = new Bishop(BLACK, NA);
	bKnight1 = new Knight(BLACK, NA);
	bKnight2 = new Knight(BLACK, NA);
	bPawn1 = new Pawn(BLACK, DOWN);
	bPawn2 = new Pawn(BLACK, DOWN);
	bPawn3 = new Pawn(BLACK, DOWN);
	bPawn4 = new Pawn(BLACK, DOWN);
	bPawn5 = new Pawn(BLACK, DOWN);
	bPawn6 = new Pawn(BLACK, DOWN);
	bPawn7 = new Pawn(BLACK, DOWN);
	bPawn8 = new Pawn(BLACK, DOWN);
	
	board[0][0] = bRook1;
	board[0][1] = bKnight1;
	board[0][2] = bBishop1;
	board[0][3] = bQueen;
	board[0][4] = bKing;
	board[0][5] = bBishop2;
	board[0][6] = bKnight2;
	board[0][7] = bRook2;
	board[1][0] = bPawn1;
	board[1][1] = bPawn2;
	board[1][2] = bPawn3;
	board[1][3] = bPawn4;
	board[1][4] = bPawn5;
	board[1][5] = bPawn6;
	board[1][6] = bPawn7;
	board[1][7] = bPawn8;
	
	board[7][0] = wRook1;
	board[7][1] = wKnight1;
	board[7][2] = wBishop1;
	board[7][3] = wQueen;
	board[7][4] = wKing;
	board[7][5] = wBishop2;
	board[7][6] = wKnight2;
	board[7][7] = wRook2;
	board[6][0] = wPawn1;
	board[6][1] = wPawn2;
	board[6][2] = wPawn3;
	board[6][3] = wPawn4;
	board[6][4] = wPawn5;
	board[6][5] = wPawn6;
	board[6][6] = wPawn7;
	board[6][7] = wPawn8;
}

void ChessBoard::initializeBlankTestBoard(IChessPiece* piece, int row, int col) {
	//although all of these pieces aren't used, in test cases in individual classes,
	//	after the board is done being used and going to be destroyed, the 
	//	method calls the destructor on every piece, because it assumes they've
	//	all been created like in a normal game
	
	wKing = new King(WHITE, NA);
	wQueen = new Queen(WHITE, NA);
	wRook1 = new Rook(WHITE, NA);
	wRook2 = new Rook(WHITE, NA);
	wBishop1 = new Bishop(WHITE, NA);
	wBishop2 = new Bishop(WHITE, NA);
	wKnight1 = new Knight(WHITE, NA);
	wKnight2 = new Knight(WHITE, NA);
	wPawn1 = new Pawn(WHITE, UP);
	wPawn2 = new Pawn(WHITE, UP);
	wPawn3 = new Pawn(WHITE, UP);
	wPawn4 = new Pawn(WHITE, UP);
	wPawn5 = new Pawn(WHITE, UP);
	wPawn6 = new Pawn(WHITE, UP);
	wPawn7 = new Pawn(WHITE, UP);
	wPawn8 = new Pawn(WHITE, UP);

	bKing = new King(BLACK, NA);
	bQueen = new Queen(BLACK, NA);
	bRook1 = new Rook(BLACK, NA);
	bRook2 = new Rook(BLACK, NA);
	bBishop1 = new Bishop(BLACK, NA);
	bBishop2 = new Bishop(BLACK, NA);
	bKnight1 = new Knight(BLACK, NA);
	bKnight2 = new Knight(BLACK, NA);
	bPawn1 = new Pawn(BLACK, DOWN);
	bPawn2 = new Pawn(BLACK, DOWN);
	bPawn3 = new Pawn(BLACK, DOWN);
	bPawn4 = new Pawn(BLACK, DOWN);
	bPawn5 = new Pawn(BLACK, DOWN);
	bPawn6 = new Pawn(BLACK, DOWN);
	bPawn7 = new Pawn(BLACK, DOWN);
	bPawn8 = new Pawn(BLACK, DOWN);
	
	for (int i=0; i<8; ++i)
		for (int j=0; j<8; ++j)
			board[i][j] = NULL;
	board[row][col] = piece;
}

void ChessBoard::initializeTwoTwoBoard(IChessPiece* piece, int row, int col) {
	//although all of these pieces aren't used, in test cases in individual classes,
	//	after the board is done being used and going to be destroyed, the 
	//	method calls the destructor on every piece, because it assumes they've
	//	all been created like in a normal game
	
	wKing = new King(WHITE, NA);
	wQueen = new Queen(WHITE, NA);
	wRook1 = new Rook(WHITE, NA);
	wRook2 = new Rook(WHITE, NA);
	wBishop1 = new Bishop(WHITE, NA);
	wBishop2 = new Bishop(WHITE, NA);
	wKnight1 = new Knight(WHITE, NA);
	wKnight2 = new Knight(WHITE, NA);
	wPawn1 = new Pawn(WHITE, UP);
	wPawn2 = new Pawn(WHITE, UP);
	wPawn3 = new Pawn(WHITE, UP);
	wPawn4 = new Pawn(WHITE, UP);
	wPawn5 = new Pawn(WHITE, UP);
	wPawn6 = new Pawn(WHITE, UP);
	wPawn7 = new Pawn(WHITE, UP);
	wPawn8 = new Pawn(WHITE, UP);

	bKing = new King(BLACK, NA);
	bQueen = new Queen(BLACK, NA);
	bRook1 = new Rook(BLACK, NA);
	bRook2 = new Rook(BLACK, NA);
	bBishop1 = new Bishop(BLACK, NA);
	bBishop2 = new Bishop(BLACK, NA);
	bKnight1 = new Knight(BLACK, NA);
	bKnight2 = new Knight(BLACK, NA);
	bPawn1 = new Pawn(BLACK, DOWN);
	bPawn2 = new Pawn(BLACK, DOWN);
	bPawn3 = new Pawn(BLACK, DOWN);
	bPawn4 = new Pawn(BLACK, DOWN);
	bPawn5 = new Pawn(BLACK, DOWN);
	bPawn6 = new Pawn(BLACK, DOWN);
	bPawn7 = new Pawn(BLACK, DOWN);
	bPawn8 = new Pawn(BLACK, DOWN);
	
	for (int i=0; i<8; ++i)
		for (int j=0; j<8; ++j)
			board[i][j] = NULL;
	board[row][col] = piece;
	
	board[2][2] = new Pawn(BLACK, DOWN);
}

IChessPiece* ChessBoard::getPiece(BoardPosition bp) {
	return board[bp.getRow()][bp.getColumn()];
}

Move ChessBoard::movePiece(BoardPosition before, BoardPosition after) {
	IChessPiece* movingPiece = board[before.getRow()][before.getColumn()];
	IChessPiece* capturedPiece = board[after.getRow()][after.getColumn()];
	
	movingPiece->firstTurnDone();		//in case this piece is a pawn, so it can't go two again
										//also important for castling
	
	//create a new Move object
	Move newMove(movingPiece, BoardPosition(before), BoardPosition(after));
	if (capturedPiece != NULL) {
		newMove.addCapturedPiece(capturedPiece);	
	}
		
	//move piece on board
	board[after.getRow()][after.getColumn()] = movingPiece;
	board[before.getRow()][before.getColumn()] = NULL;
	
	movingPiece = NULL;					//FOR MEMORY ISSUES
	capturedPiece = NULL;
	
	return newMove;
	//printBoard();
}

bool ChessBoard::moveHypotheticalPiece(BoardPosition& before, BoardPosition& after) {

	bool noSelfCheck = true;
	
	IChessPiece* movingPiece = board[before.getRow()][before.getColumn()];
	IChessPiece* capturedPiece = board[after.getRow()][after.getColumn()];
	
	//make the hypothetical move
	board[after.getRow()][after.getColumn()] = movingPiece;
	board[before.getRow()][before.getColumn()] = NULL;
	
	
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			IChessPiece* hypPiece = board[i][j];
			BoardPosition bp(i,j);
			if (hypPiece != NULL) {
				if (hypPiece->isEnemy(movingPiece)) {	//if a piece is on square and is an enemy
					if (hypPiece->canCaptureKing(this, bp)) {	//check if it is an position to
						noSelfCheck = false;					// capture current player's king
					}
				}
			}
			hypPiece = NULL;
		}
	}
	
	//reset the board to pre-move status
	board[before.getRow()][before.getColumn()] = movingPiece;
	board[after.getRow()][after.getColumn()] = capturedPiece;
	
	movingPiece = NULL;
	capturedPiece = NULL;
	
	return noSelfCheck;
}

//reuses code of next method, but easiest way of calling
// next method within this method would involve doing the method over here as well
bool ChessBoard::kingInCheck(BoardPosition bp) {
	IChessPiece* king;
		
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			if (board[i][j] != NULL &&
				board[i][j]->getType() == KING &&
				!board[i][j]->isEnemy(getPiece(bp)))
				 king = board[i][j];
		}
	}
		
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			if (board[i][j] != NULL) {
				BoardPosition bp(i,j);
				if (board[i][j]->canCapturePiece(king, this, bp)) {
					king = NULL;
					return true;
				}
			}
		}
	}
	return false;
}

//TODO simplify by removing one of double for loops
bool ChessBoard::enemyKingInCheck(BoardPosition bp) {
	IChessPiece* king;
		
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			if (board[i][j] != NULL &&
				board[i][j]->getType() == KING &&
				board[i][j]->isEnemy(getPiece(bp)))
				 king = board[i][j];
		}
	}
		
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			if (board[i][j] != NULL) {
				BoardPosition bp(i,j);
				if (board[i][j]->canCapturePiece(king, this, bp)) {
					king = NULL;
					return true;
				}
			}
		}
	}
	
	return false;
}

BoardPosition ChessBoard::getRandomPosition(Color c) {
	vector<BoardPosition> currentTeam;
	
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			if (board[i][j] != NULL) {
				if (!(board[i][j]->isEnemy(c))) {
					BoardPosition bp(i,j);
					currentTeam.push_back(bp);
				}
			}
		}
	}
	
	int randNum = (rand() % currentTeam.size());

	return currentTeam.at(randNum);
}

void ChessBoard::placePiece(IChessPiece* piece, BoardPosition bp) {
	board[bp.getRow()][bp.getColumn()] = piece;
}

string ChessBoard::getCurrentXMLState() {
	stringstream stream;
	
	stream << "<board>\n";
	
	for (int i=0; i<8; ++i) {
		for (int j=0; j<8; ++j) {
			IChessPiece* piece = board[i][j];
			if (piece != NULL) {
				stream << piece->getXMLInfo(i,j);
			}
		}	
	}
	
	stream << "</board>\n";
	return stream.str();
}

bool ChessBoard::canPromotePawn(BoardPosition bp) {
	IChessPiece* possiblePawn = board[bp.getRow()][bp.getColumn()];
	
	return (possiblePawn->getType() == PAWN && 
	   ((possiblePawn->getColor() == WHITE && bp.getRow() == 0) ||
		(possiblePawn->getColor() == BLACK && bp.getRow() == 7)));
}

void ChessBoard::promotePawn(PieceType newType, BoardPosition bp) {
	Color color = board[bp.getRow()][bp.getColumn()]->getColor();
	Direction dir = board[bp.getRow()][bp.getColumn()]->getDirection();
	
	//delete board[bp.getRow()][bp.getColumn()];
	//instead of deleting the object pointed to, store it so it can be deleted if game ends
	// need to keep this object still because move objects store pointers to the object
	// that moved and need them to restore moves to board
	promotedPieces.push(board[bp.getRow()][bp.getColumn()]);

	switch (newType) {
		case KNIGHT:
			board[bp.getRow()][bp.getColumn()] = new Knight(color, dir);
			break;
		case BISHOP:
			board[bp.getRow()][bp.getColumn()] = new Bishop(color, dir);
			break;
		case ROOK:
			board[bp.getRow()][bp.getColumn()] = new Rook(color, dir);
			break;
		case QUEEN:
			board[bp.getRow()][bp.getColumn()] = new Queen(color, dir);
			break;
	}
	
	board[bp.getRow()][bp.getColumn()]->setPromoted();
}

//TODO, if not empty at end of game, delete pawns here
IChessPiece* ChessBoard::popLastPromotion() {
	IChessPiece* last = promotedPieces.top();
	last->unSetPromoted();
	promotedPieces.pop();
	return last;
}

bool ChessBoard::Test(ostream& out) {
	bool success = true;
	
	ChessBoard cb;
	cb.initializeBoard();
	
	//cb.printBoard();
	
	return success;
}
