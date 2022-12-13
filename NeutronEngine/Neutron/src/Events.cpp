//
// Created by awilt on 20/10/22.
//

#include "Neutron/Events.h"
#include <thread>
#include <utility>
#include <Logger/Logger.h>
#include <string>

namespace Neutron {
    EventMap EventSystem::events = {};

    void Event::Constructor(std::string name, bool supportMultithread, bool reg) {
        this->name = name;
        if (reg) {
            EventSystem::events[name] = this;
        }
    }

    Event::Event(std::string name, bool supportMultithread, bool reg) {
        this->Constructor(name, supportMultithread, reg);
    }

    Event::Event(std::string name, bool reg) {
        this->Constructor(name, reg, true);
    }

    Event::Event(std::string name) {
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
        }).detach();
    }
    void EventSystem::broadcastThreaded(Event* event, EventArgs data) {
        event->run(data);
    }

    void EventSystem::broadcast(std::string event, EventArgs data, bool multithreaded) {
        auto it = EventSystem::events.find(event);

        if (it != EventSystem::events.end()) {  // the element exists
            multithreaded ?
            broadcastMultithreaded((it->second), data) :
            broadcastThreaded((it->second), data);
        }
    }

    void EventSystem::broadcast(std::string event, bool multithreaded) {
        EventSystem::broadcast(event, EventArgs(), multithreaded);
    }

    void EventSystem::broadcast(std::string event) {
        EventSystem::broadcast(event, EventArgs(), EventSystem::events[event]->supportMultithread || true);
    }

    void EventSystem::broadcast(std::string event, EventArgs data) {
        EventSystem::broadcast(event, data, EventSystem::events[event]->supportMultithread || true);
    }

    Event* EventSystem::get(std::string name) {
        return EventSystem::get(name, true);
    }

    Event* EventSystem::get(std::string name, bool safe) {
        Event* ev = EventSystem::events["name"];
        if (ev) {
            return ev;
        } else if (safe) {
            return new Event(name);
        } else {
            return nullptr;
        }
    }

    void EventSystem::deconst() {
        for (const auto it : Neutron::EventSystem::events) {
            delete it.second;
        }
    }

    void EventSystem::relay(const std::vector<std::string>& original, std::vector<std::string> destination) {
        for (auto it : original) {
            EventSystem::get(it)->on([destination](EventArgs args){
                for (auto it : destination) {
                    EventSystem::broadcast(it);
                }
            });
        }
    }
}