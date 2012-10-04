#ifndef CHESS_CONTROLLER_H
#define CHESS_CONTROLLER_H

#include "IChessController.h"
#include "IChessView.h"
#include "IChessPlayer.h"
#include "ChessGame.h"
#include "ModelDefines.h"

class ChessController : public IChessController {
private:
	/*
	 * pointer to IChessView instance
	 */
	 IChessView* view;
	 
	 /*
	  * pointer to ChessGame instance (facade)
	  */
	 ChessGame* game;
	 
	 /*
	  * pointer to two IChessPlayer instances
	  */
	 IChessPlayer* playerWhite;
	 IChessPlayer* playerBlack;
	 
	 //used to stop computer movement if save/load dialog is open
	 bool onSaveLoadGame;
	 
	 //stores argument from command line
	 int playersSetting;
	 
	 //so we can know if when starting a new game, if there had been a previous game played
	 // and so we can know if we need to prompt to save the old game
	 bool firstGame;
	 
	 void clearAndRemoveHighlights();
	 
public:
	/*
	 * Constructor
	 */
	ChessController(int playersSetting);
	
	/**
	 * Destructor
	 */
	~ChessController();
	
	/*
	 * deletes the current game and objects associated with it
	 */
	void clear();
	
	/**
	 * Indicate to the player that the user clicked on the given
	 * row and column with the mouse.
	 */
	virtual void on_CellSelected(int row, int col, int button);
	
	///@param row where drag began
	///@param col where drag began
	virtual void on_DragStart(int row,int col);

	///@param row where drag ended
	///@param col where drag ended
	///@return true if the drag resulted in a successful drop
	virtual bool on_DragEnd(int row,int col);

	/**
	 * Handle when the user selected the new game button.
	 */
	virtual void on_NewGame();

	/**
	 * Handle when the user selected the save game button.
	 */
	virtual void on_SaveGame();

	/**
	 * Handle when the user selected the save game as button.
	 */
	virtual void on_SaveGameAs();

	/**
	 * Handle when the user selected the load game button.
	 */
	virtual void on_LoadGame();

	/**
	 * Handle when the user selected the undo move button.
	 */
	virtual void on_UndoMove();
		
	/**
	 * Handle when the user selects to quit the game, either through the
	 * quit button, the close X button, or the file menu.
	 */
	virtual void on_QuitGame();
		
	/**
	 * Handle when a timer event has been signaled.
	 */
	virtual void on_TimerEvent();
	
	/**
	 * Set the IChessView that this IChessController will handle inputs for.
	 */
	virtual void SetView(IChessView* view);
	
	/**
	 * Determines whether hh, hc, ch, or cc and creates both player objects
	 * @param commandline argument (0, 1, 2, or 3)
	 */
	void determinePlayers(int playersSetting);
	
	/**
	 * Similar to methods in player classes, but used for checking state of a file just loaded
	 * Checks to see if the game's status is in check and if opposing player
	 *  has no legal moves on next turn
	 * Called at end of turn
	 */
	bool isCheckMate();
	
	/**
	 * Similar to methods in player classes, but used for checking state of a file just loaded
	 * Checks to see if the game's status is not in check and if opposing player
	 *  has no legal moves on next turn
	 * Called at end of turn
	 */
	bool isStaleMate();
	
	/**
	 * Similar to methods in player classes, but used for checking state of a file just loaded
	 * Tells user game has ended due to either checkmate or stalemate and asks user
	 *  if he wants to start a new game
	 * Called at end of turn by isCheckMate() and isStaleMate(), if those functions
	 *  are true
	 */
	void endGame();
	
	/**
	 * Clears all images from gui board and puts all pieces in original places
	 */
	void initializeBoardImages();
};
#endif
