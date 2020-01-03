//
// Created by sdr on 20. 1. 3..
//

#ifndef CBASEDOGLTETRIS_INITGLSL_H
#define CBASEDOGLTETRIS_INITGLSL_H

#define GLFW_INCLUDE_GLEXT
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

extern char *readShaderSource(const char *shaderFile);
extern GLuint InitShader(const char *, const char *);

#endif //CBASEDOGLTETRIS_INITGLSL_H
