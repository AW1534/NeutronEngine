//
// Created by awilt on 23/10/22.
//

#ifndef NEUTRONENGINE_EXCEPTION_H
#define NEUTRONENGINE_EXCEPTION_H

#include <cstdio>
#include <exception>

namespace Neutron {

    class Exception : public std::exception {
    public:
        char * message = (char*)"(no further information)";
        Exception(char * msg) : message(msg) {};
    };

} // Neutron

#endif //NEUTRONENGINE_EXCEPTION_H
