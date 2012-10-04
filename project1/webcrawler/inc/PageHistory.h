#ifndef PAGE_HISTORY_H
#define PAGE_HISTORY_H

#include "Page.h"
#include "BST.h"

/*
 * PageHistory.h
 * tracks all pages/urls that have already been seen
 *  (whose links have been found previously)
 */
 
class PageHistory{
	private:
		BST<Page> historyTree;
		int size;				//keeps track of number of elements in array
	public:
		/*
		 * no-arg constructor
		 */
		PageHistory();
		
		/*
		 * destructor
		 */
		~PageHistory();
		
		/*
		 * inserts page into array
		 * 
		 * Parameters:
		 *  page--a Page object containing URL and description
		 * 
		 * Returns:
		 *  nothing
		 */
		bool add(Page page);
		
		/*
		 * checks to see if page has already been encountered before
		 *
		 * Parameters:
		 *  page--a Page object to be searched for
		 *
		 * Returns:
		 *  true if found, false otherwise
		 */
		bool contains(Page page);
		
		bool contains(URL& url);
		
		/*
		 * returns array of Page objects
		 * 
		 * Parameters:
		 *  none
		 *
		 * Returns:
		 *  the array of Pages created during this object's existence
		 */
		//Page[] historyList(); 
		
		/*
		 * returns number of elements in array
		 *
		 * Parameters:
		 *  none
		 *
		 * Returns:
		 *  size--an int representing number of Pages in history
		 */
		int getSize();
		
		string getXML();
		
		void printHistory() const;
		
		//string printTreeXML();
		 
		static bool Test(ostream& os);
};

#endif
