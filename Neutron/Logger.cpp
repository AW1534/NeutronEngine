//
// Created by awilt on 23/10/22.
//

#include <iostream>
#include <string>
#include <boost/stacktrace.hpp>
#include "Logger.h"
#include "macros/ansi.h"

namespace Neutron {
    void Logger::Info(std::basic_string<char> text) {
        if (Logger::level > 0) {return;}

        *output << text.c_str() << std::endl;
    }

    void Logger::Log(std::string text) {
        if (Logger::level > 1) {return;}

        *output << text.c_str() << std::endl;
    }

    void Logger::Warn(std::string text) {
        if (Logger::level > 2) {return;}

        setColor(FORE_YELLOW);
        *output << "WARNING: ";
        resetColors();
        *output << text.c_str() << std::endl;
    }

    void Logger::Crit(std::string text) {
        if (Logger::level > 3) {return;}

        setColor(FORE_RED);
        *output << "CRITICAL: ";
        resetColors();
        std::cout << text.c_str() << std::endl;
        *output << boost::stacktrace::stacktrace() << std::endl;
    }

    void Logger::Error(std::string text) {
        if (Logger::level > 4) {return;}

        setColor(FORE_RED);
        *output << "ERROR: ";
        resetColors();
        *output << text.c_str() << std::endl;
        *output << boost::stacktrace::stacktrace() << std::endl;
        exit(1);
    }

    void Logger::resetColors() {
        *output << RESET_COLOR;
    }

    void Logger::setColor(char* fgc) {
        *output << fgc;
    }

}