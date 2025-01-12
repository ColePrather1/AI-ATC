#ifndef EVENT_ACTIONS_H
#define EVENT_ACTIONS_H

#pragma once

#include <array>
#include <functional>
#include <variant>
#include "EventTypes.h"
#include "Logging.h"
#include "Session.h"

class EventActions {
private:
    using EventHandlerBase = std::function<void()>;
    using EventHandlerWithData = std::function<void(uint64_t)>;
    using EventHandlerWithTimestamp = std::function<void(uint32_t)>;
    using EventHandlerWithDataAndTimestamp = std::function<void(uint32_t, uint64_t)>;

    using EventHandlerVariant = std::variant<
        EventHandlerBase,
        EventHandlerWithData,
        EventHandlerWithTimestamp,
        EventHandlerWithDataAndTimestamp
    >;

    std::array<EventHandlerVariant, static_cast<size_t>(EventType::FLIGHT_PHASE_CHANGE_COMPLETE_FLIGHT) + 1> handlers;

    void logEvent(const std::string& eventName) {
        std::cout << "Event occurred: " << eventName << std::endl;
    }

public:
    EventActions() {
        initializeHandlers();
    }

    template<typename... Args>
    void handleEvent(EventType event, Args&&... args) {
        if (event < handlers.size()) {
            std::visit([&](auto&& handler) {
                using HandlerType = std::decay_t<decltype(handler)>;
                if constexpr (std::is_invocable_v<HandlerType, Args...>) {
                    handler(std::forward<Args>(args)...);
                }
            }, handlers[static_cast<size_t>(event)]);
        }
    }

private:
    void initializeHandlers() {
        // System Events
        handlers[static_cast<size_t>(EventType::SYSTEM_STARTUP)] = [this]() { 
            Logging::insertEventLog(EventType::SYSTEM_STARTUP, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
        };
        handlers[static_cast<size_t>(EventType::SYSTEM_SHUTDOWN)] = [this]() {
            Logging::insertEventLog(EventType::SYSTEM_SHUTDOWN, static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
        };

    // Events with timestamp
        handlers[static_cast<size_t>(EventType::FLIGHT_TIME_START_SET_TRUE)] = [this](uint32_t timestamp) { 
            Session::insertEventLog(EventType::FLIGHT_TIME_START_SET_TRUE, timestamp, 0);
        };

    // Events with data
        handlers[static_cast<size_t>(EventType::FIXED_ALTITUDE_DATA_CHANGE)] = [this](uint64_t data) {
            logEvent("FIXED_ALTITUDE_DATA_CHANGE: " + std::to_string(data));
        };

    // Events with timestamp and data
        handlers[static_cast<size_t>(EventType::ALTITUDE_WARNING)] = [this](uint32_t timestamp, uint64_t data) {
            logEvent("ALTITUDE_WARNING at " + std::to_string(timestamp) + " with value " + std::to_string(data));
        };

    // Simple events without parameters
        handlers[static_cast<size_t>(EventType::GPS_FAIL)] = [this]() { logEvent("GPS_FAIL"); };
        handlers[static_cast<size_t>(EventType::ENGINE_ON_TRUE)] = [this]() { logEvent("ENGINE_ON_TRUE"); };
        handlers[static_cast<size_t>(EventType::ENGINE_ON_FALSE)] = [this]() { logEvent("ENGINE_ON_FALSE"); };

        // Initialize other handlers similarly...
    }
};

#endif // EVENT_ACTIONS_H
