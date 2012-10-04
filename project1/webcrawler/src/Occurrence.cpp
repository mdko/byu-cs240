//Occurence.cpp

#include "Occurrence.h"
#include "UnitTest.h"

Occurrence::Occurrence(URL passedURL) : url(passedURL), count(1) {		
//initialized to one because if an occurence is being made, there must be a word that was found

}

Occurrence::~Occurrence() {

}

bool Occurrence::operator ==(const Occurrence& other) const {
	return (url == other.url);			//relies on URL's overloaded == method
}

bool Occurrence::operator <(const Occurrence& other) const {
	return (url < other.url);
}

ostream& operator <<(ostream& s, const Occurrence& o) {
	s << o.getURLValue();
	return s;
}

string Occurrence::getURLValue() const {
	return url.getURL();
}

int Occurrence::getSize() const {
	return count;
}

void Occurrence::increaseCount() {
	++count;
}

string Occurrence::getXMLinfo() {
	string info;
	info += "\t\t\t<occurrence>\n";
	info += "\t\t\t\t<url>\n";
	info += "\t\t\t\t\t";
	info += StringUtil::EncodeToXmlCopy(getURLValue());
	info += "\n\t\t\t\t</url>\n";
	info += "\t\t\t\t<count>";
	
	//there's probably a simpler way to do this, but this works
	//(was getting errors before when just concatenating count)
	string num;
	stringstream out;
	out << count;
	num = out.str();
	
	info += num;
	info += "</count>\n";
	info += "\t\t\t</occurrence>\n";
	
	return info;
}

bool Occurrence::Test(ostream& os) {
	bool success = true;
	
	URL url1("http://www.google.com");
	Occurrence oc1(url1);
	
	URL url2("http://www.yahoo.com");
	Occurrence oc2(url2);
	
	//cout << oc1.getXMLinfo();
	
	return success;
}
