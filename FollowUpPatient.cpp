
#include "FollowUpPatient.h"
#include <iostream>

namespace clinic {
namespace model {

FollowUpPatient::FollowUpPatient(
    int id,
    const std::string& name,
    int age,
    const std::string& contact,
    const std::string& previousDate)
    : PatientRecord(id, name, age, contact),
      previousVisitDate(previousDate) {
}

// Get patient category
std::string FollowUpPatient::getCategory() const {
    return "Follow-Up Patient";
}

// NEW: Get previous visit date
std::string FollowUpPatient::getPreviousVisitDate() const {
    return previousVisitDate;
}

// Display patient details
void FollowUpPatient::displayDetails() const {
    std::cout << "\n--- Follow-Up Patient ---\n";
    std::cout << "ID: " << getPatientID() << "\n";
    std::cout << "Name: " << getName() << "\n";
    std::cout << "Age: " << getAge() << "\n";
    std::cout << "Contact: " << getContact() << "\n";
    std::cout << "Previous Visit: " << previousVisitDate << "\n";
}

// Schedule appointment
void FollowUpPatient::scheduleAppointment(
    const Appointment& appointment) {

    addAppointment(appointment);

    std::cout << "Follow-up appointment scheduled.\n";
}

// Cancel appointment
void FollowUpPatient::cancelAppointment(int appointmentID) {

    cancelAppointmentRecord(appointmentID);

    std::cout << "Follow-up appointment cancelled.\n";
}

}
}
