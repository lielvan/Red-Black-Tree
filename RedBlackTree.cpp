// BST.cpp : Defines the entry point for the console application.
// Created By: Liel van der Hoeven
// Algorithms for left/right rotate and recoloring found in book; Introduction to Algorithms, 3rd Edition 

#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
using namespace std;

class Node
{
public:
	string word;
	string color;
	Node *parent;
	Node *left;
	Node *right;

	Node(){};
};

class RBT
{
public:
	Node *root;
	int numCount = 0;
	int ftc = 0;

	void add(Node *r, string x);
	void print(Node *x);
	int depth(Node *d);
	int search(string w, Node *s);
	void leftRotate(Node &x);
	void rightRotate(Node &x);
	void fix(Node *z);
	RBT();
};
RBT::RBT()
{
	root = NULL;
}

void RBT::add(Node *p, string word)
{
	try
	{
		if (p == NULL)
		{
			p = new Node;
			p->word = word;
			p->color = "B";							// Set color of root to BLACK
			p->parent = NULL;						// Set the parent of the root to NULL
			p->left = new Node;						// Create empty black Nodes to the left & right of the root
			p->right = new Node;
			p->left->color = "B";
			p->right->color = "B";

			root = p;
			numCount++;
		}
		if (word < p->word)
		{
			if (p->left->word == "")
			{
				p->left->word = word;
				p->left->color = "R";
				p->left->parent = p;
				p->left->left = new Node;			// Create empty black Nodes to the left & right of the newly created Node
				p->left->right = new Node;
				p->left->left->color = "B";
				p->left->right->color = "B";

				fix(p->left);
				numCount++;
			}
			else
			{
				p = p->left;
				add(p, word);
			}
		}
		else
		{
			if (p->right->word == "")
			{
				p->right->word = word;
				p->right->color = "R";
				p->right->parent = p;
				p->right->left = new Node;			// Create empty black Nodes to the left & right of the newly created Node
				p->right->right = new Node;
				p->right->left->color = "B";
				p->right->right->color = "B";

				fix(p->right);
				numCount++;
			}
			else
			{
				p = p->right;
				add(p, word);
			}
		}
	}
	catch (exception& e)
	{
		cout << "Something happened and you broke the pointer... -_-" << endl;

	}
}

void RBT::leftRotate(Node &x)
{
	try
	{
		Node *y;
		y = x.right;						// Set y
		x.right = y->left;					// Turn y's LEFT subtree into x's RIGHT subtree
		if (y->left != NULL)
		{
			y->left->parent = &x;
		}
		y->parent = x.parent;				// Links x's parent to y
		if (x.parent == NULL)
		{
			root = y;
		}
		else
		{
			if (&x == x.parent->left)
			{
				x.parent->left = y;
			}
			else
				x.parent->right = y;
		}
		y->left = &x;
		x.parent = y;
	}
	catch (exception& e)
	{
		cout << "Something happened and you broke the pointer... -_-" << endl;

	}
}

void RBT::rightRotate(Node &x)
{
	try
	{
		Node *y;
		y = x.left;							// Set y
		x.left = y->right;					// Turn y's RIGHT subtree into x's LEFT subtree
		if (y->right != NULL)
		{
			y->right->parent = &x;
		}
		y->parent = x.parent;				// Links x's parent to y
		if (x.parent == NULL)
		{
			root = y;
		}
		else
		{
			if (&x == x.parent->right)
			{
				x.parent->right = y;
			}
			else
				x.parent->left = y;
		}
		y->right = &x;
		x.parent = y;
	}
	catch (exception& e)
	{
		cout << "Something happened and you broke the pointer... -_-" << endl;

	}
}

