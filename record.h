/*****************************************************************
//  NAME:        Joseph Carmelo Averion
//
//  HOMEWORK:    project2
//  
//  CLASS:       ICS 212
//  
//  INSTRUCTOR:  Ravi Narayan
//  
//  DATE:        April 14, 2023
//  
//  FILE:        record.h
//  
//  DESCRIPTION: Record header file for the record struct definition
//  
******************************************************************/

#ifndef RECORD_H

#define RECORD_H
struct record
{
    int                accountno;
    char               name[30];
    char               address[50];
    struct record*     next;
};
#endif
