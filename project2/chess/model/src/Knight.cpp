//Knight.cpp

#include "Knight.h"
#include "UnitTest.h"
using namespace std;

Knight::Knight(Color c, Direction d) : IChessPiece(KNIGHT, c, d) {
}

Knight::~Knight() {
}

set<BoardPosition> Knight::getCandidateMoves(ChessBoard* board, BoardPosition pos) {
	set<BoardPosition> candidateMovesSet;
	
	//TODO simplify nested if statements
	
	//up-up-right
	BoardPosition origPos(pos);
	if (origPos.moveUp()) {
		if (origPos.moveUp()) {
			if (origPos.moveRight()) {
				if (board->getPiece(origPos) != NULL) {
					if (board->getPiece(origPos)->isEnemy(getColor()))
						candidateMovesSet.insert(BoardPosition(origPos));
				}
				else	
					candidateMovesSet.insert(BoardPosition(origPos));
			}
		}
	}
	
	//up-right-right
	origPos = pos;
	if (origPos.moveUp()) {
		if (origPos.moveRight()) {
			if (origPos.moveRight()) {
				if (board->getPiece(origPos) != NULL) {
					if (board->getPiece(origPos)->isEnemy(getColor()))
						candidateMovesSet.insert(BoardPosition(origPos));
				}
				else	
					candidateMovesSet.insert(BoardPosition(origPos));
			}
		}
	}
	
	//down-right-right
	origPos = pos;
	if (origPos.moveDown()) {
		if (origPos.moveRight()) {
			if (origPos.moveRight()) {
				if (board->getPiece(origPos) != NULL) {
					if (board->getPiece(origPos)->isEnemy(getColor()))
						candidateMovesSet.insert(BoardPosition(origPos));
				}
				else	
					candidateMovesSet.insert(BoardPosition(origPos));
			}
		}
	}
	
	//down-down-right
	origPos = pos;
	if (origPos.moveDown()) {
		if (origPos.moveDown()) {
			if (origPos.moveRight()) {
				if (board->getPiece(origPos) != NULL) {
					if (board->getPiece(origPos)->isEnemy(getColor()))
						candidateMovesSet.insert(BoardPosition(origPos));
				}
				else	
					candidateMovesSet.insert(BoardPosition(origPos));
			}
		}
	}
	
	//down-down-left
	origPos = pos;
	if (origPos.moveDown()) {
		if (origPos.moveDown()) {
			if (origPos.moveLeft()) {
				if (board->getPiece(origPos) != NULL) {
					if (board->getPiece(origPos)->isEnemy(getColor()))
						candidateMovesSet.insert(BoardPosition(origPos));
				}
				else	
					candidateMovesSet.insert(BoardPosition(origPos));
			}
		}
	}
	
	//down-left-left
	origPos = pos;
	if (origPos.moveDown()) {
		if (origPos.moveLeft()) {
			if (origPos.moveLeft()) {
				if (board->getPiece(origPos) != NULL) {
					if (board->getPiece(origPos)->isEnemy(getColor()))
						candidateMovesSet.insert(BoardPosition(origPos));
				}
				else	
					candidateMovesSet.insert(BoardPosition(origPos));
			}
		}
	}
	
	//up-left-left
	origPos = pos;
	if (origPos.moveUp()) {
		if (origPos.moveLeft()) {
			if (origPos.moveLeft()) {
				if (board->getPiece(origPos) != NULL) {
					if (board->getPiece(origPos)->isEnemy(getColor()))
						candidateMovesSet.insert(BoardPosition(origPos));
				}
				else	
					candidateMovesSet.insert(BoardPosition(origPos));
			}
		}
	}
	
	//up-up-left
	origPos = pos;
	if (origPos.moveUp()) {
		if (origPos.moveUp()) {
			if (origPos.moveLeft()) {
				if (board->getPiece(origPos) != NULL) {
					if (board->getPiece(origPos)->isEnemy(getColor()))
						candidateMovesSet.insert(BoardPosition(origPos));
				}
				else	
					candidateMovesSet.insert(BoardPosition(origPos));
			}
		}
	}
	
	return candidateMovesSet;
}

string Knight::getTypeString() {
	return "knight";
}

ImageName Knight::getImageName() {
	if (getColor() == WHITE)
		return W_KNIGHT;
	else
		return B_KNIGHT;
}

void Knight::firstTurnDone() {
	return;
}

void Knight::firstTurnUnDone() {
	return;
}

