#include <fstream>
#include "classifier.h"

#define MAX_LINE_SIZE 255

NBC::NBC() {
	std::cout << "NBC constructor called\n";
}

NBC::NBC(const string& fileName) {
	std::cout << "NBC char * constructor called\n";
	train(fileName);
}	 	

// Creates decision tree based off training data file
void NBC::train(const string& fileName) {
	std::cout << "NBC train called\n";

	readFile(fileName);
}

// Classifies data file
void NBC::test(const string& fileName) {
	std::cout << "NBC test called\n";
}	


void NBC::readFile(const string& fileName) { 
	std::cout << "NBC readFile called\n";
	std::ifstream inFile(fileName);

	if(!inFile) {
		std::cout << "Could not open " << fileName << '\n';
		exit(1);
	}

	string line;

	while(inFile >> std::ws) {	
		getline(inFile, line);
		//std::cout << "Line: "<< line << '\n';

		dataSet * set = new dataSet;
		size_t pos;
			
		// Checks to see if line is valid. 
		// Valid if format follows: <label> <index>:<int> <index>:<int> ...
		pos = line.find(':');	
		if(pos == string::npos)
		   	break;

		// Prases label from line
		pos = line.find(' ');
		if(pos != string::npos) {
			set->label = std::stoi(line.substr(0, pos));	
			line = line.substr(pos+1);
		}

		// Parse int's after each ':' from line
		while(pos != string::npos) {
			size_t index;
			pos = line.find(':');

			if(pos != string::npos) {
				index = std::stoi(line.substr(0,pos)) - 1;				
				// Remove characters up to ':'
				line = line.substr(pos+1);
			}

			pos = line.find(' ');

			if(pos != string::npos) {
				while(set->values.size() < index)
					set->values.push_back(0);

				set->values.push_back(std::stoi(line.substr(0, pos)));
				line = line.substr(pos+1);
			}
		}

		// grab whats left
		set->values.push_back(std::stoi(line));
		this->dataTable.push_back(set);

		std::cout << set->label << ", ";
		int i = 0; 
		for(const auto& val : set->values)
			std::cout << i++ << ':'<< val << ' ';
		std::cout << '\n';

	} // end of while

	inFile.close();
}
