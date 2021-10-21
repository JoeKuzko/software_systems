#ifndef Header_h
#define Header_h

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>


using namespace std;

class record {
public:
    string zipcode;
    string city;
    string state;
    string county;
    string latitude;
    string longitude;
};

class buffer {

public:
    vector <record> vectorRecords; //vector that will store records
    void Read(string);
    void col_names(string);
    void convert();
    vector <string> columns;
    vector <char>   col_chars;
    void Write();
    record unpack(string);
    void pack(record);
    friend bool operator< (const record& r1, const record& r2); //overload < operator
};


#endif // !Header_h

