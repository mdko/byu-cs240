//PageDownloader.cpp

#include "PageDownloader.h"
#include "UnitTest.h"
#include <iostream>
using namespace std;

/*
 * NEED TO MAKE SURE DELETING STRING* AFTER USE, SOMEWHERE
 */

//public
/*
 * no-arg constructor
 */
PageDownloader::PageDownloader() {
}
 
/*
 * destructor
 */
PageDownloader::~PageDownloader() {
}

/*
 * downloads a webpage, stores it in a string
 *  to be used by HTML parser
 *  (opens a stream with url)
 *
 * Parameters:
 *  url--URL object containing the resolved URL
 *
 * Returns:
 *  a string containing the entire contents of webpage
 */
string* PageDownloader::download(URL& url) {

	pageText = new string("");
	
	URLInputStream stream(url.getURL());
	
	putContentsToString(stream);
	
	return pageText;
}

bool PageDownloader::Test(ostream& os) {
	
	bool success = true;
	
	//COMMENTED OUT FOR LACK OF INTERNET CONNECTION
	/*PageDownloader downloader;
	URL url1("http://students.cs.byu.edu/~cs240ta/crawler_tests/crawlindex.html");
	string* s = downloader.download(url1);
	
	delete s;*/	
	
	/*PageDownloader downloader;
	URL url1("http://lightplanet.com/mormons/people/joseph_smith/prophesies.html");
	string* s = downloader.download(url1);
	
	cout << *s << endl;
	
	delete s;*/
	
	return success;
	
}
