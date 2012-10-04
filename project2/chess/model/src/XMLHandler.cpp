//XMLHandler.cpp

#include "XMLHandler.h"
#include "UnitTest.h"
#include "StringUtil.h"
#include "BoardPosition.h"
#include "URLInputStream.h"
#include <cstdlib>
#include <iostream>

using namespace std;

XMLHandler::XMLHandler(ChessBoard* _board, MoveHistory* _history) {
	board = _board;
	history = _history;
}
		
XMLHandler::~XMLHandler() {

}

void XMLHandler::generateSaveFile(std::string newFile) {
	outFile.open(newFile.c_str());
	
	outFile << "<chessgame>\n";
	
	outFile << board->getCurrentXMLState();
	
	outFile << history->getMovesXML();
	
	outFile << "</chessgame>";
	outFile.close();
}

bool XMLHandler::loadFile(std::string loadFile) {
	
	string absoluteFile;
	
	//make sure file is absolute (in file:/ format for HTMLTokenizer to use)
	if (!StringUtil::IsPrefix(loadFile, "file:/"))
		absoluteFile = "file:/" + loadFile;
	else
		absoluteFile = loadFile;
	
	//initializes inputstream/tokenizer	
	URLInputStream file(absoluteFile);
	if (!file.IsOpen())
		return false;
		
	HTMLTokenizer tokenizer(&file);
	
	/*
	 *parse xml file
	 */
	bool insideHistory = false;
	
	HTMLToken newToken = tokenizer.GetNextToken();
	
	//skip to <board>...</board> until we reach <history>
	while (StringUtil::ToLowerCopy(newToken.GetValue()) != "history") {
		newToken = tokenizer.GetNextToken();
	}
	
	//fill up moves from <history>'s children tags
	while (tokenizer.HasNextToken()) {
		newToken = tokenizer.GetNextToken();
		
		if (StringUtil::ToLowerCopy(newToken.GetValue()) == "move" && 
									newToken.GetType() == TAG_START) {
			parseMove(tokenizer);
		}
	}
	
	return true;
}

//get two or three piece children tags to add to new move
void XMLHandler::parseMove(HTMLTokenizer& tokenizer) {
	
	bool bpBeforeFound = false;
	bool bpAfterFound = false;
	
	BoardPosition bpBefore;
	BoardPosition bpAfter;
	
	//get token right after opening <move> tag
	HTMLToken newToken = tokenizer.GetNextToken();
	
	while (StringUtil::ToLowerCopy(newToken.GetValue()) != "move" 
			&& newToken.GetType() != TAG_END) {
		
		if (StringUtil::ToLowerCopy(newToken.GetValue()) == "piece" && !bpBeforeFound) {
			bpBefore = BoardPosition(atoi((newToken.GetAttribute("row")).c_str()),
										   atoi((newToken.GetAttribute("column")).c_str()));
			bpBeforeFound = true;
		}
		else if (StringUtil::ToLowerCopy(newToken.GetValue()) == "piece" && !bpAfterFound) {
			bpAfter = BoardPosition(atoi((newToken.GetAttribute("row")).c_str()),
										  atoi((newToken.GetAttribute("column")).c_str()));
			bpAfterFound = true;
		}
		//don't account for captured piece, since when making real moves this will be accounted for
		
		newToken = tokenizer.GetNextToken();
	}
		
	Move newMove(NULL, bpBefore, bpAfter);
	
	moveSet.push_back(newMove);
}

vector<Move> XMLHandler::getPsuedoMovesSet() {
	return moveSet;
}

void XMLHandler::reset() {
	moveSet.clear();
}

bool XMLHandler::Test(std::ostream& os) {
	bool success = true;
	
	XMLHandler handler(NULL, NULL);
	
	//to easily see if file is being parsed correctly
	handler.loadFile("home/michael/Desktop/fewmoves.xml");
	
	return success;
}
