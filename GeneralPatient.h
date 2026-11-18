#ifndef GENERALPATIENT_H
#define GENERALPATIENT_H

#include "PatientRecord.h"
#include "Appointable.h"

namespace clinic {
namespace model {

class GeneralPatient : public PatientRecord, public Appointable {
public:
    GeneralPatient(int id,
                   const std::string& name,
                   int age,
                   const std::string& contact);

    std::string getCategory() const override;

    void displayDetails() const override;

    void scheduleAppointment(
        const Appointment& appointment) override;

    void cancelAppointment(int appointmentID) override;
};

}
}

#endif