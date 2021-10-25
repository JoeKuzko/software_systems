//---------------------------------------------------------------------------
/// @file driver.cpp
/// @brief This is the driver file
/// @author Evan Burdick, Joseph Kuzko,& Matthew Xiong
//---------------------------------------------------------------------------
#include <iomanip>
#include "buffer.h"

using namespace std;

int main(int argc, char* argv[]) //take in arguments from command line
{
    if (argc == 1) //user did not enter in any arguments 
    {
        cout << "You need to enter in arguments! Enter then in like so: ./a.exe filename.extention arguments" << endl;
        abort(); //abort to avoid errors
    }

    string file = argv[1]; //first argument is the name of the csv file
    string arr[argc];
    for (int i = 2; i < argc; i++) //for every command argument after the first (which is the filename)
    {
        arr[i-2] = argv[i];
    }
    buffer mybuffer; //create buffer instance
    mybuffer.Read(file);
    if(argc > 2) //user entered at least one argument after the filename
    {
        mybuffer.EvaluateArguments(arr, argc);
        mybuffer.PrintKeyData();
    }
    else //user only entered the filename (outputs Zipcode 1.0 functionality)
    {
        mybuffer.Write();
    }
    return 0;
}
