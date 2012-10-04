//WordIndex.cpp
#include "WordIndex.h"
#include "UnitTest.h"

//creates a word and adds to BST wordSet
void WordIndex::add(string wordVal, URL url) {	
	
	if (!stopWordsList->isStopWord(wordVal)) {
		Word newWord(wordVal);														
		if (wordSet.find(newWord) == NULL) {										
			newWord.addOccurrence(url);												
			wordSet.insert(newWord);												
		}
		else {																		
			if (wordSet.find(newWord)->getValue().hasOccurrence(url))			
				wordSet.get(newWord)->getChangeValue().incrementOccurrenceCount(url);
			else																	
				wordSet.get(newWord)->getChangeValue().addOccurrence(url);
		}
	}
}
	
WordIndex::WordIndex(StopWords* sw) {
	stopWordsList = sw;
}

WordIndex::~WordIndex() {

}

void WordIndex::addAll(string* wordsList, int size, URL	 url) {
	for (int i = 0; i < size; ++i) {
		add(wordsList[i], url);
	}
}

Word WordIndex::getFirstWord() {
	return wordSet.getRoot()->getValue();
}

Word WordIndex::getWord(string s) {
	Word toFind(s);
	return wordSet.find(toFind)->getValue();
}

int WordIndex::size() const{
	return wordSet.getSize();
}

void WordIndex::printIndex() const {
	wordSet.printTree();
}

string WordIndex::getXML() {
	return wordSet.printTreeXML();
}

bool WordIndex::Test(ostream& os) {
	bool success = true;
	
	StopWords sw;
	WordIndex index(&sw);
	
	TEST(index.size() == 0);
	
	URL url1("www.google.com");
	string s1("yoda");
	index.add(s1, url1);
	
	TEST(index.size() == 1);
	TEST(index.getFirstWord().getValue() == "yoda");
	
	string array[] = {"anakin", "mace", "quigon"};
	index.addAll(array, 3, url1);
	
	TEST(index.size() == 4);
	
	TEST(index.getFirstWord().getValue() == "yoda");
	TEST(index.getFirstWord().hasOccurrence(url1));
	TEST(index.getFirstWord().findOccurrence(url1).getSize() == 1);
	
	string s2("yoda");						
	//a duplicate word found on this same page, so increase the count on this 
	// word's particular occurence of this page
	index.add(s2, url1);
	TEST(index.getFirstWord().findOccurrence(url1).getSize() == 2);
	
	TEST(index.getWord("anakin").getValue() == "anakin");
	TEST(index.getWord("anakin").findOccurrence(url1).getSize() == 1);
	
	string s3("anakin");
	index.add(s3, url1);
	TEST(index.getWord("anakin").findOccurrence(url1).getSize() != 1);
	TEST(index.getWord("anakin").findOccurrence(url1).getSize() == 2);
	
	TEST(index.size() == 4);				
	//even though more duplicate words added, still should have same number of unique words
	
	URL url2("http://www.yahoo.com");
	TEST(!index.getWord("mace").hasOccurrence(url2));
	
	//index.printIndex();
	
	StopWords sw2;
	string w1("the");
	sw2.addWord(w1);
	string w2("a");
	sw2.addWord(w2);
	
	WordIndex index2(&sw2);
	
	//cout << index2.size() << endl;
	
	//sw2.printWords();
	
	string s10("the");
	URL url10("stuff");
	index2.add(s10, url10);
	
	//cout << s10 << endl;
	//cout << sw2.isStopWord(s10) << endl;	//NOT WORKING
	//cout << index2.size() << endl;
	
	//cout << index.getXML();
	
	
	return success;
}


