#include "Truncate.h"
#include <string>
#include <fstream>

using namespace std;

Truncate::Truncate(string filename):
	filename(filename) 
{
	takesInput = 0;
	makesOutput = 0;
}

void Truncate::execute() {
	ofstream File;
	File.open(filename, ios::trunc);
}