#include "buffer.h"

void buffer::Read()
{
    string file; 
    string  line;
    record myrecord;
    int count = 0;

    cout << "Enter a CSV file to output: ";
    cin >> file;
    ifstream filein;
    filein.open(file);
    if(!filein)
    {
        while (!filein)
        {
            cout << "That file does not exist, please enter it again: ";
            cin >> file;
            filein.open(file);
        }
    }
   


    while (!filein.eof())
    {
        getline(filein, line);
        count++;
        if (line != "")
        {
            if (count > 3)
            {
                myrecord = unpack(line);
                pack(myrecord);
               
            }
        }
    }
    Write();
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

        if (line[i] == ','|| line[i-1] ==',') {
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

    vectorRecords.push_back(new_record);
}

void buffer::Write() {

    sort(vectorRecords.begin(), vectorRecords.end()); //sort the vector to make processing easier



/////////////////////////////////////////////////////////////////////////////////
// Evaluate and ouput west,east,north, and south most zip codes for each state //
/////////////////////////////////////////////////////////////////////////////////
    record myrecord;
    myrecord = vectorRecords[0];
    string st = myrecord.state;

    double westMost = -999999, eastMost= -999999, northMost= -999999, southMost= -999999; //stores the (west,east,north,south) most value for each state. Set to impossible value to start.
    string zipWestMost, zipEastMost, zipNorthMost, zipSouthMost; //stores the zip code for the (west,east,north,south) most values.

    cout << string(55, '-') << endl;
    cout << setw(7) << "State"<< setw(12)<< "North-Most" << setw(12)<< "South-Most" << setw(12)<< "East-Most" << setw(12)<< "West-Most" << endl;
    cout << string(55, '-')<< endl;


    for(int i = 0; i < vectorRecords.size(); i++)
    {
        myrecord = vectorRecords[i]; //set myrecord equal to current record being read
        if(st == myrecord.state){ //the same state is being read
            if(stod(myrecord.latitude) < westMost || westMost == -999999) //check for west most
            {
                westMost = stod(myrecord.latitude); 
                zipWestMost = myrecord.zipcode;
            }
            if(stod(myrecord.latitude) > eastMost || eastMost == -999999) //check for east most
            {
                eastMost = stod(myrecord.latitude);
                zipEastMost = myrecord.zipcode;
            }
            if(stod(myrecord.longitude) < northMost || northMost == -999999) //check for south most
            {
                northMost = stod(myrecord.longitude);
                zipNorthMost = myrecord.zipcode;
            }
            if(stod(myrecord.longitude) > southMost || southMost == -999999) //check for north most
            {
                southMost = stod(myrecord.longitude);
                zipSouthMost = myrecord.zipcode;
            }
        }
        else{ 
            cout << setw(7) << vectorRecords[i-1].state<< setw(12)<< zipNorthMost << setw(12)<< zipSouthMost << setw(12)<< zipEastMost << setw(12)<< zipWestMost << endl;

            st = myrecord.state;
            westMost = -999999; //reset to impossible value
            eastMost = -999999; //reset to impossible value
            northMost = -999999; //reset to impossible value
            southMost = -999999; //reset to impossible value
            i--; //decrement so that this current state is accounted for 
        }
    }
     cout << string(55, '-')<< endl;

}
bool operator <(const record& r1, const record& r2) {
    return r1.state < r2.state;
}


