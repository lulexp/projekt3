#include "Remove.h"
#include <string>
#include <cstdio>

using namespace std;

Remove::Remove(string filename):
	filename(filename) 
{
	takesInput = 0;
	makesOutput = 0;
}

void Remove::execute() {
	remove(filename.c_str());
}