
#include "../controller/ClinicManager.h"
#include "../model/GeneralPatient.h"
#include "../model/EmergencyPatient.h"
#include "../model/FollowUpPatient.h"
#include "../model/Appointment.h"

#include <iostream>
#include <memory>
#include <stdexcept>

using namespace clinic::model;
using namespace clinic::controller;

int main() {

    try {

        ClinicManager manager;

        std::cout << "\n===== REGISTER PATIENTS =====\n";

        manager.registerPatient(
            std::make_unique<GeneralPatient>(
                101, "John", 25, "08012345678"
            )
        );

        manager.registerPatient(
            std::make_unique<EmergencyPatient>(
                102, "Mary", 30, "08098765432", "High"
            )
        );

        manager.registerPatient(
            std::make_unique<FollowUpPatient>(
                103, "David", 40, "08055555555", "2026-10-10"
            )
        );

        std::cout << "\n===== SCHEDULE APPOINTMENT =====\n";

        manager.scheduleAppointment(
            101,
            Appointment(
                501,
                "2026-11-20",
                "10:30",
                "General Consultation"
            )
        );

        std::cout << "\n===== SAVE PATIENTS =====\n";

        manager.savePatientRecords("patients_backup.txt");

        std::cout << "\n===== LOAD PATIENTS INTO NEW MANAGER =====\n";

        ClinicManager restoredManager;

        restoredManager.loadPatientRecords("patients_backup.txt");

        std::cout << "\n===== RESTORED PATIENTS =====\n";

        restoredManager.displayAllPatients();

        std::cout << "\n===== VERIFY RESTORED APPOINTMENTS =====\n";

        restoredManager.displayAppointments(101);

        std::cout << "\nTotal restored patients: "
                  << restoredManager.getPatientCount()
                  << "\n";

        if (restoredManager.getPatientCount() != 3) {
            throw std::runtime_error(
                "Patient restoration count is incorrect."
            );
        }

        std::cout << "\nALL FILE INTEGRATION TESTS PASSED!\n";

    }
    catch (const std::exception& error) {

        std::cerr << "\nTEST FAILED: "
                  << error.what() << "\n";

        return 1;
    }

    return 0;
}
