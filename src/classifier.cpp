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
	readFile(fileName, this->trainingData, this->trainingCounts);
	classifier(this->trainingData, this->trainingCounts);
}

void NBC::test(const string& fileName) {
	readFile(fileName, this->testingData, this->testingCounts);
	classifier(this->testingData, this->testingCounts);
}

// Classifies given data 
void NBC::classifier(const MyArray& myArray, const MyMap& myMap) {
	// Count number of -1 and 1 classes
	int negativeCount = 0, positiveCount = 0;
	for(auto val : myArray) 
		val->at(0) == -1 ? negativeCount++ : positiveCount++;

	// Probability stuff
	double total = negativeCount + positiveCount;
	double prob_negative_class = negativeCount / total;
	double prob_positive_class = positiveCount / total;
	int accuracy = 0;
	int truePositives = 0, falsePositives = 0,
	   	trueNegatives = 0, falseNegatives = 0;

	cout << "\n\nprob(-1): " << prob_negative_class 
		 << "\ttotal(-1): " << negativeCount << '\n'
		 << "prob(1): " << prob_positive_class
		 << "\ttotal(1): " << positiveCount << "\n\n";

	// Loops through each set of data and calculate the probability
	//   of each attribute for each class
	size_t length = myArray.size();
	for(size_t pos = 0; pos < length; ++pos)  {
		vector<double> probNeg(max_length, 0);	// Holds the probablity of each attr
		vector<double> probPos(max_length, 0);
		int currentLabel = myArray[pos]->at(0);

		// 
		size_t width = myArray[pos]->size();
		for(size_t col = 1; col < width; ++col) {
			int currentVal = myArray[pos]->at(col);

			// TODO: check for unindexed values
			
			if(currentVal != 0) { 	
				probNeg.at(col-1) += myMap.find(-1)->second->find(col)->second->find(currentVal)->second;
				probPos.at(col-1) += myMap.find(1)->second->find(col)->second->find(currentVal)->second;
			}	
		}

		// P(X | C)
		double pb_neg = prob_negative_class;
		double pb_pos = prob_positive_class;

		//cout << "column results\n";
		//cout << "negatives: ";
		for(size_t col = 0; col < (max_length-1); ++col) { 
		//	cout << probNeg[col] << ' ';
			probNeg[col] /= negativeCount;
			pb_neg *= probNeg[col];
		}
		
		//cout << "\npositives: ";
		for(size_t col = 0; col < (max_length-1); ++col) { 
			//cout << probPos[col] << ' ';
			probPos[col] /= positiveCount;
			pb_pos *= probPos[col];
		}
		//cout << '\n';
		
		// Calculate the true/false positives/negatives
		int predicted_label = pb_neg > pb_pos ? -1 : 1;
		// cout << pb_neg << (pb_neg > pb_pos ? " > " : " < ") << pb_pos << '\n';

		if(currentLabel == predicted_label) accuracy++;
		if(currentLabel == 1  && predicted_label == 1) truePositives++;
		if(currentLabel == -1 && predicted_label == 1) falsePositives++;
		if(currentLabel == -1 && predicted_label == -1) trueNegatives++;
		if(currentLabel == 1  && predicted_label == -1) falseNegatives++;
		} // end of long for loop

	cout << "accuracy: " << accuracy/total << '\n';
/*	cout << "True Positives: " << truePositives << '\n'
		 << "False Positives: " << falsePositives << '\n'
		 << "True Negatives: " << trueNegatives << '\n'
		 << "False Negatives: " << falseNegatives << '\n';
*/
	// Output results
	cout << truePositives  << ' ' << falseNegatives << ' '
		 << falsePositives << ' ' << trueNegatives  << '\n';
}	

void NBC::readFile(const string& fileName, MyArray& myArray, MyMap& myMap) { 
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
		vector<int> * values = new vector<int>;
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
			values->push_back(label); 	// First element on will be the label
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
				while((values->size()-1) < index)
					values->push_back(0);

				values->push_back(stoi(line.substr(0, pos)));
				line = line.substr(pos+1);
			}
		} 

		// grab whats left
		values->push_back(stoi(line));
		
		if((values->size()) > max_length)
		   	max_length = values->size();

		// Insert data in vector
		myArray.push_back(values);

		//cout << "label: " << label << '\n';
		//cout << "class\tcol\tvalue\tcount\n";
		// Insert values into hash 
		size_t length = values->size();
		for(size_t col = 1; col < length; ++col) {
			int val = values->at(col);
			auto ptr = myMap.find(label);			
			
			// Create new key val for unencounter class
			if(ptr == myMap.end()) {
				map<int, int> * tmpMapPtr = new map<int, int>;
				tmpMapPtr->insert(make_pair(val, 1));
				map<int, map<int, int> *> * tmpMapPtr2 = new map<int, map<int,int> *>;
				tmpMapPtr2->insert(make_pair(col, tmpMapPtr));
				myMap.insert(make_pair(label, tmpMapPtr2));
				tmpMapPtr = 0;
				tmpMapPtr2 = 0;
			}
			else if(ptr->second->find(col) == ptr->second->end()) {
				map<int, int> * tmpMapPtr = new map<int, int>;
				tmpMapPtr->insert(make_pair(val, 1));
				ptr->second->insert(make_pair(col,tmpMapPtr));
				tmpMapPtr = 0;
			}
			else if(ptr->second->find(col)->second->find(val)
				 == ptr->second->find(col)->second->end()) {
				ptr->second->find(col)->second->insert(make_pair(val, 1));
			}
			else {
				ptr->second->find(col)->second->find(val)->second += 1;
		//		cout << ptr->first << '\t' << col << '\t' << val
		//		<< '\t' << ptr->second->find(col)->second->find(val)->second << '\n';
			}
		}	
	} // end of outer while

	inFile.close();
}

