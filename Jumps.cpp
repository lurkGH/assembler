#include "Jumps.h"

Jumps::Jumps() {
	jumps.insert(pair<string, string>("null", "000"));
	jumps.insert(pair<string, string>("JGT", "001"));
	jumps.insert(pair<string, string>("JEQ", "010"));
	jumps.insert(pair<string, string>("JGE", "011"));
	jumps.insert(pair<string, string>("JLT", "100"));
	jumps.insert(pair<string, string>("JNE", "101"));
	jumps.insert(pair<string, string>("JLE", "110"));
	jumps.insert(pair<string, string>("JMP", "111"));
}

string Jumps::find(string str) {
	map<string, string>::iterator it;

	it = jumps.find(str);

	if (it != jumps.end()) {
		return it->second;
	}
	else {
		return "Jump code not found: " + str;
	}
}
