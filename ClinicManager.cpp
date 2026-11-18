
#include "ClinicManager.h"

#include "../model/GeneralPatient.h"
#include "../model/EmergencyPatient.h"
#include "../model/FollowUpPatient.h"
#include "../model/Appointable.h"

#include <iostream>
#include <stdexcept>
#include <utility>

namespace clinic {
namespace controller {

// ==========================================
// CONSTRUCTOR
// ==========================================

ClinicManager::ClinicManager() {
}

// ==========================================
// REGISTER PATIENT
// ==========================================

void ClinicManager::registerPatient(
    std::unique_ptr<model::PatientRecord> patient) {

    if (!patient) {
        throw std::invalid_argument("Invalid patient record.");
    }

    for (const auto& existing : patients) {
        if (existing->getPatientID() == patient->getPatientID()) {
            throw std::runtime_error("Patient ID already exists.");
        }
    }

    UndoOperation operation;
    operation.operationType = "REGISTER";
    operation.patientID = patient->getPatientID();

    undoStack.push(operation);

    try {
        patients.push_back(std::move(patient));
    }
    catch (...) {
        undoStack.pop();
        throw;
    }

    std::cout << "Patient registered successfully.\n";
}

// ==========================================
// EDIT PATIENT
// ==========================================

void ClinicManager::editPatient(
    int patientID,
    const std::string& newName,
    int newAge,
    const std::string& newContact) {

    if (newName.empty() ||
        newName.find_first_not_of(" \t\n") == std::string::npos) {
        throw std::invalid_argument("Patient name cannot be empty.");
    }

    if (newAge < 0 || newAge > 120) {
        throw std::invalid_argument(
            "Patient age must be between 0 and 120.");
    }

    if (newContact.empty() ||
        newContact.find_first_not_of(" \t\n") == std::string::npos) {
        throw std::invalid_argument(
            "Contact information cannot be empty.");
    }

    for (const auto& patient : patients) {

        if (patient->getPatientID() == patientID) {

            UndoOperation operation;
            operation.operationType = "EDIT";
            operation.patientID = patientID;
            operation.oldName = patient->getName();
            operation.oldAge = patient->getAge();
            operation.oldContact = patient->getContact();

            undoStack.push(operation);

            try {
                patient->setName(newName);
                patient->setAge(newAge);
                patient->setContact(newContact);
            }
            catch (...) {
                undoStack.pop();
                throw;
            }

            std::cout << "Patient information updated successfully.\n";
            return;
        }
    }

    throw std::runtime_error("Patient not found.");
}

// ==========================================
// DELETE PATIENT
// ==========================================

void ClinicManager::deletePatient(int patientID) {

    for (auto it = patients.begin(); it != patients.end(); ++it) {

        if ((*it)->getPatientID() == patientID) {

            model::PatientRecord* patient = it->get();

            UndoOperation operation;
            operation.operationType = "DELETE";
            operation.patientID = patientID;
            operation.oldName = patient->getName();
            operation.oldAge = patient->getAge();
            operation.oldContact = patient->getContact();
            operation.category = patient->getCategory();
            operation.appointments = patient->getAppointments();

            if (auto* emergency =
                dynamic_cast<model::EmergencyPatient*>(patient)) {

                operation.extraInformation =
                    emergency->getEmergencyLevel();
            }
            else if (auto* followUp =
                dynamic_cast<model::FollowUpPatient*>(patient)) {

                operation.extraInformation =
                    followUp->getPreviousVisitDate();
            }

            undoStack.push(operation);

            removePatientReferences(patient);
            patients.erase(it);

            std::cout << "Patient deleted successfully.\n";
            return;
        }
    }

    throw std::runtime_error("Patient not found.");
}

// ==========================================
// DISPLAY ALL PATIENTS
// ==========================================

void ClinicManager::displayAllPatients() const {

    std::cout << "\n===== REGISTERED PATIENTS =====\n";

    for (const auto& patient : patients) {
        patient->displayDetails();
    }

    std::cout << "\nTotal patients: "
              << patients.size() << "\n";
}

// ==========================================
// GET PATIENT COUNT
// ==========================================

int ClinicManager::getPatientCount() const {
    return static_cast<int>(patients.size());
}

// ==========================================
// GET PATIENT RECORDS
// ==========================================

std::vector<model::PatientRecord*>
ClinicManager::getPatientRecords() const {

    std::vector<model::PatientRecord*> records;

    for (const auto& patient : patients) {
        records.push_back(patient.get());
    }

    return records;
}

// ==========================================
// GET PATIENTS FOR FILE SAVING
// ==========================================

const std::vector<std::unique_ptr<model::PatientRecord>>&
ClinicManager::getPatientsForSaving() const {

    return patients;
}

// ==========================================
// SCHEDULE APPOINTMENT
// ==========================================

void ClinicManager::scheduleAppointment(
    int patientID,
    const model::Appointment& appointment) {

    for (const auto& patient : patients) {

        for (const auto& existing : patient->getAppointments()) {

            if (existing.getAppointmentID() ==
                appointment.getAppointmentID()) {

                throw std::runtime_error(
                    "Appointment ID already exists.");
            }
        }
    }

    for (const auto& patient : patients) {

        if (patient->getPatientID() == patientID) {

            model::Appointable* appointable =
                dynamic_cast<model::Appointable*>(patient.get());

            if (!appointable) {
                throw std::runtime_error(
                    "Patient cannot be scheduled.");
            }

            appointable->scheduleAppointment(appointment);

            std::cout << "Appointment scheduled successfully.\n";
            return;
        }
    }

    throw std::runtime_error("Patient not found.");
}

// ==========================================
// CANCEL APPOINTMENT
// ==========================================

void ClinicManager::cancelAppointment(
    int patientID,
    int appointmentID) {

    for (const auto& patient : patients) {

        if (patient->getPatientID() == patientID) {

            model::Appointable* appointable =
                dynamic_cast<model::Appointable*>(patient.get());

            if (!appointable) {
                throw std::runtime_error(
                    "Patient cannot manage appointments.");
            }

            appointable->cancelAppointment(appointmentID);

            std::cout << "Appointment cancellation completed.\n";
            return;
        }
    }

    throw std::runtime_error("Patient not found.");
}

// ==========================================
// DISPLAY APPOINTMENTS
// ==========================================

void ClinicManager::displayAppointments(int patientID) const {

    for (const auto& patient : patients) {

        if (patient->getPatientID() == patientID) {

            std::cout << "\n===== PATIENT APPOINTMENTS =====\n";
            std::cout << "Patient: "
                      << patient->getName() << "\n";

            const auto& appointments = patient->getAppointments();

            if (appointments.empty()) {
                std::cout << "No appointments found.\n";
                return;
            }

            for (const auto& appointment : appointments) {

                std::cout << "\nAppointment ID: "
                          << appointment.getAppointmentID();

                std::cout << "\nDate: "
                          << appointment.getAppointmentDate();

                std::cout << "\nTime: "
                          << appointment.getAppointmentTime();

                std::cout << "\nPurpose: "
                          << appointment.getPurpose();

                std::cout << "\nStatus: "
                          << appointment.getStatus();

                std::cout << "\n--------------------------\n";
            }

            return;
        }
    }

    throw std::runtime_error("Patient not found.");
}

// ==========================================
// ADD TO WAITING QUEUE
// ==========================================

void ClinicManager::addToWaitingQueue(int patientID) {

    for (const auto& patient : patients) {

        if (patient->getPatientID() == patientID) {

            std::queue<model::PatientRecord*> temp = waitingQueue;

            while (!temp.empty()) {

                if (temp.front() == patient.get()) {
                    throw std::runtime_error(
                        "Patient is already in the waiting queue.");
                }

                temp.pop();
            }

            waitingQueue.push(patient.get());

            std::cout << patient->getName()
                      << " added to waiting queue.\n";

            return;
        }
    }

    throw std::runtime_error("Patient not found.");
}

// ==========================================
// CALL NEXT PATIENT
// ==========================================

void ClinicManager::callNextPatient() {

    if (waitingQueue.empty()) {
        std::cout << "No patients are waiting.\n";
        return;
    }

    model::PatientRecord* patient = waitingQueue.front();

    waitingQueue.pop();

    std::cout << "\nNext patient for consultation:\n";

    patient->displayDetails();
}

// ==========================================
// DISPLAY WAITING QUEUE
// ==========================================

void ClinicManager::displayWaitingQueue() const {

    std::cout << "\n===== WAITING QUEUE =====\n";

    if (waitingQueue.empty()) {
        std::cout << "The waiting queue is empty.\n";
        return;
    }

    std::queue<model::PatientRecord*> temp = waitingQueue;

    int position = 1;

    while (!temp.empty()) {

        model::PatientRecord* patient = temp.front();

        std::cout << position << ". "
                  << patient->getName()
                  << " (ID: "
                  << patient->getPatientID()
                  << ")\n";

        temp.pop();
        position++;
    }
}

// ==========================================
// REMOVE PATIENT REFERENCES
// ==========================================

void ClinicManager::removePatientReferences(
    model::PatientRecord* patient) {

    std::queue<model::PatientRecord*> temp;

    while (!waitingQueue.empty()) {

        model::PatientRecord* current = waitingQueue.front();

        waitingQueue.pop();

        if (current != patient) {
            temp.push(current);
        }
    }

    waitingQueue = std::move(temp);

    for (int i = 0; i < recentCount; i++) {

        if (recentPatients[i] == patient) {
            recentPatients[i] = nullptr;
        }
    }
}

// ==========================================
// UNDO LAST OPERATION
// ==========================================

void ClinicManager::undoLastOperation() {

    if (undoStack.empty()) {
        std::cout << "There is no operation to undo.\n";
        return;
    }

    UndoOperation operation = undoStack.top();

    // UNDO REGISTRATION

    if (operation.operationType == "REGISTER") {

        for (auto it = patients.begin(); it != patients.end(); ++it) {

            if ((*it)->getPatientID() == operation.patientID) {

                removePatientReferences(it->get());

                patients.erase(it);

                undoStack.pop();

                std::cout << "Patient registration undone successfully.\n";
                return;
            }
        }

        throw std::runtime_error(
            "Registered patient could not be found for undo.");
    }

    // UNDO EDIT

    else if (operation.operationType == "EDIT") {

        for (const auto& patient : patients) {

            if (patient->getPatientID() == operation.patientID) {

                patient->setName(operation.oldName);
                patient->setAge(operation.oldAge);
                patient->setContact(operation.oldContact);

                undoStack.pop();

                std::cout << "Patient modification undone successfully.\n";
                return;
            }
        }

        throw std::runtime_error(
            "Patient could not be found for edit undo.");
    }

    // UNDO DELETE

    else if (operation.operationType == "DELETE") {

        for (const auto& patient : patients) {

            if (patient->getPatientID() == operation.patientID) {

                throw std::runtime_error(
                    "Cannot restore patient: ID already exists.");
            }
        }

        std::unique_ptr<model::PatientRecord> restoredPatient;

        if (operation.category == "General Patient") {

            restoredPatient =
                std::make_unique<model::GeneralPatient>(
                    operation.patientID,
                    operation.oldName,
                    operation.oldAge,
                    operation.oldContact);
        }
        else if (operation.category == "Emergency Patient") {

            restoredPatient =
                std::make_unique<model::EmergencyPatient>(
                    operation.patientID,
                    operation.oldName,
                    operation.oldAge,
                    operation.oldContact,
                    operation.extraInformation);
        }
        else if (operation.category == "Follow-Up Patient") {

            restoredPatient =
                std::make_unique<model::FollowUpPatient>(
                    operation.patientID,
                    operation.oldName,
                    operation.oldAge,
                    operation.oldContact,
                    operation.extraInformation);
        }
        else {
            throw std::runtime_error("Unknown patient category.");
        }

        for (const auto& appointment : operation.appointments) {
            restoredPatient->addAppointment(appointment);
        }

        patients.push_back(std::move(restoredPatient));

        undoStack.pop();

        std::cout << "Deleted patient restored successfully.\n";
        return;
    }

    throw std::runtime_error("Unknown undo operation.");
}

// ==========================================
// ACCESS PATIENT
// ==========================================

void ClinicManager::accessPatient(int patientID) {

    for (const auto& patient : patients) {

        if (patient->getPatientID() == patientID) {

            for (int i = 9; i > 0; i--) {
                recentPatients[i] = recentPatients[i - 1];
            }

            recentPatients[0] = patient.get();

            if (recentCount < 10) {
                recentCount++;
            }

            std::cout << patient->getName()
                      << " added to recent patient cache.\n";

            return;
        }
    }

    throw std::runtime_error("Patient not found.");
}

// ==========================================
// DISPLAY RECENT PATIENTS
// ==========================================

void ClinicManager::displayRecentPatients() const {

    std::cout << "\n===== RECENTLY ACCESSED PATIENTS =====\n";

    for (int i = 0; i < recentCount; i++) {

        if (recentPatients[i] != nullptr) {

            std::cout << i + 1 << ". "
                      << recentPatients[i]->getName()
                      << " (ID: "
                      << recentPatients[i]->getPatientID()
                      << ")\n";
        }
    }
}

}
}
