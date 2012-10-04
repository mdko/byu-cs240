#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "IChessPlayer.h"
//#include "ChessGame.h"
#include "IChessView.h"
#include "BoardPosition.h"
#include "UnitTest.h"
#include "ModelDefines.h"
#include <assert.h>
#include <set>

///solves mutual dependencies problem
class IChessController;
class ChessGame;

class HumanPlayer : public IChessPlayer {
private:
	IChessView* view;
	
	ChessGame* game;
	
	IChessController* controller;
	
	Color color;
	
	Click currentClick;
	BoardPosition bpBefore;
	BoardPosition bpAfter;
	std::set<BoardPosition> bpSet;

	/**
	 * Highlights the starting position and ending position of a move on the gui board
	 */
	void highlightLegalMoves();
	
	/**
	 * Moves piece on the gui board and calls game's movePiece() method
	 */
	void movePiece();
	
	/**
	 * Unhighlights all squares on the gui board
	 * Use at beginning of turn so the previous turn's highlights are removed from gui board
	 */
	void unHighlightAll();
	
	/**
	 * If during second click, user selects a cell containing one of their pieces,
	 *  highlight this piece and its associated legal moves (user decided not to make a move)
	 */
	void newPieceSelected();
	
	/**
	 * On first cell_selected/first click, checks to see if the cell selected contains
	 *  a piece of the user's color
	 * @return true if the cell contains a piece of the user's color
	 */
	bool isValidPiece();
	
	/**
	 * Tells user whose turn it is via gui and informs of check/chessmate/stalemate
	 */
	void setAppropriateLabels();
	
	/**
	 * Checks to see if the game's status is in check and if opposing player
	 *  has no legal moves on next turn
	 * Called at end of turn
	 */
	bool isCheckMate();
	
	/**
	 * Checks to see if the game's status is not in check and if opposing player
	 *  has no legal moves on next turn
	 * Called at end of turn
	 */
	bool isStaleMate();
	
	/**
	 * User selected a cell that wasn't highlighted, or which was empty or containing
	 *  an unreachable enemy (didn't make a move)
	 */
	void resetForSelect();
	
	/**
	 * Tells user game has ended due to either checkmate or stalemate and asks user
	 *  if he wants to start a new game
	 * Called at end of turn by isCheckMate() and isStaleMate(), if those functions
	 *  are true
	 */
	void endGame();
	
	/**
	 * Checks to see if the piece just moved was a pawn and if it just reached the 
	 *  opposite end of the board. If so, prompts user for new piece and places piece
	 *  on board position
	 * @param position to check pawn for
	 */
	void checkForPromotion();
	
public:
	/**
	 * Four arg constructor
	 * @param ChessGame pointer
	 * @param IChessView pointer
	 * @param IChessController pointer
	 * @param Color object
	 */
	HumanPlayer(ChessGame* _game, IChessView* _view, IChessController* _control, Color _color);

	~HumanPlayer();

	/**
	 * Indicate to the player that the user clicked on the given
	 * row and column with the mouse.
	 */
	virtual void on_CellSelected(int row, int col, int button);

	/**
	 * Handle when the timeout duration has passed.
	 * -----NOT IMPLEMENTED FOR HUMAN-----
	 */
	virtual void on_TimerEvent();
	
	/**
	 * Starts a move (internally calls on_CellSelected() and follows that logic)
	 */
	virtual void on_DragStart(int row, int col);
	
	/**
	 * End a move, either placing piece, highlighting moves of friendly piece landed on,
	 *	or do nothing
	 */
	virtual void on_DragEnd(int row, int col);
	
	/**
	 * If save/load game called, need to reset selection for human players
	 */
	virtual void resetCurrentClick();
	
	static bool Test(std::ostream& os);
};

#endif
