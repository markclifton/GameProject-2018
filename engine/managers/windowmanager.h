#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <vector>

#include "../utils/keyhandler.h"

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

    inline GLFWwindow* getWindow() { return m_window.get(); }

    void setTitle(const std::string& title);

    inline void toggleVsync(bool enabled) { glfwSwapInterval( enabled ); }

    bool shouldClose();
    void refresh();

    //Not Thread-safe
    void registerHandler(std::unique_ptr<utils::KeyHandler> handler);
    void keyHandler(int key, int scancode, int action, int mods);

private:
    bool create();

    std::unique_ptr<GLFWwindow, glfwWindowDeleter> m_window;
    std::vector<std::unique_ptr<utils::KeyHandler>> m_keyHandlers;

    GLuint m_vao;
};
