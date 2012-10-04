//HumanPlayer.cpp

#include "HumanPlayer.h"
#include "IChessController.h"
#include "SelectDialog.h"
#include "Move.h"
#include "ChessGame.h"

HumanPlayer::HumanPlayer(ChessGame* _game, IChessView* _view, 
						 IChessController* _control, Color _color) {
	this->game = _game;
	this->view = _view;
	this->controller = _control;					//so we can access on_NewGame()
	color = _color;
	currentClick = FIRST;
}

HumanPlayer::~HumanPlayer() {

}

void HumanPlayer::on_CellSelected(int row, int col, int button) {
	
	if (!isCheckMate() && !isStaleMate()) {
		if (currentClick == FIRST) {
			unHighlightAll();
			
			bpBefore = BoardPosition(row, col);		//instantiate before board position object
		
			if (!isValidPiece())
				return;
		
			highlightLegalMoves();
			currentClick = SECOND;	
		}
		else {										//@assert a valid piece has been selected
			bpAfter = BoardPosition(row, col);
			std::set<BoardPosition>::const_iterator iter;
			iter = bpSet.find(bpAfter);
		
			//if 2nd selected cell is in valid moves set
			if (iter != bpSet.end()) {
				movePiece();
			
				currentClick = FIRST;				//change turns, labels, etc.
				game->flipCurrentTurn();
				setAppropriateLabels();
			}
			//if 2nd selected cell is NOT in set of valid moves
			else {
				IChessPiece* possPiece = game->getPiece(bpAfter);
				//if selecting an empty square or square occupied by an enemy we cannot capture
				if (possPiece == NULL || (possPiece != NULL && possPiece->isEnemy(color))) {
					resetForSelect();
					currentClick = FIRST;
				}
				//if user decided to select a different piece to move
				else {
					newPieceSelected();
					currentClick = SECOND;
				}
			}
		}
	}
}

//do nothing
void HumanPlayer::on_TimerEvent() {
	return;
}

void HumanPlayer::highlightLegalMoves() {
	//highlight the square that piece is currently on/corresponding to board position object
	// color (3rd arg) defined in "ChessGuiDefines.h"
	view->HighlightSquare(bpBefore.getRow(), bpBefore.getColumn(), BLUE_SQUARE);
	
	bpSet = game->getLegalMoves(bpBefore);		//find set of board positions that the piece on
												// the current square/bpBefore can legally access
												
	//highlight each bp that can be accessed from current square
	std::set<BoardPosition>::const_iterator pos;	
	for (pos = bpSet.begin(); pos != bpSet.end(); ++pos)
		view->HighlightSquare(pos->getRow(), pos->getColumn(), GREEN_SQUARE);
}

void HumanPlayer::movePiece() {
	//update view (before model so we can use piece to on bpBefore to identify it's image
	view->ClearPiece(bpBefore.getRow(), bpBefore.getColumn());
	view->PlacePiece(bpAfter.getRow(), bpAfter.getColumn(), 
					 game->getPieceImageName(bpBefore));																			
	
	//update model
	Move mv = game->movePiece(bpBefore, bpAfter);
	
	//check if the piece just moved was a pawn and it reached the opposite end, promote if so
	//TODO check for free problems/backtrace
	//checkForPromotion();

	//clear highlights
	view->UnHighlightSquare(bpBefore.getRow(), bpBefore.getColumn());		//remove highlight
																			// from original square
	
	std::set<BoardPosition>::const_iterator pos;							//remove highlights on
	for (pos = bpSet.begin(); pos != bpSet.end(); ++pos)					// all possible squares
		view->UnHighlightSquare(pos->getRow(), pos->getColumn());
	
	//print move's string representation to message area
	view->WriteMessageArea(mv.toMessageString());
}

//user clicked on a non-highlighted square, (either empty or occupied by unreachable enemy)
// so let user pick a new piece (clear all highlighting)
void HumanPlayer::resetForSelect() {
	view->UnHighlightSquare(bpBefore.getRow(), bpBefore.getColumn());

	//unhighlight each bp that could have been accessed from current square
	std::set<BoardPosition>::const_iterator pos;
	for (pos = bpSet.begin(); pos != bpSet.end(); ++pos)
		view->UnHighlightSquare(pos->getRow(), pos->getColumn());
}

//do this if last player was a computer, we don't want to remove highlight of last
// move until human player starts, so we can see where it went
void HumanPlayer::unHighlightAll() {
	for (int i=0; i<8; ++i)
		for (int j=0; j<8; ++j)
			view->UnHighlightSquare(i,j);
}

