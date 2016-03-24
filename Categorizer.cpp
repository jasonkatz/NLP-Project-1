/*
*****************************************
Jason Katz
ECE-467 Project 1: Text Categorization

Document categorizer using a
naive Bayes approach

File: Categorizer.cpp
Description: Categorizer class
definitions and algorithms
*****************************************
*/

#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <climits>

#include "Categorizer.h"
#include "porter2_stemmer.h"

using namespace std;

Categorizer::Categorizer() {
	wHash = new unordered_map<string, int>();
	wcHash = new unordered_map<string, unordered_map<string, int> *>();
	totalDocuments = 0;
	categoryDocuments = new unordered_map<string, int>();
}

unordered_map<string, int> Categorizer::tokenizeDocument(string filePath) {
	unordered_map<string, int> hash;
	
	ifstream file(filePath);
	char c;
	string currentWord = "";

	while (file >> noskipws >> c) {
		// Add character to current word if it is not a word delimeter
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
			currentWord += c;
		} else {
			// If character is a word delimeter, add the previous word to the hash tables if it exists
			if (currentWord != "") {
				// Convert the word to lower case
				transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);

				// Adjust the hash tables
				if (hash.find(currentWord) == hash.end()) {
					hash.emplace(currentWord, 1);
				} else {
					hash.at(currentWord)++;
				}

				// Reset the current word
				currentWord = "";
			}
		}
	}
	file.close();

	return hash;
}

void Categorizer::trainFromFile(string filePath, string category) {
	// Get tokenized document as a hash table
	unordered_map<string, int> tokens = tokenizeDocument(filePath);

	for (unordered_map<string, int>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
		// Adjust the hash tables
		if (wHash->find(it->first) == wHash->end()) {
			wHash->emplace(it->first, it->second);
		} else {
			(wHash->at(it->first))++;
		}
		if (wcHash->find(category) == wcHash->end()) {
			wcHash->emplace(category, new unordered_map<string, int>);
		}
		if (wcHash->at(category)->find(it->first) == wcHash->at(category)->end()) {
			wcHash->at(category)->emplace(it->first, it->second);
		} else {
			(wcHash->at(category)->at(it->first))++;
		}
	}
}

string Categorizer::estimateFile(string fileName, unordered_map<string, double> categoryProbabilities) {
	unordered_map<string, int> tokens = tokenizeDocument(fileName);

	// Set prior probabilities
	for (unordered_map<string, double>::iterator it = categoryProbabilities.begin(); it != categoryProbabilities.end(); ++it) {
		categoryProbabilities.at(it->first) = log(((double) categoryDocuments->at(it->first)) / ((double) totalDocuments));
	}
	
	// Find each category probability based on prior and word probabilities
	for (unordered_map<string, double>::iterator it = categoryProbabilities.begin(); it != categoryProbabilities.end(); ++it) {
		double logProduct = 0;
		int totalCount = 0;
		// Get total word count in category
		for (unordered_map<string, int>::iterator it2 = wcHash->at(it->first)->begin(); it2 != wcHash->at(it->first)->end(); ++it2) {
			totalCount += it2->second;
		}
		// Find each test word probability in category
		for (unordered_map<string, int>::iterator it2 = tokens.begin(); it2 != tokens.end(); ++it2) {
			int wordFreq = 0;
			if (wcHash->at(it->first)->find(it2->first) != wcHash->at(it->first)->end()) {
				wordFreq = wcHash->at(it->first)->at(it2->first);
			}
			//logProduct += log(((double) wordFreq + 1) / ((double) totalCount + wcHash->at(it->first)->size())); // Laplace smoothing
			logProduct += log(((double) wordFreq + 1) / ((double) totalCount + wHash->size())); // Laplace smoothing
		}

		categoryProbabilities.at(it->first) += logProduct;
	}

	// Return the name of the category with highest likelihood
	int largest = INT_MIN;
	string largestName = "";
	for (unordered_map<string, double>::iterator it = categoryProbabilities.begin(); it != categoryProbabilities.end(); ++it) {
		if (it->second > ((double) largest)) {
			largestName = it->first;
			largest = (int) it->second;
		}
	}

	return largestName;
}

void Categorizer::Train(string trainFileName) {
	string line;
	stringstream ss;

	// Process every document on the provided list
	ifstream trainListFile(trainFileName);
	while (getline(trainListFile, line)) {
		ss.str(line);
		string filePath, category;
		ss >> filePath >> category;

		trainFromFile(filePath, category);
		totalDocuments++;
		if (categoryDocuments->find(category) == categoryDocuments->end()) {
			categoryDocuments->emplace(category, 1);
		} else {
			categoryDocuments->at(category)++;
		}
		
		ss.clear();
	}
}

void Categorizer::Test(string testFileName, string outputFileName) {
	// Set up hash table of probability estimates for each category based on training data (so we don't have to do this more than once)
	unordered_map<string, double> categories;
	for (unordered_map<string, int>::iterator it = categoryDocuments->begin(); it != categoryDocuments->end(); ++it) {
		categories.emplace(it->first, 0);
	}

	string line;
	stringstream ss;

	// Process every document on the provided list and output the result to the output file
	ifstream trainListFile(testFileName);
	ofstream outputFile(outputFileName);
	while (getline(trainListFile, line)) {
		ss.str(line);
		string filePath;
		ss >> filePath;

		string estimatedCategory = estimateFile(filePath, categories);

		outputFile << filePath << " " << estimatedCategory << "\n";

		ss.clear();
	}
	outputFile.close();
	trainListFile.close();
}