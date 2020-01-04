#include <iostream>
#include <chrono>
#include "Constants.h"
#include "EnigmaUtils.h"
#include "EnigmaMachine.h"

using namespace std;

int main(){
    vector<string> rotors = { ROTOR_1, ROTOR_2, ROTOR_3 };
    string reflector = REFLECTOR_B;
    vector<string> turnovers = { ROTOR_1T, ROTOR_2T, ROTOR_3T };
    vector<int> positions = { 0, 0, 0 };
    vector<int> ringSettings = { 0, 0, 0 };
    vector<string> plugboard = {};

    EnigmaMachineM3 machine = buildM3(rotors, reflector, turnovers, positions, ringSettings, plugboard);

    string str = "Please encode this correctly";

    QuadGram* qp = buildGram();
}

