#include "CountWC.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

CountWC::CountWC(string opt) 
	: opt(opt) 
{}

void CountWC::execute() {
	int m_count = 0;

	//parser obezbedjuje da ce sigurno biti jedna od ove dve opcije
	if (!input || !output) return; //TO-DO error;

	char c;
	bool inWord = 0;

	while (input->get(c)) {
		c_count++;
		if (isspace(c)) inWord = 0;
		else if (!inWord) {
			inWord = 1;
			w_count++;
		}
	}

	if (opt == "-w") m_count = w_count;

	else m_count = c_count;

	(*output) << m_count;

	if (!dynamic_cast<ofstream*>(output)) cout << "\n";
}