string Knight::getXMLInfo(int row, int column) {
	stringstream stream;
	stream << "<piece ";
	stream << "type=\"" << getTypeString() << "\" ";
	stream << "color=\"" << getColorString() << "\" ";
	stream << "column=\"" << column << "\" ";
	stream << "row=\"" << row << "\"/>\n";
	
	return stream.str();
}

bool Knight::Test(std::ostream& os) {
	bool success = true;
	
	/*
	 * TEST 1 white knight in starting location of full initial board
	 */
	Knight k1(WHITE, UP);
	ChessBoard board1;
	board1.initializeBoard();
	
	set<BoardPosition> bpSet = k1.getCandidateMoves(&board1, BoardPosition(7,1));
	
	TEST(bpSet.find(BoardPosition(5,0)) != bpSet.end());//should have two initial moves
	TEST(bpSet.find(BoardPosition(5,2)) != bpSet.end());
	TEST(bpSet.find(BoardPosition(5,1)) == bpSet.end());
	TEST(bpSet.find(BoardPosition(5,3)) == bpSet.end());
	TEST(bpSet.size() == 2);
	TEST(k1.getTypeString() == "knight");
	TEST(k1.getImageName() == W_KNIGHT);
	
	/*
	 * TEST 2 black knight in middle of an empty board (3, 3)
	 */
	IChessPiece* k2 = new Knight(BLACK, DOWN);
	ChessBoard board2;
	board2.initializeBlankTestBoard(k2, 3, 3);
	
	set<BoardPosition> bpSet2 = k2->getCandidateMoves(&board2, BoardPosition(3,3));
	
	TEST(bpSet2.find(BoardPosition(1,2)) != bpSet2.end());	//board positions that the knight
	TEST(bpSet2.find(BoardPosition(2,1)) != bpSet2.end());	// should be able to move to
	TEST(bpSet2.find(BoardPosition(4,1)) != bpSet2.end());
	TEST(bpSet2.find(BoardPosition(5,2)) != bpSet2.end());	
	TEST(bpSet2.find(BoardPosition(5,4)) != bpSet2.end());
	TEST(bpSet2.find(BoardPosition(4,5)) != bpSet2.end());
	TEST(bpSet2.find(BoardPosition(2,5)) != bpSet2.end());
	TEST(bpSet2.find(BoardPosition(1,4)) != bpSet2.end());
	TEST(bpSet2.find(BoardPosition(3,1)) == bpSet2.end());	//board positions that the knight
	TEST(bpSet2.find(BoardPosition(0,2)) == bpSet2.end());	// should NOT be able to move to
	TEST(bpSet2.find(BoardPosition(5,5)) == bpSet2.end());
	TEST(bpSet2.size() == 8);
	TEST(k2->getTypeString() == "knight");
	TEST(k2->getImageName() == B_KNIGHT);
	
	/*
	 * TEST 3 white knight near right edge of empty board (6, 0)
	 */
	IChessPiece* k3 = new Knight(WHITE, UP);
	ChessBoard board3;
	board3.initializeBlankTestBoard(k3, 4, 7);
	
	set<BoardPosition> bpSet3 = k3->getCandidateMoves(&board3, BoardPosition(4, 7));
	
	TEST(bpSet3.find(BoardPosition(2, 6)) != bpSet3.end());
	TEST(bpSet3.find(BoardPosition(3, 5)) != bpSet3.end());
	TEST(bpSet3.find(BoardPosition(6, 6)) != bpSet3.end());
	TEST(bpSet3.find(BoardPosition(3, 6)) == bpSet3.end());
	TEST(bpSet3.find(BoardPosition(0, 7)) == bpSet3.end());
	TEST(bpSet3.size() == 4);
	TEST(k3->getTypeString() == "knight");
	TEST(k3->getImageName() == W_KNIGHT);
	
	/*
	 * TEST 4 black knight on left edge of board with one other piece (3, 0)
	 */
	IChessPiece* k4 = new Knight(BLACK, DOWN);
	ChessBoard board4;
	board4.initializeTwoTwoBoard(k4, 3, 0);
	
	set<BoardPosition> bpSet4 = k4->getCandidateMoves(&board4, BoardPosition(3, 0));
	
	TEST(bpSet4.find(BoardPosition(1, 1)) != bpSet4.end());
	TEST(bpSet4.find(BoardPosition(2, 2)) == bpSet4.end());	//can't go past where friendly
	TEST(bpSet4.find(BoardPosition(5, 2)) == bpSet4.end());	//where the friendly piece is
	TEST(bpSet4.size() == 3);
	
	return success;
}
