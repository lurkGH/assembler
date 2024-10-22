#pragma once
#include <map>
#include <string>
using namespace std;

class Destinations
{
private:
	map<string, string> destinations;
public:
	Destinations();
	string find(string);
};
