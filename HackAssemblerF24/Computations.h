#pragma once
#include <map>
#include <string>
using namespace std;

class Computations
{
private:
	map<string, string> computations;
public:
	Computations();
	string find(string);
};