#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Keyboard.hpp"


#define CAMERA_SPEED 1.0f

class Camera {
public:
    void init();
    void update(Keyboard *kb, double deltaTime);
    glm::mat4 getView();

private:
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraFront;
    glm::vec3 m_cameraUp;   
};