
#ifndef FOLLOWUPPATIENT_H
#define FOLLOWUPPATIENT_H

#include "PatientRecord.h"
#include "Appointable.h"

namespace clinic {
namespace model {

class FollowUpPatient : public PatientRecord, public Appointable {

private:
    std::string previousVisitDate;

public:

    // Constructor
    FollowUpPatient(
        int id,
        const std::string& name,
        int age,
        const std::string& contact,
        const std::string& previousDate
    );

    // Get patient category
    std::string getCategory() const override;

    // NEW: Get previous visit date
    std::string getPreviousVisitDate() const;

    // Display patient details
    void displayDetails() const override;

    // Schedule appointment
    void scheduleAppointment(
        const Appointment& appointment
    ) override;

    // Cancel appointment
    void cancelAppointment(int appointmentID) override;

};

}
}

#endif
