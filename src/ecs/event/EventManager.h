//
// Created by Iris Chow on 2026-02-04.
//

#ifndef INC_8051PROJECT_EVENTMANAGER_H
#define INC_8051PROJECT_EVENTMANAGER_H
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

#endif //INC_8051PROJECT_EVENTMANAGER_H