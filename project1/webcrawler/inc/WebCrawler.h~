#ifndef WEB_CRAWLER_H
#define WEB_CRAWLER_H

#include <iostream>
#include "PageHistory.h"
#include "PageQueue.h"
#include "PageDownloader.h"
#include "Page.h"
#include "WordIndex.h"
#include "URLFilter.h"
#include "URL.h"
#include "StopWords.h"
using namespace std;

/*
 * WebCrawler.h
 * create a word index for a website
 * (drives overall crawling process)
 */

int main(int argc, char* argv[]) {
	
	PageHistory pageHistory;
	PageQueue pageQueue;
	PageDownloader pageDownloader;
	WordIndex wordIndex;
	
	//validate number of arguments
	if (argc < 4) {										
		cout << "USAGE: too few arguments" << endl;
		return 1;
	}
	
	char* startURL = argv[1];
	
	
	//create first URL object from startURL
	// no need to validate first URL with URLFilter
	URL firstURL = new URL(startURL);
	Page firstPage = new Page(firstURL);
	PageQueue.enqueue(firstPage);
	
	//create URL object with baseURL as param so we an determine if
	// later URLs are in scope
	URLFilter urlFilter(firstURL);
	
	do {
		//Select a page that has not yet been indexed
		Page currPage = PageQueue.dequeue();
		URL currentURL = currPage.getURL();
		
		//if encountered invalid HTML, get next page from queue		
		if (!urlFilter.isURL(currentURL))
			break;	
		
		//download page into a string
		String pageText = pageDownloader.download(currentURL);
		
		//parse all text areas in page into words
		//parse all URLS in <A> tags with HREF attributes
		HTMLParser parser = new Parser(pageText);
		
		//add pageText's words to wordIndex
		wordIndex.addAll(parser.getWords(), currentURL);
		
		//resolve each URL parsed from the CurrentPage
		//URLFilter class determines if HTML and in scope before adding to queue
		String[] linksArray = parser.getLinks();
		for (int i = 0; i < parser.numLinks(); i++) { 
			URL resolvedURL = new URL(currentURL, linksArray[i]);
			if (urlFilter.isValidURL(resolvedURL);
				pageQueue.add(new Page(resolvedURL));
		}
		
		//update current page object and add its parsed description, add to PageHistory
		//(Save summary information for the page)
		currPage.addDescription(parser.getDescription);
		pageHistory.add(currPage);
		
	}
	while (!PageQueue.isEmpty()); 							//repeat until no pages left to index
	
	//create stopWord array
	StopWords stopWordList = new StopWords(argv[3]);
	
	//output wordIndex into XML form, 
	// don't add word if found in StopWords array
	// we're checking stopwords here so we can check in groups
	OutputGenerator xmlGenerator(argv[2], stopWordsList, startURL);
	xmlGenerator.generate(pageHistory, wordIndex);
	
}
#endif
