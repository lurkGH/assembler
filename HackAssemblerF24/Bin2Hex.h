#pragma once
#include <map>
#include <string>
using namespace std;

class Bin2Hex
{
private:
	map<string, char> bin2Hex;
public:
	Bin2Hex();
	char find(string);
	string Convert16Bin2Hex(string);
};

