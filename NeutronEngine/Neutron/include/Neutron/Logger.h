//
// Created by awilt on 23/10/22.
//

#ifndef NEUTRONENGINE_LOGGER_H
#define NEUTRONENGINE_LOGGER_H

#include "Logger.h"
#include <list>
#include <cstdio>
#include <iostream>

#include "Neutron/macros/dll.h"

#ifndef BOOST_STACKTRACE_USE_BACKTRACE
#warning BOOST_STACKTRACE_USE_BACKTRACE was not set, so the Neutron Logging system will be limited. Please set the macro and recompile
#endif

namespace Neutron {
    class EXPORT Logger {
    public:
        enum Levels {
            ERROR = 5,
            CRIT = 4,
            WARN = 3,
            LOG = 2,
            INFO = 1,
            ALL = 0
        };

        inline static std::ostream* output = &std::cout;

        inline static int level = Levels::ALL;

        static void Info(std::basic_string<char> text, std::string name = "");
        static void Log(std::basic_string<char> text, std::string name = "");
        static void Warn(std::basic_string<char> text, std::string name = "");
        static void Crit(std::basic_string<char> text, std::string name = "", int stack_mod = 0);
        static void Error(std::basic_string<char> text, std::string name = "", int stack_mod = 0);

        static bool Assert(bool condition, std::basic_string<char> error = "Assertion failed", int level = 4, std::string name = "");
        static void LogAt(int level, std::basic_string<char> message, std::string name = "", int stack_mod = 0);
    };

}

#endif //NEUTRONENGINE_LOGGER_H
