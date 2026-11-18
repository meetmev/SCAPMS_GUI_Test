
#include "PatientRecord.h"

#include <stdexcept>
#include <cctype>

namespace clinic {
namespace model {

// =====================================
// CONSTRUCTOR
// =====================================

PatientRecord::PatientRecord(
    int id,
    const std::string& patientName,
    int patientAge,
    const std::string& patientContact)
    : patientID(id),
      name(patientName),
      age(patientAge),
      contact(patientContact) {

    if (id <= 0) {
        throw std::invalid_argument(
            "Invalid patient ID."
        );
    }

    if (patientName.empty() ||
        patientName.find_first_not_of(" \t\n") == std::string::npos) {

        throw std::invalid_argument(
            "Patient name cannot be empty."
        );
    }

    if (patientAge < 0 || patientAge > 120) {
        throw std::invalid_argument(
            "Patient age must be between 0 and 120."
        );
    }

    if (patientContact.empty() ||
        patientContact.find_first_not_of(" \t\n") == std::string::npos) {

        throw std::invalid_argument(
            "Contact information cannot be empty."
        );
    }
}

// =====================================
// GETTERS
// =====================================

int PatientRecord::getPatientID() const {
    return patientID;
}

std::string PatientRecord::getName() const {
    return name;
}

int PatientRecord::getAge() const {
    return age;
}

std::string PatientRecord::getContact() const {
    return contact;
}

// =====================================
// SETTERS
// =====================================

void PatientRecord::setName(
    const std::string& newName) {

    if (newName.empty() ||
        newName.find_first_not_of(" \t\n") == std::string::npos) {

        throw std::invalid_argument(
            "Name cannot be empty."
        );
    }

    name = newName;
}

void PatientRecord::setAge(int newAge) {

    if (newAge < 0 || newAge > 120) {

        throw std::invalid_argument(
            "Patient age must be between 0 and 120."
        );
    }

    age = newAge;
}

void PatientRecord::setContact(
    const std::string& newContact) {

    if (newContact.empty() ||
        newContact.find_first_not_of(" \t\n") == std::string::npos) {

        throw std::invalid_argument(
            "Contact information cannot be empty."
        );
    }

    contact = newContact;
}

// =====================================
// ADD APPOINTMENT
// =====================================

void PatientRecord::addAppointment(
    const Appointment& appointment) {

    appointments.push_back(appointment);
}

// =====================================
// GET APPOINTMENTS
// =====================================

const std::vector<Appointment>&
PatientRecord::getAppointments() const {

    return appointments;
}

// =====================================
// CANCEL APPOINTMENT
// =====================================

void PatientRecord::cancelAppointmentRecord(
    int appointmentID) {

    for (auto& appointment : appointments) {

        if (appointment.getAppointmentID() == appointmentID) {

            if (appointment.getStatus() == "Cancelled") {

                throw std::runtime_error(
                    "Appointment is already cancelled."
                );
            }

            appointment.setStatus("Cancelled");

            return;
        }
    }

    throw std::runtime_error(
        "Appointment not found."
    );
}

}
}
