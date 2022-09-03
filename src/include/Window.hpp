#pragma once 

#include "glewInclude.hpp"
#include "glfwInclude.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Camera.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

#define STARTUP_WINDOW_WIDTH 800
#define STARTUP_WINDOW_HEIGHT 600

class Window {
public:
    void init();
    void loop();
    int getWindowWidth();
    int getWindowHeight();
    GLFWwindow *getGLFWwindow();
    Keyboard *getKeyboard();
    Mouse *getMouse();
    ~Window();
private:
    GLFWwindow *m_window;
    Keyboard m_keyboard;
    Camera m_camera;
    Mouse m_mouse;
    double m_deltaTime;
};