//  Copyright © 2018 by Jacob Christiansen. All rights reserved.
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>
#include <time.h>

using namespace std;

struct Patient{
    string name;
    int priority;
    int treatment;

    Patient(){
    };

    Patient(string thisname, string thispriority, string thistreatment){
    	name = thisname;
    	priority = stoi(thispriority);
    	treatment = stoi(thistreatment);
    };
};

struct Compare{
	bool operator()(const Patient &one, const Patient &two){
		if(one.priority != two.priority){
			return one.priority > two.priority;
		}
		else{
			return one.treatment > two.treatment;
		}
	}
};


int main(int argc, char *argv[]){
	cout<<endl<<"~~~~~~~~~~~~~~~~~~~~ Welcome to Priority Queue - STL Implementation ~~~~~~~~~~~~~~~~~~~~"<<endl;
	priority_queue<Patient, vector<Patient>, Compare> pQueue;

	ifstream fr;
	fr.open(argv[1]);

	string ln = "";
	int index = 0;
	string infoArr[880][3];

	getline(fr, ln, '\r'); //skips first line
	while(!fr.eof()){
		getline(fr, ln, ',');
		infoArr[index][0] = ln; //name
		getline(fr, ln, ',');
		infoArr[index][1] = ln; // priority
		getline(fr, ln, '\r');
		infoArr[index][2] = ln; //treatment
		index++;
	}

	//fill pQueue
	for(int i=0; i<index; i++){
		Patient newPatient(infoArr[i][0], infoArr[i][1], infoArr[i][2]);
		pQueue.push(newPatient);
	}
////////////////////////////////////////////////////////
	int input;
	cout<<endl<<"Would you like to print the Queue?"<<endl<<"1 - Yes"<<endl<<"2 - No"<<endl;
	cin >> input;
	if(input == 1){
		// print pQueue
		index = 0;
		while(!pQueue.empty()){
			Patient tempP = pQueue.top();
			cout<<index+1<<":\t"<<tempP.name<<",  "<<tempP.priority<<",  "<<tempP.treatment<<endl;
			pQueue.pop();
			index++;
		}
		//refilling queue
		for(int i=0; i<index; i++){
			Patient newPatient(infoArr[i][0], infoArr[i][1], infoArr[i][2]);
			pQueue.push(newPatient);
		}
	}

////////////////////////////////////////////////////////
	input = 0;
	// inputs
	while(input != 3){
		cout<<endl;
		cout<<"Would you like to dequeue?"<<endl<<"1 - Yes, one Patient"<<endl<<"2 - Yes, all Patients"<<endl<<"3 - No"<<endl;
		cin >> input;
		if(input == 1){//dequeue one
			Patient tempP = pQueue.top();
			pQueue.pop();
			cout<<"Dequeued "<<tempP.name<<",  "<<tempP.priority<<",  "<<tempP.treatment<<endl;
		}
		if(input == 2){//dequeue all
			while(!pQueue.empty()){
				Patient tempP = pQueue.top();
				pQueue.pop();
				cout<<"Dequeued "<<tempP.name<<",  "<<tempP.priority<<",  "<<tempP.treatment<<endl;
			}
		}
	}
////////////////////////////////////////////////////////
//RESETING QUEUE
	//dequeuing remainder
	while(!pQueue.empty()){
		Patient tempP = pQueue.top();
		pQueue.pop();
	}
	//refilling queue
	for(int i=0; i<index; i++){
		Patient newPatient(infoArr[i][0], infoArr[i][1], infoArr[i][2]);
		pQueue.push(newPatient);
	}
////////////////////////////////////////////////////////
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
					Patient newPatient(infoArr[index][0], infoArr[index][1], infoArr[index][2]);
					pQueue.push(newPatient);
					temp--;
					index++;
				}

	//DEQUEUING ALL
				while(!pQueue.empty()){
					Patient tempP = pQueue.top();
					pQueue.pop();
				}

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