
#include "SortEngine.h"

namespace clinic {
namespace controller {

// =====================================
// 1. SELECTION SORT BY NAME
// =====================================

void SortEngine::selectionSortByName(
    std::vector<model::PatientRecord*>& patients) {

    int n = static_cast<int>(patients.size());

    for (int i = 0; i < n - 1; i++) {

        int minIndex = i;

        for (int j = i + 1; j < n; j++) {

            if (patients[j]->getName() <
                patients[minIndex]->getName()) {

                minIndex = j;
            }
        }

        model::PatientRecord* temp = patients[i];

        patients[i] = patients[minIndex];

        patients[minIndex] = temp;
    }
}

// =====================================
// 2. SELECTION SORT BY ID
// =====================================

void SortEngine::selectionSortByID(
    std::vector<model::PatientRecord*>& patients) {

    int n = static_cast<int>(patients.size());

    for (int i = 0; i < n - 1; i++) {

        int minIndex = i;

        for (int j = i + 1; j < n; j++) {

            if (patients[j]->getPatientID() <
                patients[minIndex]->getPatientID()) {

                minIndex = j;
            }
        }

        model::PatientRecord* temp = patients[i];

        patients[i] = patients[minIndex];

        patients[minIndex] = temp;
    }
}

// =====================================
// 3. INSERTION SORT BY AGE
// =====================================

void SortEngine::insertionSortByAge(
    std::vector<model::PatientRecord*>& patients) {

    int n = static_cast<int>(patients.size());

    for (int i = 1; i < n; i++) {

        model::PatientRecord* key = patients[i];

        int j = i - 1;

        while (j >= 0 &&
               patients[j]->getAge() > key->getAge()) {

            patients[j + 1] = patients[j];

            j--;
        }

        patients[j + 1] = key;
    }
}

// =====================================
// 4. INSERTION SORT BY ID
// =====================================

void SortEngine::insertionSortByID(
    std::vector<model::PatientRecord*>& patients) {

    int n = static_cast<int>(patients.size());

    for (int i = 1; i < n; i++) {

        model::PatientRecord* key = patients[i];

        int j = i - 1;

        while (j >= 0 &&
               patients[j]->getPatientID() >
               key->getPatientID()) {

            patients[j + 1] = patients[j];

            j--;
        }

        patients[j + 1] = key;
    }
}

}
}
