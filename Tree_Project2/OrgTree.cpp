#include "stdafx.h"
#pragma once
#include "OrgTree.h"
using namespace std;
/* Theta 2n */
OrgTree::OrgTree()
{
	
	deleted = 0;
	factor = 1; // Tracks the resize factor
	last = 0; // Keeps track of last row and count
	root = -1; // Row index for the root node
	orgArr.resize(ROWS, vector<int>(ORGCOLS, TREENULLPTR));//matrix to store organization
	dataArr.resize(ROWS, vector<string>(DATACOLS, "")); //matrix to store title, name
}
/*Theta n */
OrgTree::~OrgTree()
{
	vector<vector<int>>().swap(orgArr);
	vector<vector<string>>().swap(dataArr);
}
/*Theta 1 */
void OrgTree::addRoot(string title, string name) {
	int indx;
	if (indexQueue.count >= 1) {
		indx = indexQueue.draw();
	}
	else indx = last;
	//Create new root
	dataArr[indx][0]=(title); //Col 0 is for the title
	dataArr[indx][1]=(name); //Col 1 is for the name

	//If root != -1 we need to set previous root as left child of new root
	if(root != -1) {
		orgArr[root][1] = indx; //Sets previous root's parent to new root 
		orgArr[indx][0] = root; //Sets new root's left child to previous root
	}
	root = indx; //Reassign the root pointer to new root index
	last++;
	checkResizeTree(false, true); //if max rows, resize vectors
}
/*Theta 1 */
void OrgTree::checkResizeTree(bool forceResize, bool increase) {
	if (last + 1 == ROWS*factor || forceResize) {
		if(increase)
			factor++;
		else factor--;
		orgArr.resize(ROWS*factor, vector<int>(ORGCOLS, -1));
		dataArr.resize(ROWS*factor, vector<string>(DATACOLS, ""));
	}
	else return;
}
/* Theta 1 */
unsigned int OrgTree::getSize() {
	return last-deleted;
}
/* Theta 1 */
TREENODEPTR OrgTree::getRoot() {
	return root;
}
/* Theta 1 */
TREENODEPTR OrgTree::leftmostChild(TREENODEPTR node) {
	if (node != TREENULLPTR)
		return orgArr[node][0];
	else return TREENULLPTR;
}
/* Theta 1 */
TREENODEPTR OrgTree::rightSibling(TREENODEPTR node) {
	if(node != TREENULLPTR)
		return orgArr[node][2];
	return TREENULLPTR;
}
/* Theta n */
TREENODEPTR OrgTree::find(string title) {
	string current = dataArr[0][0];
	int indx = 0;
	while (indx < last) {
		cout << "CURRENT: " << current << ". TITLE: " << title << ". INDX: " << indx << endl;
		if (current == title)return indx;
		indx++;
		if(indx < dataArr.size()) current = dataArr[indx][0];
	}
	return TREENULLPTR;
}
/* Theta n */
void OrgTree::hire(TREENODEPTR ptr, string newTitle, string newName) {
	
	
	//check if root exists, if not just create it and return
	if (root == TREENULLPTR) {
		addRoot(newTitle, newName);
		return;
	}
	//Get a deleted index if it exists.
	int indx;
	if (indexQueue.count >= 1) {
		indx = indexQueue.draw();
	}
	else indx = last;

	//Create the new node
	dataArr[indx][0] = newTitle;//Update node's Title
	dataArr[indx][1] = newName;//Update nodes Name
	orgArr[indx][1] = ptr; //Update node's Parent
	//If left child does not exist
	if (leftmostChild(ptr) == TREENULLPTR) {
		orgArr[ptr][0] = indx;//Update the ptr left child
	}
	else {
		//Else append right sibling
		unsigned int rs = rightSibling(leftmostChild(ptr));
		if (rs == TREENULLPTR) orgArr[leftmostChild(ptr)][2] = indx; //If the left child node has no right sib
		else {
			while (rightSibling(rs) != TREENULLPTR) { //Loop until right sib is null
				rs = rightSibling(rs);
			}
			orgArr[rs][2] = indx; //Update the right sibling col to reflect new node
		}
	}
	//increment and check if resize is necessary
	last++;
	checkResizeTree(false, true);
}

/*Theta 1 - just calls helper */
void OrgTree::printSubTree(TREENODEPTR subTreeRoot) {
	recPrint(subTreeRoot, 0);
}
/*Theta n^2 */
void OrgTree::recPrint(TREENODEPTR subTreeRoot, int spaceFactor){
	const string INDENT = "    "; //used for alignment of output
								   // If the node exists, print contents
	if (subTreeRoot != TREENULLPTR) {
		printData(subTreeRoot, true);
	}
	else return;
	//Print the left child if it exists
	int leftChild = leftmostChild(subTreeRoot);
	if (leftChild == TREENULLPTR) return;

	for (int i = 0; i < spaceFactor+1; i++) {
		cout << INDENT;
	}
	recPrint(leftChild, spaceFactor+1);
	
	//Print the right sib if it exists
	int rs = rightSibling(leftChild);
	while (rs != TREENULLPTR) { //Loop until right sib is null
		cout << INDENT;
		for (int i = 0; i < spaceFactor; i++) {
			cout << INDENT;
		}
		recPrint(rs, spaceFactor+1);
		rs = rightSibling(rs);
	}
}
/*Theta 1 */
string OrgTree::printData(TREENODEPTR node, bool consolePrint) {
	string data = dataArr[node][0] + ", " + dataArr[node][1];
	if(consolePrint)
	cout << data << endl;
	return data;
}

