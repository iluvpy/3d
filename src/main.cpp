#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "Window.hpp"

int main() {

    try {
        Window window;
        window.init();
        window.loop();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }
    
    return 0;
}