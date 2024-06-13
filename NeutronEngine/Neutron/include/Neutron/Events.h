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

#include "Neutron/macros/dll.h"


// TODO: Create "EventDevice" System (like the window system)

namespace Neutron {
    typedef std::map<std::string, void*> EventArgs;
    typedef std::function<void(EventArgs)> Callback;

    class EXPORT Event {
    public:
        std::string name;
        std::vector<Callback> listeners = {};
        bool supportMultithread = true;

        explicit Event(std::string name);
        Event(std::string name, bool supportMultithread, bool reg);
        Event(std::string name, bool reg);
        void run(const EventArgs& data) const;
        void on(Callback cb);
    private:
        void Constructor(std::string name, bool supportMultithread, bool reg);
    };

    typedef std::map<std::string, Event*> EventMap;

    class EXPORT EventSystem {
    public:
        static EventMap events;

        static void relay(const std::vector<std::string>& original, std::vector<std::string> destination);
        static void broadcast(std::string event, EventArgs data, bool multithreaded);
        static void broadcast(std::string event, bool multithreaded);
        static void broadcast(std::string event, EventArgs data);
        static void broadcast(std::string event);

        static void broadcastMultithreaded(Event *event, EventArgs data);
        static void broadcastThreaded(Event *event, EventArgs data);
        static Event* get(std::string name);
        static Event* get(std::string name, bool safe);

        static void deconst();

        template <typename T>
        static T GetArg(Neutron::EventArgs args, std::string name) {
            return ((T)args[name]);
        }
    };
}

#endif //NEUTRONENGINE_EVENTS_H
