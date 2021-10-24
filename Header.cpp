#include "header.h"

string header::addHeaderInformation()
{
    
    string hInfo;

    structureType = "Length Indicated Records, Comma Seperated fields";
    version = 1.0;
    // !headerSize determined after seeing length of header
    // recordSizeByte hard coded in header.h
    recordSizeFormat = "ASCII";
    indexFileName = "indexFile.txt";
    indexSchema = "Zipcode, ByteLocation";
    //fieldCount hard coded in header.h
    //record cound set in buffer::Read()
    //primaryKey set in determineOrder
    //fieldOrder set in determineOrder

    hInfo = "Structure: " + structureType + ","+
            "Version: " + to_string(version) + ","+
            "Record Size Byte: " + to_string(recordSizeByte) + ","+
            "Record Size Format: " + recordSizeFormat + ","+
            "Index File Name: " + indexFileName + ","+
            "Index Schema: " + indexSchema + ","+
            "Number of fields in each record: " + to_string(fieldCount) + ","+
            "Number of records in file: " + to_string(recordCount) + ","+
            "Primary Key: " + to_string(primaryKey) + ","+
            "Field Order: [" + to_string(fieldOrder[0]) + ","+ to_string(fieldOrder[1]) + ","+ to_string(fieldOrder[2]) + ","+ to_string(fieldOrder[3]) + ","+ to_string(fieldOrder[4]) + ","+ to_string(fieldOrder[5]) + "]\n";
    
    headerSize = hInfo.size();
    string headerSizeString = to_string(headerSize);
    headerSize = headerSize + headerSizeString.length(); //set headerSize equal to the contents of the header, the number of bytes the headerSize takes, and + 1 for the comma included after the size.
   
    hInfo.insert(0, to_string(headerSize) + ",");

    return hInfo;
}

void header::determineOrder(string columnHeaders) 
{
    string label ="";
    int j = 0;
    for (int i = 0; i < columnHeaders.size(); i++)
    {
        if(columnHeaders[i] != ',')
        {
            label = label + columnHeaders[i];
        }
        if(label == "\"ZipCode\""){
            fieldOrder[j] = 1;
            primaryKey = j+1;
            j++;
            label = ""; //reset label
        }
        else if(label == "\"PlaceName\""){
            fieldOrder[j] = 2;
            j++;
            label = ""; //reset label
        }
        else if(label == "State"){
            fieldOrder[j] = 3;
            j++;
            label = ""; //reset label
        }
        else if(label == "County"){
            fieldOrder[j] = 4;
            j++;
            label = ""; //reset label
        }
        else if(label == "Lat"){
            fieldOrder[j] = 5;
            j++;
            label = ""; //reset label
        }
        else if(label == "Long"){
            fieldOrder[j] = 6;
            j++;
            label = ""; //reset label    
        }
    }
}