#include "Keyboard.hpp"
#include "Window.hpp"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window *windowPtr = (Window*)glfwGetWindowUserPointer(window);

    if (action == GLFW_PRESS) {
        windowPtr->getKeyboard()->press(key);
    }
    else if (action == GLFW_RELEASE) {
        windowPtr->getKeyboard()->release(key);
    }
}

void Keyboard::init(GLFWwindow *window) {
    glfwSetKeyCallback(window, keyCallback);
}

void Keyboard::press(int keyCode) {
    auto it = m_keys.find(keyCode);
    if (it != m_keys.end()) {
        it->second = true;
    }
    else {
        m_keys.insert(std::make_pair(keyCode, true));
    }
    justPressed = keyCode;
}

void Keyboard::release(int keyCode) {
    // theres no need to check if the key exists
    // as when press is called a key is inserted into m_keys
    auto it = m_keys.find(keyCode);
    it->second = false;
    justReleased = keyCode;
}

bool Keyboard::isDown(int keyCode) {
    auto it = m_keys.find(keyCode);
    return it != m_keys.end() ? it->second : false;
}

bool Keyboard::wasPressed(int keyCode) {
    return lastKeyPressed != justPressed;
}

bool Keyboard::wasReleased(int keyCode) {
    return lastKeyReleased != justReleased;
}  

void Keyboard::update() {
    lastKeyPressed = justPressed;
    lastKeyReleased = justReleased;
}

