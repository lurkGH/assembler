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
#include <chrono>
using namespace std;

vector<string> instructions;
vector<string> binaryInstructions;
map<string, int> labels;
map<string, int>::iterator itLabels;
map<string, int> symbols;
map<string, int>::iterator itSymbols;

void convertToBinary(int value);

int main(int argc, char* argv[]) {
	auto start = std::chrono::high_resolution_clock::now();
	Destinations dstTbl;
	Jumps jmpTbl;
	Computations compTbl;
	Bin2Hex bin2HexTbl;
	string inFileName, outFileName, inStr;
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

	// Opens the input file
	ifstream inFile(inFileName);
	// Opens the output file
	ofstream outFile(outFileName);

	// check if file was successfully opened
	if (!inFile) {
		cerr << "Error: Input file '" << inFileName << "' not found." << endl;
		return 1;
	}

	// check if file was successfully opened
	if (!outFile) {
		cerr << "Error: Output file '" << outFileName << "' not found." << endl;
		return 1;
	}

#pragma region Pass1
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
#pragma endregion Pass1

#pragma region Pass2
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
			// A instructions:
			string addrName = inst.substr(1, inst.length() - 1);
			itLabels = labels.find(addrName);
			itSymbols = symbols.find(addrName);

			// If address exists in neither
			if (itLabels == labels.end() && itSymbols == symbols.end()) {
				// Save address of variable to the symbols table
				symbols.insert(pair<string, int>(addrName, memoryAddress));
				convertToBinary(memoryAddress);

				// Increment memory address for use with next variable name
				memoryAddress++;
			}
			// If address exists only in the Labels table
			else if (itLabels != labels.end() && itSymbols == symbols.end()) {
				// Get linie number of Label from labels table
				int lineNumber = itLabels->second;

				convertToBinary(lineNumber);
			}
			// If address exists only in the Symbols table
			else if (itLabels == labels.end() && itSymbols != symbols.end()) {
				// Get memory adddress of variable from symbols table
				int addr = itSymbols->second;

				convertToBinary(addr);
			}
			// If address exists in both tables (shouldn't happen)
			else {
				// WIP
			}
		}
	}
#pragma endregion Pass2

#pragma region Pass3
	// Pass 3
	// Generate output file
	outFile << "v2.0 raw" << endl;

	for (string inst : binaryInstructions) {
		// Convert to hex and write
		outFile << bin2HexTbl.Convert16Bin2Hex(inst) << endl;
	}
	outFile.close();

	ofstream lstFile(outFileName + ".lst");

	lstFile << "List file for: " << inFileName << endl;
	lstFile << endl << endl << "**** Code ****" << endl;

	for (int i = 0; i < binaryInstructions.size(); i++) {
		lstFile << binaryInstructions[i] << "\t" << bin2HexTbl.Convert16Bin2Hex(binaryInstructions[i]) << "\t\t" << instructions[i] << endl;
	}

	lstFile << endl << endl << "**** Symbols ****" << endl;

	if (symbols.size() != 0) {
		for (pair<string, int> symbol : symbols) {
			lstFile << symbol.second << "\t\t" << symbol.first << endl;
		}
	}
	else {
		lstFile << "No symbols found" << endl;
	}

	lstFile << endl << endl << "**** Labels ****" << endl;

	if (labels.size() != 0) {
		for (pair<string, int> label : labels) {
			lstFile << label.second << "\t\t" << label.first << endl;
		}
	}
	else {
		lstFile << "No labels found" << endl;
	}

	lstFile.close();

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;

	cout << "Assembly Complete \n\t" << "Look for files: \n\t" << outFileName << "\n\t" << outFileName + ".lst" << endl;
	cout << "Elapsed Time: " << elapsed.count() << endl;

#pragma endregion Pass3
}

void convertToBinary(int value) {
	// Convert to binary and write to binaryInstructions vector
	char symb[16] = { 0 };
	_itoa_s(value, symb, 2);
	string str(symb);
	string binStr = string(16 - str.length(), '0') + str;
	binaryInstructions.push_back(binStr);
}