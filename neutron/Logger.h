//
// Created by awilt on 23/10/22.
//

#ifndef NEUTRONENGINE_LOGGER_H
#define NEUTRONENGINE_LOGGER_H

#include "Exception.h"
#include "Logger.h"
#include <list>

namespace Neutron {
    class Logger {
    public:
        static std::list<char*> queue;
        static void Log(std::basic_string<char> text);
        static void Warn(std::basic_string<char> text);
        static void Crit(std::basic_string<char> text);
        static void Error(std::basic_string<char> text);
    };

}

#endif //NEUTRONENGINE_LOGGER_H
