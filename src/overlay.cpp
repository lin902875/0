#include "overlay.h"
#include <iostream>

namespace Overlay {
    Window::Window(int w, int h) : width(w), height(h), open(true) {
        windowName = "Valorant ESP Overlay";
        cv::namedWindow(windowName, cv::WINDOW_NORMAL);
        cv::resizeWindow(windowName, width, height);
    }
    
    Window::~Window() {
        Close();
    }
    
    bool Window::IsOpen() const {
        return open;
    }
    
    void Window::Update() {
        // Check if window was closed
        if (cv::getWindowProperty(windowName, cv::WND_PROP_VISIBLE) < 1) {
            open = false;
        }
    }
    
    void Window::Show(const cv::Mat& frame) {
        if (open) {
            cv::imshow(windowName, frame);
        }
    }
    
    void Window::Close() {
        if (open) {
            cv::destroyWindow(windowName);
            open = false;
        }
    }
}
