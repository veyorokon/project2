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
	/*
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
	cout << "size: " + to_string(t.dataArr.size()) << endl;

	cout << "Left Child Test: " + to_string(t.leftmostChild(1)) << endl;
	cout << "Root: " + to_string(t.getRoot()) << endl;
	cout << "Find: " + to_string(t.find("Intern")) << endl;
	cout << "Parent of Janitor: " + to_string(t.orgArr[4][1]) << endl;

	cout << "Right Sib Pres: ";
	t.printData(t.rightSibling(0), true);


	t.printSubTree(1);
	cout << endl;
	//cout << " Jubal's Parent: "+t.orgArr[0][1] << endl;

	t.write("OutputFile.txt");
	*/
	t.read("OutputFile.txt");
	t.printSubTree(0);


	system("pause");
	return 0;
}

