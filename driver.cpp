#include <iomanip>
#include "buffer.h"



using namespace std;


int main(int argc, char* argv[]) //take in arguments from command line
{
    string file = argv[1]; //first argument is the name of the csv file
    string arr[argc];
    for (int i = 2; i < argc; i++) //for every command argument after the first (which is the filename)
    {
        arr[i-2] = argv[i];
    }

    buffer mybuffer; //create buffer instance
    mybuffer.Read(file); 
    mybuffer.EvaluateArguments(arr, argc);
    mybuffer.PrintKeyData();

    return 0;
}










