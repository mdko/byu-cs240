#ifndef WORD_INDEX_H
#define WORD_INDEX_H

#include "Word.h"
#include "BST.h"
#include "URL.h"
#include "UnitTest.h"
#include "StopWords.h"	
#include <string>
#include <iostream>
using namespace std;
/*
 * WordIndex.h
 * a map of words to their respective OccurenceSet
 *  and methods to add and iterate over this map
 */
 
class WordIndex{
	private:
		BST<Word> wordSet;				//binary search tree containing all words encountered
										// --a map of words to their OccurenceSet
										// --each OccurenceSet contains a BST of occurences
										//ie a BST of Word objects, where each Word object 
										// contains an Occurence Set

		StopWords* stopWordsList;
		/*
		 * add the word to the WordIndex's BST (create a Word obj)
		 *  if word already there (determined via BST's find method),
		 *   create a new occurence in that word's occurence set
		 */
		void add(string word, URL url);
	
	public:
		/*
		 * no-arg constructor
		 */
		WordIndex(StopWords* sw);
		
		/*
		 * destructor
		 */
		~WordIndex();
		
		/*
		 * cycles through each word in wordsList, calls private add() method
		 */
		void addAll(string* wordsList, int size, URL url);
		
		/*
		 * for testing purposes
		 */
		Word getFirstWord();
		
		Word getWord(string s);
		
		/*
		 * returns size of wordSet bst
		 *  calls bst's getSize() method
		 */
		int size() const;
		
		void printIndex() const;
		
		/*
		 * iterates over each word in the index and 
		 *  calls that words own printXML method
		 *
		 * Parameters:
		 *  none
		 *
		 * Returns:
		 *  a string containing word's information in XML format
		 */
		string getXML();
		
		static bool Test(ostream& os);
};

#endif
