//Pawn.cpp

#include "Pawn.h"
#include "UnitTest.h"
using namespace std;

Pawn::Pawn(Color c, Direction d) : IChessPiece(PAWN, c, d), firstTurn(true) {
	//firstTurn = true;
}

Pawn::~Pawn(){
}

set<BoardPosition> Pawn::getCandidateMoves(ChessBoard* board, BoardPosition pos) {
	set<BoardPosition> candidateMovesSet;
	
	BoardPosition origPos(pos);
	
	if (getDirection() == UP) {
		if (firstTurn) {
			origPos.moveUp();
			if (board->getPiece(origPos) == NULL) {				  //if the current square we're on
				candidateMovesSet.insert(BoardPosition(origPos)); //  is empty, pawn can move here
				origPos.moveUp();	
					if (board->getPiece(origPos) == NULL)	
						candidateMovesSet.insert(BoardPosition(origPos));
				}
			}
		else if (origPos.moveUp()) {									
			if (board->getPiece(origPos) == NULL)
				candidateMovesSet.insert(BoardPosition(origPos));
		}
	}
	else {
		if (firstTurn) {
			origPos.moveDown();
			if (board->getPiece(origPos) == NULL) {				  //if the current square we're on
				candidateMovesSet.insert(BoardPosition(origPos)); //  is empty, pawn can move here
				origPos.moveDown();	
					if (board->getPiece(origPos) == NULL)	
						candidateMovesSet.insert(BoardPosition(origPos));
				}
			}
		else if (origPos.moveDown()) {
			if (board->getPiece(origPos) == NULL)
				candidateMovesSet.insert(BoardPosition(origPos));
		}
	}
	
	//adds any of the special diagonal positions that pawns can capture
	addCapturePositions(pos, board, candidateMovesSet);
				
	return candidateMovesSet;
}

string Pawn::getTypeString() {
	return "pawn";
}

ImageName Pawn::getImageName() {
	if (getColor() == WHITE)
		return W_PAWN;
	else
		return B_PAWN;
}

void Pawn::firstTurnDone() {
	firstTurn = false;
}

void Pawn::firstTurnUnDone() {
	firstTurn = true;			//caller will determine if this piece is on its original position
}

//TODO simplify
void Pawn::addCapturePositions(BoardPosition pos, ChessBoard* board, set<BoardPosition>& bpSet) {
	BoardPosition origPos(pos);
	
	if (getDirection() == UP) {
		if (origPos.moveUp()) {
			if (origPos.moveRight()) {
				if (board->getPiece(origPos) != NULL) {
					if (board->getPiece(origPos)->isEnemy(getColor()))
						bpSet.insert(BoardPosition(origPos));
				}
			}
		}
		
		origPos = pos;
		if (origPos.moveUp()) {
			if (origPos.moveLeft()) {
				if (board->getPiece(origPos) != NULL) {
					if (board->getPiece(origPos)->isEnemy(getColor()))
						bpSet.insert(BoardPosition(origPos));
				}
			}
		}
	}
	else {
		if (origPos.moveDown()) {
			if (origPos.moveRight()) {
				if (board->getPiece(origPos) != NULL) {
					if (board->getPiece(origPos)->isEnemy(getColor()))
						bpSet.insert(BoardPosition(origPos));
				}
			}
		}
		
		origPos = pos;
		if (origPos.moveDown()) {
			if (origPos.moveLeft()) {
				if (board->getPiece(origPos) != NULL) {
					if (board->getPiece(origPos)->isEnemy(getColor()))
						bpSet.insert(BoardPosition(origPos));
				}
			}
		}
	}	
}

string Pawn::getXMLInfo(int row, int column) {
	stringstream stream;
	
	stream << "<piece ";
	stream << "type=\"" << getTypeString() << "\" ";
	stream << "color=\"" << getColorString() << "\" ";
	stream << "column=\"" << column << "\" ";
	stream << "row=\"" << row << "\"/>\n";
	
	return stream.str();
}

