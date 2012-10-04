//King.cpp

#include "King.h"
#include "UnitTest.h"
using namespace std;

King::King(Color c, Direction d) : IChessPiece(KING, c, d), firstTurn(true) {
}

King::~King() {
}

set<BoardPosition> King::getCandidateMoves(ChessBoard* board, BoardPosition pos) {
	set<BoardPosition> candidateMovesSet;
	
	//up
	BoardPosition origPos(pos);
	if(origPos.moveUp()) {
		if (board->getPiece(origPos) != NULL) {
			if (board->getPiece(origPos)->isEnemy(getColor()))	//if currentSquare has enemy piece
				candidateMovesSet.insert(BoardPosition(origPos));
		}
		else													//else we're on an empty square
			candidateMovesSet.insert(BoardPosition(origPos));
	}
	
	//up-right
	origPos = pos;
	if(origPos.moveUpRight()) {
		if (board->getPiece(origPos) != NULL) {
			if (board->getPiece(origPos)->isEnemy(getColor()))
				candidateMovesSet.insert(BoardPosition(origPos));
		}
		else	
			candidateMovesSet.insert(BoardPosition(origPos));
	}
	
	//right
	origPos = pos;
	if(origPos.moveRight()) {
		if (board->getPiece(origPos) != NULL) {
			if (board->getPiece(origPos)->isEnemy(getColor()))
				candidateMovesSet.insert(BoardPosition(origPos));
		}
		else	
			candidateMovesSet.insert(BoardPosition(origPos));
	}
	
	//down-right
	origPos = pos;
	if(origPos.moveDownRight()) {
		if (board->getPiece(origPos) != NULL) {
			if (board->getPiece(origPos)->isEnemy(getColor()))
				candidateMovesSet.insert(BoardPosition(origPos));
		}
		else	
			candidateMovesSet.insert(BoardPosition(origPos));
	}
	
	//down
	origPos = pos;
	if(origPos.moveDown()) {
		if (board->getPiece(origPos) != NULL) {
			if (board->getPiece(origPos)->isEnemy(getColor()))
				candidateMovesSet.insert(BoardPosition(origPos));
		}
		else	
			candidateMovesSet.insert(BoardPosition(origPos));
	}
	
	//down-left	
	origPos = pos;
	if(origPos.moveDownLeft()) {
		if (board->getPiece(origPos) != NULL) {
			if (board->getPiece(origPos)->isEnemy(getColor()))
				candidateMovesSet.insert(BoardPosition(origPos));
		}
		else	
			candidateMovesSet.insert(BoardPosition(origPos));
	}
	
	//left
	origPos = pos;
	if(origPos.moveLeft()) {
		if (board->getPiece(origPos) != NULL) {
			if (board->getPiece(origPos)->isEnemy(getColor()))
				candidateMovesSet.insert(BoardPosition(origPos));
		}
		else	
			candidateMovesSet.insert(BoardPosition(origPos));
	}
	
	//up-left
	origPos = pos;
	if(origPos.moveUpLeft()) {
		if (board->getPiece(origPos) != NULL) {
			if (board->getPiece(origPos)->isEnemy(getColor()))
				candidateMovesSet.insert(BoardPosition(origPos));
		}
		else	
			candidateMovesSet.insert(BoardPosition(origPos));
	}
	
	//if (firstTurn)
	//	addCastlePositions(pos, board, candidateMovesSet);
	
	return candidateMovesSet;
}

string King::getTypeString() {
	return "king";
}

//TODO fix so that undo-ing the castle and selecting the king shows castling possibilities again
//TODO move the rook at the same time
void King::addCastlePositions(BoardPosition pos, ChessBoard* board, set<BoardPosition>& bpSet) {
	BoardPosition orig(pos);
	
	//find clear path to right rook
	while (orig.moveRight() && orig.getColumn() != 7) {
		if (board->getPiece(orig) != NULL)
			break;
	}
	//origPos should now be where a rook is
	if (board->getPiece(orig)->getType() == ROOK &&
		board->getPiece(orig)->isFirstTurn()) {
			orig.moveLeft();
			bpSet.insert(BoardPosition(orig));
	}
	
	orig = pos;
	
	//find clear path to left rook
	while (orig.moveLeft() && orig.getColumn() != 0) {
		if (board->getPiece(orig) != NULL)
			break;		
	}
	//origPos should now be where a rook is
	if (board->getPiece(orig)->getType() == ROOK &&
		board->getPiece(orig)->isFirstTurn()) {
			orig.moveRight();
			orig.moveRight();
			bpSet.insert(BoardPosition(orig));
	}
}

