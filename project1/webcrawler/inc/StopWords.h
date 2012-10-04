#ifndef STOP_WORDS_H
#define STOP_WORDS_H

#include <string>
#include <fstream>				//need to review which one to include
#include <iostream>
#include <algorithm>
#include "UnitTest.h"
using namespace std;
/*
 * StopWords.h
 * the list of stopwords,
 *  methods to search list for specific words
 */
 
class StopWords{
	private:
		/* smarter way to do this?
		 */
		string/* * */ wordArray[200000];		// array of words(strings)
		int wordCount;
		
		static int wordCompare(const void* ap, const void* bp);
		
	public:
	
		/*
		 * one-arg constructor
		 *  opens and stores contents of file via addWord() method
		 *
		 * Parameters:
		 *  file--pointer to file containing ordered list of stopWords
		 *  (from argv[] in main)
		 */
		StopWords(char* file);
		
		StopWords();
		
		/*
		 * destructor
		 */
		~StopWords();
		
		/*
		 * traverses array via binary search to determine
		 *  if the passed-in word is a stop word
		 *
		 * Parameters:
		 *  word -- string to be searched for in wordArray
		 *
		 * Returns:
		 *  true if word is found, false otherwise
		 */
		bool isStopWord(string word);
		
		void addWord(string& s);
		
		void printWords();
		
		static bool Test(ostream& os);
		
};

#endif
