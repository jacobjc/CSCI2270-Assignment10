//  Copyright © 2018 by Jacob Christiansen. All rights reserved.
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>

using namespace std;

#include "pQueue-LL.hpp"

LinkedList::LinkedList(){
	head = createPatient("", 0, 0, NULL);
	tail = createPatient("", 0, 0, NULL);
}

LinkedList::~LinkedList(){
}

Patient* LinkedList::createPatient(string thisname, int thispriority, int thistreatment, Patient *thisnext){
	Patient* newPatient = new Patient;
	newPatient->name = thisname;
	newPatient->priority = thispriority;
	newPatient->treatment = thistreatment;
	newPatient->next = thisnext;
	return newPatient;
}

void LinkedList::enqueue(Patient *add){
	length++;

	if(head->next == NULL){ //if queue is empty
		head = add;
		tail = add;
		head->next = tail;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////
	else{
		if(add->priority > tail->priority){ //deals with values greater than tail
			add->next = tail->next;
			tail->next = add;
			tail = add;
			tail->next = NULL;
			return;
		}
		if(add->priority <= head->priority){ //deals with values less than head
			if(add->priority < head->priority){
				add->next = head;
				head = add;
				return;
			}
			else if(add->treatment < head->treatment){
				add->next = head;
				head = add;
				return;
			}
			else{
				add->next = head->next;
				head->next = add;
				return;
			}
		}
//////////////////////////////////////////////////////////////////////////////////////////////////
		Patient *search = head;
		while(search->next != NULL){ //add one Patient of each priority

			if(add->priority > search->priority && add->priority < search->next->priority){
				if(add->priority < search->next->priority){
					add->next = search->next;
					search->next = add;
					return;
				}
			}
			search = search->next;
		}
//////////////////////////////////////////////////////////////////////////////////////////////////
		search = head; //handles equal prioities
		while(search->next->priority != add->priority){
			search = search->next;
		}
		if(search->next->treatment > add->treatment){
			add->next = search->next;
			search->next = add;
			return;
		}
		while(search->next->priority == add->priority && search->next->treatment < add->treatment){
			search = search->next;
		}
		add->next = search->next;
		search->next = add;
	}
}

void LinkedList::dequeue(){
	length--;
	if(length == 0){
		cout<<"Dequeued "<<head->name<<" from the LL, the LL is now empty."<<endl;
		free(head);
		return;
	}
	cout<<"Dequeued "<<head->name<<" from the LL, ";
	Patient *temp = head;
	head = head->next;
	free(temp);
	cout<<head->name<<" is the new head."<<endl;
}

void LinkedList::dequeueAll(){
	while(length !=0){
		dequeue();
	}
}

void LinkedList::dequeueAllTest(){
	while(length !=0){
		length--;
		if(length == 0){
			free(head);
			return;
		}
		Patient *temp = head;
		head = head->next;
		free(temp);
	}
}

void LinkedList::printQueue(){
	Patient *list = head;
	int i = 0;

	while(list != NULL){
		cout<<i+1<<": "<<list->name<<",  "<<list->priority<<",  "<<list->treatment<<endl;
		i++;
		list = list->next;
	}
}

int main(int argc, char *argv[]){
	cout<<endl<<"~~~~~~~~~~~~~~~~~~~~ Welcome to Priority Queue - LINKED LIST Implementation ~~~~~~~~~~~~~~~~~~~~"<<endl;
	LinkedList pQueue;

	ifstream fr;
	fr.open(argv[1]);

	string ln;
	string name[880];
	int priority[880];
	int treatment[880];

	getline(fr, ln, '\r'); //skips first line

	int index = 0;

	while(!fr.eof()){
		getline(fr, ln, ',');
		name[index] = ln;
		getline(fr, ln, ',');
		priority[index] = stoi(ln);
		getline(fr, ln, '\r');
		treatment[index] = stoi(ln);

		pQueue.enqueue(pQueue.createPatient(name[index], priority[index], treatment[index], NULL));
		index++;
	}

	//dequeue
	int input;
	// inputs
	while(input != 4){
		cout<<endl;
		cout<<"Would you like to test?"<<endl<<"1 - Print the Queue"<<endl<<"2 - Dequeue, one Patient"<<endl<<"3 - Dequeue, all Patients"<<endl<<"4 - No"<<endl;
		cin >> input;
		if(input == 1){
			pQueue.printQueue();
		}
		if(input == 2){//dequeue one
			pQueue.dequeue();
		}
		if(input == 3){//dequeue all
			pQueue.dequeueAll();
		}
	}

//////////////////////////////////////////////////////////////////////////////////////////////////

	input = 0;
	while(input != 2){
		cout<<endl;
		cout<<"Would you like to perform Data Analysis?"<<endl<<"1 - Yes"<<endl<<"2 - No"<<endl;
		cin >> input;
		if(input == 1){
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
					pQueue.enqueue(pQueue.createPatient(name[index], priority[index], treatment[index], NULL));
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