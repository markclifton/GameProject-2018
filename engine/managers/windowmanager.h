#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>

struct glfwWindowDeleter
{
    void operator()(GLFWwindow* ptr){
        glfwTerminate();
        glfwDestroyWindow(ptr);
    }
};

class WindowManager
{
public:
    WindowManager();
    ~WindowManager();

    inline GLFWwindow* getWindow() { return window.get(); }

    void setTitle(const std::string& title);

    bool shouldClose();
    void refresh();

private:
    bool create();

    std::unique_ptr<GLFWwindow, glfwWindowDeleter> window;

    GLuint m_vao;
};
