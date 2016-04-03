#include <fstream>
#include "classifier.h"

NBC::NBC() {
}

NBC::NBC(const string& trainingFileName) {
	train(trainingFileName);
}	 	

NBC::NBC(const string& trainingFileName, const string& testingFileName) {
	train(trainingFileName);
	test(testingFileName);
}	 	

void NBC::train(const string& fileName) {
	// Store training set data into memory
	readFile(fileName, this->trainingSet);
	classifier(this->trainingSet);
}

void NBC::test(const string& fileName) {
	readFile(fileName, this->testingSet);
	classifier(this->testingSet);
}

// Classifies given data 
void NBC::classifier(multimap<int, vector<int> >& myMap ) {
	// Probability stuff
	int negativeCount = myMap.count(-1);
	int positiveCount = myMap.count(1);
	double total = negativeCount + positiveCount;
	double prob_positive_class = myMap.count(1) / total;
	double prob_negative_class = myMap.count(-1) / total;
	int accuracy = 0;
	int truePositives = 0, falsePositives = 0,
	   	trueNegatives = 0, falseNegatives = 0;

/*
	cout << "\n\nprob(-1): " << prob_negative_class 
		 << "\ttotal(-1): " << negativeCount << '\n'
		 << "prob(1): " << prob_positive_class
		 << "\ttotal(1): " << positiveCount << "\n\n";
*/

	// Loops through each set of data and calculate the probability
	//   of each attribute for each class
	for(auto current = myMap.cbegin(); current != myMap.cend(); ++current)  {
		const auto& values = current->second;	// Row of data
		multimap<int, vector<double> > prob;	// Holds the probablity of each attr
		int currentLabel = current->first;

		// Loops through each column (or attribute) to count occurences
		for(size_t attr = 0; attr < values.size(); ++attr) {
			// Find count of attribute given class
			for(auto set = myMap.begin(); set != myMap.end(); ++set) {
				int setLabel = set->first;
				// Add new key for unencountered class
				if(prob.find(setLabel) == prob.end())
					prob.insert(make_pair(setLabel, vector<double>(max_length, 1)));

				if(attr < set->second.size()
					  	&& values.at(attr) == set->second.at(attr))
					prob.find(setLabel)->second.at(attr) += 1;
			}
		}
			
		// P(attr) / P(C)
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

		// Calculate the true/false positives/negatives
		int predicted_label = pb_neg > pb_pos ? -1 : 1;

		if(currentLabel == predicted_label) accuracy++;
		if(currentLabel == 1  && predicted_label == 1) truePositives++;
		if(currentLabel == -1 && predicted_label == 1) falsePositives++;
		if(currentLabel == -1 && predicted_label == -1) trueNegatives++;
		if(currentLabel == 1  && predicted_label == -1) falseNegatives++;
		} // end of long for loop

/*
	cout << "accuracy: " << accuracy/total << '\n';
	cout << "True Positives: " << truePositives << '\n'
		 << "False Positives: " << falsePositives << '\n'
		 << "True Negatives: " << trueNegatives << '\n'
		 << "False Negatives: " << falseNegatives << '\n';
*/
	// Output results
	cout << truePositives  << ' ' << falseNegatives << ' '
		 << falsePositives << ' ' << trueNegatives  << '\n';
}	

void NBC::readFile(const string& fileName, multimap<int, vector<int> >& myMap) { 
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
				// Increase array size if need (fills with zeros)
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
	} // end of outer while

	inFile.close();
}

