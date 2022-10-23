//
// Created by awilt on 23/10/22.
//

#include <iostream>
#include <string>
#include "Logger.h"
#include "Exception.h"
#include "macros.h"

namespace Neutron {
    void Logger::Log(std::string text) {
        std::cout << ((std::string) CONSOLE_NC).append(text).append(CONSOLE_NC).c_str() << std::endl;
    }

    void Logger::Warn(std::string text) {
        std::cout << ((std::string) CONSOLE_YELLOW).append("WARNING: ").append(CONSOLE_NC).append(text).c_str() << std::endl;}

    void Logger::Crit(std::string text) {
        std::cout << ((std::string) CONSOLE_RED).append("CRITICAL: ").append(CONSOLE_NC).append(text).c_str() << std::endl;
    }

    void Logger::Error(std::string text) {
        std::cout << ((std::string) CONSOLE_RED).append("ERROR: ").append(CONSOLE_NC).append(text).c_str() << std::endl;
    }

}