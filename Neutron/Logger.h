//
// Created by awilt on 23/10/22.
//

#ifndef NEUTRONENGINE_LOGGER_H
#define NEUTRONENGINE_LOGGER_H

#include "Logger.h"
#include <list>
#include <stdio.h>
#include <iostream>

#define LEVEL_NONE 5
#define LEVEL_ERROR 4
#define LEVEL_CRIT 2
#define LEVEL_WARN 2
#define LEVEL_LOG 1
#define LEVEL_INFO 0

namespace Neutron {
    class Logger {
    public:
        inline static std::ostream* output = &std::cout;

        inline static int level = 0;

        static void resetColors();
        static void setColor(char *fgc);

        static void Info(std::basic_string<char> text);
        static void Log(std::basic_string<char> text);
        static void Warn(std::basic_string<char> text);
        static void Crit(std::basic_string<char> text);
        static void Error(std::basic_string<char> text);
    };

}

#endif //NEUTRONENGINE_LOGGER_H
