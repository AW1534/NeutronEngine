//
// Created by awilt on 23/10/22.
//

#include <ctime>
#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>

#include <boost/stacktrace.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "Neutron/Logger.h"
#include "../include/Neutron/macros/ansi.h"
#include "Neutron/Helper.h"
#include "../include/Neutron/Utils/Files.h"

namespace Neutron {
    std::string fill(std::string str, int len = 2, char fill = 48) {
        if (str.length() < len)
            str.insert(str.front() == '-' ? 1 : 0, len - str.length(), fill);
        return str;
    }

    std::string prettyStacktrace(std::string t, int highlight_frame = -1, std::string highlight_color = FORE_BRIGHT_MAGENTA) {

        // -- Highlight the most important frame and dim the others -- //
        for (int x : range(split(t,"\n").size())) {
            std::string c_color;
            if (x == highlight_frame) {
                c_color = highlight_color + BOLD;
            } else {
                c_color = FORE_GRAY;
            }

            std::string n = fill(std::to_string(x), 2, 32);

            boost::replace_all(t, n + "# ", c_color + n + "# " + RESET);
        }

        #ifndef BOOST_STACKTRACE_USE_BACKTRACE
        return t;
        #endif

        #ifdef BOOST_STACKTRACE_USE_BACKTRACE
        std::vector<std::string> t_list = split(t);

        // -- Insert a snippet of the most important frame's respective file right below it -- //
        int current_trace = 0;

        for (const std::string& stack : t_list) {
            if (current_trace == highlight_frame) {
                std::vector<std::string> file_and_line = split(split(stack, " at ")[1],":");
                std::string filename = file_and_line[0];
                int line = parseInt(file_and_line[1]);

                int min_line = line - 1;
                int max_line = line + 1;

                std::vector<int> t_lines = {};
                std::vector<std::string> important_lines = Utils::Files::readLines_gi(filename, t_lines, min_line, max_line);

                std::ostringstream oss;

                int i = 0;
                for (std::string x : important_lines) {
                    if (t_lines[i] == line) {
                        oss << highlight_color;
                        oss << "\n  * ";
                        oss << RESET;
                    } else {
                        oss << "\n    ";
                    }

                    oss << fill(std::to_string(t_lines[i]), 2, ' ') << FORE_GRAY << " | " << RESET << x;
                    i++;
                }
                std::string s = oss.str();
                t_list[current_trace] = stack + oss.str();

                break;  //end the loop because the if statement should only be true once
            }
            current_trace++;
        }


        return join(t_list,"\n");

        #endif
    }

    std::string fancyTime() {
        time_t currentTime;
        struct tm *localTime;

        time(&currentTime);
        localTime = localtime(&currentTime);

        std::string Hour = fill(std::to_string(localTime->tm_hour));
        std::string Min = fill(std::to_string(localTime->tm_min));
        std::string Sec = fill(std::to_string(localTime->tm_sec));

        return "[" + Hour + ":" + Min + ":" + Sec + "]";
    }

    void Logger::Info(std::basic_string<char> text, std::string name) {
        if (Logger::level >= Logger::Levels::INFO) { return; }

        if (name != "") {
            name = "[" + name + "] ";
        }

        std::string end = std::string("");

        end.append(FORE_GRAY);
        end.append(BOLD);
        end.append(fancyTime() + " ");
        end.append(name);
        end.append(RESET);
        end.append(text);

        *output << end << std::endl;
    }

    void Logger::Log(std::string text, std::string name) {
        if (Logger::level >= Logger::Levels::LOG) {return;}

        if (name != "") {
            name = "[" + name + "] ";
        }

        std::string end = std::string("");

        end.append(FORE_GRAY);
        end.append(BOLD);
        end.append(fancyTime() + " ");
        end.append(name);
        end.append(RESET);
        end.append(text);

        *output << end << std::endl;
    }

    void Logger::Warn(std::string text, std::string name) {
        if (Logger::level >= Logger::Levels::WARN) {return;}

        if (name != "") {
            name = "[" + name + "] ";
        }

        std::string end = std::string("");

        end.append(FORE_YELLOW);
        end.append(BOLD);
        end.append(fancyTime() + " ");
        end.append(name + "WARNING: ");
        end.append(RESET);
        end.append(text);

        *output << end << std::endl;
    }

    void Logger::Crit(std::string text, std::string name, int stack_mod) {
        if (Logger::level >= Logger::Levels::CRIT) {return;}

        if (name != "") {
            name = "[" + name + "] ";
        }

        std::string end = std::string("");

        end.append(FORE_BRIGHT_MAGENTA);
        end.append(BOLD);
        end.append(fancyTime() + " ");
        end.append(name + "CRITICAL: ");
        end.append(RESET);
        end.append(text);
        end.append("\n");
        end.append(prettyStacktrace(to_string(boost::stacktrace::stacktrace()), 1 + stack_mod, FORE_BRIGHT_MAGENTA));

        *output << end << std::endl;
    }

    void Logger::Error(std::string text, std::string name, int stack_mod) {
        if (Logger::level >= Logger::Levels::ERROR) { return; }

        if (name != "") {
            name = "[" + name + "] ";
        }

        std::string end = std::string("");

        end.append(FORE_RED);
        end.append(BOLD);
        end.append(fancyTime() + " ");
        end.append(name + "ERROR: ");
        end.append(RESET);
        end.append(text);
        end.append("\n");
        end.append(prettyStacktrace(to_string(boost::stacktrace::stacktrace()), 1 + stack_mod, FORE_RED));

        *output << end << std::endl;
        exit(1);
    }

    void Logger::LogAt(int level, std::basic_string<char> message, std::string name, int stack_mod) {
        if (level == 5) Logger::Error(message, name, stack_mod+1);
        else if (level == 4) Logger::Crit(message, name, stack_mod+1);
        else if (level == 3) Logger::Warn(message, name);
        else if (level == 2) Logger::Log(message, name);
        else if (level == 1) Logger::Info(message, name);
    }

    bool Logger::Assert(bool condition, std::basic_string<char> error, int level, std::string name) {
        if (condition) return true;

        Logger::LogAt(level, std::move(error), name, 1);

        return false;
    }

}