#include "common/Console.hpp"
#include "common/EventDispatcher.hpp"
#include <random>
#include <vector>

namespace id {
    const std::string EventDispatcher::registerCallback(const std::string& eventName, std::function<void(id::Event&)> callback, const std::string callbackID, bool overwrite) {
        std::string id = callbackID;

        if (id == "") {
            int findEntry;

            do {
                id = getUUID();
                findEntry = m_eventRegistrations.count(id);
            } while (findEntry != 0);
        }

        bool callbackPresent = m_callbacks.count(id) != 0;
        bool registrationsPresent = m_eventRegistrations.count(id) != 0;
        bool eventRegistered = std::find(m_events[eventName].begin(), m_events[eventName].end(), id) != m_events[eventName].end();

        if (!callbackPresent && !eventRegistered && !registrationsPresent) {
            m_callbacks[id] = callback;
            m_eventRegistrations[id] = eventName;
            m_events[eventName].push_back(id);

            id::Console::success("Successfully registered Event \"" + id + "\"!", "EventDispatcher.cpp:" + std::to_string(__LINE__));
            return id;
        }

        if (overwrite) {
            m_callbacks.erase(id);
            m_eventRegistrations.erase(id);
            std::vector<std::string>::iterator it = std::find(m_events[eventName].begin(), m_events[eventName].end(), "id");
            m_events[eventName].erase(it);

            m_callbacks[id] = callback;
            m_eventRegistrations[id] = eventName;
            m_events[eventName].push_back(id);

            id::Console::success("Successfully overwrote Event \"" + id + "\"!", "EventDispatcher.cpp:" + std::to_string(__LINE__));
            return id;
        }

        id::Console::error("Error registering Event \"" + id + "\"!", "EventDispatcher.cpp:" + std::to_string(__LINE__));
        return "";
    }

    bool EventDispatcher::unregisterCallback(const std::string& callbackID) {
        if (m_eventRegistrations.count(callbackID) != 0) {
            m_callbacks.erase(callbackID);

            std::string eventName = m_eventRegistrations[callbackID];
            std::vector<std::string>::iterator it = std::find(m_events[eventName].begin(), m_events[eventName].end(), "id");
            m_events[eventName].erase(it);

            m_eventRegistrations.erase(callbackID);

            id::Console::success("Successfully unregistered Event \"" + callbackID + "\"!", "EventDispatcher.cpp:" + std::to_string(__LINE__));
            return true;
        }

        id::Console::error("Error unregistering Event \"" + callbackID + "\"!", "EventDispatcher.cpp:" + std::to_string(__LINE__));
        return false;
    }

    bool EventDispatcher::dispatch(id::Event& event) {
        for (auto& callback: m_events[event.getEventName()]) {
            if (!event.isPropagating()) {
                return false;
            }

            m_callbacks[callback](event);
        }

        return true;
    }

    // protected methods
    // credits to: https://stackoverflow.com/a/58467162
    const std::string EventDispatcher::getUUID() const {
        static std::random_device dev;
        static std::mt19937 rng(dev());

        std::uniform_int_distribution<int> dist(0, 15);

        const char* v = "0123456789abcdef";
        const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

        std::string result;

        for (int i = 0; i < 16; i++) {
            if (dash[i]) {
                result += "-";
            }

            result += v[dist(rng)];
            result += v[dist(rng)];
        }

        return result;
    }
} /* id */
