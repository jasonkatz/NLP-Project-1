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
#include "Categorizer.h"

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

void Categorizer::Train(string fileName) {
	string line;
	stringstream ss;

	// Process every document on the provided list
	ifstream trainListFile(fileName);
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
	return;
}

void Categorizer::Test(string testFileName, string outputFileName) {

}