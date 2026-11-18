
#include "SearchEngine.h"

namespace clinic {
namespace controller {

// =====================================
// 1. LINEAR SEARCH
// =====================================

model::PatientRecord* SearchEngine::linearSearch(
    const std::vector<model::PatientRecord*>& patients,
    int patientID) {

    for (int i = 0; i < static_cast<int>(patients.size()); i++) {

        if (patients[i]->getPatientID() == patientID) {
            return patients[i];
        }
    }

    return nullptr;
}

// =====================================
// 2. BINARY SEARCH
// =====================================

model::PatientRecord* SearchEngine::binarySearch(
    const std::vector<model::PatientRecord*>& sortedPatients,
    int patientID) {

    int left = 0;

    int right = static_cast<int>(sortedPatients.size()) - 1;

    while (left <= right) {

        int middle = left + (right - left) / 2;

        int currentID = sortedPatients[middle]->getPatientID();

        if (currentID == patientID) {

            return sortedPatients[middle];

        } else if (currentID < patientID) {

            left = middle + 1;

        } else {

            right = middle - 1;
        }
    }

    return nullptr;
}

// =====================================
// 3. RECURSIVE SEARCH
// =====================================

model::PatientRecord* SearchEngine::recursiveSearch(
    const std::vector<model::PatientRecord*>& patients,
    const std::string& patientName) {

    return recursiveSearchHelper(patients, patientName, 0);
}

// Recursive helper function
model::PatientRecord* SearchEngine::recursiveSearchHelper(
    const std::vector<model::PatientRecord*>& patients,
    const std::string& patientName,
    int index) {

    // Base case: end of vector reached
    if (index >= static_cast<int>(patients.size())) {
        return nullptr;
    }

    // Check current patient
    if (patients[index]->getName() == patientName) {
        return patients[index];
    }

    // Recursive call: check next patient
    return recursiveSearchHelper(
        patients,
        patientName,
        index + 1
    );
}

}
}
