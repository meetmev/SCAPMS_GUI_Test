
#include "../utils/FileHandler.h"

#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <utility>

#include "../model/GeneralPatient.h"
#include "../model/EmergencyPatient.h"
#include "../model/FollowUpPatient.h"
#include "../model/Appointment.h"

namespace clinic {
namespace utils {

// ==========================================
// SAVE PATIENT RECORDS
// ==========================================

void FileHandler::savePatients(
    const std::vector<std::unique_ptr<model::PatientRecord>>& patients,
    const std::string& filename) {

    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Unable to open file for saving."
        );
    }

    for (const auto& patient : patients) {

        std::string category = patient->getCategory();

        file << std::quoted(category) << " "
             << patient->getPatientID() << " "
             << std::quoted(patient->getName()) << " "
             << patient->getAge() << " "
             << std::quoted(patient->getContact()) << " ";

        if (auto emergency =
            dynamic_cast<model::EmergencyPatient*>(patient.get())) {

            file << std::quoted(
                emergency->getEmergencyLevel()
            );

        }
        else if (auto followUp =
            dynamic_cast<model::FollowUpPatient*>(patient.get())) {

            file << std::quoted(
                followUp->getPreviousVisitDate()
            );

        }
        else {
            file << std::quoted(std::string(""));
        }

        file << " "
             << patient->getAppointments().size()
             << "\n";

        for (const auto& appointment :
             patient->getAppointments()) {

            file << appointment.getAppointmentID() << " "
                 << std::quoted(
                     appointment.getAppointmentDate()
                 ) << " "
                 << std::quoted(
                     appointment.getAppointmentTime()
                 ) << " "
                 << std::quoted(
                     appointment.getPurpose()
                 ) << " "
                 << std::quoted(
                     appointment.getStatus()
                 ) << "\n";
        }
    }

    if (!file.good()) {
        throw std::runtime_error(
            "Error occurred while saving records."
        );
    }

    file.close();
}

// ==========================================
// LOAD PATIENT RECORDS
// ==========================================

std::vector<std::unique_ptr<model::PatientRecord>>
FileHandler::loadPatients(const std::string& filename) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Unable to open file for loading."
        );
    }

    std::vector<std::unique_ptr<model::PatientRecord>>
        patients;

    std::string category;

    while (file >> std::quoted(category)) {

        int id;
        int age;
        int appointmentCount;

        std::string name;
        std::string contact;
        std::string extraInformation;

        if (!(file >> id
                  >> std::quoted(name)
                  >> age
                  >> std::quoted(contact)
                  >> std::quoted(extraInformation)
                  >> appointmentCount)) {

            throw std::runtime_error(
                "Invalid patient data in file."
            );
        }

        std::unique_ptr<model::PatientRecord> patient;

        if (category == "General Patient") {

            patient =
                std::make_unique<model::GeneralPatient>(
                    id, name, age, contact
                );

        }
        else if (category == "Emergency Patient") {

            patient =
                std::make_unique<model::EmergencyPatient>(
                    id, name, age, contact,
                    extraInformation
                );

        }
        else if (category == "Follow-Up Patient") {

            patient =
                std::make_unique<model::FollowUpPatient>(
                    id, name, age, contact,
                    extraInformation
                );

        }
        else {
            throw std::runtime_error(
                "Unknown patient category."
            );
        }

        if (appointmentCount < 0) {
            throw std::runtime_error(
                "Invalid appointment count."
            );
        }

        for (int i = 0; i < appointmentCount; i++) {

            int appointmentID;

            std::string date;
            std::string time;
            std::string purpose;
            std::string status;

            if (!(file >> appointmentID
                      >> std::quoted(date)
                      >> std::quoted(time)
                      >> std::quoted(purpose)
                      >> std::quoted(status))) {

                throw std::runtime_error(
                    "Invalid appointment data."
                );
            }

            model::Appointment appointment(
                appointmentID,
                date,
                time,
                purpose
            );

            appointment.setStatus(status);

            patient->addAppointment(appointment);
        }

        patients.push_back(std::move(patient));
    }

    if (!file.eof()) {
        throw std::runtime_error(
            "Error reading patient records."
        );
    }

    file.close();

    return patients;
}

}
}
