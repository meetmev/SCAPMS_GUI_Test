
#include <iostream>
#include <memory>
#include <vector>

#include "../model/GeneralPatient.h"
#include "../model/EmergencyPatient.h"
#include "../model/FollowUpPatient.h"
#include "../model/PatientRecord.h"
#include "../model/Appointment.h"
#include "../utils/FileHandler.h"

using namespace clinic::model;
using namespace clinic::utils;

int main() {

    try {

        std::vector<std::unique_ptr<PatientRecord>> patients;

        // Create three patient types
        patients.push_back(
            std::make_unique<GeneralPatient>(
                101, "John", 25, "08012345678"
            )
        );

        patients.push_back(
            std::make_unique<EmergencyPatient>(
                102, "Mary", 30, "08098765432", "High"
            )
        );

        patients.push_back(
            std::make_unique<FollowUpPatient>(
                103, "David", 40, "08055555555", "2026-10-10"
            )
        );

        // Add an appointment
        Appointment appointment(
            501, "2026-11-20", "10:30", "General Consultation"
        );

        patients[0]->addAppointment(appointment);

        // SAVE PATIENTS
        std::cout << "\n===== SAVING PATIENTS =====\n";

        FileHandler::savePatients(patients, "patients.txt");

        std::cout << "Patients saved successfully!\n";

        // LOAD PATIENTS
        std::cout << "\n===== LOADING PATIENTS =====\n";

        auto loadedPatients =
            FileHandler::loadPatients("patients.txt");

        std::cout << "Patients loaded successfully!\n";

        // DISPLAY LOADED PATIENTS
        std::cout << "\n===== RESTORED PATIENT RECORDS =====\n";

        for (const auto& patient : loadedPatients) {
            patient->displayDetails();

            for (const auto& appointment :
                 patient->getAppointments()) {

                std::cout << "Appointment ID: "
                          << appointment.getAppointmentID() << "\n";

                std::cout << "Date: "
                          << appointment.getAppointmentDate() << "\n";

                std::cout << "Time: "
                          << appointment.getAppointmentTime() << "\n";

                std::cout << "Purpose: "
                          << appointment.getPurpose() << "\n";

                std::cout << "Status: "
                          << appointment.getStatus() << "\n";
            }
        }

        std::cout << "\nTotal restored patients: "
                  << loadedPatients.size() << "\n";

        std::cout << "\nAll file handling tests completed!\n";

    }
    catch (const std::exception& error) {

        std::cout << "\nERROR: "
                  << error.what() << "\n";

        return 1;
    }

    return 0;
}
