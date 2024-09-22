#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;
using std::string, std::vector, std::pair;

struct VitalData {
    string vitalType;
    float lowerLimit;
    float upperLimit;
    float tolerance;
};

vector<VitalData> m_vitalParameters = {
    {"Temperature", 95, 102, 1.5},
    {"Pulse Rate", 60, 100, 1.5},
    {"SPO2", 90, 100, 1.5}
};

bool isVitalsOutOfRange(const VitalData& vital, float vitalValue) {
    if (vitalValue < vital.lowerLimit || vitalValue > vital.upperLimit) {
        return true;
    }
    return false;
}

void displayAlertMessage(const string& vitalType) {
    cout << vitalType << " is out of range!\n";
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    vector<float> vitalValues = {temperature, pulseRate, spo2};
    for (int i = 0; i < m_vitalParameters.size(); i++) {
        if (isVitalsOutOfRange(m_vitalParameters[i], vitalValues[i])) {
            displayAlertMessage(m_vitalParameters[i].vitalType);
            return 0;
        }
    }
    return 1;
}
