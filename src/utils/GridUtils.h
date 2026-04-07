//
// Created by Iris Chow on 2026-04-05.
//

#ifndef INC_8051PROJECT_GRIDUTILS_H
#define INC_8051PROJECT_GRIDUTILS_H

#include <cmath>
#include "../ecs/component/Interaction.h"
#include "../utils/Vector2D.h"

namespace GridUtils {

    [[nodiscard]] inline Vector2D directionToVector(const Direction direction) {
        switch (direction) {
            case Direction::UP:
                return {0.0f, -1.0f};
            case Direction::DOWN:
                return {0.0f, 1.0f};
            case Direction::LEFT:
                return {-1.0f, 0.0f};
            case Direction::RIGHT:
                return {1.0f, 0.0f};
        }

        return {0.0f, 0.0f};
    }

    // Convert world position to tile coordinates
    [[nodiscard]] inline Vector2D worldToTile(const Vector2D& worldPos, const float tileSize) {
        return {
            std::floor(worldPos.x / tileSize),
            std::floor(worldPos.y / tileSize)
        };
    }

    // Get tile directly in front of an entity
    [[nodiscard]] inline Vector2D getFacingTile(
        const Vector2D& position,
        const Direction facing,
        const float scale,
        const float tileSize)
    {
        const float scaledSize = tileSize * scale;
        const Vector2D facingVector = directionToVector(facing);

        // Move from top-left to center of entity
        const Vector2D center{
            position.x + scaledSize * 0.5f,
            position.y + scaledSize * 0.5f
        };

        // Step forward one tile in facing direction
        const Vector2D target{
            center.x + facingVector.x * scaledSize,
            center.y + facingVector.y * scaledSize
        };

        return worldToTile(target, scaledSize);
    }

}

#endif // INC_8051PROJECT_GRIDUTILS_H