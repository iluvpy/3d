#pragma once 

#include "glewInclude.hpp"
#include "glfwInclude.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

#define STARTUP_WINDOW_WIDTH 800
#define STARTUP_WINDOW_HEIGHT 600

class Window {
public:
    void init();
    void loop();
    ~Window();
private:
    GLFWwindow *m_window;
};