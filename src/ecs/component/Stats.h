//
// Created by Iris Chow on 2026-04-04.
//

#ifndef INC_8051PROJECT_STATS_H
#define INC_8051PROJECT_STATS_H

#include "../core/Component.h"

struct Health : Component {
    int current{0};
    int max{0};
};

#endif //INC_8051PROJECT_STATS_H