bool Pawn::Test(std::ostream& os) {
	bool success = true;
	
	/*
	 * TEST 1 white pawn in starting location of full initial board
	 */
	Pawn p1(WHITE, UP);
	ChessBoard board1;
	board1.initializeBoard();
	
	set<BoardPosition> bpSet = p1.getCandidateMoves(&board1, BoardPosition(6,5));
	
	TEST(bpSet.find(BoardPosition(5,5)) != bpSet.end());//should have two initial moves
	TEST(bpSet.find(BoardPosition(4,5)) != bpSet.end());
	TEST(bpSet.find(BoardPosition(5,4)) == bpSet.end());
	TEST(bpSet.find(BoardPosition(3,5)) == bpSet.end());
	TEST(bpSet.size() == 2);
	TEST(p1.getTypeString() == "pawn");
	TEST(p1.getImageName() == W_PAWN);
	
	/*
	 * TEST 2 black pawn in middle of an empty board (3, 3)
	 */
	IChessPiece* p2 = new Pawn(BLACK, DOWN);
	ChessBoard board2;
	board2.initializeBlankTestBoard(p2, 3, 3);
	
	p2->firstTurnDone();
	set<BoardPosition> bpSet2 = p2->getCandidateMoves(&board2, BoardPosition(3,3));
	
	//tests to make sure up vs down is correct
	TEST(bpSet2.find(BoardPosition(4,3)) != bpSet2.end());	//board position that the pawn
															// should be able to move to
	TEST(bpSet2.find(BoardPosition(2,3)) == bpSet2.end());	//board positions that the pawn
															// should NOT be able to move to
	TEST(bpSet2.find(BoardPosition(5,3)) == bpSet2.end());	//no two square after first turn
	TEST(bpSet2.size() == 1);
	TEST(p2->getTypeString() == "pawn");
	TEST(p2->getImageName() == B_PAWN);
	
	/*
	 * TEST 3 white pawn at top of empty board (0, 5)
	 */
	IChessPiece* p3 = new Pawn(WHITE, UP);
	ChessBoard board3;
	board3.initializeBlankTestBoard(p3, 0, 5);
	
	set<BoardPosition> bpSet3 = p3->getCandidateMoves(&board3, BoardPosition(0, 5));
	
	TEST(bpSet3.find(BoardPosition(1, 5)) == bpSet3.end());
	TEST(bpSet3.size() == 0);
	TEST(p3->getTypeString() == "pawn");
	TEST(p3->getImageName() == W_PAWN);
	
	/*
	 * TEST 4 black pawn behind friend pawn (1, 2) (hypothetically, since a pawn could never
	 *	get to this exact position)
	 */
	IChessPiece* p4 = new Pawn(BLACK, DOWN);
	ChessBoard board4;
	board4.initializeTwoTwoBoard(p4, 1, 2);
	
	set<BoardPosition> bpSet4 = p4->getCandidateMoves(&board4, BoardPosition(1, 2));
	
	TEST(bpSet4.find(BoardPosition(2, 2)) == bpSet4.end());	//can't go past where friendly
	TEST(bpSet4.find(BoardPosition(2, 1)) == bpSet4.end());	//where the friendly piece is
	TEST(bpSet4.size() == 0);
	
	/*
	 * TEST 5 white pawn on near enemy pawn, checks for addCapturePositions
	 */
	IChessPiece* p5 = new Pawn(WHITE, UP);
	ChessBoard board5;
	board5.initializeTwoTwoBoard(p5, 3, 3);
	
	p5->firstTurnDone();
	set<BoardPosition> bpSet5 = p5->getCandidateMoves(&board5, BoardPosition(3, 3));
	
	TEST(bpSet5.find(BoardPosition(2, 2)) != bpSet5.end());	//can capture enemy diagonally
	TEST(bpSet5.find(BoardPosition(2, 3)) != bpSet5.end());	//where the friendly piece is
	TEST(bpSet5.find(BoardPosition(1, 3)) == bpSet5.end());	//no two square after first turn
	TEST(bpSet5.size() == 2);
	
	return success;
}
