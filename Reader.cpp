#include "Reader.h"

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

//ideja je da reader ne ide line po line nego da vraca ceo input kad stigne do eof-a
//moze bar filereader tako da radi za sad

Reader::Reader(istream* input) 
	: input(input) {}

string Reader::getLine() {
	string line;

	getline(*input, line);

	if (line.size() > 512) {
		line.erase(512, line.size() - 512);
	}

	return line;
}	


bool Reader::isEof() {
	if (input->eof()) {
		input->clear();
		return true;
	}

	return false;
}

ConsoleReader::ConsoleReader() 
	: Reader(&cin) {}

FileReader::FileReader(string path) :
	Reader(new ifstream(path)) {}

FileReader::~FileReader() {
	delete input;
}