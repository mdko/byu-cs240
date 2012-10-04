#ifndef PAGE_H
#define PAGE_H

#include <string>
#include <iostream>
#include "URL.h"
#include "UnitTest.h"
#include "StringUtil.h"
/*
 * Page.h
 * contains url description
 * stores page's words, other urls found in <a href> tags
 */
 
class Page{
	private:
		URL url;				//a pointer to the URL object containing url of the current page
		string description;		//description of page
		
	public:
		/*
		 * one-arg constructor, for creating Page objects that need to be added to queue
		 *
		 * Parameters:
		 *  resolvedURL--URL that will need to be downloaded
		 */
		Page(URL& resolvedURL);
		
		Page(URL& resolvedURL, string des);
		
		Page(const Page& other);
		/*
		 * destructor
		 */
		~Page();
		
		/*
		 * equality operator
		 */
		bool operator ==(const Page& other) const;
		
		/*
		 * less-than opeator
		 */
		bool operator <(const Page& other) const;
		
		/*
		 * not-equal operator
		 */
		bool operator !=(const Page& other) const;
		
		/*
		 * overloaded cout operator
		 */
		friend ostream& operator <<(ostream& s, const Page& p);
		
		/*
		 * returns the description of the Page for creating XML documents
		 *
		 * Parameters:
		 *  none
		 *
		 * Returns:
		 *  description--string representation of page description
		 */
		string getDescription() const;
		
		/*
		 * sets the page's description, which is available
		 *  after the page has been through HTML parser
		 *
		 * Parameters:
		 *  description--string representation of page description
		 *
		 *	Returns:
		 *   nothing
		 */
		void setDescription(string& description);
		
		string getURL() const;
		
		string getXMLinfo();
		
		/*
		 * Unit Testing method
		 */
		static bool Test(ostream& os);
};

#endif
