//
// Created by sdr on 20. 1. 3..
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "initglsl.h"

void gotoShaderDir(void)
{
    int len, sublen;
    char buf[32] = "shader";
    char pwd[128] = "\0";

    chdir(buf);
    len = strlen(buf);

    getcwd(pwd, sizeof(pwd));
    sublen = strlen(pwd);

    if(!strncmp(&pwd[sublen - len], buf, len))
        printf("Here is %s\n", buf);

    printf("pwd = %s\n", pwd);
}

char *readShaderSource(const char *shaderFile)
{
    gotoShaderDir();

    FILE* fp = fopen(shaderFile, "r");

    if(fp == NULL)
    {
        return NULL;
    }

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    printf("size = %u\n", size);

    fseek(fp, 0L, SEEK_SET);
    char *buf = (char *)malloc(sizeof(char) * size);
    fread(buf, 1, size, fp);

    buf[size] = '\0';
    fclose(fp);

    return buf;
}

// Create a GLSL program object from vertex and fragment shader files
GLuint InitShader(const char *vShaderFile, const char *fShaderFile)
{
    int i;

    struct Shader {
        const char *    filename;
        GLenum          type;
        GLchar *        source;
    };

    struct Shader shaders[2] = {
            { vShaderFile, GL_VERTEX_SHADER, NULL },
            { fShaderFile, GL_FRAGMENT_SHADER, NULL }
    };

    GLuint program = glCreateProgram();

    for(i = 0; i < 2; ++i )
    {
        shaders[i].source = readShaderSource(shaders[i].filename);

        if(shaders[i].source == NULL)
        {
            printf("Failed to read %s\n", shaders[i].filename);
            exit(EXIT_FAILURE);
        }

        GLuint shader = glCreateShader(shaders[i].type);
        glShaderSource(shader, 1, (const GLchar **) &shaders[i].source, NULL);
        glCompileShader(shader);

        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            printf("%s Failed to compile\n", shaders[i].filename);
            GLint logSize;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
            char *logMsg = (char *)malloc(sizeof(char) * (logSize + 1));
            glGetShaderInfoLog(shader, logSize, NULL, logMsg);
            printf("%s\n", logMsg);
            free(logMsg);

            exit( EXIT_FAILURE );
        }

        free(shaders[i].source);

        glAttachShader(program, shader);
    }

    /* link  and error check */
    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if(!linked)
    {
        printf("Shader Program Failed to Link\n");
        GLint logSize;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
        char *logMsg = (char *)malloc(sizeof(char) * (logSize + 1));
        glGetProgramInfoLog(program, logSize, NULL, logMsg);
        printf("%s\n", logMsg);
        free(logMsg);

        exit(EXIT_FAILURE);
    }

    /* use program object */
    glUseProgram(program);

    return program;
}