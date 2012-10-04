#ifndef URL_H
#define URL_H

#include <cstring>
#include <string>
#include <iostream>
using namespace std;
/*
 * URL.h
 * parses/stores urls, resolves relative urls
 */
 
class URL{
		
	public:
	
		/*
		 * no-arg constructor
		 */
		URL();
		
		/*
		 * one-arg constructor
		 *  used for startURL only (n	o relative URL to resolve)
		 *	assigns value to the cstring passed in via
		 *
		 * Parameters:
		 *  startURL cstring
		 */
		URL(char* startURL);
		
		/*
		 * two-arg constructor
		 *  resolves otherURL, if necessary, and assigns it to value via resolve() method
		 * 
		 * Parameters:
		 *  startURL cstring
		 *  otherURL cstring to resolve (if necessary)
		 */
		URL(char* startURL, char* otherURL);
		
		URL(string& baseURL, string& otherURL);
		
		/*
		 * copy constructor
		 */
		URL(const URL& other);
		
		/*
		 * assignment operator
		 */
		URL& operator =(const URL& other);
		
		/*
		 * equality operator
		 */
		bool operator ==(const URL& other) const;
		
		/*
		 * less-than operator
		 */ 
		bool operator <(const URL& other) const;
		
		/*
		 * not-equals operator
		 */
		bool operator !=(const URL& other) const;
		
		friend ostream& operator <<(ostream& s, URL& u);
		
		/*
		 * destructor
		 */
		~URL();
		
		/*
		 * returns the string value of the URL ("http://...")
		 *
		 * Paramters:
		 *  none
		 *
		 * Returns:
		 *  *value--value of string(URL) pointed to by value
		 */
		string getURL() const;
		
		//friend ostream& operator <<(ostream& s, URL& u);
		
		/*
		 * Unit Testing method
		 */
		static bool Test(ostream& os);
		
	private:
		string value;		//string containing actual value of url (ptr because on HEAP)
		/*
		 * resolves relative urls, changes cstring to c++ string
		 *
		 * Parameters:
		 *  baseURL--a cstring containing the base URL
		 *  relURL--a cstring containing the relative URL
		 *
		 * Returns:
		 *  nothing
		 */
		void resolve(char* baseURL, char* relURL);
		
		void removeFragsAndQueries(string& s);
		
		void removeFrags(string& s);
};

#endif
