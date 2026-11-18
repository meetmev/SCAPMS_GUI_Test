
#include "ReportGenerator.h"

#include <iostream>
#include <algorithm>
#include <map>

namespace clinic {
namespace controller {

// =============================================
// REPORT 1: MOST FREQUENTLY ATTENDED PATIENTS
// =============================================

void ReportGenerator::generateMostFrequentPatients(
    const std::vector<model::PatientRecord*>& patients) {

    std::cout << "\n===== MOST FREQUENTLY ATTENDED PATIENTS =====\n";

    std::vector<std::pair<model::PatientRecord*, int>> attendance;

    for (auto* patient : patients) {

        int completedCount = 0;

        for (const auto& appointment : patient->getAppointments()) {

            if (appointment.getStatus() == "Completed") {
                completedCount++;
            }
        }

        attendance.push_back({patient, completedCount});
    }

    std::sort(attendance.begin(), attendance.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

    for (const auto& record : attendance) {

        std::cout << "Patient: " << record.first->getName()
                  << " | ID: " << record.first->getPatientID()
                  << " | Completed Appointments: " << record.second
                  << "\n";
    }

    if (attendance.empty()) {
        std::cout << "No patient records available.\n";
    }
}


// =============================================
// REPORT 2: PENDING APPOINTMENTS
// =============================================

void ReportGenerator::generatePendingAppointments(
    const std::vector<model::PatientRecord*>& patients) {

    std::cout << "\n===== PENDING APPOINTMENTS REPORT =====\n";

    bool found = false;

    for (auto* patient : patients) {

        for (const auto& appointment : patient->getAppointments()) {

            if (appointment.getStatus() == "Pending") {

                found = true;

                std::cout << "\nPatient: "
                          << patient->getName() << "\n";

                std::cout << "Patient ID: "
                          << patient->getPatientID() << "\n";

                std::cout << "Appointment ID: "
                          << appointment.getAppointmentID() << "\n";

                std::cout << "Date: "
                          << appointment.getAppointmentDate() << "\n";

                std::cout << "Time: "
                          << appointment.getAppointmentTime() << "\n";

                std::cout << "Purpose: "
                          << appointment.getPurpose() << "\n";
            }
        }
    }

    if (!found) {
        std::cout << "No pending appointments found.\n";
    }
}


// =============================================
// REPORT 3: PATIENT CATEGORY DISTRIBUTION
// =============================================

void ReportGenerator::generateCategoryDistribution(
    const std::vector<model::PatientRecord*>& patients) {

    std::cout << "\n===== PATIENT CATEGORY DISTRIBUTION =====\n";

    std::map<std::string, int> categories;

    for (auto* patient : patients) {
        categories[patient->getCategory()]++;
    }

    for (const auto& category : categories) {

        std::cout << category.first
                  << ": " << category.second
                  << "\n";
    }

    std::cout << "Total Patients: " << patients.size() << "\n";
}


// =============================================
// REPORT 4: DAILY APPOINTMENT SUMMARY
// =============================================

void ReportGenerator::generateDailyAppointmentSummary(
    const std::vector<model::PatientRecord*>& patients,
    const std::string& selectedDate) {

    std::cout << "\n===== DAILY APPOINTMENT SUMMARY =====\n";

    std::cout << "Date: " << selectedDate << "\n";

    int total = 0;
    int completed = 0;
    int pending = 0;
    int cancelled = 0;

    for (auto* patient : patients) {

        for (const auto& appointment : patient->getAppointments()) {

            if (appointment.getAppointmentDate() == selectedDate) {

                total++;

                if (appointment.getStatus() == "Completed") {
                    completed++;
                }
                else if (appointment.getStatus() == "Pending") {
                    pending++;
                }
                else if (appointment.getStatus() == "Cancelled") {
                    cancelled++;
                }
            }
        }
    }

    std::cout << "Total Appointments: " << total << "\n";
    std::cout << "Completed: " << completed << "\n";
    std::cout << "Pending: " << pending << "\n";
    std::cout << "Cancelled: " << cancelled << "\n";
}

}
}
