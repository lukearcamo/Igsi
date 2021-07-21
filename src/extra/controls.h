#ifndef CONTROLS_H
#define CONTROLS_H

#include <iostream>

#define GLFW_DLL
#define GLFW_INCLUDE_NONE // Just to be sure
#include "..\..\include\glfw3.h"

#include "..\core\mathematics.h"
#include "..\core\transform.h"

using namespace Igsi;

namespace Controls {
    const float rad90 = 90 * toRadians; // approx 1.5707963267948966
    vec2 lastMousePos;
    vec2 deltaMousePos;

    vec2 mousePos(GLFWwindow* window) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return vec2(xpos, ypos);
    }
    
    // Pointer lock stuff
    // Either set these directly as the GLFW callbacks or put them inside your own callbacks
    void mouseEvent(GLFWwindow* window, int button, int action, int mods) {
        if (action == GLFW_PRESS && (button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT || button == GLFW_MOUSE_BUTTON_MIDDLE)) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            lastMousePos = mousePos(window); // To prevent mouse jumping
        }
    }
    void keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
    void focusEvent(GLFWwindow* window, int focused) {
        if (!focused) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    void update(GLFWwindow* window, Transform* camera, float deltaTime, float movementSpeed, float sprintSpeed, float mouseSensitivity) {
        if (glfwRawMouseMotionSupported()) glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        
        // Maybe disable movement if window unfocused??
        movementSpeed *= deltaTime;
        sprintSpeed *= deltaTime;

        vec3 dir = -camera->getWorldDirection(); // Negative because camera faces negative z direction
        float hAngle = std::atan2(dir.z, dir.x);
        float s = std::sin(hAngle);
        float c = std::cos(hAngle);
        vec3 forward = vec3(c, 0, s) * (glfwGetKey(window, GLFW_KEY_C) ?  sprintSpeed : movementSpeed);
        vec3 right = vec3(-s, 0, c) * movementSpeed;

        if (glfwGetKey(window, GLFW_KEY_W)) camera->position += forward;
        if (glfwGetKey(window, GLFW_KEY_S)) camera->position -= forward;
        if (glfwGetKey(window, GLFW_KEY_D)) camera->position += right;
        if (glfwGetKey(window, GLFW_KEY_A)) camera->position -= right;
        if (glfwGetKey(window, GLFW_KEY_SPACE)) camera->position.y += movementSpeed;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) camera->position.y -= movementSpeed;

        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
            deltaMousePos = mousePos(window) - lastMousePos;
            lastMousePos += deltaMousePos;

            camera->rotation.y += deltaMousePos.x * -mouseSensitivity;
            float mvY = deltaMousePos.y * -mouseSensitivity;
            if (std::abs(mvY + camera->rotation.x) <= 1.5707963267948966) { // Clamps x rotation to +/- 90 degrees
                camera->rotation.x += mvY;
            }
            // camera->rotation.x += deltaMousePos.y * -mouseSensitivity;
            // if (camera->rotation.x < -rad90) camera->rotation.x = -rad90;
            // else if (camera->rotation.x > rad90) camera->rotation.x = rad90;
        }
    }
}

#endif
