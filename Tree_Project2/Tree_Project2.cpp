// Eyorokon_Project2.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include "OrgTree.h"
using namespace std;

int main()
{
	OrgTree t = OrgTree();
	//cout << t.dataArr.size() << endl;
	
	t.addRoot("President", "Jubal");
	t.addRoot("CEO", "Monica May");
	t.hire(t.getRoot(), "Secretary", "Bill");
	t.hire(t.getRoot(), "Intern", "Shelly");

	//hire under secretary bill
	t.hire(t.find("Secretary"), "Janitor", "John");
	t.hire(t.find("Secretary"), "Janitor2", "Jack");
	t.hire(t.find("Janitor2"), "Part-Time Janitor", "Niel");

	cout << "Root: ";
	t.printData(t.getRoot(), true);

	t.checkResizeTree(true, true);
	cout << "size: " + to_string(t.getSize()) << endl;

	cout << "Left Child Test: " + to_string(t.leftmostChild(1)) << endl;
	cout << "Root: " + to_string(t.getRoot()) << endl;
	cout << "Find: " + to_string(t.find("Intern")) << endl;
	cout << "Parent of Janitor: " + to_string(t.orgArr[4][1]) << endl;

	cout << "Right Sib Pres: ";
	t.printData(t.rightSibling(0), true);


	//t.printSubTree(1);
	cout << endl;
	//cout << " Jubal's Parent: "+t.orgArr[0][1] << endl;

	t.write("OutputFile.txt");
	
	t.read("Input.txt");
	cout << "size: " + to_string(t.getSize()) << endl;

	t.printSubTree(0);

	cout << endl;
	
	//t.fire("VP Software Development");
	int i = t.find("Software Engineer I");
	i = t.rightSibling(i);
	cout << i;
	cout << endl;
	t.printSubTree(0);
	//cout << "size: " + to_string(t.getSize()) << endl;
	cout << "Root: " + to_string(t.getRoot()) << endl;
	t.fire("Cloud Development");
	t.hire(t.getRoot(), "TEST", "TEST");
	t.hire(t.getRoot(), "YAYAY", "NEW");
	t.printSubTree(t.getRoot());
	t.fire("VP Sales");
	//test if the internal linked list can regrow
	t.hire(0, "Cool guy", "Money bags");
	//cout << "Index of new: " + to_string(t.rightSibling(13)) << endl;
	t.printSubTree(t.getRoot());

	t.fire("Software Engineer I");
	t.fire("Cool guy");
	t.fire("YAYAY");
	t.printSubTree(t.getRoot());
	cout << "size: " + to_string(t.getSize()) << endl;

	system("pause");
	return 0;
}

