
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "buffer.h"


using namespace std;


int main() {
    buffer mybuffer;

    mybuffer.Read();






    /*
    buffer Mybuffer;  // creates object of buffer
    record Myrecord;

    vector<string> states;
    vector<record> records;

    string file = "Copy of us_postal_codes.csv";
    string line;
    int count=0;

    ifstream filein(file);
    while (!filein.eof()) 
    {
        getline(filein, line); // have it check if string in line is empty
        count++;
        if (count > 3) 
        {
            Myrecord = Mybuffer.unpack(line);
            //Mybuffer.pack(Myrecord);
            cout << Myrecord.zipcode << endl;
            cout << Myrecord.city << endl;
            cout << Myrecord.state << endl;
            cout << Myrecord.county << endl;
            cout << Myrecord.latitude << endl;
            cout << Myrecord.longitude << endl;
            cout << endl;
        }
    }
    */
    return 0;
}










