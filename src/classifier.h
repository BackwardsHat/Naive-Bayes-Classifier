#ifndef MY_NBC
#define MY_NBC

#include <iostream>
#include <string.h>
#include <vector>
#include <map>

using namespace std;

class NBC {
public:
	NBC();
	NBC(const string&);		
	NBC(const string&, const string&);		

	void train(const string&);	
	void test(const string&); 		

private:
	void readFile(const string&, multimap<int, vector<int> >&);
	// Attempts to predict class label 
	void classifier(multimap<int, vector<int> >&);	

	multimap<int, vector<int> > trainingSet;  // Holds training data
	multimap<int, vector<int> > testingSet;	  // Holds data you want to predict
	map<int, vector<double> > means;
	map<int, vector<double> > variances;
	size_t max_length;
};

#endif
