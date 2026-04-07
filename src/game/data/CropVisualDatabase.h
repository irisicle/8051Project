//
// Created by Iris Chow on 2026-04-05.
//

#ifndef INC_8051PROJECT_CROPDATABASE_H
#define INC_8051PROJECT_CROPDATABASE_H

#include "CropVisualData.h"

class CropVisualDatabase {
public:
    static void initialize();
    static const CropVisualData& get(CropType type);
};

#endif //INC_8051PROJECT_CROPDATABASE_H