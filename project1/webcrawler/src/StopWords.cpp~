//StopWords.cpp

#include "StopWords.h"

//private:


int StopWords::wordCompare(const void* ap,const void* bp) {
	string* a = (string*) ap;
	string* b = (string*) bp;
	return (*a).compare(*b);
}

//public:

/*
 * empty for testing
 */
StopWords::StopWords() : wordCount(0) {
}

StopWords::StopWords(char* f) : wordCount(0) {
	ifstream file;
	file.open(f);
	
	/*if (!file.is_open()) {
		cout << "Unable to open file: " << f << endl;
		return -2;
	}*/
	
	//while (!file.oef()) {
	//	++wordCount;
	//}
	
	char curLine[50];
	
	while (file.getline(curLine, sizeof(curLine))) {
		//string* newWord = new string(curLine);
		string newWord(curLine);
		wordArray[wordCount] = newWord;
		++wordCount;
	}
	
	file.close();
}

void StopWords::addWord(string& word) {
	wordArray[wordCount] = word;
	++wordCount;
}

StopWords::~StopWords() {
	//for (int i = 0; i < wordCount; ++i) {
	//	delete wordArray[i];
	//}
}

bool StopWords::isStopWord(string word) {
	return (bsearch(&word, wordArray, wordCount, sizeof(string), wordCompare) != NULL) ? 1 : 0;
}

void StopWords::printWords() {
	for (int i = 0; i < wordCount; ++i) {
		cout << /* * */wordArray[i] << endl;
	}
}

bool StopWords::Test(ostream& os) {
	bool success = true;
	
	StopWords sw;
	string s1("apple");
	string s2("mango");
	string s3("peaches");
	string s4("orange");
	string s5("apple");
	
	string s6("notastopword");
	
	sw.addWord(s1);
	sw.addWord(s2);
	sw.addWord(s3);
	sw.addWord(s4);
	
	//cout << sw.isStopWord(s5) << endl;		//YES WORKING
	//cout << sw.isStopWord(s1) << endl;
	//cout << sw.isStopWord(s6) << endl;
	return success;	
}
