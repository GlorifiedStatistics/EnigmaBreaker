#pragma once
#include "Constants.h"
#include "EnigmaUtils.h"

using namespace std;

struct EnigmaMachineM3 {
	bool turnovers[3][ALPHABET_SIZE];
	int rotorsRight[3][ALPHABET_SIZE];
	int rotorsLeft[3][ALPHABET_SIZE];
	int reflector[ALPHABET_SIZE];
	int plugboard[ALPHABET_SIZE];
	int positions[3];
	int ringSettings[3];

	string encode(string str) {
		string ret = "";

		for (const char& c : str) {

			// Lowercase the char if needed. If it is not an encodable char, skip it.
			int v = (int)tolower(c) - 'a';
			if (v < 0 || v > ALPHABET_SIZE) continue;

			// Rotate the rotors
			for (int n = 2; n >= 0; n--) {
				bool rotateNext = turnovers[n][positions[n]];
				positions[n] = (positions[n] + 1) % 26;
				if (!rotateNext) break;
			}

			// Go through the plugboard
			v = plugboard[v];

			// Go through the rotors from the right
			for (int n = 2; n >= 0; n--) v = (v + rotorsRight[n][(v + positions[n] - ringSettings[n]) % 26]) % 26;

			// Bounce off reflector plate
			v = reflector[v];

			// Go through the rotors from the left
			for (int n = 0; n < 3; n++) v = (v + rotorsLeft[n][(v + positions[n] - ringSettings[n]) % 26]) % 26;

			// Go back through the plugboard
			v = plugboard[v];

			// Add char to string
			ret += toupper((char)(v + 'a'));
		}

		return ret;
	}
};

EnigmaMachineM3 buildM3(vector<string>& rotors, string& reflector, vector<string>& turnovers, vector<int>& positions, 
	vector<int>& ringSettings, vector<string>& plugboard) {

	EnigmaMachineM3 ret;

	// The rotors right and left
	for (int n = 0; n < 3; n++) {
		vector<int> alphabet = stringToInts(rotors[n]);
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			ret.rotorsRight[n][i] = alphabet[i] - i;
			ret.rotorsLeft[n][i] = findIndex(i, alphabet) - i;
		}
	}

	// The reflector
	vector<int> mappings = stringToInts(reflector);
	for (int i = 0; i < ALPHABET_SIZE; i++) ret.reflector[i] = mappings[i];

	// The turnovers
	for (int n = 0; n < 3; n++) {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			ret.turnovers[n][i] = false;
		}
		vector<int> t = stringToInts(turnovers[n]);
		for (int i = 0; i < t.size(); i++) {
			ret.turnovers[n][t[i]] = true;
		}
	}

	// The positions and ring settings
	for (int i = 0; i < 3; i++) {
		ret.positions[i] = positions[i];
		ret.ringSettings[i] = ringSettings[i];
	}

	// The plugboard
	for (int i = 0; i < ALPHABET_SIZE; i++) ret.plugboard[i] = i;
	for (string s : plugboard) {
		vector<int> plug = stringToInts(s);
		ret.plugboard[plug[0]] = plug[1];
		ret.plugboard[plug[1]] = plug[0];
	}

	return ret;
}