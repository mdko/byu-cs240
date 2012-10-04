#ifndef CS240_LINKED_LIST_H
#define CS240_LINKED_LIST_H

#include <iostream>
#include "UnitTest.h"
#include "URL.h"
#include "Word.h"

//! forward declaration of LinkedList class
template <typename T> class LinkedList;

//! LLNode implements a doubly-linked list node
template <typename E>
class LLNode {
		friend class LinkedList<E>;  //!< LinkedList can access private members of LLNode
	public:
	
		//!  Constructor
		LLNode(const E & v, LLNode * p, LLNode * n) :
		  value(v), prev(p), next(n) {	
		}
		
		//! Copy Constructor 
		LLNode(const LLNode<E> & other) : 
		   value(other.value),prev(other.prev),next(other.next) {
		}
		
		~LLNode() {
			//delete value;				//Deletes the URL contained in the Node--REMOVE IF I'M DELETING THE URL OBJECTS LATER (WHICH I PROBABLY WILL)
		}
	
		//!  Read-only public methods for use by clients of the LinkedList class
		const E & getValue() const {
		  return value;
		}
	
	
		LLNode<E> * getPrevious()const {
		  return prev;
		}
	
	
		LLNode<E> * getNext()const {
		  return next;
		}
		
		//! Assignment operator 
		LLNode<E> & operator=(const LLNode & other) {
			if(this!=&other){
				value=other.value;
				prev=other.prev;
				next=other.next;
			}
			return *this;
		}
		
		//overload insertion operator for displaying contents of node
		//if ever used: "cout << <some LLNode value> << endl;"
		friend ostream& operator <<(ostream& s, LLNode& lln) {
			cout << lln.value << endl;
			return s;	
		}
	
	private:
		E value;        			 //!< value stored in the node
		LLNode<E> * prev;            //!< pointer to previous node in the list
		LLNode<E> * next;            //!< pointer to next node in the list
};


//! LinkedList implements a doubly-linked list
template <typename T>
class LinkedList{
	public:
	
		//!  No-arg constructor.  Initializes an empty linked list
		LinkedList(): head(NULL),  count(0) {
		}
		
	
		//!  Copy constructor.  Makes a complete copy of its argument
		LinkedList(const LinkedList & other) {
			Init(other);
		}	
		
		//!  Destructor
		~LinkedList() {
			clear();
		}
	
		//! Assignment operator.  Makes a complete copy of its argument
		//! @return A reference to oneself
		LinkedList<T>& operator =(const LinkedList & other) {
			if (&other != this){
				free();
				init(other);
				return *this;
			}
		}
	
		//!  @return true if the list is empty, or false if the list is not empty
		bool isEmpty() const {
			return !count;			//true if 0, false if otherwise
		}

		//!  Removes all values from the list
		void clear() {
			free();
		}
	
		//!  @return the number of values in the list
		int getSize() const {
			return count;
		}
	
		//!  @return a pointer to the first node in the list, or NULL if the list is empty
		LLNode<T>* getFirst()const {
			return head;
		}
	
		//!  @returns a pointer to the last node in the list, or NULL if the list is empty
		LLNode<T>* getLast()const {
			LLNode<T>* curNode = head;
				if (curNode != NULL){
					while (curNode->next != NULL){
						curNode = curNode->next;
					}
			}
			return curNode;
		}
	
		//!  Inserts value v into the list after node n
		//!  
		//!  @param v The new value being inserted
		//!  @param n A node that is already in the list after which the new node should 
		//!      be inserted.
		//!      If n is NULL, the new node should be inserted at the beginning of the list.
		//!
		//!  @return a pointer to the newly inserted node
		LLNode<T>* insert(const T & v, LLNode<T> * n) {
			LLNode<T>* newNode = new LLNode<T>(v,NULL,NULL);
			if (n == NULL){
				  if (head == NULL){
					 head = newNode;                   //uses assignment operator in LLNode class
					 }
				  else{
					  newNode->next = head;				//THERE WERE PROBLEMS HERE
					  head->prev = newNode;				//HAD PROBLEM HERE
					  head = newNode;
				  }
			}
			else{
				newNode->next = n->next;
				if (newNode->next != NULL)				//HAD PROBLEMS HERE
					newNode->next->prev = newNode;
				n->next = newNode;
				newNode->prev = n;
			}
			count++;
			return newNode;
		}
	
		//! Searches for the first occurrence of value v that appears in the list 
		//!   after node n
		//!   
		//!  @param v The value being searched for
		//!  @param n The node in the list after which the search should begin.
		//!      If n is NULL, the list should be searched from the beginning.
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not found
		LLNode<T> * find(const T & v, LLNode<T> * n) const { //???Why <T> necessary in function argument?
			LLNode<T>* curNode; 
			if (n == NULL)
				curNode = head;
			else
				curNode = n->next;

			while (curNode != NULL){
				if ((curNode->value).compare(v)==0){
					return curNode;
				}
				curNode = curNode->next;
			}
			return NULL;
		}
	
		//!  Removes node n from the list
		//!  
		//!  @param n The node being removed from the list
		//!  @param b Boolean on whether the item should be deleted too
		void remove(LLNode<T> * n){
			if (n != NULL && head != NULL){
				if (head == n){
					head = head->next;
					if (head != NULL)
						head->prev = NULL;
				}
				else{
					//if (n->prev != NULL)
						if (n->next != NULL)
							n->next->prev = n->prev;
						n->prev->next = n->next;
				}
				//NEED TO FIGURE OUT HOW TO DELETE NODE WITHOUT DELETING URL
				delete n;				//delete what n points to (SAVE DELETING UNTIL END, SAVE URLS)
				n = NULL;				//point the ptr to NULL	(THESE TWO LINES SHOULD BE UNCOMMENTED NORMALLY)
			count--;
			}
		}
		
