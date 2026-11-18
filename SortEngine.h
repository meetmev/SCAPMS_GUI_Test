
#ifndef SORTENGINE_H
#define SORTENGINE_H

#include <vector>
#include <string>

#include "../model/PatientRecord.h"

namespace clinic {
namespace controller {

class SortEngine {
public:

    // Selection Sort by patient name
    static void selectionSortByName(
        std::vector<model::PatientRecord*>& patients
    );

    // Selection Sort by patient ID
    static void selectionSortByID(
        std::vector<model::PatientRecord*>& patients
    );

    // Insertion Sort by patient age
    static void insertionSortByAge(
        std::vector<model::PatientRecord*>& patients
    );

    // Insertion Sort by patient ID
    static void insertionSortByID(
        std::vector<model::PatientRecord*>& patients
    );
};

}
}

#endif
