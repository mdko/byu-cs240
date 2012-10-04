#ifndef URL_FILTER_H
#define URL_FILTER_H

#include "URL.h"
#include "UnitTest.h"

/*
 * URLFilter.h
 * distinguishes between HTML and non-HTML links
 *  (determines if url is valid and in-scope)
 */
 
class URLFilter{
	
	private:
	
		URL startURL;					//URL object containing initial URL passed in via argv[1]--or should be URL&?
		string basePrefix;
		/*
		 * ensures url is HTML by seeing if any of the following conditions hold:
		 *  --<path> part is a directory name (ends with "/")
		 *  --file name in URL's <path> does not end with a file extension
		 *  --file name ends .html, .htm, .shtml, .cgi, .jsp, .asp, .aspx,
		 *					 .php, .pl, or .cfm
		 * ignores <query> or <fragment>, if present
		 *
		 * Parameters:
		 *  url -- url object containing the resolved url
		 * 
		 * Returns:
		 *  true if one of above conditions hold, false otherwise
		 */
		bool isHTML(URL& currURL);
		
		/*
		 * determines if currURL is within crawling scope
		 *  compares prefix of currURL to startURL
		 */
		bool inScope(URL& currURL);			//HOW TO USE CONST CORRECTLY
		
		/*
		 * to make cycling through suffix list more cohesive/simpler to see
		 */
		bool hasCorrectSuffix(string s);
		
		bool hasNoExtension(string s);
	
	public:
		
		/*
		 * one-arg constructor
		 *
		 * 
		 */
		URLFilter(URL& baseURL);
	
		/*
		 * destructor
		 */
		~URLFilter();
		 
		/*
		 * determines if url is valid
		 *  calls isHTML and inScope
		 *
		 * Parameters:
		 *  url -- url object containing the resolved url
		 *
		 * Returns:
		 *  true if url isURL and inScope
		 */
		bool isValidURL(URL& currURL);
		
		static bool Test(ostream& os);
		
};

#endif
