
#include <iostream>
#include <fstream>
//#include <string>
//#include <map>
#include "Destinations.h"
#include "Jumps.h"
//#include "Computations.h"
//#include "Bin2Hex.h"

using namespace std;

int main(int argc, char* argv[])
{
	Destinations dstTbl;
	Jumps jmpTbl;
	//Computations compTbl;
	//Bin2Hex bin2HexTbl;

	cout << dstTbl.find("AMD") << endl;
	cout << dstTbl.find("error") << endl;

	cout << jmpTbl.find("JGT") << endl;
	cout << jmpTbl.find("error") << endl;

	//cout << compTbl.find("D&A") << endl;
	//cout << compTbl.find("error") << endl;

	// right click HackAssemblerF24, Properties, Debugging, command arguments "test test.asm"

	string inFileName, outFileName, inStr;

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