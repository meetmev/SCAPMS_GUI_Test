
#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <vector>
#include <string>

#include "../model/PatientRecord.h"

namespace clinic {
namespace controller {

class ReportGenerator {

public:

    // Report 1: Most frequently attended patients
    static void generateMostFrequentPatients(
        const std::vector<model::PatientRecord*>& patients
    );

    // Report 2: Patients with pending appointments
    static void generatePendingAppointments(
        const std::vector<model::PatientRecord*>& patients
    );

    // Report 3: Patient category distribution
    static void generateCategoryDistribution(
        const std::vector<model::PatientRecord*>& patients
    );

    // Report 4: Daily appointment summary
    static void generateDailyAppointmentSummary(
        const std::vector<model::PatientRecord*>& patients,
        const std::string& selectedDate
    );

};

}
}

#endif
