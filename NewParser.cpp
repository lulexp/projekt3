#include "NewParser.h"

#include "Echo.h"
#include "Time.h"
#include "Date.h"
#include "Touch.h"
#include "Truncate.h"
#include "Remove.h"
#include "CountWC.h"
#include "Tr.h"
#include "Head.h"
#include "Batch.h"
#include "Prompt.h"

#include<fstream>

using namespace std;

NewParser::NewParser() {}

vector<vector<Token>> NewParser::getSegments(vector<Token> tokens) {
	vector<Token> segment;
	vector<vector<Token>> segments;
	for (Token s : tokens) {
		if (s.parameter != "|") {
			segment.push_back(s);
		}
		else {
			if (segment.empty()) {
				/*TO-DO: ExceptionHandler()*/
			}
			else {
				segments.push_back(segment);
				segment.clear();
			}
		}
	}
	if(!segment.empty()) segments.push_back(segment);

	return segments;
}

void checkStringArgument(vector<Token> segment, IOdata* IOdata) {

}

/*
vector<Token> setType(IOdata* IOdata, vector<Token> segment, int idx) {
	if (IOdata->input != "file") {
		if (segment.size() == idx + 1) {
			if (segment[idx].inQuotes) IOdata->input = "string", IOdata->inputString = segment[idx].parameter, segment.erase(segment.begin() + idx);
			else IOdata->input = "file", IOdata->inputFile = segment[idx].parameter, segment.erase(segment.begin() + idx);
		}
		else if (segment.size() == idx) IOdata->input = "console";
		else; //TO-DO error;
	}
}
*/


void checkAndSetInput(vector<Token>& segment, IOdata* IOdata, int idx) {
	if (segment[idx].inQuotes) IOdata->input = "string", IOdata->inputString = segment[idx].parameter;
	else IOdata->input = "file", IOdata->inputFile = segment[idx].parameter;
	segment.erase(segment.begin() + idx);
}

bool isWhat(Token t) {
	//!t.parameter.empty() jer tokenizer dozvoljava "" bez icega unutra
	if (!t.parameter.empty() && t.parameter[0] == '-' && t.inQuotes) return true;
	else return false;
}

vector<Token> getInputOutput(vector<Token> segment, IOdata* IOdata) {
	//ako su vec dobijeni input/output ne treba ih opet proveravati
	string cmd = segment[0].parameter;

	if (IOdata->output != "file") IOdata->output = "console";

	if (cmd == "date" || cmd == "time") {
		if (segment.size() != 1) {

		}//TO-DO error;
		IOdata->input = "no_input";
		return segment;
	} 

	if (IOdata->hasInputRedirect) return segment;

	if (cmd == "echo") {
			if (segment.size() == 2) {
				checkAndSetInput(segment, IOdata, 1);
			}
			else if (segment.size() == 1) IOdata->input = "console";
			else; //TO-DO error
			return segment;
	}

	if (cmd == "wc" || cmd == "head") {
			if (segment.size() == 3) {
				checkAndSetInput(segment, IOdata, 2);
			}
			else if (segment.size() == 2) IOdata->input = "console";
			else; //TO-DO error
			return segment;
	}
	
	if (cmd == "tr") {
			if (segment.size() == 4) {
				checkAndSetInput(segment, IOdata, 1);
			}
			else if (segment.size() == 3) {
				if (isWhat(segment[1])) IOdata->input = "console";
				else checkAndSetInput(segment, IOdata, 1);
			}
			else if (segment.size() == 2) {
				if (isWhat(segment[1])) IOdata->input = "console";
			}
			else {
				//TO-DO error;
			}
			return segment;
	}

	return segment;
}

void getOutput(IOdata* IOdata) {
	if (IOdata->output != "file") IOdata->output = "console";
}

bool notOperator(string s) {
	if (s == "|" || s == "<" || s == ">" || s == ">>") {
		return false;
	}
	else return true;
}

bool isRedirectOp(string s) {
	if (s == "<" || s == ">" || s == ">>") {
		return true;
	}
	else return false;
}

//zamenska f-ja bi skratila kod za 12 linija

bool isInSuffix(vector<Token> segment, int idx) {
	if ((segment.size()-idx) == 2 && notOperator(segment[idx + 1].parameter)) return true;
	else if ((segment.size() - idx) == 4 && notOperator(segment[idx + 1].parameter) && isRedirectOp(segment[idx + 2].parameter) && notOperator(segment[idx + 3].parameter)) return true;
	else return false;
	//da li je struktura tipa < filename > filename
}

bool doubleRedirection(vector<Token> segment, int idx) {
	if ((segment.size() - idx) == 4)
	{
		string op1 = segment[idx].parameter;
		string op2 = segment[idx + 2].parameter;
		//dupli input
		if (op1 == "<" && op2 == "<") return true;
		//dupli output
		if ((op1 == ">" || op1 == ">>") && (op2 == ">" || op2 == ">>")) return true;

		else return false;
	}
	else return false;
}

