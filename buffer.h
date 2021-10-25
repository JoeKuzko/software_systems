//---------------------------------------------------------------------------
/// @file buffer.h
/// @brief The header file for the classes buffer and record
/// @author Authors:    Joseph Kuzko & Matthew Xiong  
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
*   @brief  class for the structure of data stored as strings
*   @author Joseph Kuzko
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
    *   @author Matthew Xiong
    */
class buffer {

public:

    vector <record> vectorRecords; //vector that will store records
    vector <primaryKey> primaryKeyIndex;
    header myheader; //header which contains information about the file
    void EvaluateArguments(string arr[], int count);
    void Read(string file);
    int searchForPrimaryKey(primaryKey);
    void createPrimaryKeyIndexFile();
    void PrintKeyData();

    /**
    *   @brief      Sorts and Outputs the most North,South,West and East Zip code for each state
    *   @author:    Evan Burdick
    *   @pre        Data has been read in and packed into the vector
    *   @post       Data has been sorted and put into a table
    *
    */
    void Write();


    record unpack(string);

    /**
    *   @brief      Packs each temp_record and puts them into the vector
    *   @author:    Matthew Xiong 
    *   @param      Object of myrecord (structured line of data) passed in
    *   @pre        Must be an object of class record created and passed in
    *   @post       New record has been added into the vector 
    *  
   */
    void pack(record);
    void createLengthIndicatedFile(string); //creates the length indicated file with the header at the top
    friend bool operator< (const record& r1, const record& r2); //overload < operator
};
#include "buffer.cpp"
#endif