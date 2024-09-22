#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;
using std::string, std::vector, std::pair;

vector<string> vitalType = { "Temperature", "Pulse Rate", "SPO2" };

vector<pair<float, float>> vitalLimits = {
    {95, 102},  // Temperature
    {60, 100},  // Pulse Rate
    {90, 100}   // SPO2
};

bool isVitalsOutOfRange(float vitalValue, pair<float, float> vitalLimits){
    if (vitalValue < vitalLimits.first || vitalValue > vitalLimits.second){
        return true;
    }
    return false;
}

void displayWarningMessage(const string& vitalType) {
    cout << vitalType << " is out of range!\n";
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    vector<float> vitals = { temperature, pulseRate, spo2 };
    for (int i = 0; i < vitalType.size(); i++) {
        if (isVitalsOutOfRange(vitals[i], vitalLimits[i])) {
            displayWarningMessage(vitalType[i]);
            return 0;
        }
    }
    return 1;
}
