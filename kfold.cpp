#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <numeric>
#include <algorithm>
#include <ctime>

using namespace std;

//int main() {
//
//	srand(time(0));
//
//	string trainFileName, testFileName;
//	cout << "Enter the name of a training list: ";
//	cin >> trainFileName;
//
//	cout << "Enter a desired test file name: ";
//	cin >> testFileName;
//
//	ifstream trainFile(trainFileName);
//
//	vector<pair<string, string>> files;
//	string line;
//	stringstream ss;
//	while (getline(trainFile, line)) {
//		ss.str(line);
//		string filePath, category;
//		ss >> filePath >> category;
//		files.push_back(pair<string, string>(filePath, category));
//		ss.clear();
//	}
//	trainFile.close();
//
//	cout << "There are " << files.size() << " files in this list." << endl;
//	int numTrain;
//	cout << "Enter the desired number of testing files: ";
//	cin >> numTrain;
//
//	// Generate random indices
//	vector<unsigned int> indices(files.size());
//	iota(indices.begin(), indices.end(), 0);
//	random_shuffle(indices.begin(), indices.end());
//
//	// Pick first k random indices and generate test list from those respective files and a train list from the rest
//	ofstream testFileLabeled(testFileName + ".labels");
//	ofstream trainFileNew(trainFileName + ".new");
//	for (unsigned int i = 0; i < files.size(); ++i) {
//		int index = indices[i];
//		if (i < numTrain) {
//			testFileLabeled << files[index].first << " " << files[index].second << endl;
//		} else {
//			trainFileNew << files[index].first << " " << files[index].second << endl;
//		}
//	}
//	trainFileNew.close();
//	testFileLabeled.close();
//
//	ofstream testFile(testFileName + ".list");
//	for (int i = 0; i < numTrain; ++i) {
//		int index = indices[i];
//		testFile << files[index].first << endl;
//	}
//	testFile.close();
//
//	return 0;
//}