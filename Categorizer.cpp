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
}

void Categorizer::trainFromFile(string filePath, string category) {
	ifstream trainFile(filePath);
	char c;
	string currentWord = "";
	while (trainFile >> noskipws >> c) {
		// Add character to current word if it is not a word delimeter
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
			currentWord += c;
		} else {
			// If character is a word delimeter, add the previous word to the hash tables if it exists
			if (currentWord != "") {
				// Convert the word to lower case
				transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);

				// Adjust the hash tables
				if (wHash->find(currentWord) == wHash->end()) {
					wHash->emplace(currentWord, 1);
				} else {
					(wHash->at(currentWord))++;
				}
				if (wcHash->find(category) == wcHash->end()) {
					wcHash->emplace(category, new unordered_map<string, int>);
				}
				if (wcHash->at(category)->find(currentWord) == wcHash->at(category)->end()) {
					wcHash->at(category)->emplace(currentWord, 1);
				} else {
					(wcHash->at(category)->at(currentWord))++;
				}

				// Reset the current word
				currentWord = "";
			}
		}
	}

	trainFile.close();
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
		
		ss.clear();
	}
}

void Categorizer::Test(string testFileName, string outputFileName) {

}