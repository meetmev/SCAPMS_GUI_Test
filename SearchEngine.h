
#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <vector>
#include <string>

#include "../model/PatientRecord.h"

namespace clinic {
namespace controller {

class SearchEngine {
public:

    // Linear Search: search by patient ID
    static model::PatientRecord* linearSearch(
        const std::vector<model::PatientRecord*>& patients,
        int patientID
    );

    // Binary Search: search by patient ID in sorted records
    static model::PatientRecord* binarySearch(
        const std::vector<model::PatientRecord*>& sortedPatients,
        int patientID
    );

    // Recursive Search: search by patient name
    static model::PatientRecord* recursiveSearch(
        const std::vector<model::PatientRecord*>& patients,
        const std::string& patientName
    );

private:

    // Helper function for recursive search
    static model::PatientRecord* recursiveSearchHelper(
        const std::vector<model::PatientRecord*>& patients,
        const std::string& patientName,
        int index
    );
};

}
}

#endif
