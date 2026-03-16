#include "Prompt.h"
#include <string>

Prompt::Prompt(string new_sigil) :
	new_sigil(new_sigil) 
{
	takesInput = 1;
	makesOutput = 0;
}

void Prompt::execute() {
	
}

string Prompt::get_Sigil() {
	return new_sigil;
}