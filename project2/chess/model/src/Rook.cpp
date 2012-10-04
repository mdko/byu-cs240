//Rook.cpp

#include "Rook.h"
#include "UnitTest.h"
using namespace std;

Rook::Rook(Color c, Direction d) : IChessPiece(ROOK, c, d), firstTurn(true) {
}

Rook::~Rook() {
}

set<BoardPosition> Rook::getCandidateMoves(ChessBoard* board, BoardPosition pos) {
	set<BoardPosition> candidateMovesSet;
	
	BoardPosition origPos(pos);
	while (origPos.moveUp()) {
		if (board->getPiece(origPos) != NULL) {
			if (!board->getPiece(origPos)->isEnemy(getColor()))
				break;
			candidateMovesSet.insert(BoardPosition(origPos));
			break;
		}
		candidateMovesSet.insert(BoardPosition(origPos));
	}
		
	origPos = pos;
	while (origPos.moveRight()) {
		if (board->getPiece(origPos) != NULL) {
			if (!board->getPiece(origPos)->isEnemy(getColor()))
				break;
			candidateMovesSet.insert(BoardPosition(origPos));
			break;
		}
		candidateMovesSet.insert(BoardPosition(origPos));
	}
		
	origPos = pos;
	while (origPos.moveDown()) {
		if (board->getPiece(origPos) != NULL) {
			if (!board->getPiece(origPos)->isEnemy(getColor()))
				break;
			candidateMovesSet.insert(BoardPosition(origPos));
			break;
		}
		candidateMovesSet.insert(BoardPosition(origPos));
	}
	
	origPos = pos;
	while (origPos.moveLeft()) {
		if (board->getPiece(origPos) != NULL) {
			if (!board->getPiece(origPos)->isEnemy(getColor()))
				break;
			candidateMovesSet.insert(BoardPosition(origPos));
			break;
		}
		candidateMovesSet.insert(BoardPosition(origPos));
	}
	
	return candidateMovesSet;
}

string Rook::getTypeString() {
	return "rook";
}

ImageName Rook::getImageName() {
	if (getColor() == WHITE)
		return W_ROOK;
	else
		return B_ROOK;
}

void Rook::firstTurnDone() {
	firstTurn = false;
}

void Rook::firstTurnUnDone() {
	firstTurn = true;
}

string Rook::getXMLInfo(int row, int column) {
	stringstream stream;
	
	stream << "<piece ";
	stream << "type=\"" << getTypeString() << "\" ";
	stream << "color=\"" << getColorString() << "\" ";
	stream << "column=\"" << column << "\" ";
	stream << "row=\"" << row << "\"/>\n";
	
	return stream.str();
}

bool Rook::Test(std::ostream& os) {
	bool success = true;
	
	/*
	 * TEST 1 white rook in top-left corner of a full initial board (rook already present on board)
	 */
	Rook rk1(WHITE, UP);
	ChessBoard board1;
	board1.initializeBoard();
	
	set<BoardPosition> bpSet = rk1.getCandidateMoves(&board1, BoardPosition(7,0));
	
	TEST(bpSet.find(BoardPosition(0,1)) == bpSet.end());
	TEST(bpSet.size() == 0);
	TEST(rk1.getTypeString() == "rook");
	TEST(rk1.getImageName() == W_ROOK);
	
	/*
	 * TEST 2 black rook in middle of an empty board (3, 3)
	 */
	IChessPiece* rk2 = new Rook(BLACK, DOWN);
	ChessBoard board2;
	board2.initializeBlankTestBoard(rk2, 3, 3);
	
	set<BoardPosition> bpSet2 = rk2->getCandidateMoves(&board2, BoardPosition(3,3));
	
	TEST(bpSet2.find(BoardPosition(2,3)) != bpSet2.end());	//board positions that the rook
	TEST(bpSet2.find(BoardPosition(7,3)) != bpSet2.end());	// should be able to move to
	TEST(bpSet2.find(BoardPosition(0,0)) == bpSet2.end());	//board positions that the rook
	TEST(bpSet2.find(BoardPosition(4,4)) == bpSet2.end());	// should NOT be able to move to
	TEST(bpSet2.size() == 14);
	TEST(rk2->getTypeString() == "rook");
	TEST(rk2->getImageName() == B_ROOK);
	
	/*
	 * TEST 3 white rook near bottom right edge of empty board (6, 5)
	 */
	IChessPiece* rk3 = new Rook(WHITE, UP);
	ChessBoard board3;
	board3.initializeBlankTestBoard(rk3, 5, 6);
	
	set<BoardPosition> bpSet3 = rk3->getCandidateMoves(&board3, BoardPosition(5, 6));
	
	TEST(bpSet3.find(BoardPosition(5, 7)) != bpSet3.end());
	TEST(bpSet3.find(BoardPosition(7, 6)) != bpSet3.end());
	TEST(bpSet3.find(BoardPosition(4, 4)) == bpSet3.end());
	TEST(bpSet3.find(BoardPosition(7, 0)) == bpSet3.end());
	TEST(bpSet3.size() == 14);
	TEST(rk3->getTypeString() == "rook");
	TEST(rk3->getImageName() == W_ROOK);
	
	/*
	 * TEST 4 black rook near top of board with one other piece (1, 4), a black pawn
	 */
	IChessPiece* rk4 = new Rook(BLACK, DOWN);
	ChessBoard board4;
	board4.initializeTwoTwoBoard(rk4, 2, 4);
	
	set<BoardPosition> bpSet4 = rk4->getCandidateMoves(&board4, BoardPosition(2, 4));
	
	TEST(bpSet4.find(BoardPosition(2, 3)) != bpSet4.end());
	TEST(bpSet4.find(BoardPosition(2, 1)) == bpSet4.end());	//can't go past where friendly
	TEST(bpSet4.find(BoardPosition(2, 2)) == bpSet4.end());	//where the friendly piece is
	TEST(bpSet4.size() == 11);
	
	return success;
}
