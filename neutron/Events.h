//
// Created by awilt on 20/10/22.
//

#ifndef NEUTRONENGINE_EVENTS_H
#define NEUTRONENGINE_EVENTS_H

#include <map>
#include <vector>
#include <functional>
#include <string>
#include <any>
#include "Window.h"

namespace Neutron {
    typedef std::map<std::string, void*> EventArgs;
    typedef std::function<void(EventArgs)> Callback;

    class Event {
    public:
        char* name;
        std::vector<std::function<void(EventArgs)>> listeners = {};
        bool supportMultithread = true;

        explicit Event(char *name);
        Event(char *name, bool supportMultithread, bool reg);
        Event(char *name, bool reg);
        void run(const EventArgs& data) const;
        void on(Callback cb);
    private:
        void Constructor(char *name, bool supportMultithread, bool reg);
    };

    typedef std::map<std::string, Event*> EventMap;

    class EventSystem {
    public:
        static EventMap events;
        static void broadcast(char *event, EventArgs data, bool multithreaded);
        static void broadcast(char *event, bool multithreaded);
        static void broadcast(char *event, EventArgs data);
        static void broadcast(char* event);

        static void broadcastMultithreaded(Event *event, EventArgs data);
        static void broadcastThreaded(Event *event, EventArgs data);
        static Event* get(char* name);
        static Event* get(char* name, bool safe);
    };

    template <typename T>
    static T getArg(Neutron::EventArgs args, std::string name);
}

#endif //NEUTRONENGINE_EVENTS_H
