//  Copyright © 2018 by Jacob Christiansen. All rights reserved.
#ifndef PQUEUELL_H
#define PQUEUELL_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Patient;

struct Patient{
    string name;
    int priority;
    int treatment;
    Patient *next = NULL;
};

class LinkedList{
    public:
        LinkedList();
        ~LinkedList();
        Patient* createPatient(string,int,int,Patient*);
        void enqueue(Patient *);
        void dequeue();
        void dequeueAll();
        void dequeueAllTest();
        void printQueue();
        int length = 0;

    protected:
    private:
        Patient *head = NULL;
        Patient *tail = NULL;

};
#endif //PQUEUELL_H