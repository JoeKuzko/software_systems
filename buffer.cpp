//---------------------------------------------------------------------------
/// @file buffer.cpp
/// @brief The file that drives the program essentially, reads in file and makes proper calls to pack/unpack
/// @author Evan Burdick, Joseph Kuzko,& Matthew Xiong
//---------------------------------------------------------------------------
#include "buffer.h"

//see header for info
void buffer::Read(string file)
{

    record myrecord;
    string headerRecordString ="", line, tempString;
    string columnHeaders; //concatenation of all of the column headers, to determine their order
    char c;
    int commaCount = 0; //keep track of number of commas in data (to determine how many fields/records there are)

    ifstream filein;
    filein.open(file);

    if(!filein)
    {
        cout << "The file you have entered does not exist, re-run the program with the correct file name"<<endl;
        abort();
    }
    for (int i = 0; i < 3; i++) //gets the first 3 lines of file, which contain information on how the columns are ordered
    {
        getline(filein, line);

        if(line == ""){
            cout << "The file you have entered is empty, please re-run the program with a correct file"<< endl;
            abort();
        }
         columnHeaders = columnHeaders + line;
    }

    myheader.determineOrder(columnHeaders); //determines the order of the columns

    while (!filein.eof())
    {
        getline(filein, line);
        if (line != "")
        {
            myrecord = unpack(line);
            pack(myrecord);
        }
    }

    filein.close(); //close the file

    myheader.recordCount = vectorRecords.size();

    headerRecordString = myheader.addHeaderInformation(); // get header record string

    createLengthIndicatedFile(headerRecordString);
}
void buffer::createLengthIndicatedFile(string headerRecord) {

    record temp_record;
    ofstream fileout;
    fileout.open("lengthIndicated.txt"); //open the file
    fileout << headerRecord;
    for (int i = 0; i < myheader.recordCount; i++) //for each record, print the record to the file
    {
        temp_record = vectorRecords[i];
        fileout << temp_record.recordSize<< ","; //first, output the length of the record
        for (int i = 0; i < myheader.fieldCount; i++)
        {
            if(myheader.fieldOrder[i] == 1){
                fileout <<temp_record.zipcode << ",";
            }
            else if (myheader.fieldOrder[i] == 2){
                fileout <<temp_record.city << ",";
            }
            else if (myheader.fieldOrder[i] == 3){
                fileout <<temp_record.state << ",";
            }
            else if (myheader.fieldOrder[i] == 4){
                fileout <<temp_record.county << ",";
            }
            else if (myheader.fieldOrder[i] == 5){
                fileout <<temp_record.latitude << ",";
            }
            else if (myheader.fieldOrder[i] == 6){
                fileout <<temp_record.longitude << ",";
            }
        }
    }
    fileout.close(); //close the file before leaving
}
//see header for info
record buffer::unpack(string line) {
    record temp_record;
    temp_record.recordSize = line.length() + myheader.recordSizeByte +2;
    int temp_count = 0, switchTemp;
    string record[myheader.fieldCount];
    for (int i = 0; i <line.length(); i++) { //for every character in line

        if (line[i] == ','|| line[i-1] ==',') {
            temp_count++;
            i++;
        }
        switchTemp = myheader.fieldOrder[temp_count];

        switch (switchTemp)
        {
        case 1:
            temp_record.zipcode += line[i];
            break;
        case 2:
            temp_record.city += line[i];
            break;
        case 3:
            temp_record.state += line[i];
            break;
        case 4:
            temp_record.county += line[i];
            break;
        case 5:
            temp_record.latitude += line[i];
            break;
        case 6:
            temp_record.longitude += line[i];
            break;
        }
    }
    return temp_record;
}

