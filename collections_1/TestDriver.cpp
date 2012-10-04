#include <iostream>
#include "LinkedList.h"
#include "BST.h"

using namespace std;

void TestBST(){
	BST tree;
	
	cout << "Get Root: " << tree.GetRoot() << endl;
	cout << "Is Empty: " << tree.IsEmpty() << endl;
	
	cout << "Inserted Alan: " << tree.Insert("Alan")->GetValue() << endl;
	
	cout << "Size: " << tree.GetSize() << endl;
	cout << "Root: " << tree.GetRoot()->GetValue() << endl;
	cout << "Is Empty: " << tree.IsEmpty() << endl;
	
	cout << "Insterted John: " << tree.Insert("John")->GetValue() << endl;
	cout << "Inserted Sally: " << tree.Insert("Sally")->GetValue() << endl;
	cout << "Insterted Jared: " << tree.Insert("Jared")->GetValue() << endl;
	
	cout << "Size: " << tree.GetSize() << endl;
	cout << "Root: " << tree.GetRoot()->GetValue() << endl;
	
	cout << "Find Sally: " << tree.Find("Sally")->GetValue() << endl;
	cout << "Find John: " << tree.Find("John")->GetValue() << endl;
	cout << "Find Jared: " << tree.Find("Jared")->GetValue() << endl;
	cout << "Find Alan: " << tree.Find("Alan")->GetValue() << endl;	
	
	cout << "Size of tree 1: " <<  tree.GetSize() << endl;
	cout << "Root of tree 1: " << tree.GetRoot()->GetValue() << endl;
	cout << "Root's immediate tree: " << endl;
	tree.PrintYourTree(tree.GetRoot());
	cout << "Root->Right's immediate tree: " << endl;
	tree.PrintYourTree(tree.Find("John"));
	
	//cout << tree.Find("Alan")->left << endl;
	//cout << tree.Find("Alan")->right->GetValue() << endl;
	//cout << tree.Find("Alan")->right->left->GetValue() << endl;
	//cout << tree.Find("Alan")->right->right->GetValue() << endl;
	//cout << tree.Find("John")->left->GetValue() << endl;
	//cout << tree.Find("John")->right->GetValue() << endl;

	BST tree2;
	cout << "Size of tree 2: " << tree2.GetSize() << endl;
	cout << "Root of tree 2: " << tree2.GetRoot() << endl;
	cout << "Inserted Ebenezer into tree 2: " << tree2.Insert("Ebenezer")->GetValue() << endl;
	cout << "Inserted Mary into tree 2: " << tree2.Insert("Mary")->GetValue() << endl;
	cout << "Inserted George into tree 2: " << tree2.Insert("George")->GetValue() << endl;
	
	
	cout << "Size of tree 2: " << tree2.GetSize() << endl;
	cout << "Root of tree 2: " << tree2.GetRoot()->GetValue() << endl;
	
	cout << "Tried to insert George again: " << tree2.Insert("George") << endl;
	
	tree.PrintYourTree(tree2.GetRoot());
	cout << "Root->Right's immediate tree: " << endl;
	tree.PrintYourTree(tree2.Find("Mary"));
	
	//cout << tree2.Find("Ebenezer")->left << endl;
	//cout << tree2.Find("Ebenezer")->right->GetValue() << endl;
	//cout << tree2.Find("Ebenezer")->right->left->GetValue() << endl;
	//cout << tree2.Find("Ebenzer")->right->right << endl;
	
	tree2 = tree;
	cout << "Assigned tree 2 to tree 1 " << endl;
	
	cout << "Size of tree 2: " << tree2.GetSize() << endl;
	cout << "Root of tree 2: " << tree2.GetRoot()->GetValue() << endl;
	
	//tree2.Clear();
	//tree.Clear();
	
	/*
	 * NEED TO MAKE SURE REMOVE WORKS--NOT YET
	 */
	
	//cout << tree2.Find("Alan")->left<< endl;
	//cout << tree2.Find("Alan")->right->GetValue() << endl;
	//cout << tree2.Find("Alan")->right->left->GetValue() << endl;
	//cout << tree2.Find("Alan")->right->right->GetValue() << endl;
	//cout << tree2.Find("John")->left->GetValue() << endl;
	//cout << tree2.Find("John")->right->GetValue() << endl;
	
	
}

