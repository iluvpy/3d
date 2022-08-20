#include "Camera.hpp"

void Camera::init() {
    m_cameraPos = glm::vec3(0.0f, 0.0f,  3.0f);
    m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    m_cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);
}

void Camera::update(Keyboard *kb, double deltaTime) {
    float speed = CAMERA_SPEED * deltaTime;
    if (kb->isDown(GLFW_KEY_W))
        m_cameraPos += speed * m_cameraFront;
    if (kb->isDown(GLFW_KEY_S) == GLFW_PRESS)
        m_cameraPos -= speed * m_cameraFront;
    if (kb->isDown(GLFW_KEY_A) == GLFW_PRESS)
        m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * speed;
    if (kb->isDown(GLFW_KEY_D) == GLFW_PRESS)
        m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * speed;
}

glm::mat4 Camera::getView() {
    return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}
