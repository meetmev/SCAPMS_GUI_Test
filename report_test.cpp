
#include <iostream>
#include <memory>
#include <vector>

#include "../model/GeneralPatient.h"
#include "../model/EmergencyPatient.h"
#include "../model/FollowUpPatient.h"
#include "../model/PatientRecord.h"
#include "../model/Appointment.h"
#include "../controller/ReportGenerator.h"

using namespace clinic::model;
using namespace clinic::controller;

int main() {

    std::vector<std::unique_ptr<PatientRecord>> storage;

    storage.push_back(
        std::make_unique<GeneralPatient>(
            101, "John", 25, "08012345678"
        )
    );

    storage.push_back(
        std::make_unique<EmergencyPatient>(
            102, "Mary", 30, "08098765432", "High"
        )
    );

    storage.push_back(
        std::make_unique<FollowUpPatient>(
            103, "David", 40, "08055555555", "2026-10-10"
        )
    );

    // John: completed and pending appointments
    Appointment a1(501, "2026-11-17", "09:00", "Consultation");
    a1.setStatus("Completed");
    storage[0]->addAppointment(a1);

    Appointment a2(502, "2026-11-17", "10:30", "Check-up");
    storage[0]->addAppointment(a2);

    // Mary: completed appointment
    Appointment a3(503, "2026-11-17", "11:00", "Emergency");
    a3.setStatus("Completed");
    storage[1]->addAppointment(a3);

    // David: pending appointment
    Appointment a4(504, "2026-11-17", "12:00", "Follow-up");
    storage[2]->addAppointment(a4);

    std::vector<PatientRecord*> patients;

    for (const auto& patient : storage) {
        patients.push_back(patient.get());
    }

    std::cout << "\n===== TESTING REPORT GENERATOR =====\n";

    ReportGenerator::generateMostFrequentPatients(patients);

    ReportGenerator::generatePendingAppointments(patients);

    ReportGenerator::generateCategoryDistribution(patients);

    ReportGenerator::generateDailyAppointmentSummary(
        patients, "2026-11-17"
    );

    std::cout << "\nAll report tests completed!\n";

    return 0;
}
