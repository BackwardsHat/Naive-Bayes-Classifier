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

	while(inFile ) {	
		inFile >> std::ws;
		getline(inFile, line);
		std::cout << line  << '\n'; 
	}

	inFile.close();
}
