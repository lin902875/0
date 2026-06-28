#pragma once

#include <string>

namespace ESP {
    // Screen resolution
    constexpr int SCREEN_WIDTH = 2560;
    constexpr int SCREEN_HEIGHT = 1600;
    
    // ESP Settings
    constexpr bool ENABLE_PLAYER_ESP = true;
    constexpr bool ENABLE_ENEMY_ESP = true;
    constexpr bool ENABLE_BOX_ESP = true;
    constexpr bool ENABLE_LINE_ESP = true;
    constexpr bool ENABLE_HEALTH_BAR = true;
    
    // Colors (BGR format for OpenCV)
    struct Color {
        int b, g, r;
    };
    
    constexpr Color COLOR_ENEMY = {0, 0, 255};      // Red
    constexpr Color COLOR_ALLY = {0, 255, 0};       // Green
    constexpr Color COLOR_HEALTH_FULL = {0, 255, 0}; // Green
    constexpr Color COLOR_HEALTH_LOW = {0, 0, 255};  // Red
}
