#pragma once
#include "Constants.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct QuadGram {
	int counts[ALPHABET_SIZE][ALPHABET_SIZE][ALPHABET_SIZE][ALPHABET_SIZE];
	int total;
};

vector<int> stringToInts(string& s) {
	vector<int> ret;
	for (const char& c : s) {
		ret.push_back(tolower(c) - 'a');
	}
	return ret;
}

int findIndex(int find, vector<int>& alphabet) {
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (alphabet[i] == find)return i;
	}
	return -10000;
}

QuadGram* buildGram() {
	QuadGram* ret = (QuadGram*)malloc(sizeof(QuadGram));
	ret->total = 0;
	memset(ret->counts, 0, ALPHABET_SIZE * ALPHABET_SIZE * ALPHABET_SIZE * ALPHABET_SIZE);
	ifstream infile(DICTIONARY_FILE);

	string line;
	while (getline(infile, line)) {
		if (line.size() < 4) continue;
		for (int i = 0; i < line.size() - 4 + 1; i++) {
			ret->counts[(int)(line[i] - 'a')][(int)(line[i + 1] - 'a')][(int)(line[i + 2] - 'a')][(int)(line[i + 3] - 'a')] += 1;
		}
	}
	
	infile.close();
	return ret;
}