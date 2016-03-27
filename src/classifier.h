#ifndef MY_NBC
#define MY_NBC

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

struct dataSet {
	int label;
	std::vector<int> values;
};

class NBC {
public:
	NBC();
	NBC(const string&);	// 	

	// Creates decision tree based off training data file
	void train(const string&);	
	// Classifies data file
	void test(const string&); 		

private:
	void readFile(const string&);

	std::vector<dataSet * > dataTable; 
	std::vector<double> means;
	std::vector<double> variances;
};

#endif
