//BST.cpp
#include <string>
#include <iostream>
#include "BST.h"

using namespace std;

//public:
	
		//!  No-arg constructor.  Initializes an empty BST
		BST::BST():root(NULL), count(0){
        }
	
	
		//!  Copy constructor.  Makes a complete copy of its argument
		BST::BST(const BST & other){
            Init(other);
        }
	
	
		//!  Destructor
		BST::~BST(){
			Clear();
        }
	
	
		//!  Assignment operator.  Makes a complete copy of its argument
		//!  @return Reference to oneself
		BST& BST::operator =(const BST & other){
             if (&other != this){
                Clear();					//MEMORY PROBLEM--wasn't clearing before assigning
                //root = NULL;
                //count = 0;
                Init(other);
             } 
             return *this;
        }
	
	
		//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
		//!  @note This is useful for BST clients that need to traverse the tree.)
		BSTNode * BST::GetRoot()const{
			if (count)
				return root;
			else
				return NULL;
		}
	
	
		//!  @return true if the BST is empty, or false if the BST is not empty
		bool BST::IsEmpty() const{
			return (!count);					//a 1 if empty (count = 0)
		}
	
	
		//!  Removes all values from the BST
		void BST::Clear(){
			if (root != NULL){
				Free(root);
				//delete root;
				root = NULL;					//IMPORTANT--in clear, curNode is local, 
				count = 0;						//so assigning it to null doesn't assign null to rt
			}
		}
	
	
		//!  @return the number of values in the BST
		int BST::GetSize() const{
			return count;
		}
	
	
		//!  Inserts value v into the BST
		//!  
		//!  @param v The new value being inserted
		//!
		//!  @return a pointer to the newly inserted node, or NULL if v was already
		//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
		BSTNode * BST::Insert(const std::string & v){
		
			if (Find(v) != NULL)					//check for duplicates
				return NULL;
			else{
				BSTNode* newNode = new BSTNode(v);
				root = Add(root,newNode);
				return newNode;
			}
		}
	
	
		//!  Searches the tree for value v
		//!  
		//!  @param v The new value being searched for
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not in the tree
		BSTNode * BST::Find(const std::string & v) const{
			return Look(root,v);
		}
	
		//! @NOTE: YOU ARE NOT REQUIRED TO IMPLEMENT THE Remove METHOD BELOW
		//!        (BUT YOU CAN IF YOU WANT TO)
		//!
		//!  Removes value v from the tree
		//!  
		//!  @param v The value being removed from the tree
		//!
		//!  @return true if v was removed from the tree, or false if v was not in the tree
		//bool Remove(const std::string & v);
	
//private:

		void const BST::PrintYourTree(BSTNode* current){
			cout << "Current: " << current->value << endl;
			if (current->left != NULL)
				cout << "Current->Left: " << current->left->value << endl;
			if (current->right != NULL)
				cout << "Current->Right: " << current->right->value << endl;
		}
            
        void BST::Init(const BST& other){
        	if (&other != NULL){
		        count = other.count;
		        //do a post-order traversal?
		       root = Copy(other.root);				//needed to assign root to my results
           }
        }
            
        void BST::Free(BSTNode* curNode){
        
        	if (curNode != NULL){
        		if (curNode->left)
        			Free(curNode->left);
        		if (curNode->right)
        			Free(curNode->right);
        		delete curNode;
        		//curNode = NULL;
        	}
        	else{
        	}
        	//BELOW DOES SAME, SLIGHTLY MORE COMPLICATED, my first way
        	//if (curNode == NULL)				//make sure we're not trying to deref stg later
        	//	return;
        	/*if ((curNode->left == NULL) && (curNode->right == NULL)){
        		delete curNode;						//delete what curNode points to
        		curNode = NULL;
        	}
        	else{
        		if (curNode->left != NULL)			//needed to make sure not trying 
        			Free(curNode->left); //to give as param to Free fcn NULL
        		if (curNode->right != NULL)			//assignment isn't necessary
        			Free(curNode->right);
        		delete curNode;
        		curNode = NULL;
        	}*/
        }
        
        BSTNode* BST::Copy(BSTNode* other){
        	if (other == NULL){
        		return NULL;
        	}
        	else{
        		BSTNode* newNode = new BSTNode(other->value);
        		newNode->left = Copy(other->left);
        		newNode->right = Copy(other->right);
        		return newNode;
        	}
        }
		
		BSTNode * BST::Add(BSTNode* localRoot, BSTNode* newNode){
			if (localRoot == NULL){
				//BSTNode* newNode = new BSTNode(v);
				count++;
				return newNode;
			}
			//else if ((localRoot->value).compare(newNode->value)==0){		//duplicates checked al
				//newNode = NULL;
				//return NULL;
				//}
			else if ((newNode->value).compare(localRoot->value)<0){			//insert into left subt
				localRoot->left = Add(localRoot->left,newNode);
				//return localRoot;
			}
			else{															//insert right subtree
				localRoot->right = Add(localRoot->right,newNode);
				//return localRoot;
			}
		}
		
		BSTNode * BST::Look(BSTNode* localRoot, const std::string &v) const{//REMEMBER CONST HERE
			if (localRoot == NULL)
				return NULL;
			else if (v.compare(localRoot->value)==0)
				return localRoot;
			else if (v.compare(localRoot->value)<0){
				return Look(localRoot->left,v);							//Review why this works
			}
			else{
				return Look(localRoot->right,v);
			}
		}

