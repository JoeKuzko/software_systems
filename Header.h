#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class header{
public:
    string addHeaderInformation(); //adds the header file information from the file and then returns the string with the header information added
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