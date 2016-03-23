/*
*****************************************
Jason Katz
ECE-467 Project 1: Text Categorization

Document categorizer using a 
naive Bayes approach

File: main.cpp
Description: Trains the program with
training documents, tests the program
with testing documents, and outputs
the results to an output file
*****************************************
*/

#include <iostream>
#include <string>
#include "Categorizer.h"

using namespace std;

int main() {

	// Get input filenames
	string trainFileName;
	cout << "Enter the filename of a list of labeled training documents: ";
	//cin >> trainFileName;
	trainFileName = "corpus1_train.labels";

	string testFileName;
	cout << "Enter the filename of a list of unlabeled testing documents: ";
	//cin >> testFileName;
	testFileName = "corpus1_test.list";

	// Train categorizer
	Categorizer categorizer;
	categorizer.Train(trainFileName);
    return 0;

	// Get output filename
	string outputFileName;
	cout << "Enter the name of an output file: ";
	//cin >> outputFileName;
	outputFileName = "out";

	categorizer.Test(testFileName, outputFileName);

	return 0;
}
