
#include "EmergencyPatient.h"
#include <iostream>
#include <stdexcept>

namespace clinic {
namespace model {

EmergencyPatient::EmergencyPatient(
    int id,
    const std::string& name,
    int age,
    const std::string& contact,
    const std::string& level)
    : PatientRecord(id, name, age, contact),
      emergencyLevel(level) {

    if (level != "High" && level != "Medium" && level != "Low") {
        throw std::invalid_argument(
            "Invalid emergency level."
        );
    }
}

// Get patient category
std::string EmergencyPatient::getCategory() const {
    return "Emergency Patient";
}

// NEW: Get emergency level
std::string EmergencyPatient::getEmergencyLevel() const {
    return emergencyLevel;
}

// Display patient details
void EmergencyPatient::displayDetails() const {
    std::cout << "\n--- Emergency Patient ---\n";
    std::cout << "ID: " << getPatientID() << "\n";
    std::cout << "Name: " << getName() << "\n";
    std::cout << "Age: " << getAge() << "\n";
    std::cout << "Contact: " << getContact() << "\n";
    std::cout << "Emergency Level: " << emergencyLevel << "\n";
}

// Schedule appointment
void EmergencyPatient::scheduleAppointment(
    const Appointment& appointment) {

    addAppointment(appointment);

    std::cout << "Emergency appointment scheduled with priority.\n";
}

// Cancel appointment
void EmergencyPatient::cancelAppointment(int appointmentID) {

    cancelAppointmentRecord(appointmentID);

    std::cout << "Emergency appointment cancelled.\n";
}

}
}
