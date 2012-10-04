#ifndef BOARD_POSITION_H
#define BOARD_POSITION_H

#include <iostream>
#include <string>

class BoardPosition {
	private:
		int row;
		int column;
	
	public:
		/**
		 * two arg constructor
		 * @param row position of the this object
		 * @param column position of this object
		 */
		BoardPosition(int _row, int _col);
		
		/**
		 * empty constructor, used for creating pseudo moves when recreating history on load game
		 */
		BoardPosition();
		
		~BoardPosition();
		
		/**
		 * copy constructor
		 */
		BoardPosition(const BoardPosition& other);
		
		/**
		 * assignment operator
		 */
		BoardPosition& operator =(const BoardPosition& other);
		
		/**
		 * less-than operator
		 */
		bool operator <(const BoardPosition& other) const;
		
		/**
		 * equality operator
		 */
		bool operator ==(const BoardPosition& other) const;
		
		/**
		 * @return row position of this object
		 */
		int getRow() const;
		
		/**
		 * @return column position of this object
		 */
		int getColumn() const;
		
		/**
		 * sets the row position of this object (used primarily when a no-arg object is created)
		 */
		void setRow(int r);
		
		/**
		 * set the column position of this object (used when a no-arg object is created)
		 */
		void setColumn(int c);
		
		/**
		 * decrements row (up on the gui board)
		 * @return true if able to move up the board, false if tried to go past top edge of board
		 */
		bool moveUp();
		
		/**
		 * decrements row, increments column (up-right on gui board)
		 * @return true if able to move up-right the board,
		 *  false if tried to go past top or right edge of board
		 */
		bool moveUpRight();
		
		/**
		 * increments column (right on gui board)
		 * @return true if able to move right on board, 
		 *  false if tried to go past right edge of board
		 */
		bool moveRight();
		
		/**
		 * increments row, increments column (down-right on gui board)
		 * @return true if able to move up-right on the board,
		 *  false if tried to go past bottom or right edge of board
		 */
		bool moveDownRight();
		
		/**
		 * increments row (down on gui board)
		 * @return true if able to move down on the board,
		 *	false if tried to go past bottom edge of board
		 */
		bool moveDown();
		
		/**
		 * increments row, decrements column (down-left on gui board)
		 * @return true if able to move down-left on the board,
		 *	false if tried to go past bottom or left edge of board
		 */
		bool moveDownLeft();
		
		/**
		 * decrements column (left on gui board)
		 * @return true if able to move left on board, false if tried to go past left edge of board
		 */
		bool moveLeft();
		
		/**
		 * decrements row, decrements column (up-left on gui board)
		 * @return true if able to move up-left on board,
		 *  false if tried to go past top or left edge of board
		 */
		bool moveUpLeft();
		
		/**
		 * prints representation of object (row, col) to std::cout
		 */
		void print() const;
		
		static bool Test(std::ostream& os);
};

#endif
