#ifndef OUTPUT_GENERATOR_H
#define OUTPUT_GENERATOR_H

#include "PageHistory.h"
#include "Page.h"
#include "WordIndex.h"
#include "Word.h"
#include "URL.h"
#include <iostream>
#include <fstream>
#include "StringUtil.h"
using namespace std;
/*
 * OutputGenerator.h
 * emits XML output
 */
 
class OutputGenerator{
	private:
		ofstream outFile;				//the file we're writing to
		URL url;
		
		/*
		 * generates the <page></page> part of the XML file
		 *
		 * Parameters:
		 *  pageHistory--
		 *   a pointer to the PageHistory object created and populated in main()
		 *
		 * Returns:
		 *  nothing		 
		 */
		void generateHistory(PageHistory* pageHistory);
		
		/*
		 * generates the <index></index> part of the XML file
		 *
		 * Parameters:
		 *  index--
		 *   the WordIndex object created and populated via main()
		 * 
		 * Returns:
		 *  nothing
		 */
		 void generateWords(WordIndex* index);
		 
	public:
		/*
		 * three-arg constructor
		 *
		 * Parameters:
		 *	file--file to write output to
		 *
		 *  stopwords--a StopWords object containing an array of stopwords 
		 *   to iterate over when outputting XML
		 *
		 *  startURL--the URL object containing address of start page
		 */
		OutputGenerator(char* file, URL& startURL);
		
		/*
		 * destructor
		 */
		~OutputGenerator();
		 
		/*
		 * generates the XML output
		 *  calls generateHistory(), generateWords()
		 *
		 * Parameters:
		 *  none
		 *
		 * Returns:
		 *  nothing
		 */
		void generate(PageHistory* pageHistory, WordIndex* index);

};

#endif
