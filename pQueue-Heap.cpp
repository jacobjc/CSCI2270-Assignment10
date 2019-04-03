//  Copyright © 2018 by Jacob Christiansen. All rights reserved.
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <time.h>

using namespace std;

#include "pQueue-Heap.hpp"

MinHeap::MinHeap(){
}

MinHeap::~MinHeap(){
}

void MinHeap::enqueue(Patient add){
	if(currSize == capacity){ //Heap is filled
		cout<<"The heap is filled, cannot enqueue!"<<endl;
		return;
	}
////////////////////////////////////////////////////////
	else{ //Heap not filled
		currSize++;
		int temp = currSize;
		theHeap[temp] = add;

		while(temp > 1  &&  theHeap[temp] < theHeap[temp/2]){
			swap(theHeap[temp], theHeap[temp/2]);
			temp = temp/2;
		}
	}
}

void MinHeap::dequeue(){
	if(currSize == 0){ //Heap is empty
		cout << "Heap is empty, cannot dequeue!" << endl;
		return;
	}
////////////////////////////////////////////////////////
	else{ //Heap not empty
		cout<<abs(881 - currSize)<<": "<<theHeap[1].name<<",  "<<theHeap[1].priority<<",  "<<theHeap[1].treatment<<endl;
		theHeap[1] = theHeap[currSize];
		currSize--;
		heapify(1);
	}
}

void MinHeap::dequeueAll(){
	while(currSize != 0){
		dequeue();
	}
}

void MinHeap::dequeueAllTest(){
	while(currSize != 0){
		if(currSize == 0){ //Heap is empty
			return;
		}
////////////////////////////////////////////////////////
		else{ //Heap not empty
			theHeap[1] = theHeap[currSize];
			currSize--;
			heapify(1);
		}
	}
}

void MinHeap::heapify(int i){
	int smallestChild;
	int leftChild = 2*i;
	int rightChild = 2*i + 1;

	while(leftChild <= currSize  ||  rightChild <= currSize){ //at least one of the children
		leftChild = 2*i; //increment the 2* step
		rightChild = 2*i + 1; //
////////////////////////////////////////////////////////
		if(leftChild <= currSize  &&  rightChild <= currSize){ //both of the children
			if(theHeap[leftChild] < theHeap[rightChild]){
				smallestChild = leftChild;
			}
			else{
				smallestChild = rightChild;
			}
		}
////////////////////////////////////////////////////////
		else if(leftChild <= currSize){ //only the left child
			smallestChild = leftChild;
		}
////////////////////////////////////////////////////////
		else if(rightChild <= currSize){ //only the right child
			smallestChild = rightChild;
		}
////////////////////////////////////////////////////////
		if(theHeap[i] > theHeap[smallestChild]){ //correct heap if i > smallestChild, by swapping
			swap(theHeap[i], theHeap[smallestChild]);
			i = smallestChild;
		}
		else{ //if i is not > than smallestChild, heap is corrected!
			break;
		}
	}
}


int main(int argc, char *argv[]){
	cout<<endl<<"~~~~~~~~~~~~~~~~~~~~ Welcome to Priority Queue - HEAP Implementation ~~~~~~~~~~~~~~~~~~~~"<<endl;
	MinHeap pQueue;

	ifstream fr;
	fr.open(argv[1]);

	string ln;
	string name[880];
	int priority[880];
	int treatment[880];

	getline(fr, ln, '\r'); //skips first line
	// cout << "Rank	patient,  Priority,  Treatment" << endl;

	int index = 0;

	while(!fr.eof()){
		getline(fr, ln, ',');
		name[index] = ln;
		getline(fr, ln, ',');
		priority[index] = stoi(ln);
		getline(fr, ln, '\r');
		treatment[index] = stoi(ln);

		pQueue.enqueue(Patient(name[index], priority[index], treatment[index]));
		// cout<<"enqueuing: "<< name[index] << index<<endl;
		index++;
	}
////////////////////////////////////////////////////////
	int input;
	// inputs
	while(input != 3){
		cout<<endl;
		cout<<"Would you like to dequeue?"<<endl<<"1 - Yes, one Patient"<<endl<<"2 - Yes, all Patients"<<endl<<"3 - No"<<endl;
		cin >> input;
		if(input == 1){//dequeue one
			pQueue.dequeue();
		}
		if(input == 2){//dequeue all
			pQueue.dequeueAll();
		}
	}
	input = 0;
	while(input != 2){
		cout<<endl;
		cout<<"Would you like to perform Data Analysis?"<<endl<<"1 - Yes"<<endl<<"2 - No"<<endl;
		cin >> input;
		if(input == 1){

//MAKING SURE THE HEAP IS EMPTY BEFORE REFILLING
			if(pQueue.currSize != 0){
				pQueue.dequeueAllTest();
			}
//
			int patientNum;
			cout<<endl;
			cout<<"For how many patients would you like to test?"<<endl;
			cin >> patientNum;

//SETTING UP VARIABLES
			float total = 0;
			int runs = 500;

			while(runs != 0){
				clock_t t1, t2;
				t1 = clock();
				int temp = patientNum;

	//REFILLING QUEUE
				index = 0;
				while(temp != 0){
					pQueue.enqueue(Patient(name[index], priority[index], treatment[index]));
					temp--;
					index++;
				}

	//DEQUEUING ALL
				pQueue.dequeueAllTest();

				runs--;
				t2 = clock();
				total += ( (float)t2 - (float)t1 );
			}
			float seconds = total/CLOCKS_PER_SEC;
			seconds = seconds / 500.000; //getting average
			cout<<"The average runtime for enqueuing/dequeuing "<<patientNum<<" patients, out of 500 runs, is "<<seconds<<" seconds."<<endl;
		}
	}
}