void TestLinkedList(){
    LinkedList ll;
    
    cout << "Get First: " << ll.GetFirst() << endl;
    if (ll.GetLast() == NULL)
    	cout << "Yes" << endl;
    cout << "Get Last: " << ll.GetLast() << endl;
    
    cout << "Count: " << ll.GetSize() << endl;
    cout << "IsEmpty: " << ll.IsEmpty() << endl;
    
    cout << "\nInserted \"Michael\": " << ll.Insert("Michael",NULL)->GetValue() << endl;
    
    cout << "\nCount: " << ll.GetSize() << endl;
    cout << "IsEmpty: " << ll.IsEmpty() << endl;
    cout << "First: " << ll.GetFirst()->GetValue() << endl;
    cout << "Last: " << ll.GetLast()->GetValue() << endl;  
    
    ll.Insert("Joe",NULL);
    ll.Insert("Bob",NULL);
    cout << "\nInserted \"Joe\" " << endl;
    cout << "Inserted \"Bob\" " << endl;
    
    cout << "\nCount: " << ll.GetSize() << endl;
    cout << "First: " << ll.GetFirst()->GetValue() << endl;
    cout << "Last: " << ll.GetLast()->GetValue() << endl;

	if (ll.Find("Bob",NULL)!=NULL)
  		cout << "Find Bob: " << ll.Find("Bob",NULL)->GetValue() << endl; 
  	cout << "Find Michael: " << ll.Find("Michael",NULL)->GetValue() << endl;

	cout << "\nPrinted List: " << endl;
	ll.PrintList();
	
	ll.Remove(ll.Find("Michael",NULL));
	cout << "Remove Michael" << endl;
    cout << "First: " << ll.GetFirst()->GetValue() << endl;
    
    cout << "Count: " << ll.GetSize() << endl;
    cout << "Last: " << ll.GetLast()->GetValue() << endl;
    
	cout << "\nPrinted List: " << endl;
	ll.PrintList();
    
    ll.Remove(ll.Find("Bob",NULL));
    cout << "Remove Bob" << endl;
    cout << "First: " << ll.GetFirst()->GetValue() << endl;
    cout << "Count: " << ll.GetSize() << endl;
    
    cout << "Inserted Amy" << endl;
    cout << "Inserted Harold" << endl;
    ll.Insert("Amy",NULL);
    ll.Insert("Harold",NULL);
    cout << "First: " << ll.GetFirst()->GetValue() << endl;
    cout << "Count: "<< ll.GetSize() << endl;
    
    LLNode* ames = ll.Find("Amy",NULL);
    cout << "Insert Evan after Amy: " << endl;
    ll.Insert("Evan",ames);
    cout << "Count: " <<ll.GetSize() << endl;
    cout << "Last: " << ll.GetLast()->GetValue() << endl;
    
    cout << "\nPrinted List: " << endl;
	ll.PrintList();
    
    cout << "Last: " << ll.GetLast()->GetValue() << endl; 
    cout << "Insert Jeremy after last " << endl;
    ll.Insert("Jeremy",ll.GetLast());
    cout << "First: " << ll.GetFirst()->GetValue() << endl;
    cout << "Insert Louis after first " << endl;
    ll.Insert("Louis",ll.GetFirst());
    
    cout << "\nPrinted List: " << endl;
	ll.PrintList();
	cout << "Count: " << ll.GetSize() << endl;
	
	ll.Remove(ll.Find("Harold",NULL));
	cout << "Remove Harold" << endl;
	cout << "\nPrinted List: " << endl;
	ll.PrintList();
	cout << "Count: " << ll.GetSize() << endl;
	
	//ll.Remove(ll.Find("Jeremy",NULL));
	//cout << "Remove Jeremy" << endl;
	ll.Remove(ll.GetLast());
	cout << "Remove Last" << endl;
	
	cout << "\nPrinted List: " << endl;
	ll.PrintList();
	cout << "Count: " << ll.GetSize() << endl;
	
	cout << "Last: " << ll.GetLast()->GetValue() << endl;
	ll.Remove(ll.GetLast());
	cout << "Remove Last" << endl;
	//cout << "Evan: " << ll.Find("Evan", NULL)->GetValue() << endl;
	//ll.Remove(ll.Find("Evan", NULL));
	//cout << "Remove Evan" << endl;
	cout << "\nPrinted List: " << endl;
	ll.PrintList();
	cout << "Count: " << ll.GetSize() << endl;
    
    /*
	 * SEEMS TO BE WORKING UP TO HERE
	 */    
	cout << endl;
	cout << endl;
    
    LinkedList l2;
    l2.Insert("Jindhal",NULL);
    l2.Insert("Guptal",NULL);

    cout << "\nInserted \"Jindhal\" into list 2 " << endl;
	cout << "\nInserted \"Guptal\" into list 2 " << endl;

    cout << "\nCount: " << l2.GetSize() << endl;
    cout << "First: " << l2.GetFirst()->GetValue() << endl;
    cout << "Last: " << l2.GetLast()->GetValue() << endl;
    
    l2 = ll;       //test assignment operator
    cout << "\nAssigned second list to first " << endl;

    cout << "\nCount: " << l2.GetSize() << endl;
    cout << "First: " << l2.GetFirst()->GetValue() << endl;
    cout << "Last: " << l2.GetLast()->GetValue() << endl;
    
    //l2.Clear();				//put Clear in BST destructor
    //ll.Clear();
    
    /*
     * SEEMS TO BE WORKING UP TO HERE
     */
    
}

int main(){
	cout << "Test Linked List:\n" << endl;
    TestLinkedList();
    cout << "\n\nTest BST:\n" << endl;
    TestBST();
    return 0;   
}
