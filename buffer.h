#ifndef BUFFER_H
#define BUFFER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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

    //ostream & operator << (ostream &out, const record &r)
};

class buffer {

public:

    vector <record> vectorRecords;

    void Read();
    void Write();
    record unpack(string);
    void pack(record);

    friend bool operator< (const record& r1, const record& r2);

};
#include "methods.cpp"
#endif