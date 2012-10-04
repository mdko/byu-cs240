//Word.cpp

#include "Word.h"
#include "UnitTest.h"

Word::Word(string str) : value(str) {
}

Word::~Word() {

}

bool Word::addOccurrence(URL url) {
	Occurrence newOcc(url);
	occurrenceSet.insert(newOcc);
}

void Word::incrementOccurrenceCount(URL url) {
	Occurrence toFind(url);
	occurrenceSet.get(toFind)->getChangeValue().increaseCount();
}
 
bool Word::hasOccurrence(URL url) const {
	Occurrence posOcc(url);
	return (occurrenceSet.find(posOcc) != NULL) ? 1 : 0;
}

string Word::getValue() const {
	return value;
}

Occurrence Word::findOccurrence(URL url) const {
	Occurrence findOcc(url);
	return occurrenceSet.find(findOcc)->getValue();
}
/*
 * prints each occurrence object this word's occurrenceSet contains
 * 	--each occurrence object knows how to print itself 
 *  (url value and number of times this word occurs on that page)
 */
void Word::printOccurrences() const {
	occurrenceSet.printTree();
}

bool Word::operator ==(const Word& other) const {
	return (value.compare(other.value) == 0);
}

bool Word::operator <(const Word& other) const {
	return (value.compare(other.value) < 0);
}

ostream& operator <<(ostream& s, const Word& w) {
	s << w.getValue();
	return s;
}

string Word::getXMLinfo() {
	string info;
	info = "\t\t<word>\n";
	
	info += "\t\t\t<value>";
	info += value;
	info += "</value>\n";
	
	//call each occurrence's getXMLinfo method
	//for each occurrence
	info += occurrenceSet.printTreeXML();
	
	info +="\t\t</word>\n";
	
	return info;
}

bool Word::Test(ostream& os) {
	bool success = true;
	
	Word word1("yoda");
	Word word2("windu");
	Word word3("vader");
	Word word4("yoda");
	
	TEST(word1.getValue() == "yoda");
	TEST(word1.getValue() ==  word4.getValue());
	//test equality operator
	TEST(word1 == word4);
	
	//word1.addOccurrence(URL("http://www.google.com"));
	//word1.printOccurrences();
	
	//word1.addOccurrence(URL("http://www.yahoo.com"));
	//word1.addOccurrence(URL("http://www.google.com/reader/"));
	//word1.printOccurrences();
	
	return success;
}

