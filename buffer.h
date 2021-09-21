
#ifndef buffer_h
#define buffer_h
#include <iostream>
#include <string>
#include <vector>
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


vector < vector<record>> vector_Array; // idkkkkk

class buffer {

public:
    void Read();
    void Write();
    record unpack(string);
    void pack(record);
    // bool compareStates(const Record& a, const Record& b)
      //   bool compareLat(const Record& a, const Record& b)

    

};

#endif