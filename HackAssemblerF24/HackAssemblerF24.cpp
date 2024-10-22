#include <iostream>
#include <fstream>
#include "Destinations.h"
#include "Jumps.h"
#include "Computations.h"
#include "Bin2Hex.h"
using namespace std;

int main(int argc, char* argv[])
{
	Destinations dstTbl;
	Jumps jmpTbl;
	Computations compTbl;
	Bin2Hex bin2HexTbl;
	string inFileName, outFileName, inStr;

	cout << "Testing Destination Instructions:" << endl;
	cout << dstTbl.find("AMD") << endl;
	cout << dstTbl.find("error") << endl << endl;

	cout << "Testing Jump Instructions:" << endl;
	cout << jmpTbl.find("JGT") << endl;
	cout << jmpTbl.find("error") << endl << endl;

	cout << "Testing Computation Instructions:" << endl;
	cout << compTbl.find("!D") << endl;
	cout << compTbl.find("error") << endl << endl;

	cout << "Testing file input and output:" << endl;

	// To add test files: right click HackAssemblerF24 in Solution Explorer, go to Properties, Debugging, and in Command Arguments put "test test.asm"

	if (argc < 2) {
		cout << "You must enter two parameters: input file and output file names" << endl;
	}
	else {
		inFileName = "C:\\mydata\\" + string(argv[1]) + ".asm";
		outFileName = "C:\\mydata\\" + string(argv[2]);
	}

	ifstream inFile(inFileName);

	while (getline(inFile, inStr, '\r')) {
		cout << inStr << endl;
	}
}