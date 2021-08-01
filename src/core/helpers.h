#ifndef IGSI_HELPERS_H
#define IGSI_HELPERS_H

// This header needs access to OpenGL definitions
// Replace this with whatever loader you are using
#include "..\..\include\glad.h"

#include <vector>
#include <string>

namespace Igsi {
    class vec2;
    class vec3;
    class vec4;
    class mat4;
    class Geometry;

    GLuint compileShader(GLenum shaderType, std::string path);

    // GLuint createShaderProgram(GLuint* shaders, int numShaders);
    GLuint createShaderProgram(std::string vsPath, std::string fsPath, std::string gsPath=std::string());

    // GLuint createVBO(GLint location, std::vector<GLfloat> &buffer, GLint itemSize, GLboolean normalized=GL_FALSE, GLenum usage=GL_STATIC_DRAW);
    GLuint createVBO(GLint location, Geometry* geometry, std::string key, GLenum usage=GL_STATIC_DRAW, GLsizei stride=0, const void* pointer=(void*)0);
    GLuint createEBO(std::vector<GLuint> &buffer, GLenum usage=GL_STATIC_DRAW);
    GLuint createVAO();
    GLuint createTexture(GLenum target);
    GLuint createFBO(GLenum target);
    GLuint createRBO();

    void set1(int idx, float value);
    void set2(int idx, vec2 value);
    void set3(int idx, vec3 value);
    void set4(int idx, vec4 value);

    // extern GLint currentShaderProgram;
    // void useProgram(GLint shaderProgram);
    GLuint getCurrentShaderProgram();

    void setUniformInt(const GLchar* name, int value, GLuint program=0);
    void setUniform(const GLchar* name, float value, GLuint program=0);
    void setUniform(const GLchar* name, vec2 value, GLuint program=0);
    void setUniform(const GLchar* name, vec3 value, GLuint program=0);
    void setUniform(const GLchar* name, vec4 value, GLuint program=0);
    void setUniform(const GLchar* name, mat4 value, GLuint program=0);

    void activateTexture(GLuint texture, GLenum target, unsigned int unit=0);

    // Must have a texture currently bound
    void setTexParams(GLenum target, GLenum minFilter=GL_LINEAR, GLenum magFilter=GL_LINEAR, GLenum wrapS=GL_CLAMP_TO_EDGE, GLenum wrapT=GL_CLAMP_TO_EDGE, GLenum wrapR=GL_ZERO);
}

#endif
