#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

struct glfwWindowDeleter
{
    void operator()(GLFWwindow* ptr){
         glfwDestroyWindow(ptr);
    }
};

class WindowManager
{
public:
    WindowManager();

private:
    std::unique_ptr<GLFWwindow, glfwWindowDeleter> window;
};
