//
// Created by aw1lt on 08/12/22.
//

#ifndef NEUTRONEXAMPLEC_FILES_H
#define NEUTRONEXAMPLEC_FILES_H

#include <string>
#include <vector>

namespace Neutron::Utils::Files {
    std::vector<std::string> readLines_gi(std::string file, std::vector<int> &index_of, int min = 0, int max = -1);
    std::vector<std::string> readLines(std::string file, int min = 0, int max = -1);
    std::vector<std::string> readLines(std::string file, int max = -1);
    std::string read(std::string file);
}

#endif //NEUTRONEXAMPLEC_FILES_H
