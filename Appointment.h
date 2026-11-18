
#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

namespace clinic {
namespace model {

class Appointment {

private:

    int appointmentID;
    std::string appointmentDate;
    std::string appointmentTime;
    std::string purpose;
    std::string status;

public:

    Appointment(
        int id,
        const std::string& date,
        const std::string& time,
        const std::string& reason
    );

    int getAppointmentID() const;

    std::string getAppointmentDate() const;

    std::string getAppointmentTime() const;

    std::string getPurpose() const;

    std::string getStatus() const;

    void setStatus(const std::string& newStatus);

    void setAppointmentDate(const std::string& newDate);

    void setAppointmentTime(const std::string& newTime);

    void setPurpose(const std::string& newPurpose);
};

}
}

#endif
