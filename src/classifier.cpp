#include <fstream>
#include "classifier.h"

NBC::NBC() {
	cout << "NBC constructor called\n";
}

NBC::NBC(const string& fileName) {
	cout << "NBC char * constructor called\n";
	train(fileName);
}	 	

void NBC::train(const string& fileName) {
	cout << "NBC train called\n";
	// Store training set data into memory
	readFile(fileName, this->trainingSet);
	
	cout << "NBC readFile after\n";
	// calc probabilities
	
	for(auto it = trainingSet.begin(); it != trainingSet.end(); ++it) {
		if(means.find(it->first) == means.end())
			means.insert( make_pair(it->first, vector<double>(max_length, 0.0) ));

		size_t tmp = 0;
		for(auto& count : means.find(it->first)->second)
			if(tmp < it->second.size())
				count += it->second.at(tmp++);
	}

	// Print means for each class
	cout << "key\tvalues\n";
	for(auto it = means.cbegin(); it != means.end(); ++it) {
		cout << it->first << '\t';
		for(const auto& j : it->second) 
			cout << j << ' ';
		cout << '\n';
		
	}

	size_t count_1 = trainingSet.count(-1);
	size_t count1 = trainingSet.count(1);
	for(auto it = means.begin(); it != means.end(); ++it) {
		for(auto& j : it->second)
			j /= trainingSet.count(it->first);
	}
	
	cout << "(attr_count) / total\n";
	cout << "count-1: " << count_1 << "\tcount1: " << count1 << '\n';
	cout << "key\tvalues\n";
	for(auto it = means.cbegin(); it != means.end(); ++it) {
		cout << it->first << '\t';
		for(const auto& j : it->second) 
			cout << j << ' ';
		cout << '\n';
	}
}

// Classifies data file
void NBC::test(const string& fileName) {
	cout << "NBC test called\n";

	// Store testing set data into memory
	readFile(fileName, this->testingSet);
	
	int negativeCount = trainingSet.count(-1);
	int positiveCount = trainingSet.count(1);
	double total = negativeCount + positiveCount;
	double prob_positive_class = trainingSet.count(1) / total;
	double prob_negative_class = trainingSet.count(-1) / total;

	cout << "prob(1): " << prob_positive_class << '\t'
		 << "prob(-1): " << prob_negative_class << '\n';

	cout << "max_length: " << max_length << '\n';
	auto placeholder = testingSet.find(1);
	vector<int> * t = &testingSet.find(1)->second;
	multimap<int, vector<double> > prob;
	for(size_t attr = 0; attr < t->size(); ++attr) {
		// find attr given class
		for(auto set = trainingSet.begin(); set != trainingSet.end(); ++set) {
			// Add new key for unencountered class
			if(prob.find(set->first) == prob.end())
				prob.insert(make_pair(set->first, vector<double>(max_length, 1)));

			vector<double> * ptr = &prob.find(set->first)->second;

			if(attr < set->second.size() && t->at(attr) == set->second.at(attr))
				ptr->at(attr) += 1;
		}
	}
		
	for(size_t attr = 0; attr < max_length; ++attr) {
		prob.find(-1)->second.at(attr) /= negativeCount;
		prob.find(1)->second.at(attr) /= positiveCount;
	}

	
	double pb_neg = prob_negative_class;
	double pb_pos = prob_positive_class;
	for(size_t attr = 0; attr < max_length; ++attr) {
		pb_neg *= prob.find(-1)->second.at(attr);
		pb_pos *= prob.find(1)->second.at(attr);
	}	

	cout << "pb_neg: " << pb_neg << "\tpb_pos: " << pb_pos << '\n';

	cout << "test counts\n";
	for(auto it = prob.cbegin(); it != prob.end(); ++it) {
		cout << it->first << '\t';
		for(const auto& j : it->second) 
			cout << j << ' ';
		cout << '\n';
	}

	cout << "It's " << (pb_neg > pb_pos ? "-1" : "1") << "!\n";
	cout << "Real answer: " << placeholder->first << '\n';
}	

void NBC::readFile(const string& fileName, multimap<int, vector<int> >& myMap) { 
	cout << "NBC readFile called\n";
	ifstream inFile(fileName);

	if(!inFile) {
		cout << "Could not open " << fileName << '\n';
		exit(1);
	}

	string line;

	while(inFile >> ws) {	
		getline(inFile, line);
		//cout << "Line: "<< line << '\n';

		int label;
		vector<int> values;
		size_t pos;
			
		// Checks to see if line is valid. 
		// Valid if format follows: <label> <index>:<int> <index>:<int> ...
		pos = line.find(':');	
		if(pos == string::npos)
		   	break;

		// Prases label from line
		pos = line.find(' ');
		if(pos != string::npos) {
			label = stoi(line.substr(0, pos));	
			line = line.substr(pos+1);
		}

		// Parse int's after each ':' from line
		while(pos != string::npos) {
			size_t index;
			pos = line.find(':');

			if(pos != string::npos) {
				index = stoi(line.substr(0,pos)) - 1;				
				// Remove characters up to ':'
				line = line.substr(pos+1);
			}

			pos = line.find(' ');

			if(pos != string::npos) {
				while(values.size() < index)
					values.push_back(0);

				values.push_back(stoi(line.substr(0, pos)));
				line = line.substr(pos+1);
			}
		} 

		// grab whats left
		values.push_back(stoi(line));
		
		if(values.size() > max_length) max_length = values.size();
		
		myMap.insert(make_pair(label, values));
/*
		cout << label << '\t';
		for(const auto& i : *values)
			cout << i << ' ';
		cout << '\n';
*/
	} // end of outer while

	inFile.close();
}

