

#include <iostream>
#include "Reader.h"
#include "Interpreter.h"

int main()
{
    Interpreter* interpreter = new Interpreter();
    Reader* reader = new ConsoleReader();

    while (true) {

        try {
            //cout << "\n";
            cout << interpreter->getReadinessSigil();
            string line = reader->getLine();
           // if (reader->isEof()) break;
            interpreter->run(line, cout, cout);
        } 
        catch (exception) {
            //TO-DO error
        }
    }
}