//TODO CLEAN THIS UP
//user clicked on a non-highlighted square but on a cell occupied by piece of own side
// so let user pick a new piece (clear all highlighting)
void HumanPlayer::newPieceSelected() {
	view->UnHighlightSquare(bpBefore.getRow(), bpBefore.getColumn());			

	//unhighlight each bp that could have been accessed from current square
	std::set<BoardPosition>::const_iterator pos;
	for (pos = bpSet.begin(); pos != bpSet.end(); ++pos)
		view->UnHighlightSquare(pos->getRow(), pos->getColumn());
		
	view->HighlightSquare(bpAfter.getRow(), bpAfter.getColumn(), GREEN_SQUARE);
	
	bpBefore = BoardPosition(bpAfter.getRow(), bpAfter.getColumn());
	highlightLegalMoves();
}

bool HumanPlayer::isValidPiece() {
	if (game->getPiece(bpBefore) == NULL)		//if first cell_selected is empty, need to reset
		return false;
			
	if (game->getPiece(bpBefore)->isEnemy(color))	//if the selected piece isn't our color
		return false;
	else
		return true;
}
	
void HumanPlayer::setAppropriateLabels() {
	if (color == WHITE) {
		view->SetBottomLabel("");
		//the game will be in check if the current player just completed a move 
		// that put the opponent in check
		if (game->inCheck())
			view->SetTopLabel("Black's Turn. Black is currently in check!");
		else
			view->SetTopLabel("Black's Turn");
	}
	else {
		view->SetTopLabel("");
		if (game->inCheck())
			view->SetBottomLabel("White's Turn. White is currently in check!");
		else
			view->SetBottomLabel("White's Turn");
	}
	
	if (isCheckMate() || isStaleMate())
		endGame();
}

bool HumanPlayer::isCheckMate() {

	if (game->inCheck() && !game->movesRemain((color == WHITE) ? BLACK : WHITE))
		return true;
	return false;
}

bool HumanPlayer::isStaleMate() {
	if (!game->inCheck() && !game->movesRemain((color == WHITE) ? BLACK : WHITE))
		return true;
	return false;
}

void HumanPlayer::endGame() {
	
	view->SetBottomLabel("");
	view->SetTopLabel("");
	
	std::string title;
	std::string message;
	
	//if the game is in checkmate, that means that the current player did something to cause it,
	// so current player is winner
	if (isCheckMate()) {					
		if (color == WHITE)	{							//if current player (the winner)'s color
			view->SetBottomLabel("White Wins!");		//  is WHITE, put message on bottom
			message =  "Black is in check and cannot move.";
		}
		else {
			view->SetTopLabel("Black Wins!");
			message = "White is in check and cannot move.";
		}
		title ="Checkmate!";
	}
	//if current player did something that made next player have no turns and not be in check
	else {
		if (color == WHITE)	{				
			view->SetBottomLabel("No one wins!");
			message = "Black is not in check and cannot move.";
		}
		else {
			view->SetTopLabel("No one wins!");
			message = "White is not in check and cannot move.";
		}
		title = "Stalemate!";
	}
	
	message += " New game?";
	std::vector<std::string> labels;
	labels.resize(2);
	labels[0]="YES";
	labels[1]="NO";

	signed int selected = SelectDialog::SelectDialogRun(title,message,labels);
	switch (selected) {
		case 0:							//click the "x", let stuff stay on board
			break;
		case 1:
			controller->on_NewGame();	//click "YES"
			break;
		case 2:							//click "NO", quit (TODO: implement this)
			controller->on_QuitGame();
			break;
	}
}

void HumanPlayer::on_DragStart(int row, int col) {
	on_CellSelected(row, col, 0);
}

void HumanPlayer::on_DragEnd(int row, int col) {
	on_CellSelected(row, col, 0);
}

void HumanPlayer::resetCurrentClick() {
	currentClick = FIRST;
}

void HumanPlayer::checkForPromotion() {
	
	if (!game->canPromote(bpAfter))
		return;
	
	std::string title = "Pawn Promoted!";
	std::string message = "Select a new class for this brave Pawn!";
	std::vector<std::string> labels;
	labels.resize(4);
	labels[0]="KNIGHT";
	labels[1]="BISHOP";
	labels[2]="ROOK";
	labels[3]="QUEEN";

	signed int selected = SelectDialog::SelectDialogRun(title,message,labels);
	switch (selected) {
		case 0:							//click the "x", let stuff stay on board
			break;
		case 1:							//click "KNIGHT"
			game->promotePawn(KNIGHT, bpAfter, game->getMostRecentMove());
			break;
		case 2:							//click "BISHOP"
			game->promotePawn(BISHOP, bpAfter, game->getMostRecentMove());
			break;
		case 3:							//click "ROOK"
			game->promotePawn(ROOK, bpAfter, game->getMostRecentMove());
			break;
		case 4:							//click "QUEEN"
			game->promotePawn(QUEEN, bpAfter, game->getMostRecentMove());
			break;
	}

	view->PlacePiece(bpAfter.getRow(), bpAfter.getColumn(), 
					 game->getPieceImageName(bpAfter));
}

bool HumanPlayer::Test(std::ostream& os) {
	bool success = true;
	
	return success;
}
