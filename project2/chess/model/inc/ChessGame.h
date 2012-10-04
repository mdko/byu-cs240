#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "BoardPosition.h"
#include "ChessBoard.h"
#include "ModelDefines.h"
#include "IChessPiece.h"
#include "Pawn.h"
#include "MoveHistory.h"
#include "Move.h"
//#include "XMLHandler.h"
#include <set>
#include <iostream>
#include <string>
class XMLHandler;

///This class serves as the facade between the controller and the model
class ChessGame {
	private:
		ChessBoard* board;
		MoveHistory* history;
		XMLHandler* xmlHandler;
		
		///enumerated color representing whose turn it currently is
		Color currentTurn;
		//records whether someone in the game is currently in check
		bool check;
		///records whether this game has been saved or not, if not, create new save file
		bool gameSaved;
		///if a move has been done, this is set to false until right after game is saved
		bool recentSave;
		///name of this game's save file
		std::string gameName;
	
	public:
		/**
		 * no-arg constructor
		 */
		ChessGame();
		
		~ChessGame();
		
		/**
		 * determines the set of legal moves of the piece on the current position (pos)
		 *  part of the heat of the move-finding algorithm
		 * @param position of piece of which to search its legal moves
		 * @return a copy of set of legal board positions for the piece on the passed in position
		 */
		std::set<BoardPosition> getLegalMoves(BoardPosition pos);
		
		/**
		 * @return state of currentTurn bool (WHITE or BLACK)
		 */
		Color getCurrentTurn();
		
		/**
		 * switches the current turn (from WHITE to BLACK, or vice versa)
		 */
		void flipCurrentTurn();
		
		/**
		 * moves the piece from "before" to "after",
		 *  creates a Move object, and adds it to moveHistory
		 * @param starting position of piece
		 * @param ending position of piece
		 */
		Move movePiece(BoardPosition before, BoardPosition after);
		
		/**
		 * saves the current state of game using XMLHandler to already-defined file
		 *	assigned to "gameName" variable
		 */
		void saveGame();
		
		/**
		 * saves the current state of game using XMLHandler to a new file
		 * @param name of file to create and save to
		 */
		void saveGameAs(std::string stringFile);
		
		/**
		 * opens a game, calls XMLHandler to parse contents,
		 *  then moves pieces to correct positions according to history in XML file
		 * @param name of file to parse
		 * @param true if able to load game
		 */
		bool loadGame(std::string loadFile);
		
		/**
		 * reset/reinitialize game
		 */
		void startNewGame();
		
		/**
		 * @param position of piece on board to get ImageName for
		 * @return enumerated ImageName (defined in ChessGuiDefines)
		 */
		ImageName getPieceImageName(BoardPosition bp);
		
		/**
		 * @param position of piece on board to get pointer for
		 * @return pointer to piece at position
		 */
		IChessPiece* getPiece(BoardPosition bp);
		
		
		/**
		 * filters set of the possible moves for the piece at this position,
		 *	 only adding moves that don't cause you to put yourself in check to set of legal moves
		 * @param position of piece to find moves for
		 * @param set of this piece's possible moves (contains self-checking board positions)
		 * @param set of this peice's legal moves (contains no self-checking board positions)
		 */
		void determineLegalMoves(BoardPosition piecePos, std::set<BoardPosition>& bpSetPossible,
								 std::set<BoardPosition>& bpSetLegal);
		
		/**
		 * determines if the team of this color has any more legal moves
		 *  (used for calculating checkmate/stalemate)
		 * @param color of team to check for
		 * @return true if there remains at least one legal move 
		 *	by one remaining piece on this team
		 */
		bool movesRemain(Color c);
		
		/**
		 * @return status of check bool, true if one player is in check
		 */
		bool inCheck();
		
		/**
		 * Finds a random position containing a piece of color c to start on, 
		 *	used by computer player
		 * @param color of pieces that can be considered
		 * @return position of the piece of that friendly color
		 */
		BoardPosition getRandomStartPosition(Color c);
		
		/**
		 * Calculates a random position that the piece determined by 
		 *	getRandomStartPosition can land on, used by computer player
		 * @param start position of piece to move
		 * @return end position where piece will move
		 */
		BoardPosition getRandomEndPosition(BoardPosition pos);
		
		/**
		 * removes last move from history, undoes move on board and replaces any captured piece
		 * @return last move from history
		 */
		Move undoMove();
		
		/**
		 * @return string representation of move history
		 */
		std::string getMoveHistory();
		
		/**
		 * @return true if history contains no moves (so currently on first move and
		 *	cannot undo any more)
		 */
		bool historyIsEmpty();
		
		/**
		 * @return true if the game hasn't had any moves since the last save
		 */
		bool isRecentlySaved();
		
		/**
		 * @return true if the current game has been saved (status of gameSaved bool)
		 */
		bool isSaved();
		
		/**
		 * sets the name of the gameName file
		 * @param name of file to save the current game in
		 */
		void setGameName(std::string name);
		
		/**
		 * @return the gameName file
		 */
		std::string getGameName();
		
		/**
		 * resets turns for when file is loaded, as if new game had started, so then
		 *	file's moves are presented correctly
		 */
		void resetTurns();
		
		void promotePawn(PieceType type, BoardPosition bp, Move& move);
		
		bool canPromote(BoardPosition bp);
		
		Move& getMostRecentMove();
		
		static bool Test(std::ostream& os);
};

#endif
