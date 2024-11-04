#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "Destinations.h"
#include "Jumps.h"
#include "Computations.h"
#include "Bin2Hex.h"
#include <boost/algorithm/string.hpp>
using namespace std;

int main(int argc, char* argv[])
{
	Destinations dstTbl;
	Jumps jmpTbl;
	Computations compTbl;
	Bin2Hex bin2HexTbl;
	string inFileName, outFileName, inStr;
	vector<string> instructions;
	vector<string> binaryInstructions;
	map<string, int> labels;
	map<string, int>::iterator itLabels;
	map<string, int> symbols;
	map<string, int>::iterator itSymbols;
	int lineCount = 0;
	int memoryAddress = 100;
	string dest;
	string comp;
	string jump;
	string prefix;

	if (argc < 2) {
		cout << "You must enter two parameters: input file and output file names" << endl;
	}
	else {
		inFileName = "C:\\mydata\\" + string(argv[1]) + ".asm";
		outFileName = "C:\\mydata\\" + string(argv[2]);
	}

	ifstream inFile(inFileName);

	// Pass 1
	// Processes comments and labels
	while (getline(inFile, inStr, '\n')) {

		boost::erase_all(inStr, " ");
		boost::to_upper(inStr);

		int commentLoc = inStr.find("//");
		// Removes comments
		if (commentLoc != string::npos) {
			inStr = inStr.substr(0, commentLoc);
		}

		// Removes empty lines
		if (inStr.size() == 0) {
			continue;
		}

		// Removes parentheses from loop targets
		if (inStr.find("(") != string::npos && inStr.find(")") != string::npos) {
			int leftLoc = inStr.find("(");
			int rightLoc = inStr.find(")");
			string label = inStr.substr(leftLoc + 1, rightLoc - (leftLoc + 1));
			itLabels = labels.find(label);
			if (itLabels == labels.end()) {
				labels.insert(pair<string, int>(label, lineCount));
			}
			else {
				cout << "Duplicate Label at line: " + lineCount << endl;
			}
		}
		else {
			instructions.push_back(inStr);
			lineCount++;
		}
	}

	// Pass 2
	for (string inst : instructions) {
		// C instructions:
		if (inst.substr(0, 1) != "@") {
			int eqLoc = inst.find("=");
			int scLoc = inst.find(";");

			// D=M (found = but not ;)
			if (eqLoc != string::npos && scLoc == string::npos) {
				dest = inst.substr(0, eqLoc);
				comp = inst.substr(eqLoc + 1, inst.length() - (eqLoc + 1));
				jump = "NULL";
			}

			// D=M;jmp (found = and ;)
			if (eqLoc != string::npos && scLoc != string::npos) {
				dest = inst.substr(0, eqLoc);
				comp = inst.substr(eqLoc + 1, scLoc - (eqLoc + 1));
				jump = inst.substr(scLoc + 1, inst.length() - (scLoc + 1));
			}

			// D;jgt (found ; but not =)
			if (eqLoc == string::npos && scLoc != string::npos) {
				dest = "NULL";
				comp = inst.substr(0, scLoc);
				jump = inst.substr(scLoc + 1, inst.length() - (scLoc + 1));
			}

			if (comp.find("M") != string::npos) {
				prefix = "1001";
			}
			else {
				prefix = "1000";
			}

			binaryInstructions.push_back(prefix + compTbl.find(comp) + dstTbl.find(dest) + jmpTbl.find(jump));
		}
		else {
			// A instruction:
			string addrName = inst.substr(1, inst.length() - 1);
			itLabels = labels.find(addrName);
			itSymbols = symbols.find(addrName);
			char symb[16] = { 0 };

			// @Loop
			// @X

			// If address exists in neither
			if (itLabels == labels.end() && itSymbols == symbols.end()) {
				symbols.insert(pair<string, int>(addrName, memoryAddress));
				_itoa_s(memoryAddress, symb, 2);
				string str(symb);
				string binStr = string(16 - str.length(), '0') + str;
				binaryInstructions.push_back(binStr);
				memoryAddress++;
			}
			// If address exists only in the Labels table
			else if (itLabels != labels.end() && itSymbols == symbols.end()) {

			}
			// If address exists only in the Symbols table
			else if (itLabels == labels.end() && itSymbols != symbols.end()) {
				int addr = itSymbols->second;
				_itoa_s(addr, symb, 2);
				string str(symb);
				string binStr = string(16 - str.length(), '0') + str;
				binaryInstructions.push_back(binStr);
				cout << "test" << endl;
				cout << binStr << endl;
			}
			// If address exists in both tables (shouldn't happen)
			else {

			}
		}
	}

	// DEBUG
	for (string inst : binaryInstructions) {
		cout << inst << endl;
	}
}