vector<Token> getRedirect(vector<Token> segment, IOdata* IOdata) {

	//ovo moze da se skrati
	for (int i = 0; i < segment.size(); i++) {
		if (segment[i].parameter == "<") {
			if (!isInSuffix(segment, i)) return segment;
			if (doubleRedirection(segment, i)) return segment;//baci error
			IOdata->input = "file";
			if (segment.size() > i + 1 && !segment[i+1].inQuotes) IOdata->inputFile = segment[i + 1].parameter;
			else return segment; //TO-DO greska
			segment.erase(segment.begin() + (i + 1));
			segment.erase(segment.begin() + i);
			IOdata->hasInputRedirect = 1;
			i--;
		}
		else if (segment[i].parameter == ">") {
			if (!isInSuffix(segment, i)) return segment; //baci error
			if (doubleRedirection(segment, i)) return segment;//baci error
			IOdata->output = "file";
			IOdata->append = false;
			if (segment.size() > i + 1 && !segment[i + 1].inQuotes) IOdata->outputFile = segment[i + 1].parameter;
			else return segment; //TO-do greska
			segment.erase(segment.begin() + (i+1));
			segment.erase(segment.begin() + i);

			i--;
		}
		else if (segment[i].parameter == ">>") {
			if (!isInSuffix(segment, i)) return segment; //baci error
			if (doubleRedirection(segment, i)) return segment;//baci error
			IOdata->output = "file";
			IOdata->append = true;
			if (segment.size() > i + 1 && !segment[i + 1].inQuotes) IOdata->outputFile = segment[i + 1].parameter;
			else return segment; //TO-do greska
			segment.erase(segment.begin() + (i+1));
			segment.erase(segment.begin() + i);
			i--;
		} 
		
	}

	
		return segment;
}

void resetIOdata(IOdata* IOdata) {
	IOdata->hasInputRedirect = false;
	IOdata->append = false;
	IOdata->input = "";   // ili "console" ako ti je default
	IOdata->output = "";  // ili "console"
	IOdata->inputFile.clear();
	IOdata->outputFile.clear();
	IOdata->inputString.clear();
}

Pipe NewParser::parseCommands(string line) {
	vector<Token> tokens = tokenize(line);
	vector<ParsedCommand> commands;
	ParsedCommand curr_pcmd;
	Pipe parsedPipe;
	IOdata IOdata;

	if (tokens.empty()) return parsedPipe;
	
	else {

		vector<vector<Token>> segments = getSegments(tokens);

		resetIOdata(&IOdata);

		for (int i = 0; i < segments.size(); i++) {
			string cmd = segments[i].at(0).parameter;
			Command* curr_cmd = nullptr;

			if (segments.size() > 1 && (cmd == "touch" || cmd == "truncate" || cmd == "rm" || cmd == "prompt")) {
				//TO-DO error
			}

			if (i == 0) {
				segments[i] = getRedirect(segments[i], &IOdata);
				segments[i] = getInputOutput(segments[i], &IOdata);
			}
			else if (0 < i && i < segments.size() - 1) {

				//potencijalno treba spreciti "stream-argument" ako se ocekuje specifican error type

				if (cmd == "time" || cmd == "date" || cmd == "batch") {
					//TO-DO error
				}
				for (Token t : segments[i]) {
					if (t.parameter == "<" || t.parameter == ">" || t.parameter == ">>") {
						//TO-DO error (no redirection in the middle of a pipe)
					}
				}
			}
			else {
				if (cmd == "time" || cmd == "date" || cmd == "batch") {
					//TO-DO error
				}
				segments[i] = getRedirect(segments[i], &IOdata);
				getOutput(&IOdata);
			}

			if (cmd == "time" || cmd == "date" || cmd == "echo") {
				curr_cmd = parseZero(segments[i]);
			}
			else if (cmd == "touch" || cmd == "truncate" || cmd == "rm" || cmd == "batch" || cmd == "prompt") {
				curr_cmd = parseUnary(segments[i]);
			}
			else if (cmd == "wc" || cmd == "head") {
				curr_cmd = parseBinary(segments[i]);
			}
			else if (cmd == "tr") {
				if (segments[i].size() == 3) curr_cmd = parseTernary(segments[i]);
				else if (segments[i].size() == 2) curr_cmd = parseBinary(segments[i]);
			}

			if (curr_cmd != nullptr) {
				curr_pcmd.cmd = curr_cmd;
				curr_pcmd.cmd_name = cmd;
				commands.push_back(curr_pcmd);
			}
			else {
				//TO-DO error;
			}
		}

		parsedPipe.p_cmds = commands;
		parsedPipe.io = IOdata;

		return parsedPipe;
	}
}

