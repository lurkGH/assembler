#include "Destinations.h"
#include <boost/algorithm/string.hpp>

Destinations::Destinations() {
	destinations.insert(pair<string, string>("NULL", "000"));
	destinations.insert(pair<string, string>("M", "001"));
	destinations.insert(pair<string, string>("D", "010"));
	destinations.insert(pair<string, string>("MD", "011"));
	destinations.insert(pair<string, string>("A", "100"));
	destinations.insert(pair<string, string>("AM", "101"));
	destinations.insert(pair<string, string>("AD", "110"));
	destinations.insert(pair<string, string>("AMD", "111"));
}

string Destinations::find(string str) {
	map<string, string>::iterator it;

	it = destinations.find(str);
	boost::to_upper(str);

	if (it != destinations.end()) {
		return it->second;
	}
	else {
		throw IllegalDestination(str + " not found in Destinations Table");
		//return "Destination code not found: " + str;
	}
}
