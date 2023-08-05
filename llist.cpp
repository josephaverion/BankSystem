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
//  FILE:        llist.cpp
//
//  DESCRIPTION: The file where the bank database runs
//
******************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include "llist.h"

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Constructor for creating a llist for database
//      
//  Parameters:    none
//
//  Return values: none
//
****************************************************************/

llist::llist()
{
    this->start = NULL;
    strcpy(this->filename, "database.txt");

    #ifdef DEBUG
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
        std::cout << "llist created with default filename" << std::endl;
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
    #endif

    readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Constructor for creating a llist for database
//                 adding previous saved records
//
//  Parameters:    file (char[]) : specific file to get records from
//
//  Return values: none
//
****************************************************************/

llist::llist(char file[])
{
    this->start = NULL;
    strcpy(this->filename, file);

    #ifdef DEBUG
        std::cout << "\n***DEBUG MODE***" << std::endl;
        std::cout << "llist created with specific filename" << std::endl;
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
    #endif

    readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Copy Constructor for llist
//
//  Parameters:    toCopy (const llist&) : llist object to copy
//
//  Return values: none
//
****************************************************************/

llist::llist(const llist& toCopy)
{
    record * currRec;
    record * nextRec;
    currRec = toCopy.start;
    this->start = NULL;
    strcpy(this->filename, toCopy.filename);

    #ifdef DEBUG
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
        std::cout << "Copying llist" << std::endl;
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
    #endif

    while (currRec != NULL)
    {
        nextRec = currRec->next;
        this->addRecord(currRec->accountno, currRec->name, currRec->address);
        currRec = nextRec;
    }
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   Destructor for deallocating the llist
//
//  Parameters:    none
//
//  Return values: none
//
****************************************************************/

llist::~llist()
{
    writefile();
    cleanup();

    #ifdef DEBUG
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
        std::cout << "llist deleted" << std::endl;
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
    #endif
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds record to database
//      
//  Parameters:    uaccountno (int) : account number of record to be added
//                 uname (char[]) : name in the  record to be added
//                 uaddress (char[]): address in the record to be added
//
//  Return values: void
//
****************************************************************/

void llist::addRecord(int uaccountno, char uname[], char uaddress[])
{
    record * toadd;
    toadd = new record();

    toadd->accountno = uaccountno;
    strcpy(toadd->name, uname);
    strcpy(toadd->address, uaddress);
    toadd->next = NULL;

    #ifdef DEBUG
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
        std::cout << "addRecord called" << std::endl;
        std::cout << "Account Number Added: " << uaccountno << std::endl;
        std::cout << "Name Added: " << uname << std::endl;
        std::cout << "Address Added: " << "\n" <<  uaddress;
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
    #endif

    if (this->start == NULL)
    {
        this->start = toadd;
    }
    else if ((start)->accountno >= uaccountno)
    {
        toadd->next = start;
        this->start = toadd;
    }
    else if (this->start->next == NULL)
    {
        (this->start)->next = toadd;
    }
    else
    {
        record * prevRec;
        record * currRec;
        int found;

        prevRec = this->start;
        currRec = this->start;
        found = 0;

        do
        {
            if (currRec->accountno >= uaccountno)
            {
                found = 1;
                prevRec->next = toadd;
                toadd->next = currRec;
            }
            else
            {
                prevRec = currRec;
                currRec = currRec->next;
            }
        }
        while (currRec != NULL && found != 1);

        if (currRec == NULL)
        {
            prevRec->next = toadd;
        }
    }
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   Prints all records in database
//
//  Parameters:    none
//
//  Return values: void
//
****************************************************************/

void llist::printAllRecords()
{
    record * currRec;
    currRec = this->start;

    #ifdef DEBUG
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
        std::cout << "printAllRecords called" << std::endl;
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
    #endif

    while (currRec != NULL)
    {
        std::cout << "Acount Number: " << currRec->accountno << std::endl;
        std::cout << "Name: " << currRec->name << std::endl;
        std::cout << "Address: \n" << currRec->address;
        currRec = currRec->next;
    }

    if (this->start == NULL)
    {
        std::cout << "There are no Records in the list" << std::endl;
    }
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   Find a specific record in database
//      
//  Parameters:    accNum (int) : account number of record(s) to find
//
//  Return values: -1 : record not found
//                  0 : record found
//
****************************************************************/

int llist::findRecord(int uaccountno)
{
    record * currRec;
    int found;

    currRec = this->start;
    found = -1;

    #ifdef DEBUG
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
        std::cout << "findRecord called" << std::endl;
        std::cout << "Account Number of Record(s) to Find: "
        << uaccountno << std::endl;
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
    #endif

    while (currRec != NULL && found != 0)
    {
        if (currRec->accountno == uaccountno)
        {
            found = 0;
            do
            {
                std::cout << "Account Number: " << currRec->accountno << std::endl;
                std::cout << "Name: " << currRec->name << std::endl;
                std::cout << "Address: \n" << currRec->address;
                currRec = currRec->next;
            }
            while (currRec != NULL && currRec->accountno == uaccountno);
        }
        else
        {
            currRec = currRec->next;
        }
    }
    return found;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   Delete a specific record in database
//
//  Parameters:    accNum (int) : account number of record(s) to delete
//
//  Return values: -1 : record not found to delete
//                  0 : record found to delete
//
****************************************************************/

int llist::deleteRecord(int uaccountno)
{
    int found;
    record * prevRec;
    record * currRec;
    record * nextRec;

    found = -1;
    prevRec = NULL;
    currRec = this->start;

    #ifdef DEBUG
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
        std::cout << "deleteRecord called" << std::endl;
        std::cout << "Account Number of Record(s) to Delete: "
        << uaccountno << std::endl;
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
    #endif

    while (currRec != NULL && found != 0)
    {
        if (currRec->accountno == uaccountno)
        {
            found = 0;
            do
            {
                nextRec = currRec->next;
                delete currRec;
                currRec = nextRec;
            }
            while (currRec != NULL && currRec->accountno == uaccountno);
            if (prevRec != NULL && currRec != NULL)
            {
                prevRec->next = currRec;
            }
            else if (prevRec != NULL && currRec == NULL)
            {
                prevRec->next = NULL;
            }
            else if (prevRec == NULL && currRec != NULL)
            {
                this->start = currRec;
            }
            else if (prevRec == NULL && currRec == NULL)
            {
                this->start = NULL;
            }
        }
        else
        {
            prevRec = currRec;
            currRec = currRec->next;
        }
    }
    return found;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   saves the records into a txt file
//
//  Parameters:    none
//
//  Return values: -1 : file failed to write to
//                  0 : file successfully to write to
//
****************************************************************/

int llist::writefile()
{
    record * currRec;
    std::ofstream outStream;
    int couldOpen;
    int numrecords;
    numrecords = 0;
    outStream.open(this->filename);

    currRec = this->start;

    couldOpen = 0;
    if (outStream.fail())
    {
        couldOpen = -1;
    }

    #ifdef DEBUG
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
        std::cout << "writeFile called" << std::endl;
        std::cout << "File to Save Records to: " << filename
        << "\n" << std::endl;
    #endif

    while (currRec != NULL && couldOpen == 0)
    {
        numrecords++;
        outStream << currRec->accountno << std::endl;
        outStream << currRec->name << std::endl;
        outStream << currRec->address;

        #ifdef DEBUG
            std::cout << "Account Number Saved " << numrecords << ": "
            << currRec->accountno << std::endl;
            std::cout << "Name Saved " << numrecords << ": "
            << currRec->name << std::endl;
            std::cout << "Address Saved "<< numrecords << ": "
            << currRec->address << std::endl;
        #endif

        currRec = currRec->next;
    }

    #ifdef DEBUG
        std::cout << "Amount of records: " << numrecords << std::endl;
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
    #endif
    outStream.close();

    return couldOpen;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   saves the records into a txt file
//
//  Parameters:    none
//
//  Return values: -1 : file failed to write to
//                  0 : file successfully to write to
//
****************************************************************/

int llist::readfile()
{
    std::ifstream inStream;
    int couldOpen;
    int filesize;
    int numrecords;
    numrecords = 0;

    #ifdef DEBUG
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
        std::cout << "readFile called" << std::endl;
        std::cout << "File to Read Records from: " << filename
        << "\n" << std::endl;
    #endif

    inStream.open(this->filename);

    couldOpen = 0;
    if (inStream.fail())
    {
        couldOpen = -1;
    }

    if (couldOpen == 0)
    {
        inStream.seekg(0, inStream.end);
        filesize = inStream.tellg();
        inStream.seekg(0, inStream.beg);
    }

    if (couldOpen == 0 && filesize > 0)
    {
        char ch;
        while (inStream.get(ch))
        {
            inStream.unget();
            int uaccountno;
            char uname[30];
            char uaddress[50];
            int index;
            int enterCounter;
            numrecords++;

            inStream >> uaccountno;
            inStream.get();
            inStream.getline(uname, 30);

            enterCounter = 0;
            index = 0;

            while (enterCounter < 2)
            {
                inStream.get(ch);
                if (ch == '\n')
                {
                    enterCounter++;
                }
                else
                {
                    enterCounter = 0;
                }

                uaddress[index++] = ch;
            }

            uaddress[index] = '\0';

            #ifdef DEBUG
                std::cout << "Account Number Read " << numrecords << ": "
                << uaccountno  << std::endl;
                std::cout << "Name Read " << numrecords << ": "
                << uname << std::endl;
                std::cout << "Address Read " << numrecords << ": \n"
                << uaddress << std::endl;
            #endif

            addRecord(uaccountno, uname, uaddress);
        }

        #ifdef DEBUG
            std::cout << "Amount of records: " << numrecords << std::endl;
            std::cout << "\n***DEBUG MODE***\n" << std::endl;
        #endif

        inStream.close();
    }
    return couldOpen;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   release all allocated spaces in heap and assign NULL to start
//
//  Parameters:    none
//
//  Return values: void
//
****************************************************************/

void llist::cleanup()
{
    record * currRec;
    record * nextRec;
    currRec = this->start;

    #ifdef DEBUG
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
        std::cout << "cleanup called" << std::endl;
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
    #endif

    while (currRec != NULL)
    {
        nextRec = currRec->next;
        delete currRec;
        currRec = nextRec;
    }

    this->start = NULL;
}

/*****************************************************************
//
//  Function name: operator=
//
//  DESCRIPTION:   Overload assignment operator for the llist class
//
//  Parameters:    toCopy (const llist&) : llist instance to copy
//
//  Return values: llist& : return by reference in order to avoid 
//                          constructor and destructor being called
//
****************************************************************/

llist& llist::operator=(const llist& toCopy)
{
    record * currRec;
    record * nextRec;
    currRec = toCopy.start;
    strcpy(this->filename, toCopy.filename);

    #ifdef DEBUG
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
        std::cout << "Copying llist" << std::endl;
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
    #endif

    this->cleanup();

    while (currRec != NULL)
    {
        nextRec = currRec->next;
        this->addRecord(currRec->accountno, currRec->name, currRec->address);
        currRec = nextRec;
    }

    return *this;
}

/*****************************************************************
//
//  Function name: operator<<
//
//  DESCRIPTION:   Overload assignment operator for the llist class
//
//  Parameters:    os (ostream&) : handles the output stream
//                 toCopy (const llist&) : llist instance to print all records
//
//  Return values: ostream& : for combining the operator in a chain
//
****************************************************************/

std::ostream& operator<<(std::ostream& os, const llist& toPrint)
{
    record * currRec;
    currRec = toPrint.start;

    #ifdef DEBUG
        os << "\n***DEBUG MODE***\n" << std::endl;
        os << "printing all records using << operator" << std::endl;
        os << "\n***DEBUG MODE***\n" << std::endl;
    #endif

    while (currRec != NULL)
    {
        os << "Acount Number: " << currRec->accountno << std::endl;
        os << "Name: " << currRec->name << std::endl;
        os << "Address: \n" << currRec->address;
        currRec = currRec->next;
    }

    if (toPrint.start == NULL)
    {
        os << "There are no Records in the list" << std::endl;
    }

    return os;
}
