#ifndef MY_NBC
#define MY_NBC

#include <iostream>
#include <string.h>
#include <vector>
#include <map>

using namespace std;

struct dataSet {
	int label;
	vector<int> values;
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
	void readFile(const string&, multimap<int, vector<int> >&);

	multimap<int, vector<int> > trainingSet; 
	multimap<int, vector<int> > testingSet; 
	map<int, vector<double> > means;
	map<int, vector<double> > variances;
	size_t max_length;
};

#endif
