#pragma once

#include "glewInclude.hpp"
#include "glfwInclude.hpp"
#include <unordered_map>

class Keyboard {
public:
    void init(GLFWwindow *window);
    void press(int keyCode);
    void release(int keyCode);
    bool isDown(int keyCode);
    bool wasPressed(int keyCode);
    bool wasReleased(int keyCode);
    void update();
private:
    std::unordered_map<int, bool> m_keys;
    int lastKeyPressed;
    int justPressed;
    int justReleased;
    int lastKeyReleased;
};