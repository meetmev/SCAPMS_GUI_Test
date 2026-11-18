
#ifndef CLINICMANAGER_H
#define CLINICMANAGER_H

#include <vector>
#include <queue>
#include <stack>
#include <memory>
#include <string>

#include "../model/PatientRecord.h"
#include "../model/Appointment.h"

namespace clinic {
namespace controller {

class ClinicManager {

private:

    std::vector<std::unique_ptr<model::PatientRecord>> patients;

    std::queue<model::PatientRecord*> waitingQueue;

    struct UndoOperation {

        std::string operationType;
        int patientID;

        std::string oldName;
        int oldAge;
        std::string oldContact;

        std::string category;
        std::string extraInformation;

        std::vector<model::Appointment> appointments;
    };

    std::stack<UndoOperation> undoStack;

    model::PatientRecord* recentPatients[10] = {};

    int recentCount = 0;

    void removePatientReferences(
        model::PatientRecord* patient
    );

public:

    ClinicManager();

    // PATIENT MANAGEMENT

    void registerPatient(
        std::unique_ptr<model::PatientRecord> patient
    );

    void editPatient(
        int patientID,
        const std::string& newName,
        int newAge,
        const std::string& newContact
    );

    void deletePatient(int patientID);

    void displayAllPatients() const;

    int getPatientCount() const;

    std::vector<model::PatientRecord*> getPatientRecords() const;

    // NEW: ACCESS PATIENTS FOR FILE SAVING

    const std::vector<std::unique_ptr<model::PatientRecord>>&
    getPatientsForSaving() const;

    // APPOINTMENT MANAGEMENT

    void scheduleAppointment(
        int patientID,
        const model::Appointment& appointment
    );

    void cancelAppointment(
        int patientID,
        int appointmentID
    );

    void displayAppointments(int patientID) const;

    // WAITING QUEUE

    void addToWaitingQueue(int patientID);

    void callNextPatient();

    void displayWaitingQueue() const;

    // UNDO MANAGEMENT

    void undoLastOperation();

    // RECENT PATIENTS

    void accessPatient(int patientID);

    void displayRecentPatients() const;

};

}
}

#endif
