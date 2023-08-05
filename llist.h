/*****************************************************************
//  NAME:        Joseph Carmelo Averion
//
//  HOMEWORK:    project2
//  
//  CLASS:       ICS 212
//  
//  INSTRUCTOR:  Ravi Narayan
//  
//  DATE:        April 15, 2023
//  
//  FILE:        llist.h
//  
//  DESCRIPTION: Class definition for llist object, includes function
//               prototypes for the Bank Database Application
//  
******************************************************************/

#ifndef LLIST_H

#define LLIST_H

#include <iostream>
#include "record.h"

class llist
{
    private:
        record * start;
        char filename[20];
        int readfile();
        int writefile();
        void cleanup();

    public:
        llist();
        llist(char[]);
        llist(const llist&);
        ~llist();
        void addRecord(int, char[], char[]);
        int findRecord(int);
        void printAllRecords();
        int deleteRecord(int);
        llist& operator=(const llist&);
        friend std::ostream& operator<<(std::ostream&, const llist&);
};
#endif
