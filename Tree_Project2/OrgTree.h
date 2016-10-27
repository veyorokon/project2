#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#define TREENODEPTR int
#define TREENULLPTR -1
#define ROWS 50
#define ORGCOLS 3
#define DATACOLS 2

using namespace std;

class OrgTree
{
private:
	int factor;
	unsigned int last;
	int root;
	int deleted;
public:
	/*Our 2D array to keep track of tree organization:
	Left child, Parent, Right Sibling */
	vector <vector<int>> orgArr;

	//Our 2D array to keep track of tree data: Title, Name
	vector<vector<string>> dataArr;

	/* Default Constructor */
	OrgTree();
	~OrgTree();

	/* Creates a new node and adds it as the new root */
	void addRoot(string, string);

	/* Resize the Tree vectors by a new row factor */
	void checkResizeTree(bool force, bool increase);

	/* Returns the number of nodes in the tree */
	unsigned int getSize();

	/* Returns the root of the tree */
	TREENODEPTR getRoot();

	/* Returns the Left most child of a node */
	TREENODEPTR leftmostChild(TREENODEPTR );

	/* Returns the right sibling */
	TREENODEPTR rightSibling(TREENODEPTR );

	/* Returns index of specified title */
	TREENODEPTR find(string title);

	/*Inserts new employee as last child of node pointed to */
	void hire(TREENODEPTR, string title, string name);

	/* This function print out the structure of 
	the specified subtree, and is paired with the recPrint*/
	void printSubTree(TREENODEPTR );

	/* Recursively print the tree. */
	void recPrint(TREENODEPTR, int);

	/* This function prints and returns the selected 
	node in format of title, name */
	string printData(TREENODEPTR node, bool consolePrint);

	/*Recursively write to file where ')' designates the end of a subtree*/
	void OrgTree::write(string filename);

	/* Helper function to write to file*/
	void OrgTree::recWrite(ofstream& filename, TREENODEPTR subTreeRoot);

	/*Read from the file line by line and build tree where ')' designates the end of a subtree*/
	bool OrgTree::read(string filename);

	/*Helper function to read input file, also returns an integer to the parent node */
	int recRead(ifstream & infile, TREENODEPTR subTreeRoot);

	/*Removes the employee whos title matches from the tree so long 
	as the formerTitle is not the root node*/
	bool OrgTree::fire(string formerTitle);
};

