#include "Window.hpp"
#include "Vertex.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Shader.hpp"
#include "RenderSettings.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  


void Window::init() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    m_window = glfwCreateWindow(STARTUP_WINDOW_WIDTH, STARTUP_WINDOW_HEIGHT, "3D", NULL, NULL);
    if (m_window == NULL)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create Window!\n");
    }
    glfwMakeContextCurrent(m_window);

    if (glewInit() != 0) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize graphics api\n"); 
    }

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback); 
}


Window::~Window() {
    glfwTerminate();
}


void Window::loop() {

    std::vector<Vertex> vertices = {
        Vertex{ 0.5f,  0.5f, 0.0f},  // top right
        Vertex{ 0.5f, -0.5f, 0.0f},  // bottom right
        Vertex{-0.5f, -0.5f, 0.0f},  // bottom left
        Vertex{-0.5f,  0.5f, 0.0f}   // top left 
    };
    std::vector<unsigned int> indices = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  

    Shader shader;
    shader.init(RenderSettings::VERTEX_SHADER_PATH, RenderSettings::FRAGMENT_SHADER_PATH);

    VAO vao;
    vao.init();

    VBO vbo;
    vbo.init();

    EBO ebo;
    ebo.init();



    vao.bind();

    vbo.bind(vertices);
    ebo.bind(indices);
    vbo.attrib();

    vbo.unbind();
    vao.unbind();



    while (!glfwWindowShouldClose(m_window)) {


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(m_window);
        glfwPollEvents();

    }
}



