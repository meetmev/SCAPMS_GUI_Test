#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include <memory>

#include "../model/PatientRecord.h"

namespace clinic {
namespace utils {

class FileHandler {
public:

    // Save patient records to a file
    static void savePatients(
        const std::vector<std::unique_ptr<model::PatientRecord>>& patients,
        const std::string& filename
    );

    // Load patient records from a file
    static std::vector<std::unique_ptr<model::PatientRecord>>
    loadPatients(const std::string& filename);

};

}
}

#endif
