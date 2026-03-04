//
// Created by Iris Chow on 2026-02-04.
//

#ifndef INC_8051TUTORIAL_EVENTMANAGER_H
#define INC_8051TUTORIAL_EVENTMANAGER_H
#include <functional>

#include "BaseEvent.h"

// Observer Pattern
class EventManager {
public:
    using Handler = std::function<void(const BaseEvent&)>;

    void emit(const BaseEvent& event) const {
        for (const auto& listener : listeners) {
            listener(event);
        }
    }

    void subscribe(const Handler& callback) {
        listeners.emplace_back(callback);
    }

private:
    std::vector<Handler> listeners;
};

// public:
    // template<typename EventType>
    // void emit(const EventType& event) {
    //     // Retrieve the list of subscribers to certain events
    //     // Loop all the subscribers to certain events
    //     for (auto& listeners = getListeners<EventType>();
    //         auto& listener : listeners) {
    //         listener(event); // Invoke function here
    //     }
    // }

    // template<typename EventType>
    // void subscribe(std::function<void(const EventType&)> callback) {
    //     // Pass in the callback/callable wrapper/subscription to the list of subscriptions
    //     getListeners<EventType>().push_back(callback);
    // }

// private:
    // // Each event type essentially has its own std::vector of listeners without you having to manage it explicitly. This is done using the static local
    // // std:function<void(const EventTypes&)> is the callable wrapper: it can hold anything that can be called like a function (lambda, free function, functor, etc.)
    // template<typename EventType>
    // std::vector<std::function<void(const EventType&)>>& getListeners() {
    //     static std::vector<std::function<void(const EventType&)>> listeners;
    //     return listeners;
    // }
// };

#endif //INC_8051TUTORIAL_EVENTMANAGER_H