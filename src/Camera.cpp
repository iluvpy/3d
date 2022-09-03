#include "Camera.hpp"

void Camera::init() {
    m_cameraPos = glm::vec3(0.0f, 0.0f,  3.0f);
    m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    m_cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);
    m_yaw = -90.0f;
    m_pitch = 0.0f;
}

void Camera::update(Keyboard *kb, Mouse *mouse, double deltaTime) {
    float speed = CAMERA_SPEED * deltaTime;
    if (kb->isDown(GLFW_KEY_W))
        m_cameraPos += speed * m_cameraFront;
    if (kb->isDown(GLFW_KEY_S) == GLFW_PRESS)
        m_cameraPos -= speed * m_cameraFront;
    if (kb->isDown(GLFW_KEY_A) == GLFW_PRESS)
        m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * speed;
    if (kb->isDown(GLFW_KEY_D) == GLFW_PRESS)
        m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * speed;
    

    m_yaw  += (mouse->getX() - mouse->getLastX()) * SENSITIVITY;
    m_pitch += (mouse->getLastY() - mouse->getLastY()) * SENSITIVITY;

    if(m_pitch > 89.0f)
        m_pitch = 89.0f;
    if(m_pitch < -89.0f)
        m_pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cameraFront = glm::normalize(direction);

}

glm::mat4 Camera::getView() {
    return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}
