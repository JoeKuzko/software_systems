#include "Header.h"

using namespace std;

void buffer::Read(string file){
	ifstream infile(file);
    string line;
    string columns;
    int count = 0;
    if (!infile)
    {
        while (!infile) //while the file does not exist
        {
            cout << "That file does not exist, please enter it again: ";
            cin >> file;
            infile.open(file);
        }
    }
    
    record myrecord;

	while (!infile.eof()) {
        getline(infile, line);
        count++;
        if (line != "")
        {
            if (count > 3) //skip the first 3 lines, which include the column labels
            {
                myrecord = unpack(line);
                pack(myrecord);
            }
        }
	}
    
	infile.close();
}

record buffer::unpack(string line) {

    record temp_record;
    for (int j = 0; j < col_chars.size(); j++) {
        for (int i = 0; i < line.length(); i++) { //for every character in line

            if (line[i] == ',') {
                j++;
                i++;
            }

            switch (col_chars[j])
            {
            case 'Z':
                temp_record.zipcode += line[i];
                break;
            case 'P':
                temp_record.city += line[i];
                break;
            case 'S':
                temp_record.state += line[i];
                break;
            case 'C':
                temp_record.county += line[i];
                break;
            case 'L':
                temp_record.latitude += line[i];
                break;
            case 'l':
                temp_record.longitude += line[i];
                break;
            }

        }
        break;
    }

    return temp_record;

}

void buffer::pack(record new_record) {
    vectorRecords.push_back(new_record); //add record to the vector
}

void buffer::Write() {

    sort(vectorRecords.begin(), vectorRecords.end()); //sort the vector to make processing easier



// Evaluate and ouput west,east,north, and south most zip codes for each state //
    record myrecord;
    myrecord = vectorRecords[0];
    string st = myrecord.state;
    const double reset = -999999; //value to restore westmost, eastmost, northmost, southmost values after every entry per state has been accounted for
    const int design = 55; //value for formatting output

    double westMost = reset, eastMost = reset;
    double northMost = reset, southMost = reset; //stores the (west,east,north,south) most value for each state. Set to impossible value to start.
    string zipWestMost, zipEastMost, zipNorthMost, zipSouthMost; //stores the zip code for the (west,east,north,south) most values.

    cout << string(design, '-') << endl; //header for output
    cout << setw(7) << "State" << setw(12) << "North-Most" << setw(12) << "South-Most" << setw(12) << "East-Most" << setw(12) << "West-Most" << endl; //header for output
    cout << string(design, '-') << endl; //header for output


    for (int i = 0; i < vectorRecords.size(); i++) //for every record in the vector
    {
        myrecord = vectorRecords[i]; //set myrecord equal to current record being read
        if (st == myrecord.state) { //the same state is being read
            if (stod(myrecord.longitude) < westMost || westMost == reset) //check for west most
            {
                westMost = stod(myrecord.longitude); //typecast the longitude and store it as the westmost value
                zipWestMost = myrecord.zipcode; //store the zipcode for this record
            }
            if (stod(myrecord.longitude) > eastMost || eastMost == reset) //check for east most
            {
                eastMost = stod(myrecord.longitude); //typecast the longitude and store it as the eastmost value
                zipEastMost = myrecord.zipcode; //store the zipcode for this record
            }
            if (stod(myrecord.latitude) > northMost || northMost == reset) //check for south most
            {
                northMost = stod(myrecord.latitude); //typecast the latitude and store it as the northmost value
                zipNorthMost = myrecord.zipcode; //store the zipcode for this record
            }
            if (stod(myrecord.latitude) < southMost || southMost == reset) //check for north most
            {
                southMost = stod(myrecord.latitude); //typecast the latitude and store it as the southmost value
                zipSouthMost = myrecord.zipcode; //store the zipcode for this record
            }
        }
        else {
            cout << setw(7) << vectorRecords[i - 1].state << setw(12) << zipNorthMost << setw(12) << zipSouthMost << setw(12) << zipEastMost << setw(12) << zipWestMost << endl; //output the info for the state

            st = myrecord.state;
            westMost = reset; //reset to impossible value
            eastMost = reset; //reset to impossible value
            northMost = reset; //reset to impossible value
            southMost = reset; //reset to impossible value
            i--; //decrement so that this current state is accounted for 
        }
    }
    cout << string(design, '-') << endl; //footer for output

}

bool operator <(const record& r1, const record& r2) {
    return r1.state < r2.state;  //compare the state of two records, to help with sorting
}

void buffer::col_names(string file) {
    ifstream filein(file);
    string line;
    string column;
    int count = 0;
    while (!filein.eof()) {
        getline(filein, line);
        column = column + line;
        count++;
        if (count == 3) { // 3rd get line is last column names
            break;
        }
    }
    filein.close();
    count = 0;
    line = "";
    for (int i = 0; i < column.length(); i++) {
        for (int j = 0; j < column.length(); j++) {
            if (column[j] == ',') {
                columns.push_back(line);
                line = "";
                j++;
                i = j;
            }
            line = line + column[j];
            line.erase(remove(line.begin(), line.end(), '\"'), line.end());
            i++;
        }
        columns.push_back(line);
    }
}

void buffer::convert() {
    for (int i = 0; i < columns.size(); i++) {
        if (columns[i] == "ZipCode") {
            col_chars.push_back('Z');
        }
        if (columns[i] == "PlaceName") {
            col_chars.push_back('P');
        }
        if (columns[i] == ("State")) {
            col_chars.push_back('S');
        }
        if (columns[i] == ("County")) {
            col_chars.push_back('C');
        }
        if (columns[i] == ("Lat")) {
            col_chars.push_back('L');
        }
        if (columns[i] == ("Long")) {
            col_chars.push_back('l');
        }
    }
}

void buffer::LIconvert() {
    for (int i = 0; i < vectorRecords.size(); i++) {
        string temp = "";
        int tempi = 0;
        for (int j = 0; j < col_chars.size(); j++) {
            switch (col_chars[j])
            {
            case 'Z':
                temp = temp + vectorRecords[i].zipcode + ',';
                break;
            case 'P':
                temp = temp + vectorRecords[i].city + ',';
                break;
            case 'S':
                temp = temp + vectorRecords[i].state + ',';
                break;
            case 'C':
                temp = temp + vectorRecords[i].county + ',';
                break;
            case 'L':
                temp = temp + vectorRecords[i].latitude + ',';
                break;
            case 'l':
                temp = temp + vectorRecords[i].longitude + ',';
                break;
            }
        }

        tempi = temp.size() + 3 ; // 3 is the length of the number of characters count and ',' included
        temp = to_string(tempi) + ',' + temp;
        records = records + temp;
    }
}

void buffer::LIFileHeader() {
    string temp;
    int tempi = 0;
    for (int i = 0; i < columns.size(); i++) {
        temp = temp + columns[i] + ',';
    }
    tempi = temp.size() + 3 ;
    temp = to_string(tempi) + ',' + temp;
    records = temp;
}

void buffer::LIwrite() {
    ofstream NewFile("Length Indicated.txt");
    NewFile << records;
    NewFile.close();
}
