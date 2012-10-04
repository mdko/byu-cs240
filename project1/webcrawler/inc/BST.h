#ifndef BST_H
#define BST_H

#include <string>
#include <iostream>
#include "URL.h"
#include "Page.h"
//#include "Word.h"			//can't include something that includes bst.h?
#include "Occurrence.h"
#include <sstream>

using namespace std;

//! forward declaration of BST class
template <typename T>  class BST;

//!  BSTNode implements a binary search tree node
template <typename E>
class BSTNode {
		friend class BST<E>;   //!< BST can access private members of BSTNode
	
	public:
	
		//!  Constructor
		BSTNode(const E v) :
		  value(v), left(NULL), right(NULL){
		}
		
		//! copy Constructor
		BSTNode(const BSTNode<E> & other) : 
		  value(other.value),left(other.left),right(other.right){
		}
		
		~BSTNode() {
			//delete value;		//if storing pointers to new objects put on heap
		}
	
		//!  Read-only public methods for use by clients of the BST class
		const E & getValue() const {
		  return value;
		}
		
		E & getChangeValue() {
			return value;
		}	
	
		BSTNode<E> * getLeft() const {
		  return left;
		}
	
	
		BSTNode<E> * getRight() const {
		  return right;
		}
		
		//! Assignment operator 
		BSTNode<E> & operator=(const BSTNode & other) {
			if(this!=&other) {
				left=other.left;
				value=other.value;
				right=other.right;
			}
			
			return *this;
		}
	
	private:
		E value;  				//!< value stored in the node
		BSTNode<E> * left;     //!< pointer to the node's left child
		BSTNode<E> * right;    //!< pointer to the node's right child
};


//!  BST implements a binary search tree
template <typename T>
class BST {
	
	public:
	
		//!  No-arg constructor.  initializes an empty BST
		BST() : root(NULL), count(0) {
        }
	
	
		//!  copy constructor.  Makes a complete copy of its argument
		BST(const BST & other) {
            init(other);
        }
		//!  Destructor
		~BST() {
			clear();
        }
	
		//!  Assignment operator.  Makes a complete copy of its argument
		//!  @return Reference to oneself
		BST<T>& operator =(const BST & other) {
             if (&other != this) {
                clear();					//MEMORY PROBLEM--wasn't clearing before assigning
                init(other);
             } 
             return *this;
        }
	
		//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
		//!  @note This is useful for BST clients that need to traverse the tree.)
		BSTNode<T> * getRoot() const {
			if (count)
				return root;
			else
				return NULL;
		}
	
		//!  @return true if the BST is empty, or false if the BST is not empty
		bool isEmpty() const {
			return (!count);					//a 1 if empty (count = 0)
		}
	
		//!  Removes all values from the BST
		void clear() {
			if (root != NULL) {
				free(root);
				//delete root;
				root = NULL;					//IMPORTANT--in clear, curNode is local, 
			}
		}
	
		//!  @return the number of values in the BST
		int getSize() const {
			return count;
		}
	
		//!  Inserts value v into the BST
		//!  
		//!  @param v The new value being inserted
		//!
		//!  @return a pointer to the newly inserted node, or NULL if v was already
		//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
		BSTNode<T> * insert(const T & v) {
		
			if (find(v) != NULL)					//check for duplicates
				return NULL;
			else {
				BSTNode<T>* newNode = new BSTNode<T>(v);
				root = add(root,newNode);
				return newNode;
			}
		}
	
		//!  Searches the tree for value v
		//!  
		//!  @param v The new value being searched for
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not in the tree
		BSTNode<T> * find(const T & v) const {
			return look(root,v);
		}
		
		BSTNode<T> * get(T & v) {
			return look(root, v);
		}
		
		string printTreeXML() {
			XMLstring.clear();
			//if (root != NULL)
				printXML(root);
			return XMLstring.str();
		}
		
		void printTree() const {
			print(root);
		}
		
		// NEED TO OVERLOAD COMPARE METHODS...
	
	
		//! @NOTE: YOU ARE NOT REQUIRED TO IMPLEMENT THE Remove METHOD BELOW
		//!        (BUT YOU CAN IF YOU WANT TO)
		//!
		//!  Removes value v from the tree
		//!  
		//!  @param v The value being removed from the tree	
		//!
		//!  @return true if v was removed from the tree, or false if v was not in the tree
		//bool Remove(const std::string & v);
	
	private:
		
		stringstream XMLstring;
		int count;
        BSTNode<T>* root;
        
        BSTNode<T>* printXML(BSTNode<T>* curr) {
        	if (curr->left != NULL)
				printXML(curr->left);
			if (curr->right != NULL)
				printXML(curr->right);
			XMLstring << curr->getChangeValue().getXMLinfo();
        }
        
		BSTNode<T>* print(const BSTNode<T>* curr) const {
			if (curr->left != NULL)
				print(curr->left);
			if (curr->right != NULL)
				print(curr->right);
			cout << curr->getValue();//.getValue();
			cout << "\n";
		}
	
		void init(const BST& other) {
        	if (&other != NULL) {
				count = other.count;
				root = copy(other.root);				//needed to assign root to my results
           }
        }
        
		void free(BSTNode<T>* curNode) {
			if (curNode != NULL) {
		    		if (curNode->left)
		    			free(curNode->left);
		    		if (curNode->right)
		    			free(curNode->right);
		    		delete curNode;
		    		//curNode = NULL;			//set to null in clear() (the caller)
		    }
        }
        
