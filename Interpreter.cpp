#include "Interpreter.h"
#include "Prompt.h"

/*
istream& Interpreter::setInput(IOdata io) {
	if (io.input == "string") {
		str_in = istringstream(io.inputString);
		return str_in;
	}	
	else if (io.input == "file") {
		file_in = ifstream(io.inputFile);
		return file_in;
	}
	else {
		return cin;
	}
}
*/

istream& Interpreter::setInput(IOdata io) {
	if (io.input == "string") {
		str_in = istringstream(io.inputString);
		return str_in;
	}
	else if (io.input == "file") {
		file_in = ifstream(io.inputFile);
		return file_in;
	}
	else return cin;

}

string Interpreter::getReadinessSigil() {
	return readiness_sigil;
}

ostream& Interpreter::setOutput(IOdata io) {
	if (io.output == "file") {
			if(io.append) file_out = ofstream(io.outputFile, ios::app);
			else file_out = ofstream(io.outputFile);
		return file_out;
	}
	else {
		return cout;
	}
}

void Interpreter::run(string line, ostream& defaultOutput, ostream& errOut) {
	pipe = getPipe(line);
	input = &setInput(pipe.io);
	if (pipe.io.output == "file") output = &setOutput(pipe.io);
	else output = &defaultOutput;
	err_out = &errOut;
	setupPipe();
	runPipe();
}

Pipe Interpreter::getPipe(string line) {
	return m_parser.parseCommands(line);
}


void Interpreter::setupPipe() {

	if (pipe.p_cmds.empty()) return; 
	else {
		for (int i = 0; i < pipe.p_cmds.size(); i++) {
			if (i == 0) {
				if (pipe.p_cmds[i].cmd->takesInput) pipe.p_cmds[i].cmd->setInput(*input);

				if (pipe.p_cmds[i].cmd->makesOutput) {
					if (pipe.p_cmds.size() == 1) pipe.p_cmds[i].cmd->setOutput(*output);
					else pipe.p_cmds[i].cmd->setOutput(buffer_out);
				}
			}
			else if (0 < i && i < pipe.p_cmds.size() - 1) {
				pipe.p_cmds[i].cmd->setInput(buffer_in);
				pipe.p_cmds[i].cmd->setOutput(buffer_out);

			}
			else {
				pipe.p_cmds[i].cmd->setInput(buffer_in);
				pipe.p_cmds[i].cmd->setOutput(*output);
			}
		}
	}
}

void ResetBuffers(stringstream& buffer_in, stringstream& buffer_out) {
	buffer_in.seekg(0);
	buffer_in.clear();
	buffer_out.str("");
	buffer_out.clear();
}

void Interpreter::cleanUp() {
	input->clear();
	if (pipe.io.output == "file") {
		file_out.flush();
		file_out.close();
	}
	if (pipe.io.input == "file") {
		file_in.close();
	}

	//(*output) << "\n";
}

void Interpreter::runPipe() {
	if (pipe.p_cmds.empty()) return;
	else {
		ResetBuffers(buffer_in, buffer_out);
		for (int i = 0; i < pipe.p_cmds.size(); i++) {

			//fuj
			if (i == 0) {
				if (pipe.p_cmds[i].cmd_name == "prompt") {
					Prompt* p = dynamic_cast<Prompt*>(pipe.p_cmds[i].cmd);
					if (!p) {
						//TO-DO error
					}
					readiness_sigil = p->get_Sigil();
				}
			}

			pipe.p_cmds[i].cmd->execute();
			if (i < pipe.p_cmds.size() - 1) {
				swap(buffer_in, buffer_out);
				ResetBuffers(buffer_in, buffer_out);
			}
		}

		cleanUp();
	}
}