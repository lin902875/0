#pragma once

#include <opencv2/opencv.hpp>

namespace Overlay {
    class Window {
    public:
        Window(int width, int height);
        ~Window();
        
        bool IsOpen() const;
        void Update();
        void Show(const cv::Mat& frame);
        void Close();
        
    private:
        int width, height;
        bool open;
        std::string windowName;
    };
}
