#ifndef PAGE_QUEUE_H
#define PAGE_QUEUE_H

#include "LinkedList.h"
#include "URL.h"
#include <iostream>
/*
 * PageQueue.h
 * stores set of URL's that need to be processed
 */
 
class PageQueue{
	private:
		
		LinkedList<URL> pagesQueue;			//a linked-list containing URL objects
	
	public:
		/*
		 * no-arg constructor
		 */
		PageQueue();
		
		/*
		 * destructor
		 */
		~PageQueue();
		
		/*
		 * inserts page into array
		 * 
		 * Parameters:
		 *  url--a URL object containing URL/address
		 * 
		 * Returns:
		 *  true if added, false otherwise
		 */
		void enqueue(URL url);
		
		/*
		 * removes first URL object from array for processing
		 *
		 * Parameters:
		 *  none
		 *
		 * Returns:
		 *  URL object at front of queue(array)
		 */
		URL dequeue();
		
		/*
		 * returns whether or not the queue is empty and the caller should
		 *  stop downloading webpages
		 *
		 * Parameters:
		 *  none
		 *
		 * Returns:
		 *  true if pageQueue linked-list isEmpty() method returns true, false otherwise
		 */
		bool isEmpty();
		
		/*
		 * returns <linkedlist>.GetSize()
		 */
		int getSize();
		
		void printContents();
		
		/*
		 * Unit Testing method
		 */
		static bool Test(ostream& os);
};

#endif