vector<Token> NewParser::tokenize(string line) {
	vector<Token> tokens;
	Token current;
	current.inQuotes = 0;
	bool isReadingArgument = 0;

	for (int i = 0; i < line.length(); i++) {
		char c = line[i];

		//Izlazak iz navodnika

		if (isReadingArgument && c == '\n') {
			tokens.clear();
			return tokens;
		}; //TO-DO greska, nezatvoren navodnik
		if (isReadingArgument && c != '"') {
			current.parameter.push_back(c);
			continue;
		}
		if (isReadingArgument && c == '"') {
			tokens.push_back(current);
			isReadingArgument = 0;
			current.inQuotes = 0;
			current.parameter.clear();
			continue;
		}

		if (!isReadingArgument) {
			//Ulazak u navodnike
			if (c == '"') {
				isReadingArgument = 1;
				current.inQuotes = 1;
				continue;
			}

			//rad sa specijalnim karakterima
			if (c == '|' || c == '<') {
				if (!current.parameter.empty()) {
					tokens.push_back(current);
				}
				current.parameter.clear();
				current.parameter.push_back(c);
				tokens.push_back(current);
				current.parameter.clear();
				continue;
			}

			//specijalna provera za karakter >, zbog mogucnosti >>
			if (c == '>') {
				if (!current.parameter.empty()) {
					tokens.push_back(current);
				}
				current.parameter.clear();
				if (i + 1 < line.length()) {
					char next_c = line[i + 1];
					if (next_c == '>') {
						i++;
						current.parameter.push_back(c);
						current.parameter.push_back(next_c);
					}
					else {
						current.parameter.push_back(c);
					}
				}
				else {
					current.parameter.push_back(c);
				}
				tokens.push_back(current);
				current.parameter.clear();
				continue;
			}


			if (isspace(c)) {
				if (!current.parameter.empty()) {
					tokens.push_back(current);
					current.parameter.clear();
				}
				continue;
			}
			current.parameter.push_back(c);
		}

	}
	//slucaj kada nema beline na kraju linije
	if (!current.parameter.empty()) tokens.push_back(current);

	return tokens;

}

Command* NewParser::parseZero(vector<Token> segment) {

	string cmd = segment[0].parameter;
	if (segment.size() != 1) {
		//TO-DO napraviti exception
		return nullptr;
	}
	else {
		if (cmd == "date") {
			return new Date();
		}
		else if (cmd == "time") {
			return new Time();
		}
		else if (cmd == "echo") {
			return new Echo();
		}
		else {
			//TO-DO napraviti nepoznata komanda exception
			return nullptr;
		}
	}
}

Command* NewParser::parseUnary(vector<Token> segment) {

	string cmd = segment[0].parameter;

	if (segment.size() != 2) return nullptr;

	//argument prompta mora biti u navodnicima
	if (segment[1].inQuotes) {
		if (cmd == "prompt") {
			return new Prompt(segment[1].parameter);
		}
		else return nullptr;
	}
	//argument ostalih funkcija ne sme biti u navodnicima
	else {
		if (cmd == "touch") return new Touch(segment[1].parameter);
		else if (cmd == "truncate") return new Truncate(segment[1].parameter);
		else if (cmd == "rm") return new Remove(segment[1].parameter);
		else if (cmd == "batch") return new Batch(segment[1].parameter);
		else return nullptr;
	}
}

Command* NewParser::parseBinary(vector<Token> segment) {

	string cmd = segment[0].parameter;
	if (segment.size() != 2) {
		//TO-DO napraviti exception
		return nullptr;
	}
	else {
		if (cmd == "wc") {
			if (segment[1].parameter != "-w" && segment[1].parameter != "-c") {
				//TO-DO napraviti nevalidan wc format exception
				return nullptr;
			}
			return new CountWC(segment[1].parameter);
		}
		else if (cmd == "head") {
			if (segment[1].parameter.size() >= 3 && segment[1].parameter.size() < 8) {
				if (segment[1].parameter.at(0) == '-' && segment[1].parameter.at(1) == 'n') {
					bool isValid = 1;
					for (int i = 2; i < segment[1].parameter.size(); i++) {
						if (!isdigit(segment[1].parameter.at(i))) isValid = 0;
					}
					if (isValid) {
						return new Head(segment[1].parameter);
					}
					else {
						//TO-DO napraviti nevalid head format expection
						return nullptr;
					}
				}
				else {
					//TO-DO napraviti nevalidan head format exeception
					return nullptr;
				}
			}
			else {
				//TO-DO napraviti nevalidan head format exeception
				return nullptr;
			}
		}
		else if (cmd == "tr") {
			if (segment[1].parameter.size() > 1) {
				if (segment[1].parameter.at(0) == '-') {
					return new Tr(segment[1].parameter);
				}
				else {
					//TO-DO napraviti nevalid Tr format exceptio
					return nullptr;
				}
			}
			else {
				//TO-DO napraviti nevalidan Tr format exception
				return nullptr;
			}
		}
		
		else {
			//TO-DO napraviti nepoznata komanda exception
			return nullptr;
		}
	}

}

Command* NewParser::parseTernary(vector<Token> segment) {

	string cmd = segment[0].parameter;
	if (segment.size() != 3) {
		//TO-DO napraviti exception
		return nullptr;
	}
	else {
		if (cmd == "tr") {
			if (segment[1].parameter.at(0) != '-') {
				//TO-DO pogresan format tr error
				return nullptr;
			}
			else {
				return new Tr(segment[1].parameter, segment[2].parameter);
			}
		}
		else {
			//TO-DO napraviti nepoznata komanda exception
			return nullptr;
		}
	}
}

