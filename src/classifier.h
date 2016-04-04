#ifndef MY_NBC
#define MY_NBC

#include <iostream>
#include <string.h>
#include <vector>
#include <map>


using namespace std;


// data stucture general idea: [key1] -> ([key2] -> ([key3] -> count) )
// where key1: class label, key2: column number
//       key3: column value, count: occurences of key3
typedef multimap<int, map<int, map<int,int> *> *> MyMap;
typedef vector<vector<int> *> MyArray;

class NBC {
public:
	NBC();
	NBC(const string&);		
	NBC(const string&, const string&);		

	void train(const string&);	
	void test(const string&); 		

private:
	void readFile(const string&, MyArray&, MyMap&);
	// Attempts to predict class label 
	void classifier(const MyArray&, const MyMap&);	

	MyArray trainingData;	  // Holds the data from file 
	MyArray testingData;
	MyMap trainingCounts;     // Holds training occurence
	MyMap testingCounts;	  // Isn't used, but like having it
	size_t max_length;
};

#endif
