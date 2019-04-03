//  Copyright © 2018 by Jacob Christiansen. All rights reserved.
#ifndef PQUEUELL_H
#define PQUEUELL_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

struct Patient{
    string name;
    int priority;
    int treatment;

    Patient(){
    }

    Patient(string thisName, int thisPriority, int thisTreatment){
        name = thisName;
        priority = thisPriority;
        treatment = thisTreatment;
    }

    bool operator<(const Patient & temp)const{
        if(this->priority < temp.priority ){
            return true;
        }
        else if(this->priority > temp.priority){
            return false;
        }
        else if(this->treatment < temp.treatment){
            return true;
        }
        return false;
    }

    bool operator>(const Patient & temp)const{
        if(this->priority > temp.priority ){
            return true;
        }
        else if(this->priority < temp.priority){
            return false;
        }
        else if(this->treatment > temp.treatment){
            return true;
        }
        return false;
    }
};

class MinHeap{
    public:
        MinHeap();
        ~MinHeap();
        void enqueue(Patient);
        void dequeue();
        void dequeueAll();
        void dequeueAllTest();
        int capacity = 880;
        int currSize = 0;
        Patient theHeap[881];
    protected:
    private:
        void heapify(int);
};

#endif //PQUEUELL_H