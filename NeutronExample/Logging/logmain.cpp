//
// Created by aw1lt on 09/12/22.
//

#include <iostream>
#include <Logger/Logger.h>

#include <map>

int main(int argc, char* argv[]) {
    Logger::Config::level = 0; // Info and above

    std::map<int, bool> map;

    map.insert({10, true});
    map.insert({101231, false});

    Logger::Log(map);

    Logger::Info("hey\ndude");

    Logger::Info("This is an info message. (lvl 1) The only difference between ::Log and ::Info is their logging levels. the required level can be set by the ::level property");
    Logger::Info("This is an info message... With a namesapce", "NAMESPACE");

    //Logger::Log("This is a standard message. (lvl 2)");
    Logger::Log("This is a standard message... With a namesapce", "NAMESPACE");

    //Logger::Warn("This is a warning message. (lvl 3)");
    Logger::Warn("This is a warning message... With a namesapce", "NAMESPACE");

    //Logger::Info("", "TIP");
    //Logger::Info("All logging types can have namespaces (or not), but for simplicity all of the following levels will only have one example.", "TIP");
    //Logger::Info("", "TIP");

    Logger::Crit("This is a critical message. It is like an Error message, but it won't halt the process. (lvl 4)");


    //Logger::Assert(7 != 7, "This is an assertion. it only logs if the passed boolean is false. you can set the logging level. Try setting the boolean to a true value", 3);
    //Logger::Assert(1 + 1 != 2, "This is a Critical assertion. You get the gist", 4);
    //Logger::Assert(10 == 10, "This assert will never be false and is useless with no purpose in life :( try making it run?", 4);

    Logger::Info("Another useful function is LogAt");
    //Logger::LogAt(1, "It's pretty simple, you pass the logging level, a string and a namespace optionally. Try changing the Logging level number");



    //Logger::Error("Finally, This is an error message. It will halt the process. Goodbye <3 (lvl 5)");

    Logger::Warn("Hmm. what happens if i create a null pointer...");
    int* a = nullptr;

    Logger::Warn("...And then dereference it?");
    *a = 5;

    return 0;
}