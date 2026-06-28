#include "esp.h"
#include <iostream>

namespace ESP {
    ESPRenderer::ESPRenderer() : initialized(false) {}
    
    ESPRenderer::~ESPRenderer() {
        if (initialized) {
            Shutdown();
        }
    }
    
    void ESPRenderer::Initialize() {
        canvas = cv::Mat(SCREEN_HEIGHT, SCREEN_WIDTH, CV_8UC3, cv::Scalar(0, 0, 0));
        initialized = true;
        std::cout << "ESP Renderer initialized" << std::endl;
    }
    
    void ESPRenderer::Update(const std::vector<Player>& players) {
        if (!initialized) return;
        
        canvas.setTo(cv::Scalar(0, 0, 0));
        
        for (const auto& player : players) {
            if (player.isAlive) {
                DrawPlayerESP(player);
            }
        }
    }
    
    void ESPRenderer::Render() {
        if (!initialized) return;
        
        cv::imshow("Valorant ESP", canvas);
    }
    
    void ESPRenderer::Shutdown() {
        if (initialized) {
            canvas.release();
            cv::destroyAllWindows();
            initialized = false;
        }
    }
    
    void ESPRenderer::DrawPlayerESP(const Player& player) {
        if (!ENABLE_PLAYER_ESP) return;
        
        // Simple visualization
        int x = static_cast<int>(player.x);
        int y = static_cast<int>(player.y);
        
        Color color = player.isEnemy ? COLOR_ENEMY : COLOR_ALLY;
        
        if (ENABLE_BOX_ESP) {
            DrawBox(player);
        }
        
        if (ENABLE_HEALTH_BAR) {
            DrawHealthBar(player);
        }
    }
    
    void ESPRenderer::DrawBox(const Player& player) {
        int x = static_cast<int>(player.x);
        int y = static_cast<int>(player.y);
        int boxSize = 30;
        
        Color color = player.isEnemy ? COLOR_ENEMY : COLOR_ALLY;
        cv::rectangle(canvas, 
                     cv::Point(x - boxSize/2, y - boxSize/2),
                     cv::Point(x + boxSize/2, y + boxSize/2),
                     cv::Scalar(color.b, color.g, color.r),
                     2);
    }
    
    void ESPRenderer::DrawLine(const Player& player) {
        // Draw line from center to player
        int x = static_cast<int>(player.x);
        int y = static_cast<int>(player.y);
        
        Color color = player.isEnemy ? COLOR_ENEMY : COLOR_ALLY;
        cv::line(canvas,
                cv::Point(SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
                cv::Point(x, y),
                cv::Scalar(color.b, color.g, color.r),
                1);
    }
    
    void ESPRenderer::DrawHealthBar(const Player& player) {
        int x = static_cast<int>(player.x);
        int y = static_cast<int>(player.y) - 40;
        int barWidth = 30;
        int barHeight = 5;
        
        // Background
        cv::rectangle(canvas,
                     cv::Point(x - barWidth/2, y),
                     cv::Point(x + barWidth/2, y + barHeight),
                     cv::Scalar(0, 0, 0),
                     -1);
        
        // Health
        float healthPercent = player.health / player.maxHealth;
        int healthWidth = static_cast<int>(barWidth * healthPercent);
        
        Color healthColor = healthPercent > 0.5f ? COLOR_HEALTH_FULL : COLOR_HEALTH_LOW;
        cv::rectangle(canvas,
                     cv::Point(x - barWidth/2, y),
                     cv::Point(x - barWidth/2 + healthWidth, y + barHeight),
                     cv::Scalar(healthColor.b, healthColor.g, healthColor.r),
                     -1);
    }
}