void RBT::fix(Node *z)					// Takes care of rotations and recoloring
{
	try
	{
		while (z != root && z->parent->color == "R")
		{
			Node *y;
			if (z->parent == z->parent->parent->left)		//If z's parent is LEFT of z's grandparent
			{
				y = z->parent->parent->right;
				if (y->color == "R")					// Case 1 condition with subtree on the LEFT
				{
					z->parent->color = "B";				// Case 1
					y->color = "B";						// Case 1
					z->parent->parent->color = "R";		// Case 1
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->right)			//Case 2 condition
					{
						z = z->parent;					// Case 2
						leftRotate(*z);					// Case 2
					}
					z->parent->color = "B";				// Case 3
					z->parent->parent->color = "R";		// Case 3
					rightRotate(*z->parent->parent);		// Case 3
				}
			}
			else											// If z's parent is RIGHT of z's grandparent
			{
				if (z->parent == z->parent->parent->right)
				{
					y = z->parent->parent->left;
					if (y->color == "R")					// Case 1 condition with subtree on the RIGHT
					{
						z->parent->color = "B";				// Case 1
						y->color = "B";						// Case 1
						z->parent->parent->color = "R";		// Case 1
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->left)			//Case 2 condition
						{
							z = z->parent;					// Case 2
							rightRotate(*z);				// Case 2
						}
						z->parent->color = "B";				// Case 3
						z->parent->parent->color = "R";		// Case 3
						leftRotate(*z->parent->parent);		// Case 3
					}
				}
			}
		}
		root->color = "B";
	}
	catch (exception& e)
	{
		cout << "Something happened and you broke the pointer... -_-" << endl;

	}
}

void RBT::print(Node *r)
{
	try
	{
		// Print the entire tree in-order
		//if (r->word != "")					
		//{
		//	print(r->left);
		//	cout << r->word << ": " << r->color <<endl;
		//	print(r->right);
		//}

		// Print the leaves in-order
		if (r->left->word != "")
			print(r->left);
		if ((r->left->word == "") && (r->right->word == ""))
			cout << r->color << ": " << r->word << endl;
		if (r->right->word != "")
			print(r->right);
	}
	catch (exception_ptr& e)
	{
		cout << "Something happened and you broke the pointer... -_-" << endl;
	}
}

int RBT::depth(Node *dp)
{
	try
	{
		int totalDepth = 0;
		if (dp->word != "")
		{
			int leftDepth = depth(dp->left);
			int rightDepth = depth(dp->right);
			int x = max(leftDepth, rightDepth);
			totalDepth = x + 1;
		}
		return totalDepth;
	}
	catch (exception_ptr& e)
	{
		cout << "Something happened and you broke the pointer... -_-" << endl;

	}
	return 0;
}

int RBT::search(string w, Node *s)	// Search for a word in the tree and return the amount of cycles it took to find it
{
	try
	{
		if ((s->word != "") && (s->word != w))
		{
			ftc++;
			if (s->word > w)
				search(w, s->left);
			else
				search(w, s->right);
		}
		return ftc;
	}
	catch (exception_ptr& e)
	{
		cout << "Something happened and you broke the pointer... -_-" << endl;
	}
	return 0;
}
int main()
{
	try
	{
		RBT tree;

		//Extracting words from file and adding them to the tree
		string word;
		fstream file("The Declaration of Independence.txt");
		tree.add(tree.root, "m");
		while (file >> word)
		{
			string out;
			for (int i = 0; i < word.size(); i++)
			{
				if (word[i] != '.' & word[i] != ',' & word[i] != ';' & word[i] != ':' & word[i] != '-' & word[i] != '&')//Getting rid of periods, commas, etc
				{
					out += word[i];
				}
			}
			tree.add(tree.root, out);
		}
		file.close();

		// Printing the tree and the information
		tree.print(tree.root);
		cout << endl;
		cout << "Total number of words inserted: " << tree.numCount << endl;
		cout << "Total depth is: " << tree.depth(tree.root) << endl;
		cout << "It took " << tree.search("to", tree.root) << " cycles to search for the word, " << "\"to\"" << endl;
		tree.ftc = 0;
		cout << "It took " << tree.search("1776", tree.root) << " cycles to search for the word, " << "\"1776\"" << endl;
		return 0;
	}
	catch (exception& e)
	{
		cout << "Something happened and you broke the code... -_-" << e.what() << endl;
	}
}