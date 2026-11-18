
#include "GeneralPatient.h"
#include <iostream>

namespace clinic {
namespace model {

GeneralPatient::GeneralPatient(
    int id,
    const std::string& name,
    int age,
    const std::string& contact)
    : PatientRecord(id, name, age, contact) {
}

std::string GeneralPatient::getCategory() const {
    return "General Patient";
}

void GeneralPatient::displayDetails() const {
    std::cout << "\n--- General Patient ---\n";
    std::cout << "ID: " << getPatientID() << "\n";
    std::cout << "Name: " << getName() << "\n";
    std::cout << "Age: " << getAge() << "\n";
    std::cout << "Contact: " << getContact() << "\n";
}

void GeneralPatient::scheduleAppointment(
    const Appointment& appointment) {

    addAppointment(appointment);

    std::cout << "General patient appointment scheduled.\n";
}

void GeneralPatient::cancelAppointment(int appointmentID) {
    cancelAppointmentRecord(appointmentID);
    std::cout << "Appointment cancelled.\n";
}

}
}
