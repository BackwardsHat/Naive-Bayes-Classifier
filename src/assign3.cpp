// Author: Joseph Furiate
// FSUID: jaf13j
// GitHub Handle: BackwardsHat
// Summary: Naive Bayes Classifier that attempts to predict the label
// 		of binary class data. (in this case 1 or -1)

#include <iostream>
#include "classifier.h"

using namespace std;

int main(int argc, char * argv[]) {
	if(argc != 3) {
		cout << "Error: Usage: ./<prog> <trainingfile> <testfile>\n";
		return 1;
	}

	// Naive Bayes Classifier
	NBC nbc;
	nbc.train(argv[1]);
	nbc.test(argv[2]);
	
	return 0;
}


