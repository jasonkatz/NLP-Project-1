build:
	g++ -std=c++11 main.cpp Categorizer.cpp porter2_stemmer.cpp

debug:
	g++ -g -std=c++11 main.cpp Categorizer.cpp porter2_stemmer.cpp
