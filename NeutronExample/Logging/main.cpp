//
// Created by aw1lt on 09/12/22.
//

#include <Neutron/Logger.h>



int main(int argc, char* argv[]) {
    Neutron::Logger::level = 0; // Info and above

    Neutron::Logger::Info("This is an info message. (lvl 1) The only difference between ::Log and ::Info is their logging levels. the required level can be set by the ::level property");
    Neutron::Logger::Info("This is an info message... With a namesapce", "NAMESPACE");

    Neutron::Logger::Log("This is a standard message. (lvl 2)");
    Neutron::Logger::Log("This is a standard message... With a namesapce", "NAMESPACE");

    Neutron::Logger::Warn("This is a warning message. (lvl 3)");
    Neutron::Logger::Warn("This is a warning message... With a namesapce", "NAMESPACE");

    Neutron::Logger::Info("", "TIP");
    Neutron::Logger::Info("All logging types can have namespaces (or not), but for simplicity all of the following levels will only have one example.", "TIP");
    Neutron::Logger::Info("", "TIP");

    Neutron::Logger::Crit("This is a critical message. Tt is like an Error message, but it won't halt the process. (lvl 4)");


    Neutron::Logger::Assert(7 != 7, "This is an assertion. it only logs if the passed boolean is false. you can set the logging level. Try setting the boolean to a true value", 3);
    Neutron::Logger::Assert(1 + 1 != 2, "This is a Critical assertion. You get the gist", 4);

    Neutron::Logger::Info("Another useful function is LogAt");
    Neutron::Logger::LogAt(1, "It's pretty simple, you pass the logging level, a string and a namespace optionally. Try changing the Logging level number");

    Neutron::Logger::Error("Finally, This is an error message. It will halt the process. Goodbye <3 (lvl 5)");

    return 0;
}