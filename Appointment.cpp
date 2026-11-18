
#include "Appointment.h"
#include <stdexcept>

namespace clinic {
namespace model {

// Constructor
Appointment::Appointment(
    int id,
    const std::string& date,
    const std::string& time,
    const std::string& reason)
    : appointmentID(id),
      appointmentDate(date),
      appointmentTime(time),
      purpose(reason),
      status("Pending") {

    if (id <= 0) {
        throw std::invalid_argument(
            "Invalid appointment ID."
        );
    }

    if (date.empty()) {
        throw std::invalid_argument(
            "Appointment date cannot be empty."
        );
    }

    if (time.empty()) {
        throw std::invalid_argument(
            "Appointment time cannot be empty."
        );
    }

    if (reason.empty()) {
        throw std::invalid_argument(
            "Appointment purpose cannot be empty."
        );
    }
}

// Get appointment ID
int Appointment::getAppointmentID() const {
    return appointmentID;
}

// Get appointment date
std::string Appointment::getAppointmentDate() const {
    return appointmentDate;
}

// Get appointment time
std::string Appointment::getAppointmentTime() const {
    return appointmentTime;
}

// Get appointment purpose
std::string Appointment::getPurpose() const {
    return purpose;
}

// Get appointment status
std::string Appointment::getStatus() const {
    return status;
}

// Change appointment status
void Appointment::setStatus(
    const std::string& newStatus) {

    if (newStatus.empty()) {
        throw std::invalid_argument(
            "Appointment status cannot be empty."
        );
    }

    status = newStatus;
}

// Change appointment date
void Appointment::setAppointmentDate(
    const std::string& newDate) {

    if (newDate.empty()) {
        throw std::invalid_argument(
            "Appointment date cannot be empty."
        );
    }

    appointmentDate = newDate;
}

// Change appointment time
void Appointment::setAppointmentTime(
    const std::string& newTime) {

    if (newTime.empty()) {
        throw std::invalid_argument(
            "Appointment time cannot be empty."
        );
    }

    appointmentTime = newTime;
}

// Change appointment purpose
void Appointment::setPurpose(
    const std::string& newPurpose) {

    if (newPurpose.empty()) {
        throw std::invalid_argument(
            "Appointment purpose cannot be empty."
        );
    }

    purpose = newPurpose;
}

}
}
