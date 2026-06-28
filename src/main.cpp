#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "esp.h"
#include "overlay.h"
#include "config.h"

int main() {
    std::cout << "Valorant ESP - Starting..." << std::endl;
    
    try {
        // Initialize ESP Renderer
        ESP::ESPRenderer renderer;
        renderer.Initialize();
        
        // Initialize Overlay Window
        Overlay::Window window(ESP::SCREEN_WIDTH, ESP::SCREEN_HEIGHT);
        
        // Sample player data
        std::vector<ESP::Player> players;
        
        // Dummy players for testing
        ESP::Player player1 = {
            .id = 1,
            .x = 100.0f,
            .y = 200.0f,
            .z = 50.0f,
            .health = 100.0f,
            .maxHealth = 100.0f,
            .isEnemy = true,
            .isAlive = true
        };
        players.push_back(player1);
        
        std::cout << "ESP initialized successfully" << std::endl;
        std::cout << "Screen resolution: " << ESP::SCREEN_WIDTH << "x" << ESP::SCREEN_HEIGHT << std::endl;
        
        // Main loop
        while (window.IsOpen()) {
            renderer.Update(players);
            renderer.Render();
            window.Update();
            
            // Check for exit key (ESC)
            if (cv::waitKey(30) == 27) {
                break;
            }
        }
        
        renderer.Shutdown();
        window.Close();
        
        std::cout << "Valorant ESP - Shutdown complete" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
