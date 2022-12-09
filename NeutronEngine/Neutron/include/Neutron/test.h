//
// Created by aw1lt on 06/12/22.
//

#ifndef NEUTRONENGINE_TEST_H
#define NEUTRONENGINE_TEST_H
#include "../macros/dll.h"
#include "Logger.h"

using namespace Neutron;



extern "C" {
EXPORT void bruh() {
    Logger::Log("g");
}

class hi;
}


#endif //NEUTRONENGINE_TEST_H
