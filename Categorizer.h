/*
*****************************************
Jason Katz
ECE-467 Project 1: Text Categorization

Document categorizer using a
naive Bayes approach

File: Categorizer.h
Description: Categorizer class
structure and declarations
*****************************************
*/

#ifndef CATEGORIZER_H
#define CATEGORIZER_H

#include <unordered_map>
#include <map>
#include <string>

using namespace std;

class Categorizer {

	// Hash table that maps words to counts across all categories
	unordered_map<string, int> * wHash;

	// Hash table that maps words in specific categories to counts
	unordered_map<pair<string, string>, int> * wcHash;

public:

	Categorizer();
	void Train(string);
	void Test(string, string);

};

#endif