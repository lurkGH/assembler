#include "Computations.h"

Computations::Computations() {
	// a == 0
	computations["0"] = "101010";
	computations["1"] = "111111";
	computations["-1"] = "111010";
	computations["D"] = "001100";
	computations["A"] = "110000";
	computations["!D"] = "001101";
	computations["!A"] = "110001";
	computations["-D"] = "001111";
	computations["-A"] = "110011";
	computations["D+1"] = "011111";
	computations["A+1"] = "110111";
	computations["D-1"] = "001110";
	computations["A-1"] = "110010";
	computations["D+A"] = "000010";
	computations["D-A"] = "010011";
	computations["A-D"] = "000111";
	computations["D&A"] = "000000";
	computations["D|A"] = "010101";
	// a == 1
	computations["M"] = "110000";
	computations["!M"] = "110001";
	computations["-M"] = "110011";
	computations["M+1"] = "110111";
	computations["M-1"] = "110010";
	computations["D+M"] = "000010";
	computations["D-M"] = "010011";
	computations["M-D"] = "000111";
	computations["D&M"] = "000000";
	computations["D|M"] = "010101";
}

string Computations::find(string str) {
	map<string, string>::iterator it;

	it = computations.find(str);

	if (it != computations.end()) {
		return it->second;
	}
	else {
		return "Computation code not found: " + str;
	}
}