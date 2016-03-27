#include "classifier.h"

NBC::NBC() {
	std::cout << "NBC constructor called\n";
}

NBC::NBC(char * fileName) {
	std::cout << "NBC char * constructor called\n";
	train(fileName);
}	 	

// Creates decision tree based off training data file
void NBC::train(char * fileName) {
	std::cout << "NBC train called\n";
}

// Classifies data file
void NBC::test(char * fileName) {
	std::cout << "NBC test called\n";
}	
