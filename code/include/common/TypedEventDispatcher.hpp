/**
 * @file common/TypedEventDispatcher.hpp
 * @brief Defines the TypedEventDispatcher-class
 */
#pragma once

#include <functional>
#include <map>
#include <random>
#include <vector>

#include "Event.hpp"
#include "Lock.hpp"
#include "common/Console.hpp"
#include "common/EventDispatcher.hpp"

namespace id {
    /**
     * @brief Handles and dispatches @ref id::Event "Events" of a specific type to registered callbacks
     * @tparam EventType The type of Event to handle. Must be id::Event or a child-class of it
     */
    template <class EventType>
    class TypedEventDispatcher {
    public:
        /**
         * @brief Default constructor
         */
        TypedEventDispatcher() {
            static_assert(std::is_base_of<id::Event, EventType>::value, "Wrong Event-type provided. Make sure you use id::Event or a child-class of it.");
        }

        /**
         * @brief Destructor
         */
        virtual ~TypedEventDispatcher() { /* do nothing */ }

        /**
         * @brief Registers a callback to get called when the given eventName gets dispatched
         * @param eventName  The eventName to register for
         * @param callback   The callback to call - the single parameter is the dispatched Event
         * @param callbackID The id for this callback, needed to unregister this callback again. When an empty string is given, a random unique ID will be generated
         * @param overwrite  Whether to overwrite any previously with this id stored callback or not
         * @return           The callback-id of the newly registered callback
         */
        const std::string registerCallback(const std::string& eventName, std::function<void(EventType&)> callback, const std::string callbackID = "", bool overwrite = false);

        /**
         * @brief Unregisters a callback with the given id
         * @param  callbackID The id to unregister
         * @return            Whether the process was successful (usually only `false` if no such callback was registered)
         */
        bool unregisterCallback(const std::string& callbackID);

        /**
         * @brief Clears all registered callbacks
         */
        void clearCallbacks();

        /**
         * @brief Dispatches a given Event to all registered callbacks
         * @param  event The Event to dispatch
         * @return       `true` if the Event successfully propagated to all availiable callbacks, `false` if the propagation was stopped
         */
        virtual bool dispatch(EventType& event);

    protected:
        /**
         * @brief Returns a random UUID-shaped string to be used as a callback-id
         * @return A random ID. This does not test against already existing IDs - this needs to be done in the calling function
         */
        const std::string _getUUID() const;

    private:
        /* data */
        Mutex m_mutex;
              // callbackID | callback
        std::map<std::string, std::function<void(EventType&)>> m_callbacks;
              // eventName  | callbackIDs
        std::map<std::string, std::vector<std::string>> m_events;
              // callbackID | eventName
        std::map<std::string, std::string> m_eventRegistrations;
    };
} /* id */

#ifndef __DOCS__
namespace id {
    template <class EventType>
    const std::string TypedEventDispatcher<EventType>::registerCallback(const std::string& eventName, std::function<void(EventType&)> callback, const std::string callbackID, bool overwrite) {
        std::string id = callbackID;

        if (id == "") {
            int findEntry;

            do {
                id = _getUUID();
                findEntry = m_eventRegistrations.count(id);
            } while (findEntry != 0);
        }

        bool callbackPresent = m_callbacks.count(id) != 0;
        bool registrationsPresent = m_eventRegistrations.count(id) != 0;
        bool eventRegistered = std::find(m_events[eventName].begin(), m_events[eventName].end(), id) != m_events[eventName].end();

        if (!callbackPresent && !eventRegistered && !registrationsPresent) {
            id::Lock lock(m_mutex);

            m_callbacks[id] = callback;
            m_eventRegistrations[id] = eventName;
            m_events[eventName].push_back(id);

            id::Console::success("Successfully registered Event \"" + id + "\"!", "TypedEventDispatcher.cpp:" + std::to_string(__LINE__));
            return id;
        }

        if (overwrite) {
            id::Lock lock(m_mutex);

            m_callbacks.erase(id);
            m_eventRegistrations.erase(id);
            std::vector<std::string>::iterator it = std::find(m_events[eventName].begin(), m_events[eventName].end(), "id");
            m_events[eventName].erase(it);

            m_callbacks[id] = callback;
            m_eventRegistrations[id] = eventName;
            m_events[eventName].push_back(id);

            id::Console::success("Successfully overwrote Event \"" + id + "\"!", "TypedEventDispatcher.cpp:" + std::to_string(__LINE__));
            return id;
        }

        id::Console::error("Error registering Event \"" + id + "\"!", "TypedEventDispatcher.cpp:" + std::to_string(__LINE__));
        return "";
    }

    template <class EventType>
    bool TypedEventDispatcher<EventType>::unregisterCallback(const std::string& callbackID) {
        if (m_eventRegistrations.count(callbackID) != 0) {
            id::Lock lock(m_mutex);
            m_callbacks.erase(callbackID);

            std::string eventName = m_eventRegistrations[callbackID];
            std::vector<std::string>::iterator it = std::find(m_events[eventName].begin(), m_events[eventName].end(), "id");
            m_events[eventName].erase(it);

            m_eventRegistrations.erase(callbackID);

            id::Console::success("Successfully unregistered Event \"" + callbackID + "\"!", "TypedEventDispatcher.cpp:" + std::to_string(__LINE__));
            return true;
        }

        id::Console::error("Error unregistering Event \"" + callbackID + "\"!", "TypedEventDispatcher.cpp:" + std::to_string(__LINE__));
        return false;
    }

    template <class EventType>
    void TypedEventDispatcher<EventType>::clearCallbacks() {
        id::Lock lock(m_mutex);
        m_eventRegistrations.clear();
        m_events.clear();
        m_callbacks.clear();
    }

    template <class EventType>
    bool TypedEventDispatcher<EventType>::dispatch(EventType& event) {
        id::Lock lock(m_mutex);

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
    template <class EventType>
    const std::string TypedEventDispatcher<EventType>::_getUUID() const {
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

#endif