		BSTNode<T>* copy(BSTNode<T>* other) {
        	if (other == NULL) {
        		return NULL;
        	}
        	else {
        		BSTNode<T>* newNode = new BSTNode<T>(other->value);
        		newNode->left = copy(other->left);
        		newNode->right = copy(other->right);
        		return newNode;
        	}
        }
		
		BSTNode<T>* add(BSTNode<T>* localRoot, BSTNode<T>* newNode) {				//REMEMBER CONST HERE
			if (localRoot == NULL) {
				count++;
				return newNode;
			}
			else if ((newNode->value) < (localRoot->value)) {			//insert into left subt
				localRoot->left = add(localRoot->left,newNode);
			}
			else {															//insert right subtree
				localRoot->right = add(localRoot->right,newNode);
			}
		}
        
		BSTNode<T>* look(BSTNode<T>* localRoot, const T & v) const {
			if (localRoot == NULL)
				return NULL;
			else if (v == (localRoot->value))
				return localRoot;
			else if (v < (localRoot->value)) {
				return look(localRoot->left,v);								//Review why this works
			}
			else {
				return look(localRoot->right,v);
			}
		}
		
		public:
			static bool Test(ostream& os) {
				bool success = true;
				
				/* TEST 1--HOLDS INT */
				BST<int> bst1;
				
				TEST(bst1.getSize() == 0);
				TEST(bst1.isEmpty() == 1);
				bst1.insert(1);
				
				TEST(bst1.getSize() == 1);
				TEST(bst1.isEmpty() == 0);
				TEST(bst1.find(1)->getValue() == 1);
				TEST(bst1.getRoot()->getValue() == 1);
				
				bst1.insert(2);
				TEST(bst1.getSize() == 2);
				TEST(bst1.isEmpty() == 0);
				TEST(bst1.find(2)->getValue() == 2);
				TEST(bst1.getRoot()->getValue() == 1);
				
				bst1.insert(3);
				bst1.insert(4);
				TEST(bst1.getSize() == 4);
				TEST(bst1.find(4)->getValue() == 4);
				TEST(bst1.getRoot()->getValue() == 1);
				/* END TEST 1 */
				
				
				
				/* TEST 2--HOLDS URLS */
				BST<URL> bst2;
				
				TEST(bst2.getSize() == 0);
				TEST(bst2.isEmpty() == 1);
				
				URL url1("http://www.google.com");
				bst2.insert(url1);
				
				TEST(bst2.getSize() == 1);
				TEST(bst2.isEmpty() == 0);
				
				//cout << (bst2.find("http://www.google.com")->getValue());
				//cout << bst2.find("http://www.google.com")->getValue().getURL();
				
				TEST(bst2.find("http://www.google.com")->getValue() == "http://www.google.com");	//WHY IS THIS WORKING?
				TEST(bst2.getRoot()->getValue() == "http://www.google.com");		//getValue() uses overloaded << operator in URL class
				
				URL url2("file:///Documents/stuff");
				bst2.insert(url2);
				
				TEST(bst2.getSize() == 2);
				TEST(bst2.find("file:///Documents/stuff")->getValue() == "file:///Documents/stuff");
				TEST(bst2.getRoot()->getValue() != "file:///Documents/stuff");
				TEST(bst2.getRoot()->getValue() == "http://www.google.com");
				/* END TEST 2 */
				
				
				
				/* TEST 3--HOLDS PAGE OBJECTS */
				/* EMULATES PAGE HISTORY */
				BST<Page> bst3;
				
				TEST(bst3.getSize() == 0);
				TEST(bst3.isEmpty() == 1);
				
				Page page1(url1);
				bst3.insert(page1);
				
				TEST(bst3.getRoot()->getValue().getURL() == "http://www.google.com");
				
				//testing two different ways of printing out
				//cout << bst3.getRoot()->getValue().getURL() << endl;
				//cout << bst3.getRoot()->getValue() << endl;
				
				TEST(bst3.getSize() == 1);
				TEST(bst3.isEmpty() == 0);
				
				Page page2(url2);
				bst3.insert(page2);
				
				TEST(bst3.getSize() == 2);
				TEST(bst3.getRoot()->getValue().getURL() == "http://www.google.com");
				TEST(bst3.find(page2)->getValue().getURL() == "file:///Documents/stuff");
				
				URL url3("file:///Documents/stuff");	//a new page with a url that has already been inserted, so a DUPLICATE
				Page page3(url3);
				
				URL url4("file://Downloads/thing");
				Page page4(url4);
				
				TEST(bst3.find(page3));
				TEST(!bst3.find(page4));	
				//attempted insertion
				TEST(!bst3.insert(page3));			//shouldn't be inserted because there is a page with the same url
				TEST(bst3.getSize() == 2);
				
				bst3.insert(page4);
				
				TEST(bst3.getSize() == 3);
				/* END TEST 3 */
				
				
				
				/* TEST 4--HOLDS WORD OBJECTS */
				/* EMULATES WORDSET (WORD INDEX OCCURENCE) */
				
				//BST<Word> bst4;
				//Word word1("yoda");
				
				//TEST(bst4.getSize() == 0);
				//TEST(bst4.isEmpty() == 1);
				
				/* END TEST 4 */
				
				
				
				/* TEST 5--HOLDS OCCURENCE OBJECTS */
				/* EMULATES OCCURENCES (OCCURENCE SET CLASS) */
				//BST<Occurrence> bst5;
				
				
				
				return success;
			}
};


#endif
