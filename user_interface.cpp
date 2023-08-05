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
//  FILE:        user_interface.cpp
//
//  DESCRIPTION: The file where the bank UI runs
//
******************************************************************/

#include <iostream>
#include <cstring>
#include "llist.h"
#include "record.h"

void getAddress(char[], int);

/*****************************************************************
//  Function name: main
//  
//  DESCRIPTION:   User input for the database
//  
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//  
//  Return values:  0 : Quits the database
//
****************************************************************/

int main(int argc, char* argv[])
{
    int running;
    char optionInput[20];

    #ifdef DEBUG
        std::cout << "\nDebug Mode On" << std::endl;
    #endif

    running = 1;

    char filename[13] = "database.txt";

    llist database(filename);

    while (running == 1)
    {
        std::cout << "\nBank Record Management System\n\n" << std::endl;

        std::cout << "What do you want to do?\n" << std::endl;

        std::cout << "add: add a new record" << std::endl;

        std::cout << "printall: see all the records" << std::endl;

        std::cout << "find: find a record" << std::endl;

        std::cout << "delete: delete a record"  << std::endl;

        std::cout << "quit: exit the manager\n" << std::endl;

        std::cout << "Type Option Here: ";

        std::cin.getline(optionInput, 20);

        #ifdef DEBUG
            std::cout << "\n***DEBUG MODE***\n" << std::endl;
            std::cout << "What the user typed: " << optionInput << std::endl;
            std::cout << "\n***DEBUG MODE***\n" << std::endl;
        #endif

        if (strcmp(optionInput, "a") == 0
            || strcmp(optionInput, "ad") == 0
            || strcmp(optionInput, "add") == 0)
        {
            int accNumberInput;
            int validInt;
            char nameInput[30];
            char addressInput[50];

            do
            {
                validInt = 1;
                std::cout << "Type Account Number: ";
                std::cin >> accNumberInput;
                if (std::cin.fail())
                {
                    std::cout << "Invalid Input. Account Number must be an integer" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    validInt = 0;
                }
                else if (accNumberInput <= 0)
                {
                    std::cout << "Invalid Input. Account Number"
                    << " cannot be negative or 0" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    validInt = 0;
                }
            }
            while (validInt != 1);

            std::cin.get();

            std::cout << "Type Name: ";
            std::cin.getline(nameInput, 30);

            std::cout << "Type Address (Press Enter on a"
            << " blank line to send address): " << std::endl;
            getAddress(addressInput, 50);

            #ifdef DEBUG
               std::cout << "\n***DEBUG MODE***\n" << std::endl;
               std::cout << "Account Number Input: " << accNumberInput << std::endl;
               std::cout << "Name Input: " << nameInput << std::endl;
               std::cout << "Address Input: \n" << addressInput;
               std::cout << "\n***DEBUG MODE***\n" << std::endl;
            #endif

            database.addRecord(accNumberInput, nameInput, addressInput);
            std::cout << "Record Added!" << std::endl;
        }
        else if (strcmp(optionInput, "p") == 0
            || strcmp(optionInput, "pr") == 0
            || strcmp(optionInput, "pri") == 0
            || strcmp(optionInput, "prin") == 0
            || strcmp(optionInput, "print") == 0
            || strcmp(optionInput, "printa") == 0
            || strcmp(optionInput, "printal") == 0
            || strcmp(optionInput, "printall") == 0)
        {
            std::cout << "\nPrinting All Records\n" << std::endl;
            database.printAllRecords();
        }
        else if (strcmp(optionInput, "f") == 0
            || strcmp(optionInput, "fi") == 0
            || strcmp(optionInput, "fin") == 0
            || strcmp(optionInput, "find") == 0)
        {
            int accNumberInput;
            int found;
            int validInt;

            do
            {
                validInt = 1;
                std::cout << "Type Account Number: ";
                std::cin >> accNumberInput;
                if (std::cin.fail())
                {
                    std::cout << "Invalid Input. Account Number must be an integer" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    validInt = 0;
                }
                else if (accNumberInput <= 0)
                {
                    std::cout << "Invalid Input. Account Number"
                    << " cannot be negative or 0" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    validInt = 0;
                }
            }
            while (validInt != 1);

            std::cin.get();

            found = database.findRecord(accNumberInput);

            if (found == 0)
            {
                std::cout << "\nRecord(s) found!" << std::endl;
            }
            else
            {
                std::cout << "\nRecord(s) not in the Database" << std::endl;
            }
        }
        else if (strcmp(optionInput, "d") == 0
            || strcmp(optionInput, "de") == 0
            || strcmp(optionInput, "del") == 0
            || strcmp(optionInput, "dele") == 0
            || strcmp(optionInput, "delet") == 0
            || strcmp(optionInput, "delete") == 0)
        {
            int accNumberInput;
            int deleted;
            int validInt;

            do
            {
                validInt = 1;
                std::cout << "Type Account Number: ";
                std::cin >> accNumberInput;
                if (std::cin.fail())
                {
                    std::cout << "Invalid Input. Account Number must be an integer" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    validInt = 0;
                }
                else if (accNumberInput <= 0)
                {
                    std::cout << "Invalid Input. Account Number"
                    << " cannot be negative or 0" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    validInt = 0;
                }
            }
            while (validInt != 1);

            std::cin.get();

            deleted = database.deleteRecord(accNumberInput);

            if (deleted == 0)
            {
                std::cout << "\nRecord(s) Deleted!" << std::endl;
            }
            else
            {
                std::cout << "\nRecord(s) not in the Database" << std::endl;
            }
        }
        else if (strcmp(optionInput, "q") == 0
            || strcmp(optionInput, "qu") == 0
            || strcmp(optionInput, "qui") == 0
            || strcmp(optionInput, "quit") == 0)
        {
            std::cout << "\nExiting. Goodbye\n" << std::endl;
            running = 0;
        }
        else if (strcmp(optionInput, "") == 0)
        {
            std::cout << "Please Type an Option" << std::endl;
        }
        else
        {
            std::cout << "Invalid Input" << std::endl;
        }

        std::cout << "----------------------------------------------" << std::endl;
    }

    return 0;
}

/*****************************************************************
//  Function name: getAddress
//  
//  DESCRIPTION:   Gets the address
//  
//  Parameters:    address (char[]) : the char array that will get the address input
//                 arraySize (int)  : size of array
//                                  to the program.
//  
//  Return values: void
//
****************************************************************/

void getAddress(char address[], int maxSize)
{
    char ch;
    int index = 0;
    int enterCounter;
    enterCounter = 0;

    #ifdef DEBUG
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
        std::cout << "getAddress called" << std::endl;
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
    #endif

    while (enterCounter < 2 && index < maxSize - 2)
    {
        std::cin.get(ch);
        if (ch == '\n')
        {
            enterCounter++;
        }
        else
        {
            enterCounter = 0;
        }

        address[index++] = ch;

        #ifdef DEBUG
            std::cout << "***DEBUG MODE*** char read: " << ch << std::endl;
        #endif
    }

    if (index == maxSize - 2)
    {
        index++;
    }

    address[index] = '\0';

    #ifdef DEBUG
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
        std::cout << "Final Address: \n" << address;
        std::cout << "\n***DEBUG MODE***\n" << std::endl;
    #endif
}
