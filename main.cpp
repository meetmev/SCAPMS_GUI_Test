
#include <iostream>
#include <memory>

#include "../model/GeneralPatient.h"
#include "../model/EmergencyPatient.h"
#include "../model/FollowUpPatient.h"
#include "../controller/ClinicManager.h"

using namespace clinic::model;
using namespace clinic::controller;

int main() {

    ClinicManager manager;

    try {

        // =================================
        // TEST 1: REGISTER PATIENTS
        // =================================

        std::cout << "\n===== TEST 1: REGISTER PATIENTS =====\n";

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

        manager.displayAllPatients();

        // =================================
        // TEST 2: UNDO REGISTRATION
        // =================================

        std::cout << "\n===== TEST 2: UNDO REGISTRATION =====\n";

        manager.registerPatient(
            std::make_unique<GeneralPatient>(
                104, "Peter", 35, "08044444444"
            )
        );

        manager.undoLastOperation();

        manager.displayAllPatients();

        // =================================
        // TEST 3: EDIT PATIENT
        // =================================

        std::cout << "\n===== TEST 3: EDIT PATIENT =====\n";

        manager.editPatient(
            101, "John Updated", 28, "08011111111"
        );

        manager.displayAllPatients();

        // =================================
        // TEST 4: UNDO EDIT
        // =================================

        std::cout << "\n===== TEST 4: UNDO EDIT =====\n";

        manager.undoLastOperation();

        manager.displayAllPatients();

        // =================================
        // TEST 5: DELETE PATIENT
        // =================================

        std::cout << "\n===== TEST 5: DELETE PATIENT =====\n";

        manager.deletePatient(102);

        manager.displayAllPatients();

        // =================================
        // TEST 6: UNDO DELETE
        // =================================

        std::cout << "\n===== TEST 6: UNDO DELETE =====\n";

        manager.undoLastOperation();

        manager.displayAllPatients();

        // =================================
        // TEST 7: FINAL RESULT
        // =================================

        std::cout << "\n===== FINAL TEST RESULT =====\n";

        std::cout << "Total patients: "
                  << manager.getPatientCount() << "\n";

        std::cout << "\nAll Undo tests completed!\n";

    }
    catch (const std::exception& error) {

        std::cout << "\nERROR: "
                  << error.what() << "\n";

        return 1;
    }

    return 0;
}
