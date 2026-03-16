#pragma once

#include <string>
#include <istream>
using namespace std;

//ideja je da reader ne ide line po line nego da vraca ceo input kad stigne do eof-a
//moze bar filereader tako da radi za sad

//tako da dodao bih osim getLine() i getInput() koja moze da bude virtuelna ali ne obavezna

class Reader {
public: 
	Reader(istream* input);
	virtual ~Reader() {}

	string getLine();
	bool isEof();

protected:
	istream* input;
};

class ConsoleReader : public Reader {
public: 
	ConsoleReader();
};

class FileReader : public Reader {
public:
	FileReader(string path);
	~FileReader();
};