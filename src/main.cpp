#include <iostream>

#include "glewInclude.hpp"
#include "glfwInclude.hpp"
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