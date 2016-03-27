#include <iostream>
#include "classifier.h"

using namespace std;

int main(int argc, char * argv[]) {
	if(argc != 3) {
		cout << "Error: Usage: ./<prog> <trainingfile> <testfile>\n";
		return 1;
	}

	NBC nbc;
	nbc.train(argv[1]);
	nbc.test(argv[2]);
	
	return 0;
}


