#ifndef EMERGENCYPATIENT_H
#define EMERGENCYPATIENT_H

#include "PatientRecord.h"
#include "Appointable.h"

namespace clinic {
namespace model {

class EmergencyPatient : public PatientRecord, public Appointable {
private:
    std::string emergencyLevel;

public:
    EmergencyPatient(int id,
                     const std::string& name,
                     int age,
                     const std::string& contact,
                     const std::string& level);

    std::string getCategory() const override;
    std::string getEmergencyLevel() const;

    void displayDetails() const override;

    void scheduleAppointment(
        const Appointment& appointment) override;

    void cancelAppointment(int appointmentID) override;
};

}
}

#endif