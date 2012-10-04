#ifndef OCCURRENCE_H
#define OCCURRENCE_H

#include "URL.h"
#include "StringUtil.h"
#include <string>
#include <sstream>

/*
 * Occurrence.h
 * contains a Page object and number of times the word appears in page
 */
 
class Occurrence{
	private:
		URL url;				//contains information about URL and description
		int count;				//stores number of times word is found on this page
	
	public:
		
		/*
		 * one-arg constructor
		 *
		 * Parameters:
		 *  page
		 */
		Occurrence(URL passedURL);
		
		/*
		 * destructor
		 */
		~Occurrence();
		
		/*
		 * returns the URL's value
		 */
		string getURLValue() const;
		
		bool operator ==(const Occurrence& other) const;
		
		bool operator <(const Occurrence& other) const;
		
		friend ostream& operator <<(ostream& s, const Occurrence& o);
		
		/*
		 * returns number of times word occurs in URL (count)
		 */
		int getSize() const;
		
		void increaseCount();
		
		string getXMLinfo();
		
		static bool Test(ostream& os);

};

#endif
