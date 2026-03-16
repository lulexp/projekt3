#include "Batch.h"
#include <fstream>
#include <vector>
#include "Reader.h"
#include "Interpreter.h"

Batch::Batch(string filename) :
	filename(filename) {
    takesInput = 0;
    makesOutput = 1;
}


void Batch::execute() {
    //isti kod kao u main-u
    Interpreter* interpreter = new Interpreter();
    Reader* reader = new FileReader(filename);

    while (true) {

        try {
            string line = reader->getLine();
            if (output) interpreter->run(line, *output, *output);
            else if (line.empty()) continue;
            else interpreter->run(line, cout, cout);
            if (reader->isEof()) break;
        }
        catch (exception) {
            //TO-DO error
        }
    }
}