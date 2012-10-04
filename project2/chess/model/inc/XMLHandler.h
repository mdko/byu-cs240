#ifndef XML_HANDLER_H
#define XML_HANDLER_H

#include "ChessBoard.h"
#include "MoveHistory.h"
#include "Move.h"
#include "HTMLToken.h"
#include "HTMLTokenizer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class XMLHandler {
	private:
		///the outfile to write to
		std::ofstream outFile;				
		ChessBoard* board;
		MoveHistory* history;
		std::vector<Move> moveSet;
		
		/**
		 * parses moves from within <history> tags, addss them to moveSet
		 * @param tokenizer containing inputstream, created in calling function
		 */
		void parseMove(HTMLTokenizer& tokenizer);
		
	public:
		/**
		 * two-arg constructor
		 * @param pointer to board containing piece pointers and their respective positions
		 *	 for creating <board>...</board> section
		 * @param pointer to history containing set of moves
		 *	 for creating <history<...</history> section
		 */
		XMLHandler(ChessBoard* _board, MoveHistory* _history);
		
		~XMLHandler();
		
		/**
		 * creates the save file in XML format, calls related methods in board and history
		 * @param name of file to write to
		 */
		void generateSaveFile(std::string newFile);
		
		/**
		 * downloads file into tokenizer, parses file and adds psuedo-moves to moveSet
		 *	via parseMove()
		 * @param name of file to load
		 * @return true if able to load/find file
		 */
		bool loadFile(std::string loadFile);
		
		/**
		 * @return set of move objects to be used in recreating game and creating game's
		 *	real history set
		 */
		vector<Move> getPsuedoMovesSet();
		
		/**
		 * clears the moveSet of contents, so we can load a new file with a fresh set of moves
		 */
		void reset();
		
		static bool Test(std::ostream& os);
		
};

#endif
