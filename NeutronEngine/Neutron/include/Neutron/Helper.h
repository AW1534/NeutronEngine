//
// Created by awilt on 21/11/22.
//
#ifndef NEUTRONENGINE_HELPER_H
#define NEUTRONENGINE_HELPER_H

#include <string>
#include <iostream>
#include "vector"

#include "Neutron/macros/dll.h"

namespace Neutron {

    EXPORT std::vector<int> range(unsigned int start, unsigned int end, int step = 1);

    EXPORT std::vector<int> range(unsigned int end);

    EXPORT std::vector<std::string> split(std::string string, std::string delimiter = "\n");

    int parseInt(std::string str);
}

#endif //NEUTRONENGINE_HELPER_H
