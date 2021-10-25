//---------------------------------------------------------------------------
/// @file buffer.h
/// @brief The header file for the class 'buffer'
/// @author Evan Burdick, Joseph Kuzko,& Matthew Xiong
//---------------------------------------------------------------------------

#ifndef BUFFER_H
#define BUFFER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "header.h"
#include "primaryKey.h"
using namespace std;

/**
*   @class  record
*   @brief  class for the structure of data stored as strings, and the size of the record stored as an integer
*   @author Joseph Kuzko,
*/
class record {

public:
    string zipcode;
    string city;
    string state;
    string county;
    string latitude;
    string longitude;
    int recordSize;
};

    /**
    *   @class  buffer
    *   @brief  class that stores data into a vector and reads, writes,
    *               packs and unpacks data
    *   @author Evan Burdick, Joseph Kuzko, Matthew Xiong, Jordan Knight
    */
class buffer {

public:

    vector <record> vectorRecords; //vector that will store records
    vector <primaryKey> primaryKeyIndex; //vector for storing primary keys
    header myheader; //header which contains information about the file

    /**
    *   @brief  This function takes in the command line arguments given by the user and then turns them into usable zipcode integers.
	*				then it searches the primary key for said zipcode and checks for existence then creates primary key index file
    *   @author Evan Burdick
    *   @param1 command line args
    *   @param2 Count is the number of arguments
    *   @pre	there is arguments taken in from command line and the count of how many command line arguments there are
    *
    */
    void EvaluateArguments(string arr[], int count);

    /**
    *   @brief      Reads in file name and then reads the file and its information. distributes the various
	*					information to the different functions
    *   @author		Joseph Kuzko
    *   @param		String of the file name
    *   @pre		there is a file name to open
    *   @post      	Data has been read into various functions
    *
    */
    void Read(string file);

    /**
    *   @brief  Searches to see if the primary key is in the file, if so, returns the location
    *   @author	Evan Burdick
    *   @param  The primary key 'k' thats being searched for
    *   @pre	there is a primary key to look for
    *   @post 	returns either -1 which means not found or returns the location where its found
    *
    */
    int searchForPrimaryKey(primaryKey);

    /**
    *   @brief 	Creates the primary key index file and stores the keys as well as their locations
    *   @author Evan Burdick
    *   @pre 	Records have been read in
	*	@post	the primary key index file has been made or an error message is displayed
    *
    */
    void createPrimaryKeyIndexFile();

    /**
    *   @brief	opens file to search for key data and then displays it if found
    *   @author	Matthew Xiong
    *   @pre	there is zipcode data to print that was found
	*	@post	displays a data table for the user to see the results of the search
    *
    */
    void PrintKeyData();

    /**
    *   @brief      Sorts and Outputs the most North,South,West and East Zip code for each state
    *   @author:	Matthew Xiong
    *   @pre        Data has been read in and packed into the vector
    *   @post       Data has been sorted and put into a table
    *
    */
    void Write();

    /**
    *   @brief      Unpacks record information line by line
    *   @author		Joseph Kuzko
    *   @param      A string which is a line of data
    *   @pre        There is information that has been packed into record
    *   @post       A line of data has been unpacked into temp_record
    *
   */
    record unpack(string);

    /**
    *   @brief      Packs each record and puts them into the vector
    *   @author		Jordan Knight
    *   @param      Object of myrecord (structured line of data) passed in
    *   @pre        Must be an object of class record created and passed in
    *   @post       New record has been added into the vector
    *
   */
    void pack(record);

    /**
    *   @brief Creates the length indicated file with the header at the top
    *   @author	Jordan Knight
    *   @param  A string
    *   @pre Records have been read in
    *
    */
    void createLengthIndicatedFile(string);
    friend bool operator< (const record& r1, const record& r2); //overload < operator
};
#include "buffer.cpp"
#endif