/*Theta 1 - just calls helper. */
void OrgTree::write(string filename)
{
	ofstream outfile(filename);
	recWrite(outfile, root);
	outfile.close();
}

/*Theta n^2 */
void OrgTree::recWrite(ofstream& outfile, TREENODEPTR subTreeRoot) {

	const string CLOSE = ")"; //used for formating output
								  
	if (subTreeRoot != TREENULLPTR) {// If the node exists, print contents
		outfile << printData(subTreeRoot, false) << endl;
	}
	else { //Else the node doesn't exist, return
		outfile << CLOSE << endl;
		return;
	};

	//Write the left child if it exists
	int leftChild = leftmostChild(subTreeRoot);
	if (leftChild == TREENULLPTR) {
		outfile << CLOSE <<endl;
		return;
	}
	recWrite(outfile, leftChild);

	//Write the right sib if it exists
	int rs = rightSibling(leftChild);
	while (rs != TREENULLPTR) { //Loop until right sib is null
		recWrite(outfile, rs);
		rs = rightSibling(rs);
	}
	outfile << CLOSE <<endl; //Write the final close
}

/*Theta 1 - just calls the helper */
bool OrgTree::read(string filename)
{
	ifstream infile(filename);

	if (infile.fail()) {//Check if the file exists.
		cout << "File not found";
		return false;
	}

	//Else reinit everything and call helper
	factor = 1;
	last = 0;
	root = TREENULLPTR;
	orgArr.clear();
	dataArr.clear();
	orgArr.resize(ROWS, vector<int>(ORGCOLS, TREENULLPTR));
	dataArr.resize(ROWS, vector<string>(DATACOLS, ""));

	//call recursive helper
	recRead(infile, 0);
	infile.close();
	return true;
}
/*Theta n^2 - Helper function */
int OrgTree::recRead(ifstream& infile, TREENODEPTR parent) {
	//read line
	string line, title, name; 
	int comma;
	
	
	//else hire new node

	while (infile.peek() != ')') {
		if(getline(infile, line));
		else return parent;
		comma = line.find_first_of(','); //get index of the ','
		title = line.substr(0, comma);
		name = line.substr(comma + 2); //+2 for ',' and the ' ' space.
		hire(parent, title, name);
		recRead(infile, find(title)); //pass pointer to newly created node
	}
	getline(infile, line);
	return last;
}

/*Theta 2n */
bool OrgTree::fire(string formerTitle)
{
	TREENODEPTR deletedsParent, deletedsLC, deletedsRS, deletedsSib, indx = find(formerTitle);
	if(getRoot() == indx || indx == TREENULLPTR) //cannot delete root
		return false;
	
	deletedsParent = orgArr[indx][1];  //init deleted node's parent ptr
	deletedsLC = leftmostChild(indx); //init deteled node's left child ptr
	deletedsRS = rightSibling(indx); //init deleted node's right sib
	
	//Change children's parent pointers to deleted node's parent
	if (deletedsLC != TREENULLPTR) {
		orgArr[deletedsLC][1] = deletedsParent;
		int nextChild = rightSibling(deletedsLC);

		while (nextChild != TREENULLPTR) { //So long as the deleted node has children, fix their pointers
			orgArr[nextChild][1] = deletedsParent;
			nextChild = rightSibling(nextChild);
		}
	}

	//Change delted node's parent's pointer if LC = indx
	if (leftmostChild(deletedsParent) == indx) 
		orgArr[deletedsParent][0] = rightSibling(indx);
	
	else{//Else loop until we're right before deleted node
		deletedsSib = leftmostChild(deletedsParent);
		while (rightSibling(deletedsSib) != indx) {
			//cout << deletedsSib;
			deletedsSib = rightSibling(deletedsSib); //increment deletedsSib
		}
		if (deletedsLC != TREENULLPTR) {/*If the deleted node has children,
										shift the entire subtree up one level to insert
										children where the deleted node was*/
			int nextchild = deletedsLC;
			while (rightSibling(nextchild) != TREENULLPTR) {
				nextchild = rightSibling(nextchild);
			}
			orgArr[nextchild][2] = orgArr[indx][2];
			orgArr[deletedsSib][2] = deletedsLC;
		}
		else orgArr[deletedsSib][2] = orgArr[indx][2]; //Else set preceding sibling's right sib to deleteds rs
	}
	//Clear all data of deleted
	orgArr[indx][0] = TREENULLPTR;
	orgArr[indx][1] = TREENULLPTR;
	orgArr[indx][2] = TREENULLPTR;
	dataArr[indx][0] = TREENULLPTR;
	dataArr[indx][1] = TREENULLPTR;
	indexQueue.insert(indx);
	deleted++;
	return true;
}

