#include "Memory.h"
#include <iostream>
using namespace std;

Memory* Memory::instance = nullptr;

Memory::Memory() {

}

Memory* Memory::getInstance() {
	if (instance == nullptr) {
		instance = new Memory();
	}
	return instance;
}

int Memory::get(string addr) {
	return memory[addr];
}

void Memory::set(string addr, int value) {
	memory[addr] = value;
}

void Memory::dump() {
	for (auto cell : memory) {
		cout << cell.first << " = " << cell.second << endl;
	}
}