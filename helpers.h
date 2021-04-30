#ifndef IGSI_HELPERS_H
#define IGSI_HELPERS_H

#include "include\glad.h"
#include "include\glfw3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "mathematics.h"

/*
TODO:
Later on add option for the other types of shaders, maybe using templates --- Geometry shader supported since 3.2, tesselation since 4.0 or lower versions with ARB_tessellation_shader
Use GL data types
Add support for other vbo/uniform data types
Shader preprocessing?
*/

namespace Igsi {
    GLuint compileShader(GLenum shaderType, const char* path) {
        std::ifstream file(path);
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string code = buffer.str();
        // Can do shader preprocessing here
        const char* source = code.c_str();
        file.close();

        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        GLint success, logSize;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
            GLchar infoLog[logSize];
            glGetShaderInfoLog(shader, logSize, NULL, infoLog);
            std::cerr << "Shader compilation failed: " << infoLog << std::endl;
            std::cerr << source << std::endl;
        }
        return shader;
    }
    GLuint createShaderProgram(GLuint* shaders, int numShaders) {
        GLuint shaderProgram = glCreateProgram();
        for (int i = 0; i < numShaders; i++) {
            glAttachShader(shaderProgram, shaders[i]);
        }
        glLinkProgram(shaderProgram);
        for (int i = 0; i < numShaders; i++) {
            glDeleteShader(shaders[i]);
        }

        GLint success, logSize;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logSize);
            GLchar infoLog[logSize];
            glGetProgramInfoLog(shaderProgram, logSize, NULL, infoLog);
            std::cerr << "Shader program linking failed: " << infoLog << std::endl;
        }
        return shaderProgram;
    }

    GLuint createVBO(GLint location, std::vector<GLfloat> &buffer, GLint itemSize, GLboolean normalized=GL_FALSE, GLenum usage=GL_STATIC_DRAW) {
        GLuint VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(GLfloat), buffer.data(), usage);
            glVertexAttribPointer(location, itemSize, GL_FLOAT, normalized, 0, (void*)0);
            glEnableVertexAttribArray(location);
        return VBO;
    }
    GLuint createEBO(std::vector<GLuint> &buffer, GLenum usage=GL_STATIC_DRAW) {
        GLuint EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.size() * sizeof(GLuint), buffer.data(), usage);
        return EBO;
    }
    GLuint createVAO() {
        GLuint VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        return VAO;
    }
    GLuint createTexture(GLenum target) {
        GLuint tex;
        glGenTextures(1, &tex);
        glBindTexture(target, tex);
        return tex;
    }
    GLuint createFBO(GLenum target) {
        GLuint fbo;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(target, fbo);
        return fbo;
    }
    GLuint createRBO() {
        GLuint rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        return rbo;
    }

    void set1(GLuint VBO, int idx, float value, int component=0) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, (idx + component) * sizeof(float), sizeof(float), &value);  // (idx * itemsize + component) * sizeof(float)
    }
    void set2(GLuint VBO, int idx, vec2 value, int component=0) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        float vec[2] = { value.x, value.y };
        glBufferSubData(GL_ARRAY_BUFFER, (idx * 2 + component) * sizeof(float), sizeof(float), vec);
    }
    void set3(GLuint VBO, int idx, vec3 value, int component=0) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        float vec[3] = { value.x, value.y, value.z };
        glBufferSubData(GL_ARRAY_BUFFER, (idx * 3 + component) * sizeof(float), sizeof(float), vec);
    }
    void set4(GLuint VBO, int idx, vec4 value, int component=0) {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        float vec[4] = { value.x, value.y, value.z, value.w };
        glBufferSubData(GL_ARRAY_BUFFER, (idx * 4 + component) * sizeof(float), sizeof(float), vec);
    }

    GLint currentShaderProgram() {
        GLint shaderProgram;
        glGetIntegerv(GL_CURRENT_PROGRAM, &shaderProgram);
        return shaderProgram;
    }
    // Must have a shader program currently being used
    void setUniformInt(const GLchar* name, int value) { glUniform1i(glGetUniformLocation(currentShaderProgram(), name), value); }
    void setUniform(const GLchar* name, float value) { glUniform1f(glGetUniformLocation(currentShaderProgram(), name), value); }
    void setUniform(const GLchar* name, vec2 value) { glUniform2f(glGetUniformLocation(currentShaderProgram(), name), value.x, value.y); }
    void setUniform(const GLchar* name, vec3 value) { glUniform3f(glGetUniformLocation(currentShaderProgram(), name), value.x, value.y, value.z); }
    void setUniform(const GLchar* name, vec4 value) { glUniform4f(glGetUniformLocation(currentShaderProgram(), name), value.x, value.y, value.z, value.w); }
    void setUniform(const GLchar* name, mat4 value) { glUniformMatrix4fv(glGetUniformLocation(currentShaderProgram(), name), 1, value.isRowMajor, value.elements); }

    // Must have a texture currently bound
    void setTexParams(GLenum target, GLenum minFilter=GL_LINEAR, GLenum magFilter=GL_LINEAR, GLenum wrapS=GL_CLAMP_TO_EDGE, GLenum wrapT=GL_CLAMP_TO_EDGE, GLenum wrapR=GL_ZERO) { // use GL_ZERO rather than NULL since it is a GLenum but still evaluates to zero for the if statement
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter);
        glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapS);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapT);
        if (wrapR) glTexParameteri(target, GL_TEXTURE_WRAP_R, wrapR);
    }
}

#endif
