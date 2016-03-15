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

	// Hash table of hash tables that maps words to counts for specific categories
	unordered_map<string, unordered_map<string, int> *> * wcHash;

	// Total number of documents overall
	int totalDocuments;

	// Total number of documents per category
	unordered_map<string, int> * categoryDocuments;

	// Tokenizes a document into a hash table
	unordered_map<string, int> tokenizeDocument(string);

	// Trains categorizer using a document and its category label
	void trainFromFile(string, string);

public:

	// Constructor that simply initializes the hash tables
	Categorizer();

	// Trains the categorizer with a provided file containing a list of training documents
	void Train(string);

	// Tests the categorizer with a provided file containing a list of testing documents
	void Test(string, string);

};

#endif