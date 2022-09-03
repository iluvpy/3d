#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Keyboard.hpp"
#include "Mouse.hpp"


#define CAMERA_SPEED 1.0f
#define SENSITIVITY .1

class Camera {
public:
    void init();
    void update(Keyboard *kb, Mouse *mouse, double deltaTime);
    glm::mat4 getView();

private:
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraFront;
    glm::vec3 m_cameraUp;   
    Mouse *m_mouse;
    float m_yaw;
    float m_pitch;
};