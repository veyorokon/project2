#pragma once
#include <stdlib.h>    
#include <iostream>
#include <time.h>

using namespace std;



template<class T> class MagicBag
{

private:
	/*Private Node Class for the Magic Bag */
	template<class T> class Node {
	private:

	public:
		T value;
		Node<T>* next;
		/*Node constructor no params*/
		Node() {
			value = NULL;
			next = NULL;
		}
		/*Node constructor 1 param of type T*/
		Node(T newVal) {
			value = newVal;
			next = NULL;
		}
		/*Node destructor*/
		~Node() {
			
		}
	};
public:
	Node<T>* head;
	int count;
	MagicBag() {
		count = 0;
		head = new Node<T>();
		head->next = NULL;
	}
	/*Copy the values to create two distinct bags*/
	MagicBag(const MagicBag& other) {
		head = new Node<T>();
		Node<T> *ourPtr;
		ourPtr = (head);
		Node<T> *otherPtr;
		otherPtr = (other.head);
		T val = otherPtr->value;
		insert(val);
		count++;
		
		while(otherPtr->next != NULL) {
			T val = (*(otherPtr->next)).value;
			insert(val);
			ourPtr = (*ourPtr).next;
			otherPtr = (*otherPtr).next;
			count++;
		}
	}
	/*This overloads the = operator. */
	MagicBag& operator=(const MagicBag& other) {
		//Go through and assign new contents
		head = new Node<T>();
		Node<T> *ourPtr;
		ourPtr = (head);
		Node<T> *otherPtr;
		otherPtr = (other.head);
		T val = otherPtr->value;
		insert(val);
		count++;

		while (otherPtr->next != NULL) {
			T val = (*(otherPtr->next)).value;
			insert(val);
			ourPtr = (*ourPtr).next;
			otherPtr = (*otherPtr).next;
			count++;
		}
		return *this;
	}
	/*Destructor*/
	~MagicBag() {
		if (count >= 1) {
			Node<T>* ptr = head;
			Node<T>* nextPtr = head->next;
			for (int i = 0; i < count - 1; i++) {
				delete(ptr);
				ptr = nextPtr;
				nextPtr = nextPtr->next;
			}
		}
	}
	/*Append an element to the end of the list*/
	void insert(T item) {
		// If the item added is the FIRST 
		if (count == 0) {
			head=new Node <T>(item);
		}
		else { //Else append to the end
			Node<T>* ptr = head;
			while(ptr->next != NULL) {
				ptr = ptr->next;
			}
			(ptr->next) = new Node <T>(item);
		}
		count++;
	}

	/*Modified to return the first element*/
	T draw() {
		//Code for Generating random numbers was borrowed from Pilot
		if (count == 1) {
			T val = head->value;
			head = NULL;
			count--;
			return val;
		}
		else if (count > 1) {			
			T n = (*head).value;
			head = (*head).next;
			count--;
			return n;
		}
		else
			throw std::exception("Empty Bag Exception!");
	}

	/*Check if the item is in the bag. If so return the count*/
	int peek(T item) {
		int count = 0;
		Node<T>* ptr = head;
		while (ptr != NULL) {
			if ((*ptr).value == item)
				count++;
			ptr = (*ptr).next;
		}
		return count;
	}

private:
	/*Print Function to display the contents of the bag*/
	friend ostream& operator<<(ostream& os, const MagicBag& mb) {
		Node<T> *ptr;
		ptr = (mb.head);
		while (ptr != NULL) {
			if (ptr->next == NULL) 
				os << (*ptr).value << ". ";
			else
				os << (*ptr).value << ", ";
			ptr = ptr->next;
		}
		return os;
	}
};                       