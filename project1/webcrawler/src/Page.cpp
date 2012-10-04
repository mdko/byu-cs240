//Page.cpp
#include "Page.h"
#include <iostream>
using namespace std;

// url (a URL* pointer) is assigned the address of resolvedURL? or just assigned URL
Page::Page(URL& resolvedURL): url(resolvedURL), description("") {

}

Page::Page(URL& resolvedURL, string des): url(resolvedURL), description(des) {

}

Page::~Page() {
}

Page::Page(const Page& other) : url(other.url), description(other.description) {
}

/*
 * FOR NEXT THREE OVERLOADED METHODS, NEED TO DEREFERENCE BECAUSE url 
 *  IS OF TYPE POINTER (URL*)
 */
 
bool Page::operator ==(const Page& other) const {
	return (url == other.url);
}

bool Page::operator <(const Page& other) const {
	return (url < other.url);
}

bool Page::operator !=(const Page& other) const {
	return (url != other.url);
}

ostream& operator <<(ostream& s, const Page& p) {	//CONST was important, as was friend in .h file
	
	s << p.getURL();			//value returns pointer to string on heap, need to derefence 
	s << "\n\t";
	s << p.getDescription();
	return s;
}

string Page::getXMLinfo() {
	string s;
	s += ("\t\t<page>\n");
	s += ("\t\t\t<url>\n");
	s += ("\t\t\t\t");
	s += (StringUtil::EncodeToXmlCopy(getURL()));
	s += ("\n");
	s += ("\t\t\t</url>\n");
	s += ("\t\t\t<description>");
	s += (StringUtil::EncodeToXmlCopy(getDescription()));
	s += ("</description>\n");
	s += ("\t\t</page>\n");
	
	return s;
}
		
string Page::getDescription() const {
	return description;
}

void Page::setDescription(string& des) {
	description = des;
}

string Page::getURL() const {
	return url.getURL();
}	

bool Page::Test(ostream& os) {

	bool success = true;
	
	URL url1("http://www.google.com");
	Page page1(url1);
	
	URL url2("http://www.yahoo.com");
	Page page2(url2);
	
	URL url3("http://www.google.com");
	Page page3(url3);
	
	TEST(page1 != page2);
	TEST(page1.getURL() == "http://www.google.com");
	TEST(page2.getURL() == "http://www.yahoo.com");
	
	TEST(page3.getURL() == "http://www.google.com");
	TEST(page1 == page3);
	
	Page page4(url3, "DESCRIPTION");
	TEST(page4.getDescription() == "DESCRIPTION");
	
	//cout << page4.getXMLinfo();
	
	return success;
	
}
