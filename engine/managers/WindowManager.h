#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>

class State;

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
    static WindowManager& instance()
    {
        static WindowManager instance;
        return instance;
    }
    ~WindowManager();

    inline GLFWwindow* getWindow() { return window.get(); }
    void run();

    void setTitle(const std::string& title);

    inline State* getState() { return m_activeState; }
    void setState(State* state);

private:
    WindowManager();

    bool create();
    
    State* m_activeState{nullptr};
    std::unique_ptr<GLFWwindow, glfwWindowDeleter> window;

    GLuint m_vao;
};
