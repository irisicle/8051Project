//
// Created by Iris Chow on 2026-04-07.
//

#ifndef INC_8051PROJECT_AUDIOEVENTQUEUE_H
#define INC_8051PROJECT_AUDIOEVENTQUEUE_H

#include <queue>
#include <string>
#include "../../manager/AudioManager.h"

class AudioEvent {
public:
    explicit AudioEvent(const std::string& name) : name(std::move(name)) {}

    void execute() const {
        AudioManager::playSfx(name);
    }

private:
    std::string name;
};

class AudioEventQueue {
public:
    void push(std::unique_ptr<AudioEvent> event) {
        events.push(std::move(event));
    }

    void process() {
        while (!events.empty()) {
            events.front()->execute();
            events.pop();
        }
    }

private:
    std::queue<std::unique_ptr<AudioEvent>> events;
};

#endif //INC_8051PROJECT_AUDIOEVENTQUEUE_H