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

#include <fstream>
#include "Categorizer.h"

Categorizer::Categorizer() {
	wHash = new unordered_map<string, int>();
	wcHash = new unordered_map<pair<string, string>, int>();
}

void Categorizer::Train(string fileName) {

}