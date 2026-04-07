//
// Created by Iris Chow on 2026-03-31.
//

#ifndef INC_8051PROJECT_INVENTORY_H
#define INC_8051PROJECT_INVENTORY_H

#include <vector>
#include "../../utils/ItemEnums.h"
#include "../core/Component.h"

struct InventoryItem {
    ItemId id{ItemId::NONE};
    int count{0};
};

struct Inventory : Component {
    std::vector<InventoryItem> items{};
    int selectedIndex{0};

    Inventory() = default;

    explicit Inventory(std::vector<InventoryItem>& items, const int selectedItem = 0) : items(std::move(items)), selectedIndex(selectedItem) {}

    [[nodiscard]] bool isValidSelectedIndex() const {
        return selectedIndex >= 0 && selectedIndex < items.size();
    }

    InventoryItem& getSelectedItem() {
        return items[selectedIndex];
    }

    // const overload: handy when a system only needs to inspect the selected item
    [[nodiscard]] const InventoryItem& getSelectedItem() const {
        return items[selectedIndex];
    }
};

#endif //INC_8051PROJECT_INVENTORY_H