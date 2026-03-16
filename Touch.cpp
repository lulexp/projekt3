#include "Touch.h"
#include <fstream>

using namespace std;

Touch::Touch(string filename):
	filename(filename) 
{
	takesInput = 0;
	makesOutput = 0;
}

bool Touch::fileExists(string filename) {
	ifstream file(filename);
	return file.good();
}

void Touch::execute() {
	if (!fileExists(filename)) {
		ofstream File(filename);
	}
	else {
		//TO-DO error;
		cout << "Greska fajl vec postoji";
		if (!dynamic_cast<ofstream*>(output)) cout << "\n";
	}
}