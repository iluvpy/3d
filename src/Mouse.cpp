#include "Mouse.hpp"
#include "Window.hpp"

void mouse_move_callback(GLFWwindow *glfwWindow, double xpos, double ypos) {
    Window *window = (Window*)glfwGetWindowUserPointer(glfwWindow);
    Mouse *mouse = window->getMouse();
    mouse->setX(xpos);
    mouse->setY(ypos);
}

void Mouse::init(Window *window) {
    m_lastX = window->getWindowWidth()/2.0f;
    m_lastY = window->getWindowHeight()/2.0f;
    m_x = 0;
    m_y = 0;
    glfwSetCursorPosCallback(window->getGLFWwindow(), mouse_move_callback);
}

void Mouse::update() {
    m_lastX = m_x;
    m_lastY = m_y;
}


void Mouse::setX(double x) {
    m_lastX = m_x;
    m_x = x;
}

void Mouse::setY(double y) {
    m_lastY = y;
    m_y = y;
}

double Mouse::getLastX() {
    return m_lastX;
}

double Mouse::getLastY() {
    return m_lastY;
}

double Mouse::getX() {
    return m_x;
}

double Mouse::getY() {
    return m_y;
}
