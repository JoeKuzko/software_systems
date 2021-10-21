#include "Header.h"

using namespace std;

int main(){
	buffer mybuffer;
	string FileName = "zipcode.csv";
	//cout << "This program will take data from a CSV file and return the north-most, south-most, east-most,  \nand west-most zipcode for each state\n\n";
	//cout << "Enter a .csv file: ";
	//cin >> FileName;
	mybuffer.col_names(FileName);
	mybuffer.convert();
	mybuffer.Read(FileName);
	mybuffer.Write();

}