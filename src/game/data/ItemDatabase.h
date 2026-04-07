//
// Created by Iris Chow on 2026-04-05.
//

#ifndef INC_8051PROJECT_ITEMDATABASE_H
#define INC_8051PROJECT_ITEMDATABASE_H

#include <map>
#include "ItemData.h"

class ItemDatabase {
public:
    static const ItemData& get(ItemId id);

private:
    static const std::unordered_map<ItemId, ItemData> items;
};

#endif //INC_8051PROJECT_ITEMDATABASE_H