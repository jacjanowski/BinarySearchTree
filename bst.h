#pragma once

#include<iostream>
#include<algorithm>


using namespace std;
template<typename TKey, typename TValue>

class binarysearchtree {
	private:

		struct NODE {
			TKey Key;
			TValue Value;
			NODE* Left;
			NODE* Right;
		};

		NODE* Root;
		int Size;
		// delete helper function for the destructor.
		void eraseNode(NODE* curr) {
			if (curr == nullptr) { 
				return;
			}
			eraseNode(curr->Left);
			eraseNode(curr->Right);
			delete curr;
		
		}
		// in order traversel of the tree to obtain values.
		void _inorder(NODE* curr) {
			if (curr == nullptr) {
				return;
			} else {
				_inorder(curr->Left);
				_inorder(curr->Right);
			}
		}
		// reading in the height of the tree that we build
		int _height(NODE* curr){
			if (curr == nullptr)
				{return -1;}
			else {
				int heightL = _height(curr->Left);
				int heightR = _height(curr->Right);

				return 1 + std::max(heightL, heightR);
			}
		}
		// this preorder search starts at the left, go up the tree, and then right.
		// insert the values left and right, recursively call back.
		void _preorder(NODE* other) {
			if(other == nullptr) {
				return;
			} else {
				insert(other->Key, other->Value);
				_preorder(other->Left);
				_preorder(other->Right);
			}
		}

	public:
	//default constructor
		binarysearchtree()
		{
			Root = nullptr;
			Size = 0;
		}
	// copy constructor when passing in a tree and traversing that tree.
		binarysearchtree(binarysearchtree& other) {
			Root = nullptr;
			Size = 0;
			_preorder(other.Root);
		}
	//our destructor calls the helper function and deletes.
		~binarysearchtree() {
			eraseNode(Root);
		}

		// 
		// size:
		//
		// Returns the # of nodes in the tree, 0 if empty.
		//
		int size() {
			return Size;
		}

		int height() {
			return _height(Root);
		}
		// search_and_count:
		//
		// Searches the tree for the given key, returning true if found
		// and false if not.  Also counts the # of nodes that are visited
		// as part of the search; count is returned via 2nd parameter.
		//
		TValue* search(TKey key) {
			//count = 0;
			
			NODE* curr = Root;
			
			// TODO: search for key, return true if found:
			// Traverse untill root reaches to dead end 
			while (curr != nullptr) { 
			// pass right subtree as new tree 
				if(key == curr->Key) {
					
					return &(curr->Value);
				}
				
				if (key < curr->Key) { 
					curr = curr->Left; 		
				}
			// pass left subtree as new tree 
			
				else {
					curr = curr->Right;
					
				}  

				
			}
			
			return nullptr;
			
		}
		//insert the key and value in the designated node.
		// Either left our right leaves
		void insert(TKey key, TValue value) {
			NODE* prev = nullptr;
			NODE* curr = Root;

			while (curr != nullptr)
			{
				if (key == curr->Key)  // already in tree
					return;

				if (key < curr->Key)  // search left:
				{
					prev = curr;
					curr = curr->Left;
				}
				else
				{
					prev = curr;
					curr = curr->Right;
				}
			}//while

			//
			// 2. if we get here, key is not in tree, so allocate
			// a new node to insert:
			// 
			NODE* newNode;
			newNode = new NODE();
			newNode->Key = key;
			newNode->Value = value;
			newNode->Left = nullptr;
			newNode->Right = nullptr;

			//
			// 3. link in the new node:
			//
			// NOTE: curr is null, and prev denotes node where
			// we fell out of the tree.  if prev is null, then
			// the tree is empty and the Root pointer needs 
			// to be updated.
			//
			if (prev == nullptr) {
				Root = newNode;
			}
			
			else if (key < prev->Key) { 
				prev->Left = newNode;
			}
			else { 
				prev->Right = newNode;
			}

			// 
			// 4. update size and we're done:
			//
			Size++;
		}
		// our inorder traversal of the node.
		void inorder() {
			_inorder(Root);
		}


};

