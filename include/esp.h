#pragma once

#include <vector>
#include <opencv2/opencv.hpp>
#include "config.h"

namespace ESP {
    struct Player {
        int id;
        float x, y, z;
        float health;
        float maxHealth;
        bool isEnemy;
        bool isAlive;
    };
    
    class ESPRenderer {
    public:
        ESPRenderer();
        ~ESPRenderer();
        
        void Initialize();
        void Update(const std::vector<Player>& players);
        void Render();
        void Shutdown();
        
    private:
        cv::Mat canvas;
        bool initialized;
        
        void DrawPlayerESP(const Player& player);
        void DrawBox(const Player& player);
        void DrawLine(const Player& player);
        void DrawHealthBar(const Player& player);
    };
}