		/*
		 * This PrintList() function only works
		 *  when value is a pointer, not an value or primitive
		 * --how do you make a more general print method
		 */
		void const printList() {
			LLNode<T>* curNode = head;
			cout << "CONTENTS: ";
			if (curNode == NULL)
				cout << "[EMPTY]";
			else {
				while (curNode != NULL){								//curNode is of type pointer, so dereference. value is of type pointer to URL, so deref.
					cout << *(curNode->value)/*->getURL()*/;	//dereference because curNode->value evaluates to address where value points to (it's a pointer) 
					cout << " ";
					curNode = curNode->next;							//to do curNode->value, need to overload << in URL
				}														//with << overloading, cannot chain (ie <something> << " ") unless >> defined?
			}
			cout << endl;
		}
	
	private:
		LLNode<T>* head;
		int count;
		
		void init(const LinkedList& other){
			head=NULL;
			count=other.count;

			LLNode<T>* otherCurNode = other.head;
			LLNode<T>* myCurNode = NULL;

			while (otherCurNode != NULL){
				LLNode<T>* newNode = new LLNode<T>(otherCurNode->value,0,0);
				if (myCurNode == NULL)
						head = newNode;
				else{
					myCurNode->next = newNode;
					newNode->prev = myCurNode;
				}
				myCurNode = newNode;
				otherCurNode = otherCurNode->next;
			}
		}
		
		void free(){
			while (head != NULL){
				LLNode<T>* ln = head;
				head = head->next;
				delete ln;									//delete what ln points to, which includes calling destructor of URL value inside
			}
			head = NULL;
			count = 0;
		}
	
	public:
		static bool Test(ostream& os){
			bool success = true;
			
			//-----------Test template with ints------------------
			/*
			LinkedList<int> ll1;
			
			ll1.insert(3, NULL);
			
			TEST(ll1.getSize() == 1);
			TEST(ll1.getFirst()->getValue() == 3);
			
			ll1.insert(5, NULL);
			ll1.insert(1, ll1.GetLast());
			ll1.insert(2, ll1.getFirst());
			
			TEST(ll1.getSize() == 4);
			TEST(ll1.getFirst()->getValue() == 5);
			TEST(ll1.getLast()->getValue() == 1);
			
			//ll1.printList();					//should be 5, 2, 3, 1
			
			//ll1.clear();
			
			TEST(ll1.getSize() == 0);
			//no delete on ll1, because a local value on runtime stack*/
			
			//-----------Test template with URL pointers---------
			//-----------THE WAY I'LL DO IT----------------------
			
			LinkedList<URL*> ll2;
			//should I store URL values? or pointers to URL values?
			
			TEST(ll2.getSize() == 0);
	
			URL* url1 = new URL("http://www.cnn.com");
			ll2.insert(url1, NULL);
			
			//ll2.printList();
			TEST(ll2.getSize() == 1);
			
			URL* url2 = new URL("http://www.google.com/images/reader/stuff",
									"./funnies");
			ll2.insert(url2, NULL);
			
			URL* url3 = new URL("file://docs/things/foo");
			ll2.insert(url3, ll2.getLast());

			TEST(ll2.getSize() == 3);
			//ll2.printList();					//should be "google.com...,
												// cnn.cin..., file://..."
			
			TEST(ll2.getFirst()->getValue() == url2);
			TEST(ll2.getLast()->getValue() == url3);
			
			ll2.remove(ll2.getFirst());
			
			TEST(ll2.getSize() == 2);
			
			/*
			 * NEED TO MAKE SURE TO DELETE THESE SOMEWHERE
			 */
			delete url1;
			delete url2;
			delete url3;	
			//ll2.printList();					//should be "cnn.com, file://..."
			
			
			//ll2.clear();						//deleting works with this setup, but why isn't it generic enough to handle all setups?
			
			//----------Test template with URL values-----------
			/*
			LinkedList<URL> ll3;
			
			TEST(ll3.getSize() == 0);
			
			URL url1a;
			ll3.insert(url1a, NULL);
			
			//ll3.printList();
						
			URL url2a("www.facebook.com");
			ll3.insert(url2a, NULL);
			
			URL url3a("http://www.google.com/images/reader/stuff",
									"./funnies");
			TEST(url3a.getURL() == "http://www.google.com/images/reader/funnies");
			
			TEST(ll3.getSize() == 2);
			
			ll3.remove(ll3.getLast());
			
			TEST(ll3.getSize() == 1);
			//TEST(ll3.getFirst().getValue() == url2a);
			//TEST(ll3.getLast().getValue() == url1a);
			
			//ll3.clear();
			*/
			
			//---------Test template with URL pointers with a pointer to LinkedList---
			
			//Can't figure out exactly how to initialize this correctly, but
			// won't have a linkedlist on the heap anyway during webcrawler
			// --will have a linkedlist on stack with pointers to values on heap
			/*
			LinkedList<URL*> * ll4 = new LinkedList<URL>();
			
			URL* url1b = new URL("www.google.com");
			ll4->insert(url1b, NULL);
			
			URL* url2b = new URL("http://www.google.com/images/reader/stuff",
									"./funnies");
			ll4->insert(url2b, ll4->getLast());
		
			ll4->printList();
			*/
			
			/*LinkedList<Word> ll5;
			
			Word w1("yoda");
			
			ll5.insert(w1, NULL);
			//testing to see if << overloaded in Word class works (2nd line below)
			cout << ll5.getFirst()->getValue().getValue() << endl;
			cout << ll5.getFirst()->getValue() << endl;*/
			return success;
		}
};

#endif

