
#include "utils.hpp"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }
}

void frame_buffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void error(const char *msg) {
    cerr << "Error: " << msg << endl;
    exit(1);
}

const char* load_file(const char* file_path) {
    FILE* file = fopen(file_path, "rb");

    if (file == nullptr) {
        return nullptr;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buffer = new char[size + 1];

    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    fclose(file);

    return buffer;
}

GLuint generate_texture(const char *file_name) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(file_name, &width, &height, &nrChannels, 0);
    if(!data) {
        error("stbi: Failed to load the image data");
    }

    GLenum format, internal_format;
    if(nrChannels == 1) {
        format = internal_format = GL_RED;
    } else if(nrChannels == 3) {
        format = internal_format = GL_RGB;
    } else if (nrChannels == 4) {
       format = internal_format = GL_RGBA;
    } else {
        error("stbi: unsupported number of channels in given image format.");
    }
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    return texture;
}

GLuint createShader(const char *file_name, int type) {
    GLuint shader;
    const char *source_code;
    int success, length;
    char infolog[512];

    shader = glCreateShader(type);
    source_code = load_file(file_name);
    glShaderSource(shader, 1, &source_code, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, &length, infolog);
        cerr << infolog << endl;
        error("OpenGL: Failed to compile vertex shader");
    }
    return shader;
}

GLuint linkShaders(GLuint vs, GLuint fs) {
    GLuint prg;
    int success, length;
    char infolog[512];
    
    prg = glCreateProgram();
    glAttachShader(prg, vs);
    glAttachShader(prg, fs);
    glLinkProgram(prg);
    glGetProgramiv(prg, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(prg, 512, &length, infolog);
        cerr << infolog << endl;
        error("OpenGL: Failed to link shader program");
    }
    return prg;
}