//see header for info
void buffer::pack(record new_record) {

    vectorRecords.push_back(new_record); //add record to the vector
}
void buffer::EvaluateArguments(string arg[], int count) {
    primaryKey k;
    int zipcode, location;
    string argument;
    for (int i = 0; i < count; i++) //for every command argument after the first (which is the filename)
    {
        argument = arg[i];
        if (argument[0] == '-') //argument prefix
        {
            if (argument[1] =='Z'|| argument[1]== 'z') //zip code argument
            {
                argument.erase(0,2); //erase the -z from the argument
                zipcode = stoi(argument); //typecast the string zipcode into an integer
                k.key = zipcode;
                location = searchForPrimaryKey(k); //set the location of key if it exists,
                k.byteLocation = location;
                primaryKeyIndex.push_back(k); //push the key into the vector of primary keys
            }
        }
    }
    createPrimaryKeyIndexFile();
}
void buffer::createPrimaryKeyIndexFile(){
    ofstream outfile;
    outfile.open(myheader.indexFileName); //open the file
    primaryKey k;

    outfile << "Key Locations marked as \"-1\" do not exist in the csv data file."<<endl;
    outfile << string(70, '-') <<endl;
    for (int i = 0; i < primaryKeyIndex.size(); i++)
    {
        k = primaryKeyIndex[i];
        outfile<< left << setw(10)<< "PrimaryKey: " << left << setw(6)<<k.key << left<< setw(1)<< " | "<< left << setw(10)<<"Location: "<< k.byteLocation << endl; //print key index to file
    }
    outfile.close(); //close the file
}
int buffer::searchForPrimaryKey(primaryKey k) { //searches to see if the primary key is in the file, if so, returns the location

    string line;
    ifstream filein;
    filein.open("lengthIndicated.txt"); //open the file
    int location =0,totalLocation = 0;
    string numberString;
    getline(filein, line); //skip first line which contains the header information

        for (int i = 0; i < myheader.recordCount; i++)
        {
            record r = vectorRecords[i];
            location = r.recordSize;
            if(stoi(r.zipcode) == k.key) //found the key and recorded location
            {
                filein.close(); //close the file
                return(totalLocation); //return the found key location
            }
            totalLocation = totalLocation + location; //update the total location
        }
            filein.close(); //close the file
            return(-1); //key was not found, set to negative number to indicate it wasn't
}
//see header for info
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
    cout << setw(7) << "State"<< setw(12)<< "North-Most" << setw(12)<< "South-Most" << setw(12)<< "East-Most" << setw(12)<< "West-Most" << endl; //header for output
    cout << string(design, '-')<< endl; //header for output

    for(int i = 0; i < vectorRecords.size(); i++) //for every record in the vector
    {
        myrecord = vectorRecords[i]; //set myrecord equal to current record being read
        if(st == myrecord.state){ //the same state is being read
            if(stod(myrecord.longitude) < westMost || westMost == reset) //check for west most
            {
                westMost = stod(myrecord.longitude); //typecast the longitude and store it as the westmost value
                zipWestMost = myrecord.zipcode; //store the zipcode for this record
            }
            if(stod(myrecord.longitude) > eastMost || eastMost == reset) //check for east most
            {
                eastMost = stod(myrecord.longitude); //typecast the longitude and store it as the eastmost value
                zipEastMost = myrecord.zipcode; //store the zipcode for this record
            }
            if(stod(myrecord.latitude) > northMost || northMost == reset) //check for south most
            {
                northMost = stod(myrecord.latitude); //typecast the latitude and store it as the northmost value
                zipNorthMost = myrecord.zipcode; //store the zipcode for this record
            }
            if(stod(myrecord.latitude) < southMost || southMost == reset) //check for north most
            {
                southMost = stod(myrecord.latitude); //typecast the latitude and store it as the southmost value
                zipSouthMost = myrecord.zipcode; //store the zipcode for this record
            }
        }
        else{
            cout << setw(7) << vectorRecords[i-1].state<< setw(12)<< zipNorthMost << setw(12)<< zipSouthMost << setw(12)<< zipEastMost << setw(12)<< zipWestMost << endl; //output the info for the state

            st = myrecord.state;
            westMost = reset; //reset to impossible value
            eastMost = reset; //reset to impossible value
            northMost = reset; //reset to impossible value
            southMost = reset; //reset to impossible value
            i--; //decrement so that this current state is accounted for
        }
    }
     cout << string(design, '-')<< endl; //footer for output

}
void buffer:: PrintKeyData(){
    ifstream inFile;
    inFile.open("lengthIndicated.txt");
    string line;
    const int design = 140; //value for formatting output
    primaryKey k;
    bool falseKey = false;
    getline(inFile, line); //ignore the first line, which contains header information

    cout << string(design, '-') << endl; //header for output
    cout << left<< setw(12)<< "Zipcode"<< left<<setw(40)<< "City" << left<<setw(12)<< "State" << left<<setw(40)<< "County" << left<<setw(15)<< "Latitude" << left<<setw(15)<< "Longitude" << endl; //header for output
    cout << string(design, '-') << endl; //header for output

    for (int i = 0; i < primaryKeyIndex.size(); i++) //for every primarykey in the index
    {
        k = primaryKeyIndex[i];
        if(k.byteLocation == -1){
            falseKey = true;
        }
        for (int i = 0; i < myheader.recordCount; i++)
        {
            record r = vectorRecords[i];
            if(stoi(r.zipcode) == k.key) //found the key and recorded location
            {
                cout << left<< setw(12)<< r.zipcode<< left<<setw(40)<< r.city<< left<<setw(12)<< r.state<< left<<setw(40)<< r.county << left<<setw(15)<< r.latitude<< left<<setw(15)<< r.longitude << endl;
            }
        }
        inFile.close();
    }
    if (falseKey) //there was an incorrect key found, output all of the incorrect keys
    {
        cout << "\n\n\nThese keys did not exist in the file: ";
        for (int i = 0; i < primaryKeyIndex.size(); i++)
        {
            k = primaryKeyIndex[i];
            if(k.byteLocation == -1) //the location was not found for this key
            {
                cout <<" " <<k.key << ","; //output the key
            }
        }
    }
}
bool operator <(const record& r1, const record& r2) {
    return r1.state < r2.state;  //compare the state of two records, to help with sorting
}
