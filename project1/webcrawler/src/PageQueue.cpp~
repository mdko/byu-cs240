//PageQueue.cpp
#include "PageQueue.h"
#include "UnitTest.h"
#include <iostream>

PageQueue::PageQueue() {
}

PageQueue::~PageQueue() {
	//since LinkedList pagesQueue made on stack, no need to call delete on it??
}

void PageQueue::enqueue(URL url) {		//creates a copy (pass by value)
	pagesQueue.insert(url, NULL);
}

/*
 * removes the first node in list and returns the URL object pointer contained
 *  in this node
 *
 * REVIEW WHERE I AM DELETING THE URL OBJECT
 * 
 * Returns:
 *  frontURL--pointer to the URL at front of list
 */
URL PageQueue::dequeue() {
	URL frontURL = (pagesQueue.getFirst()->getValue());		//creates a lot of copies...
	pagesQueue.remove(pagesQueue.getFirst());
	return frontURL;
}

bool PageQueue::isEmpty() {
	return pagesQueue.isEmpty();
}

int PageQueue::getSize() {
	return pagesQueue.getSize();
}

void PageQueue::printContents() {
	//return pagesQueue.printList();
}

bool PageQueue::Test(ostream& os) {
	bool success = true;
	
	PageQueue pageQueue;
	
	/*char* startURLString = "http://www.google.com";
	URL startURL(startURLString);				//not put on heap, so no need to delete afterwards...
	pageQueue.enqueue(startURL);
	
	TEST(startURL.getURL() == "http://www.google.com");
	TEST(pageQueue.getSize() == 1);
	//pageQueue.printContents();				//should contain just "<argv[1]>"
	
	URL s = pageQueue.dequeue();
	
	TEST(s.getURL() == startURL.getURL());		//should contain same values (just copies of each other);
	TEST(pageQueue.getSize() == 0);
	//pageQueue.printContents();*/				//should contain nothing
	
	/*URL* url1 = new URL();
	URL* url2 = new URL("http://www.google.com/reader/stuff");
	URL* url3 = new URL("file:///things");
	URL* url4 = new URL("./reader");
	
	TEST(queue.getSize() == 0);
	TEST(queue.isEmpty() == 1);
	
	queue.enqueue(url1);
	queue.enqueue(url2);
	
	queue.printQueueContents();		//should read "...google.com..., 
									// DEFAULT CONSTRUCTOR"						
	queue.enqueue(url3);
	
	TEST(queue.getSize() == 3);
	TEST(queue.isEmpty() == 0);
	
	URL* urlRet = queue.dequeue();	//pop front--CAUSING MEMORY LEAKS*/
	
	//The URL pointers aren't the same...not passing around the same object
	/*cout << urlRet->getURL() << endl;
	cout << &urlRet << endl;
	cout << url3->getURL() << endl;
	cout << &url3 << endl;
	TEST(&urlRet == &url3);*/
	
	//TEST(queue.getSize() == 2);
	
	//queue.enqueue(url4);
	
	//TEST(queue.getSize() == 3);
	
	//queue.printQueueContents();
	
	//delete url1;
	//delete url2;
	//delete url3;			//they seem to delete the same thing, url3 nd urlRet
	//delete urlRet;
	//urlRet = NULL;
	//delete url4;
	//don't need to call delete on each URL because the pagequeue going 
	//out of scope calls delete on its nodes, which call delete on URLS
	//but how to use URL after it's been deleted supposely
	
	return success;
}
