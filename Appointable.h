#ifndef APPOINTABLE_H
#define APPOINTABLE_H

#include "Appointment.h"

namespace clinic {
namespace model {

class Appointable {
public:
    virtual void scheduleAppointment(
        const Appointment& appointment) = 0;

    virtual void cancelAppointment(int appointmentID) = 0;

    virtual ~Appointable() = default;
};

}
}

#endif