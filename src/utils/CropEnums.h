//
// Created by Iris Chow on 2026-04-05.
//

#ifndef INC_8051PROJECT_CROPENUMS_H
#define INC_8051PROJECT_CROPENUMS_H

enum class CropType {
    NONE,
    CORN,
    SUNFLOWER,
    CARROT,
    YAM,
    CAULIFLOWER,
    POTATO,
    BEET,
    WATERMELON,
    EGGPLANT,
    SWEET_POTATO,
    BLUEBERRY,
    BANANA,
    PINEAPPLE,
    PUMPKIN,
    CANTALOUPE,
    DAIKON,
    GARLIC,
    APPLE,
    RADISH,
    CUCUMBER,
    BROCCOLI,
};

enum class CropStage {
    SPROUT = 1,
    SEEDLING = 2,
    VEGETATING = 3,
    BUDDING = 4,
    FLOWERING = 5,
    RIPENING = 6
};

#endif //INC_8051PROJECT_CROPENUMS_H