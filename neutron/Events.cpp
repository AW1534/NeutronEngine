//
// Created by awilt on 20/10/22.
//

#include "Events.h"
#include <iostream>
#include <thread>
#include <utility>

namespace Neutron {
    EventMap EventSystem::events = {};

    void Event::Constructor(char* name, bool supportMultithread, bool reg) {
        std::string n = name;
        this->name = name;
        if (reg) {
            EventSystem::events[n] = this;
        }
    }

    Event::Event(char *name, bool supportMultithread, bool reg) {
        this->Constructor(name, reg, reg);
    }

    Event::Event(char* name, bool reg) {
        this->Constructor(name, reg, true);
    }

    Event::Event(char* name) {
        this->Constructor(name, true, true);
    }

    void Event::run(const EventArgs& data) const {
        for (auto it = begin (this->listeners); it != end (this->listeners); ++it) {
            (*it)(data);
        }

    }

    void Event::on(Callback cb) {
        this->listeners.push_back(cb);
    }

    void EventSystem::broadcastMultithreaded(Event* event, EventArgs data) {
        std::thread([event, data]() {
            event->run(data);
        });
    }
    void EventSystem::broadcastThreaded(Event* event, EventArgs data) {
        event->run(data);
    }

    void EventSystem::broadcast(char* event, EventArgs data, bool multithreaded) {
        auto it = EventSystem::events.find(event);

        if (it != EventSystem::events.end()) {  // the element exists
            multithreaded ?
            broadcastMultithreaded((it->second), data) :
            broadcastThreaded((it->second), data);
        }
    }

    void EventSystem::broadcast(char* event) {
        EventSystem::broadcast(event, EventArgs(), EventSystem::events[event]->supportMultithread || true);
    }

    void EventSystem::broadcast(char *event, EventArgs data) {
        EventSystem::broadcast(event, std::move(data), EventSystem::events[event]->supportMultithread || true);
    }

    Event* EventSystem::get(char *name) {
        return EventSystem::get(name, true);
    }

    Event* EventSystem::get(char *name, bool safe) {
        Event* ev = EventSystem::events["name"];
        if (ev) {
            return ev;
        } else if (safe) {
            return new Event(name);
        } else {
            return nullptr;
        }
    }
}
