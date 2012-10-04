#ifndef MOVE_HISTORY_H
#define MOVE_HISTORY_H

#include "Move.h"
#include <iostream>
#include <vector>

class MoveHistory {
	private:
		//technically functioning/access like a stack, but implemented as a vector
		//	for iterable capability
		std::vector<Move> history;
		
	public:
		/**
		 * no-arg constructor
		 */
		MoveHistory();
		
		~MoveHistory();
		
		/**
		 * adds Move object to end of vector/history
		 * @param Move object to add
		 */
		void addMove(Move move);
		
		/**
		 * removes Move object from end of vector/history
		 * @return Move object at end
		 */
		Move getLastMove();
		
		Move& peekLastMove();
		
		/**
		 * @return a string representation of history, which calls each move's toString method,
		 *	for displaying in message bar
		 */
		std::string toMessageString();
		
		/**
		 * @return true if history vector is empty, used by undoMove() method elsewhere
		 */
		bool isEmpty();
		
		/**
		 * @return a string represenation of history in XML format, calls each move's XML method
		 */
		std::string getMovesXML();
		
		/**
		 * clears the history vector of all contents
		 */
		void resetHistory();
		
		static bool Test(std::ostream& os);
};

#endif
