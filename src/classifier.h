#ifndef MY_NBC
#define MY_NBC

#include <iostream>
#include <vector>

struct dataSet {
	int label;
	std::vector<int> values;
};

class NBC {
public:
	NBC();
	NBC(char *);	// 	

	void train(char *);		// Creates decision tree based off training data file
	void test(char *); 		// Classifies data file

private:
	std::vector<dataSet> data; 
};

#endif
