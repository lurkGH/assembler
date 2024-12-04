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

class IllegalDestination : exception
{
private:
	string message;

public:
	IllegalDestination(const std::string& msg) {
		message = msg;
	}
	const char* what() const noexcept override {
		return message.c_str();
	}
};