ImageName King::getImageName() {
	if (getColor() == WHITE)
		return W_KING;
	else
		return B_KING;
}

void King::firstTurnDone() {
	firstTurn = false;
}

void King::firstTurnUnDone() {
	firstTurn = true;
}

string King::getXMLInfo(int row, int column) {
	stringstream stream;
	stream << "<piece ";
	stream << "type=\"" << getTypeString() << "\" ";
	stream << "color=\"" << getColorString() << "\" ";
	stream << "column=\"" << column << "\" ";
	stream << "row=\"" << row << "\"/>\n";
	
	return stream.str();
}

bool King::Test(ostream& os) {
	bool success = true;
	
	/*
	 * TEST 1 white king in starting location of full initial board
	 */
	King k1(WHITE, UP);
	ChessBoard board1;
	board1.initializeBoard();
	
	set<BoardPosition> bpSet = k1.getCandidateMoves(&board1, BoardPosition(7,4));
	
	TEST(bpSet.find(BoardPosition(6,4)) == bpSet.end());
	TEST(bpSet.size() == 0);		//should have no moves from a newgame board
	TEST(k1.getTypeString() == "king");
	TEST(k1.getImageName() == W_KING);
	
	/*
	 * TEST 2 black king in middle of an empty board (3, 3)
	 */
	IChessPiece* k2 = new King(BLACK, DOWN);
	ChessBoard board2;
	board2.initializeBlankTestBoard(k2, 3, 3);
	
	set<BoardPosition> bpSet2 = k2->getCandidateMoves(&board2, BoardPosition(3,3));
	
	TEST(bpSet2.find(BoardPosition(2,3)) != bpSet2.end());	//board positions that the king
	TEST(bpSet2.find(BoardPosition(2,2)) != bpSet2.end());	// should be able to move to
	TEST(bpSet2.find(BoardPosition(3,2)) != bpSet2.end());	//every direction
	TEST(bpSet2.find(BoardPosition(4,2)) != bpSet2.end());	
	TEST(bpSet2.find(BoardPosition(4,3)) != bpSet2.end());
	TEST(bpSet2.find(BoardPosition(4,4)) != bpSet2.end());
	TEST(bpSet2.find(BoardPosition(3,4)) != bpSet2.end());
	TEST(bpSet2.find(BoardPosition(2,4)) != bpSet2.end());
	TEST(bpSet2.find(BoardPosition(0,0)) == bpSet2.end());	//board positions that the king
	TEST(bpSet2.find(BoardPosition(7,3)) == bpSet2.end());	// should NOT be able to move to
	TEST(bpSet2.size() == 8);
	TEST(k2->getTypeString() == "king");
	TEST(k2->getImageName() == B_KING);
	
	/*
	 * TEST 3 white king in bottom right corner of empty board (7, 7)
	 */
	IChessPiece* k3 = new King(WHITE, UP);
	ChessBoard board3;
	board3.initializeBlankTestBoard(k3, 7, 7);
	
	set<BoardPosition> bpSet3 = k3->getCandidateMoves(&board3, BoardPosition(7, 7));
	
	TEST(bpSet3.find(BoardPosition(7, 6)) != bpSet3.end());
	TEST(bpSet3.find(BoardPosition(6, 7)) != bpSet3.end());
	TEST(bpSet3.find(BoardPosition(6, 6)) != bpSet3.end());
	TEST(bpSet3.find(BoardPosition(0, 0)) == bpSet3.end());
	TEST(bpSet3.find(BoardPosition(7, 5)) == bpSet3.end());
	TEST(bpSet3.size() == 3);
	TEST(k3->getTypeString() == "king");
	TEST(k3->getImageName() == W_KING);
	
	/*
	 * TEST 4 white king near top of board with one other piece at 2,2 (1, 3)
	 */
	IChessPiece* k4 = new King(BLACK, DOWN);
	ChessBoard board4;
	board4.initializeTwoTwoBoard(k4, 1, 3);
	
	set<BoardPosition> bpSet4 = k4->getCandidateMoves(&board4, BoardPosition(1, 3));
	
	TEST(bpSet4.find(BoardPosition(0, 3)) != bpSet4.end());
	TEST(bpSet4.find(BoardPosition(2, 2)) == bpSet4.end()); //can't hit friendly piece
	TEST(bpSet4.size() == 7);
	
	/*
	 * TEST 5 checking to make sure king cannot put himself in check would be done elsewhere,
	 *	since this class only determines candidateMoves, not legal moves
	 */
	
	return success;
}
