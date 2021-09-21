#include "buffer.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void buffer::Read()
{
    string file = "Copy of us_postal_codes.csv";    // might have different names of file
    string  line;
    record myrecord;
    buffer mybuffer;
    int count = 0;

    ifstream filein(file);


    while (!filein.eof())
    {
        getline(filein, line);
        count++;
        if (line != "")
        {
            if (count > 3)
            {
                myrecord = mybuffer.unpack(line);
                mybuffer.pack(myrecord);
                
            }
        }
    }
    // or maybe have it sort right here????
    mybuffer.Write();
}

record buffer::unpack(string line) {
    /*
    @breif takes in the line from getline
    and puts it into the proper variables in record
    and should return the record
    */

    record temp_record;
    int temp_count = 0;
    for (int i = 0; i < line.length(); i++) {

        if (line[i] == ',') {
            temp_count++;
            i++;
        }

        switch (temp_count)
        {
        case 0:
            temp_record.zipcode += line[i];
            break;
        case 1:
            temp_record.city += line[i];
            break;
        case 2:
            temp_record.state += line[i];
            break;
        case 3:
            temp_record.county += line[i];
            break;
        case 4:
            temp_record.latitude += line[i];
            break;
        case 5:
            temp_record.longitude += line[i];
            break;
        }

    }
    return temp_record;

}

void buffer::pack(record new_record) {
    // take new_record and put into 2d vector
}

void buffer::Write() {
    // outputs the northern most, western, eastern, southern, zipcodes into a table of a state
    // and will sort the vector??? 
}