//
// Created by Iris Chow on 2026-04-05.
//

#ifndef INC_8051PROJECT_ITEMDATABASE_H
#define INC_8051PROJECT_ITEMDATABASE_H

#include <unordered_map>
#include "ItemData.h"

struct ItemIdHash {
    std::size_t operator()(ItemId id) const noexcept {
        return static_cast<std::size_t>(id);
    }
};

class ItemDatabase {
public:
    static void initialize();
    static const ItemData& get(ItemId id);

private:
    static std::unordered_map<ItemId, ItemData, ItemIdHash> items;
    static bool initialized;
};

#endif //INC_8051PROJECT_ITEMDATABASE_H