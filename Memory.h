#pragma once

#include <map>
#include <string>
using namespace std;

class Memory {
public: 

	static Memory* getInstance();

	int get(string addr);
	void set(string addr, int value);
	void dump();

private: 

	Memory();
	static Memory* instance;

	map<string, int> memory;
};