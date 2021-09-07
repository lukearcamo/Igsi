#include <glad/gl.h>
// #define GLFW_DLL
#define GLFW_INCLUDE_NONE // Just to be sure
#include <GLFW/glfw3.h>

#include "dependencies/igsi/core/vec2.h"
#include "dependencies/igsi/core/vec3.h"
#include "dependencies/igsi/core/mat4.h"
#include "dependencies/igsi/core/transform.h"
#include "dependencies/igsi/core/helpers.h"
#include "dependencies/igsi/core/geometry.h"

#include "dependencies/igsi/extra/controls.h"
#include "dependencies/igsi/extra/imageLoader.h"
#include "dependencies/igsi/extra/skybox.h"

#include <iostream>
#include <thread>
#include <vector>

#define PI 3.14159265358979323846 // I didnt want to include the whole cmath header just for one value
#define TO_RADIANS PI / 180.0

using namespace Igsi;

namespace demo {
    GLFWwindow* window;
    float width = 960.0, height = 540.0;
    bool hasResized = false;
    void onResize(GLFWwindow* window, int w, int h) { width = w; height = h; hasResized = true; }
    void onError(int error, const char* description) { std::cerr << "Error" << error << ": " << description << "\n"; }
    int init() {
        glfwSetErrorCallback(onError);
        if (!glfwInit()) {
            std::cerr << "GLFW initialization failed\n";
            return -1;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(width, height, "Fenetre", NULL, NULL);
        if (!window) {
            std::cerr << "Window creation failed\n";
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window); // GLAD requires active context
        // if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        if (!gladLoadGL(glfwGetProcAddress)) {
            std::cerr << "GLAD initialization failed\n";
            return -1;
        }
        glfwMakeContextCurrent(NULL); // Will set context on the other thread
        return 0;
    }
    void render() {
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, onResize);

        // ======= Setup =======

        Transform scene;
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glEnable(GL_PROGRAM_POINT_SIZE);
        scene.dynamic = false;

        Transform camera;
        camera.position.z = 5;
        // camera.updateMatrices();
        scene.add(&camera);
        mat4 projectionMatrix = mat4().perspective(45 * TO_RADIANS, width / height, 0.1, 1000);

        glfwSetKeyCallback(window, Controls::keyEvent);
        glfwSetMouseButtonCallback(window, Controls::mouseEvent);
        glfwSetWindowFocusCallback(window, Controls::focusEvent);

        // ======= Load Water Normal Map =======
        
        GLuint normalMap = createTexture(GL_TEXTURE_2D, 1);
        setTexParams(GL_TEXTURE_2D, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);
        loadImage("./textures/waterNormalMap.png", GL_TEXTURE_2D);

        // ======= Skybox =======

        Skybox skybox(0, "./textures/sky/sunset/");

        // ======= Sphere =======

        GLuint sphereProgram = createShaderProgram(readFile("./shaders/sphere/vs.glsl"), readFile("./shaders/sphere/fs.glsl"));
        setUniform("color", vec3(1, 0, 0));
        setUniformInt("envMap", 0);

        Geometry sphereGeo;
        sphereGeometry(&sphereGeo);
        sphereGeo.toNonIndexed();
        sphereGeo.computeNormals();

        int sphereDrawCount = sphereGeo.getDrawCount();
        GLuint sphereVAO = createVAO();
            createVBO(0, &sphereGeo, "position");
            createVBO(1, &sphereGeo, "normal");
            createVBO(2, &sphereGeo, "uv");
        
        Transform sphere;
        scene.add(&sphere);

        // ======= Plane =======

        GLuint planeProgram = createShaderProgram(readFile("./shaders/plane/vs.glsl"), readFile("./shaders/plane/fs.glsl"));
        // setUniform("color", vec3(0.0, 30.0, 15.0) / 255);
        setUniformInt("envMap", 0);
        setUniformInt("normalMap", 1);
        // Set sun direction for sphere?
        vec3 sunDirection = normalize(vec3(0.0, 1.0, -10.0));
        setUniform("sunDirection", sunDirection);

        Geometry planeGeo;
        planeGeometry(&planeGeo, vec2(1000, 1000));
        planeGeo.transform(mat4().rotationX(PI / -2.0));
        int planeDrawCount = planeGeo.getDrawCount();
        GLuint planeVAO = createVAO();
            createVBO(0, &planeGeo, "position");
            createVBO(1, &planeGeo, "normal");
            createVBO(2, &planeGeo, "uv");
            // createEBO(planeGeo.indices);
        
        Transform plane;
        scene.add(&plane);

        // ======= Render =======

        glfwSwapInterval(1);
        float prevFrameTime = glfwGetTime();
        while(!glfwWindowShouldClose(window)) {
            float now = glfwGetTime();
            float deltaTime = now - prevFrameTime;
            prevFrameTime = now;

            if (hasResized) { // Opengl commands dont work in glfw callbacks? Also kinda hard to access cam object from callbacks
                glViewport(0, 0, width, height);
                projectionMatrix.perspective(45 * TO_RADIANS, width / height, 0.1, 1000);
                hasResized = false;
            }

            Controls::update(window, &camera, deltaTime, 3, 6, 0.001);
            scene.updateChildrenMatrices();
            // camera.updateMatrices();

            glClearColor(0.25, 0.25, 0.25, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(sphereProgram);
            glBindVertexArray(sphereVAO);
            sphere.setDefaultUniforms(&camera, projectionMatrix);
            // glDrawElements(GL_TRIANGLES, sphereDrawCount, GL_UNSIGNED_INT, NULL);
            glDrawArrays(GL_TRIANGLES, 0, sphereDrawCount);

            glUseProgram(planeProgram);
            plane.setDefaultUniforms(&camera, projectionMatrix);
            setUniform("time", now);
            glBindVertexArray(planeVAO);
            // If using EBO
            // glDrawElements(GL_TRIANGLES, planeDrawCount, GL_UNSIGNED_INT, NULL);
            // If not using EBO
            glDrawElements(GL_TRIANGLES, planeDrawCount, GL_UNSIGNED_INT, planeGeo.indices.data());

            skybox.draw(&camera, projectionMatrix);

            glfwSwapBuffers(window);
        }
    }
}
int main() {
    if (demo::init()) return -1;
    std::thread thr(demo::render);
    while(!glfwWindowShouldClose(demo::window)) {
        glfwWaitEvents();
    }
    thr.join();
    glfwTerminate();
    return 0;
}