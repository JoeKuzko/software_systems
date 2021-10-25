//---------------------------------------------------------------------------
/// @file header.h
/// @brief The header file for the class 'header'
/// @author Evan Burdick, Joseph Kuzko,& Matthew Xiong
//---------------------------------------------------------------------------
#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
*   @class  header
*   @brief  class for the structure of the header
*   @author	Evan Burdick
*/
class header{
public:

    /**
    *   @brief  this function creates the header string and returns it
    *   @author Evan Burdick
    *   @pre	there is a file to be read with a header
    *
    */
    string addHeaderInformation(); //adds the header file information from the file and then returns the string with the header information added
	
	    /**
    *   @brief  takes in a string of column names then determines the order to read the information and creates a vector for it
    *   @author Evan Burdick
	*	@param	string of te column names
    *   @pre	there is column names to be read
	*	@post	creates a vector in which the columns are to be read for the splitting of information
    *
    */
    void determineOrder(string); //determines the order of the fields in the record, and updates fieldOrder[]

    int headerSize; //size of the header
    string structureType; //type of record (Length indicated, comma seperated, etc.)
    double version; //version # of the file
    int recordSizeByte = 2; //number of bytes that indicates the size of each record
    string recordSizeFormat; //How the record size's number is formatted (ASCII)
    string indexFileName; //Name of the index file
    string indexSchema; //What the index file is organized like (Zipcode, Reference #) (example: 56303,47291)
    int recordCount; //Number of records in file
    int fieldCount = 6; //Number of fields per record (6 including zipcode,city,state,county,lat,lon)
    int primaryKey; //Which field is the primary key
    int fieldOrder[]; //keeps track of the order of the fields in a record (in cases where the csv is column randomized)

};
#include "header.cpp"
#endif
