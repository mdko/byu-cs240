#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "BoardPosition.h"
#include "Move.h"
#include "ModelDefines.h"
#include <string>
#include <stack>

//forward declaration to prevent circular dependencies
class IChessPiece;

class ChessBoard {
	private:
		//2-d array of chesspiece pointers, represents chessboard
		IChessPiece* board[8][8];
		
		//pointer to all 32 chesspieces
		IChessPiece* wKing;
		IChessPiece* wQueen;
		IChessPiece* wRook1;
		IChessPiece* wRook2;
		IChessPiece* wBishop1;
		IChessPiece* wBishop2;
		IChessPiece* wKnight1;
		IChessPiece* wKnight2;
		IChessPiece* wPawn1;
		IChessPiece* wPawn2;
		IChessPiece* wPawn3;
		IChessPiece* wPawn4;
		IChessPiece* wPawn5;
		IChessPiece* wPawn6;
		IChessPiece* wPawn7;
		IChessPiece* wPawn8;

		IChessPiece* bKing;
		IChessPiece* bQueen;
		IChessPiece* bRook1;
		IChessPiece* bRook2;
		IChessPiece* bBishop1;
		IChessPiece* bBishop2;
		IChessPiece* bKnight1;
		IChessPiece* bKnight2;
		IChessPiece* bPawn1;
		IChessPiece* bPawn2;
		IChessPiece* bPawn3;
		IChessPiece* bPawn4;
		IChessPiece* bPawn5;
		IChessPiece* bPawn6;
		IChessPiece* bPawn7;
		IChessPiece* bPawn8;
		
		std::stack<IChessPiece*> promotedPieces;
		
	public:
		/**
		 * no-arg constructor
		 */
		ChessBoard();
		
		~ChessBoard();
		
		/**
		 * deletes all piece objects from heap, sets pointer to NULL
		 */
		void clear();
		
		/**
		 * creates all 32 piece objects, places them in correct starting position of board array
		 */
		void initializeBoard();
		
		/**
		 * sets every element in board array to NULL, then places test piece on position
		 * for TEST
		 */
		void initializeBlankTestBoard(IChessPiece* piece, int row, int col);
		
		/**
		 * sets every element in board array to NULL, then places test piece on position and
		 *	places a white pawn at 2, 2
		 * for TESTing candidate moves excluding friendly squares
		 */
		void initializeTwoTwoBoard(IChessPiece* piece, int row, int col);
		
		/**
		 * returns a Move object to be inserted into MoveHistory container
		 *  by calling method
		 */
		Move movePiece(BoardPosition before, BoardPosition after);
		
		/**
		 * moves the piece from before position to after position, checking to see if if doing 
		 *	so will cause your own piece to be in check
		 * @param starting position of piece
		 * @param hypothetical ending position of piece
		 * @return true if moving the piece from "before" to "after" won't result in the piece's
		 *	king being put in check (if you don't put yourself in check)
		 */
		bool moveHypotheticalPiece(BoardPosition& before, BoardPosition& after);
		
		/**
		 * @param position of piece on board to retrieve
		 * @returns a pointer to the piece at this position
		 */
		IChessPiece* getPiece(BoardPosition bp);
		
		/**
		 * determines if the king of the piece on this position can be captured
		 *	by any other enemy piece
		 * @param position of friendly piece whose king to search for
		 * @return true if king can be captured
		 */
		bool kingInCheck(BoardPosition bp);
		
		/**
		 * determines if the opposing king of the piece on this position can be captured
		 *	by any piece of this piece's team
		 * @param position of piece whose enemy king to search for
		 * @return true if enemy king can be captured
		 */
		bool enemyKingInCheck(BoardPosition bp);
		
		/**
		 * gets a random piece present on board, used by computer in selecting a move
		 * @param color of team (WHITE or BLACK)
		 * @return board position of random piece of the given color
		 */
		BoardPosition getRandomPosition(Color c);
		
		/**
		 * assign piece pointer in array at bp position to this piece object
		 * used by ChessGame.undoMove() to replace captured piece if necessary
		 * @param pointer to chesspiece to place
		 * @param position in board array to place piece
		 */
		void placePiece(IChessPiece* piece, BoardPosition bp);
		
		/**
		 * @return string representation of XML state of board
		 *  (calls each piece's toXMLInfo method to build string)
		 */
		std::string getCurrentXMLState();
		
		bool canPromotePawn(BoardPosition bp);
		
		void promotePawn(PieceType type, BoardPosition bp);
		
		IChessPiece* popLastPromotion();
		
		static bool Test(std::ostream& os);
};

#endif
