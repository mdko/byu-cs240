#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include "HTMLTokenizer.h"
#include "HTMLToken.h"
#include <string>
#include "StringUtil.h"
#include "UnitTest.h"

using namespace std;
/*
 * HTMLParser.h
 * returns words and description in html page
 */
 
class HTMLParser{
	private:
	
		string wordsList[100000];		//stores all words parsed from this page's text (WAS TOO SMALL)
		string HREFLinks[10000];		//links parsed from this page's text
		int wordsCount;					//number of words encountered
		int linksCount;					//number of links encountered
		string description;				//description of page
		string wordsString;				//for testing purposes
		string linksString;				//for testing/comparisons purposes
		
		/*
		 * parses string containing all of the page's text
		 *  into words and links, adds them to respective arrays
		 *  finds page's description, stores it
		 *
		 * Parameters:
		 *  pageText--a string containing entire html page's characters
		 *
		 * Returns:
		 *  true if parsed (if not determine to be non-HTML), false otherwise
		 */
		bool parse (string* pageText);
		 
		 /*
		  * separates the token's string into words, add them to wordsList 
		  *
		  * Parameters:
		  *  textTokenString--string containing 0 or more words
		  *
		  * Returns:
		  *  nothing
		  */
		void separateIntoWords(string textTokenString);
		 
		 
		 /*
		  * determines page's description if not found in the
		  *  text following the title or first header by 
		  *  stringing together the first 100 characters in the
		  *  words of the wordsList[]
		  *
		  * we should only arrive here if the title and 1st header are empty,
		  *  so they won't be in the wordsList[] anyway
		  *
		  * Parameters:
		  *  none
		  *
		  * Returns:
		  *  nothing
		  */
		void calculateBodyDescription(string* s);
		 
		bool isWordCharacter(char c);
		
		void changeWordsToLower();
	public:
		/*
		 * constructor
		 *  calls parse() method
		 *
		 * Parameters:
		 *  pageText--a string containing entire html page's characters
		 */
		HTMLParser(string* pageText);
		
		/*
		 * destructor
		 */
		~HTMLParser();
		
		/*
		 * returns the wordsList[] array to add to wordIndex
		 *
		 * Parameters:
		 *  none
		 *
		 * Returns:
		 *  wordsList[] array containing all words found in pageText string
		 */
		string* getWordsArray();
		
		/*
		 * returns string of all words found, separated by one space
		 *  for testing/comparison purposes
		 *
		 * Parameters:
		 *  none
		 * 
		 * Returns:
		 *  a string containing all words found
		 */
		string getWordsString();
		
		/*
		 * returns the HREFLinks[] array to add to PageQueue
		 *
		 * Parameters:
		 *  none
		 *
		 * Returns:
		 *  HREFLinks[] array containing all links found in pageText string within
		 *   <a href> tags
		 */
		string* getLinksArray();
		
		/*
		 * returns string containing all links found, separated by one space
		 *
		 * Parameters:
		 *  none
		 *
		 * Returns:
		 *  a string with all HREF links found
		 */
		string getLinksString();
		
		/*
		 * returns page's description for use in creating Page objects
		 *
		 * Parameters:
		 *  none
		 *
		 * Returns:
		 *  description--string containing page's descriptions
		 */
		string getDescription();
		
		/*
		 * returns size of HREFLinks[] array
		 *
		 * Parameters:
		 *  none
		 *
		 * Returns:
		 *  linksCount--size of HREFLinks[] array
		 */
		int numLinks();
		
		/*
		 * returns size of wordsList[] array
		 *
		 * Parameters:
		 *  none
		 *
		 * Returns:
		 *  wordsCount--size of wordList[] array
		 */
		int numWords();
		 
		/*
		 * prints HREFLinks array to cout
		 */
		void printLinks();
		
		/*
		 * prints wordsList array to cout
		 */
		void printWords();
		
		/*
		 * A public method to test if separateIntoWords() method works
		 *  calls said method--for testing
		 */
		void sepWords(string s);
		
		static bool Test(ostream& os);

};

#endif
