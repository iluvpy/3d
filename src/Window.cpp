#include "Window.hpp"
#include "Vertex.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "Shader.hpp"
#include "RenderSettings.hpp"
#include "Texture.hpp"
#include "Util.hpp"

#define PRINT_OPENGL_ERROR std::cout << "error: " << glGetError() << std::endl

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  


void Window::init() {
    m_deltaTime = 0.0;
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
        // positions          // colors           // texture coords
        Vertex{ 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f},   // top right
        Vertex{ 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f},   // bottom right
        Vertex{-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f},   // bottom left
        Vertex{-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f}    // top left 
    };

    std::vector<unsigned int> indices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Shader shader;
    shader.init(RenderSettings::VERTEX_SHADER_PATH, RenderSettings::FRAGMENT_SHADER_PATH);



    VAO vao;
    vao.init();
    vao.bind();

    VBO vbo;
    vbo.init(vertices);

    EBO ebo;
    ebo.init(indices);

    vbo.bind();
    ebo.bind();
    vbo.attrib();

    vbo.unbind();
    vao.unbind();

    Texture containerTexture;
    containerTexture.createFrom("./textures/container.jpg");

    Texture faceTexture;
    faceTexture.setShouldFlip(true);
    faceTexture.setDisplayFormat(GL_RGBA);
    faceTexture.createFrom("./textures/awesomeface.png");

    shader.bind();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);



    double currentFrameTime = 0.0;
    double lastFrameTime = 0.0;

    float angle = 90.0f;

    while (!glfwWindowShouldClose(m_window)) {
        // set delta time
        currentFrameTime = Util::getTimeMS();
        m_deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;

        Util::sleep(5);
  
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // transfomations
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, 0.0f, 0.0f));
        trans = glm::rotate(trans, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        angle += 10.0f*m_deltaTime;
        if (angle >= 360.0f) angle = 0.0f;
        shader.setMatf4("transform", trans);


        glActiveTexture(GL_TEXTURE0);
        containerTexture.bind();
        glActiveTexture(GL_TEXTURE1);
        faceTexture.bind();

        shader.bind();
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



        // transfomations
        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.0f, 0.0f));
        trans = glm::rotate(trans, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        angle += 10.0f*m_deltaTime;
        if (angle >= 360.0f) angle = 0.0f;
        shader.setMatf4("transform", trans);


        glActiveTexture(GL_TEXTURE0);
        containerTexture.bind();
        glActiveTexture(GL_TEXTURE1);
        faceTexture.bind();

        shader.bind();
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(m_window);
        glfwPollEvents();

    }
}



