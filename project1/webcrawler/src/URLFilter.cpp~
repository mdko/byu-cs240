//URLFilter.cpp
#include "URLFilter.h"
#include "StringUtil.h"
#include <string>
#include <iostream>
using namespace std;


//NEED TO CHECK FOR CAPITALIZATION ISSUES WHEN COMPARING
//private:

//check for
// 1: <path> ends with "/" OR
// 2: <path> ends with no file extensions OR
// 3: ends in .html, .htm, etc... (see URLFilter.h), ignores query and fragment
bool URLFilter::isHTML(URL& currURL) {
	bool one, two, three;				//see above for def. of 1, 2, 3
	one = (currURL.getURL().at(currURL.getURL().length()-1) == '/');
	two = (hasNoExtension(currURL.getURL()));
	three = (hasCorrectSuffix(currURL.getURL()));
	
	return (one || two || three);
	/*return (currURL.getURL().at(currURL.getURL().length()-1) == '/' ||	//check [1]
			hasCorrectSuffix(currURL.getURL()) ||						//check [3]
			hasNoExtension(currURL.getURL()));							//check [2]*/
}

//compare prefixes up to directory above page name of startURL
// e.g. in "http://cs-online.cs.byu.edu/cs240/default.htm",
// "http://cs-online.cs.byu.edu/cs240/" is the prefix
bool URLFilter::inScope(URL& currURL) {
	return (StringUtil::IsPrefix(StringUtil::ToLowerCopy(currURL.getURL()), basePrefix)); 
}

bool URLFilter::hasCorrectSuffix(string s) {		//why doesn't string& s as parameter work? why copy necessary here?
	
	string noFrag = s.substr(0, s.find("#"));	
	string noQuery = noFrag.substr(0, s.find("?"));					//if a query present, get everything before it; if not present, normal string
													//no +1 because don't want to include "#" in string to be evaluated
	//string value = noFrag;
	string value = noQuery;
	return
		( (StringUtil::IsSuffix(value, ".html"))	||
		  (StringUtil::IsSuffix(value, ".htm"))	||
		  (StringUtil::IsSuffix(value, ".shtml"))	||
		  (StringUtil::IsSuffix(value, ".cgi"))	||
		  (StringUtil::IsSuffix(value, ".jsp"))	||
		  (StringUtil::IsSuffix(value, ".asp"))	||
		  (StringUtil::IsSuffix(value, ".aspx"))	||
		  (StringUtil::IsSuffix(value, ".php"))	||
		  (StringUtil::IsSuffix(value, ".pl"))		||
		  (StringUtil::IsSuffix(value, ".cfm")) );
}

bool URLFilter::hasNoExtension(string s) {
	int thirdSlash = s.find_first_of("/", 7);		//starts searching for third "/" at 7th character
	
	if (thirdSlash == -1)							//if URL is just "http://www.google.com" with no "/" after net location
		return true;
		
	int lastSlashPos = s.find_last_of("/");	
	
	if (s.find(".",lastSlashPos) == -1)				//check to see if there is a "." after the last slash
		return true;								//if not found (-1), we're good
	else
		return false;
	
}

//public:

//constructor, determines baseURL prefix for comparisons
URLFilter::URLFilter(URL& baseURL) : startURL(baseURL) {
	int prefPos = startURL.getURL().find_last_of("/");
	basePrefix = startURL.getURL().substr(0, prefPos+1);			//+1 because right-hand bound is non-inclusive, lhbound is inclusive
	
	//cout << basePrefix << endl;
}

URLFilter::~URLFilter() {
}

bool URLFilter::isValidURL(URL& currURL) {
	return (isHTML(currURL) && inScope(currURL));
}

bool URLFilter::Test(ostream& os) {
	bool success = true;
	
	URL urlBase("http://cs-online.cs.byu.edu/cs240/default.htm");
	URLFilter filter(urlBase);
	
	URL url1("http://cs-online.cs.byu.edu/cs240/mike");
	TEST(filter.isValidURL(url1));
	
	URL url2("http://cs-online.cs.byu.edu/cs235/joe");
	TEST(!filter.isValidURL(url2));
	
	URL url3("http://cs-online.cs.byu.edu/cs240/joe.js");
	TEST(!filter.isValidURL(url3));
	
	URL url4("http://www.google.com");
	TEST(!filter.isValidURL(url4));
	
	URL url5("http://cs-online.cs.byu.edu/cs240/hello#STUFF");
	TEST(filter.isValidURL(url5));
	
	URL url6("http://cs-online.cs.byu.edu/cs235/hello#STUFF");
	TEST(!filter.isValidURL(url6));
	
	//URL url7("http://cs-online.cs.byu.edu/cs240/mamamia.htm#STUFF");
	//TEST(filter.isValidURL(url7));
	
	URL url8("http://cs-online.cs.byu.edu/cs240/mama.shtm");
	TEST(!filter.isValidURL(url8));
	
	//URL url9("http://cs-online.cs.byu.edu/cs240/yo.html?name=joe&age=12");
	//TEST(filter.isValidURL(url9));
	
	//URL url10("http://cs-online.cs.byu.edu/cs240/yo.jv?name=joe&age=12");
	//TEST(!filter.isValidURL(url10));
	
	return success;
}
