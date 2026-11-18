
#ifndef PATIENTRECORD_H
#define PATIENTRECORD_H

#include <string>
#include <vector>
#include "Appointment.h"

namespace clinic {
namespace model {

class PatientRecord {

private:

    int patientID;
    std::string name;
    int age;
    std::string contact;

    // Stores patient appointments
    std::vector<Appointment> appointments;

public:

    // Constructor
    PatientRecord(
        int id,
        const std::string& patientName,
        int patientAge,
        const std::string& patientContact
    );

    virtual ~PatientRecord() = default;

    // Getters
    int getPatientID() const;
    std::string getName() const;
    int getAge() const;
    std::string getContact() const;

    // Setters
    void setName(const std::string& newName);
    void setAge(int newAge);
    void setContact(const std::string& newContact);

    // Appointment management
    void addAppointment(const Appointment& appointment);

    void cancelAppointmentRecord(int appointmentID);

    const std::vector<Appointment>& getAppointments() const;

    // Abstract functions
    virtual std::string getCategory() const = 0;

    virtual void displayDetails() const = 0;
};

}
}

#endif
