//testdriver.cpp
#include <iostream>
#include "BST.h"
#include "LinkedList.h"
#include "URL.h"
#include "PageQueue.h"
#include "URLFilter.h"
#include "HTMLParser.h"
#include "PageDownloader.h"
#include "Page.h"
#include "Word.h"
#include "Occurrence.h"
#include "WordIndex.h"
#include "PageHistory.h"
#include "StopWords.h"
#include "OutputGenerator.h"

using namespace std;

int main(int argc, char* argv[]) {
	bool success = true;
	
	if (!URL::Test(cout))
		success = false;
	
	if (!LinkedList<URL>::Test(cout))				//why is a template argument necessary here?
		success = false;
		
	if (!PageQueue::Test(cout))
		success = false;
	
	if (!URLFilter::Test(cout))
		success = false;
	
	if (!PageDownloader::Test(cout))
		success = false;
		
	if (!HTMLParser::Test(cout))
		success = false;
	
	//NEED TO CONTINUE TESTING INSERTING DUPLICATES	
	if (!BST<URL>::Test(cout))
		success = false;
	
	if (!Page::Test(cout))
		success = false;
	
	if (!Word::Test(cout))
		success = false;
			
	if (!WordIndex::Test(cout))
		success = false;
		
	if (!PageHistory::Test(cout))
		success = false;
	
	if (!StopWords::Test(cout))
		success = false;
		
	if (!Occurrence::Test(cout))
		success = false;
				
	if (success)
		cout << "Tests succeeded!" << endl;
	else
		cout << "Tests Failed!" << endl;
		
	return 0;
}
