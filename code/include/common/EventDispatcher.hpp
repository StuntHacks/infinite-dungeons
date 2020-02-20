/**
 * @file common/EventDispatcher.hpp
 * @brief Defines the EventDispatcher-class
 */
#pragma once

#include <functional>
#include <map>

#include "Event.hpp"
#include "Lock.hpp"

namespace id {
    /**
     * @brief Handles and dispatches @ref id::Event "Events" to registered callbacks
     */
    class EventDispatcher {
    public:
        /**
         * @brief Destructor
         */
        virtual ~EventDispatcher() { /* do nothing */ }

        /**
         * @brief Registers a callback to get called when the given eventName gets dispatched
         * @param eventName  The eventName to register for
         * @param callback   The callback to call - the single parameter is the dispatched Event
         * @param callbackID The id for this callback, needed to unregister this callback again. When an empty string is given, a random unique ID will be generated
         * @param overwrite  Whether to overwrite any previously with this id stored callback or not
         * @return           The callback-id of the newly registered callback
         */
        const std::string registerCallback(const std::string& eventName, std::function<void(id::Event&)> callback, const std::string callbackID = "", bool overwrite = false);

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
        virtual bool dispatch(id::Event& event);

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
        std::map<std::string, std::function<void(id::Event&)>> m_callbacks;
              // eventName  | callbackIDs
        std::map<std::string, std::vector<std::string>> m_events;
              // callbackID | eventName
        std::map<std::string, std::string> m_eventRegistrations;
    };
} /* id */
