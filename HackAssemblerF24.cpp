
#include <iostream>
#include "Destinations.h";
#include "Jumps.h";
using namespace std;

int main()
{
	Destinations dstTbl;
	Jumps jmpTbl;

	cout << dstTbl.find("AMD") << endl;
	cout << dstTbl.find("error") << endl;

	cout << jmpTbl.find("JGT") << endl;
	cout << jmpTbl.find("error") << endl;
}