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
#define FOV 45.0f


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
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback); 
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

    m_keyboard.init(m_window);
    m_mouse.init(this);
    m_camera.init();
}


Window::~Window() {
    glfwTerminate();
}


void Window::loop() {

    std::vector<Vertex> vertices = {
        Vertex{-0.5f, -0.5f, -0.5f,  0.0f, 0.0f},
        Vertex{ 0.5f, -0.5f, -0.5f,  1.0f, 0.0f},
        Vertex{ 0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
        Vertex{ 0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
        Vertex{-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
        Vertex{-0.5f, -0.5f, -0.5f,  0.0f, 0.0f},

        Vertex{-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
        Vertex{ 0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
        Vertex{ 0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
        Vertex{ 0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
        Vertex{-0.5f,  0.5f,  0.5f,  0.0f, 1.0f},
        Vertex{-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},

        Vertex{-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
        Vertex{-0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
        Vertex{-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
        Vertex{-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
        Vertex{-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
        Vertex{-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

        Vertex{ 0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
        Vertex{ 0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
        Vertex{ 0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
        Vertex{ 0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
        Vertex{ 0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
        Vertex{ 0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

        Vertex{-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
        Vertex{ 0.5f, -0.5f, -0.5f,  1.0f, 1.0f},
        Vertex{ 0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
        Vertex{ 0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
        Vertex{-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
        Vertex{-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},

        Vertex{-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
        Vertex{ 0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
        Vertex{ 0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
        Vertex{ 0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
        Vertex{-0.5f,  0.5f,  0.5f,  0.0f, 0.0f},
        Vertex{-0.5f,  0.5f, -0.5f,  0.0f, 1.0f} 
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
    float angle = 0.0f;

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(m_window)) {
        // set delta time
        currentFrameTime = Util::getTimeMS();
        m_deltaTime = (currentFrameTime - lastFrameTime) / 1000.0f;
        lastFrameTime = currentFrameTime;
        m_camera.update(&m_keyboard, &m_mouse, m_deltaTime);

        Util::sleep(5);
  
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(0.0f, -0.1f, -2.0f));
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 1.0f)); 
        angle += m_deltaTime*20.0f;
        if (angle > 360) angle = 0;

        view = m_camera.getView();

        projection = glm::perspective(glm::radians(FOV), (float)(getWindowWidth() / getWindowHeight()), 0.1f, 100.0f);

        glActiveTexture(GL_TEXTURE0);
        containerTexture.bind();
        glActiveTexture(GL_TEXTURE1);
        faceTexture.bind();

        shader.bind();
        shader.setMatf4("model", model);
        shader.setMatf4("view", view);
        shader.setMatf4("projection", projection);

        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(m_window);
        glfwPollEvents();

        m_keyboard.update();
        m_mouse.update();
    }
}


int Window::getWindowWidth() {
    int w, h;
    glfwGetWindowSize(m_window, &w, &h);
    return w;
}

int Window::getWindowHeight() {
    int w, h;
    glfwGetWindowSize(m_window, &w, &h);
    return h;
}


Keyboard *Window::getKeyboard() {
    return &m_keyboard;
}


Mouse *Window::getMouse() {
    return &m_mouse;
}

GLFWwindow *Window::getGLFWwindow() {
    return m_window;
}


