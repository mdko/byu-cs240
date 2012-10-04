//webcrawler.cpp
#include <iostream>
#include <exception>
#include "BST.h"
//#include "Word.h"
#include "PageHistory.h"
#include "PageQueue.h"
#include "Page.h"
#include "LinkedList.h"
#include "URL.h"
#include "URLFilter.h"
#include "PageDownloader.h"
#include "CS240Exception.h"
#include "HTMLParser.h"
#include "WordIndex.h"
#include "StopWords.h"
#include "OutputGenerator.h"
using namespace std;

int main(int argc, char* argv[]) {

	try {
		//validate number of arguments
		if (argc != 4) {
			cout << "USAGE: too few arguments" << endl;
			return 1;
		}
	
		PageQueue pageQueue;
		PageDownloader pageDownloader;
		PageHistory pageHistory;
		StopWords stopWords(argv[3]);
		
		WordIndex index(&stopWords);
	
		char* startURLString = argv[1];
		URL startURL(startURLString);
	
		URLFilter filter(startURL);
	
		pageQueue.enqueue(startURL);				//HOLDS COPIES
		string* pageText = NULL;
		do {
			try {
				URL currURL = pageQueue.dequeue();		//MAKES A COPY
				if (!pageHistory.contains(currURL)) {
				
					//cout << "CURRENT URL: " << currURL.getURL() << endl;
				
					//DO WE NEED TO VALIDATE FIRST URL?
					if (!filter.isValidURL(currURL)) {		//PASSES REFERENCE
						cout << "BAD URL: " << currURL.getURL() << endl;
						break;
					}
		
					//a pointer to the string object created on heap in pageDownloader
			
					/* string* */ pageText = pageDownloader.download(currURL);	
			
					HTMLParser parser(pageText);
			
					//parser.getWords returns array of words
					index.addAll(parser.getWordsArray(), parser.numWords(), currURL);	
			
					for (int i = 0; i < parser.numLinks(); ++i) {
					
						string baseURL(currURL.getURL());								
						string relURL(parser.getLinksArray()[i]);
					
						URL resolvedURL(baseURL, relURL);
				
						if (filter.isValidURL(resolvedURL) && !pageHistory.contains(resolvedURL)) {
							pageQueue.enqueue(resolvedURL);
						}
					}				
					
					delete pageText;
					pageText = NULL;
					
					Page newPage(currURL, parser.getDescription());
					pageHistory.add(newPage);
				}
			
			}
			catch (CS240Exception &e) {
				if (pageText != NULL) {
					delete pageText;
					pageText = NULL;
				}
			}
		}
		while (!pageQueue.isEmpty());
		
		
		/* if (pageText != NULL) {
			delete pageText;
			pageText = NULL;
		} */
		
		OutputGenerator xmlGenerator(argv[2], startURL);
		xmlGenerator.generate(&pageHistory, &index);
		
	}
	catch (exception &e) {
		cout << "Exception Occurred: " << e.what() << endl;
	}
	catch (CS240Exception &e) {
		cout << "Exception Occurred: " << e.GetMessage() << endl;
	}
	catch (...) {
		cout << "Unknown Exception Occurred" << endl;
	}
	return 0;
}
