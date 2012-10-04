#ifndef BISHOP_H
#define BISHOP_H

#include "IChessPiece.h"
#include <iostream>

class Bishop : public IChessPiece {
	private:
	
	public:
		/**
		 * two-arg constructor
		 * @param enumerated color of piece(BLACK or WHITE)
		 * @param enumerated direction of piece (UP or DOWN)
		 */
		Bishop(Color c, Direction d);
		
		~Bishop();
		
		/**
		 * @param pointer to board containing pieces
		 * @param position of this piece on  board
		 * @return set of all possible legal moves(BoardPositions) for this piece, barring check
		 */
		std::set<BoardPosition> getCandidateMoves(ChessBoard* board, BoardPosition pos);
		
		/**
		 * @return string representation of type enumeration ("pawn", "king", etc.)
		 */
		std::string getTypeString();
		
		/**
		 * @return enumeration of the ImageName (found in ChessGuiDefines), 
		 *  used by controller towards view to set images on gui
		 */
		ImageName getImageName();
		
		/**
		 * empty (only used by pawns)
		 */
		void firstTurnDone();
		
		/**
		 * empty (only used by pawns)
		 */
		void firstTurnUnDone();
		
		/**
		 * @param row position of piece
		 * @param column position of piece
		 * @return XML representation of the piece based on its passed in position
		 */
		std::string getXMLInfo(int row, int column);

		static bool Test(std::ostream& os);
};

#endif
