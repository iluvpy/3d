#pragma once

#include "glewInclude.hpp"
#include "glfwInclude.hpp"

class Window;

class Mouse {
public:
    void init(Window *window);
    void update();
    void setX(double x);
    void setY(double y);
    double getLastX();
    double getLastY();
    double getX();
    double getY();
private:
    double m_x;
    double m_y;
    double m_lastX;
    double m_lastY;
};