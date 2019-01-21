#pragma once

#include "ps/glad/gl.h"
#include "GLFW/glfw3.h"

#include <memory>
#include <string>
#include <vector>

#include "ps/utils/timer.h"

namespace ps
{
namespace utils
{
class KeyHandler;
class MouseHandler;
}

namespace
{
struct glfwWindowDeleter
{
    void operator()(GLFWwindow* ptr){
        glfwTerminate();
        glfwDestroyWindow(ptr);
    }
};
}

class WindowManager
{
    WindowManager();
public:
    static WindowManager& Get()
    {
        static WindowManager manager;
        return manager;
    }

    ~WindowManager();

    inline GLFWwindow* getWindow() { return m_window.get(); }

    void setTitle(const std::string& title);

    inline void toggleVsync(bool enabled) { glfwSwapInterval( enabled ); }

    void close();
    bool shouldClose();
    void refresh();

    inline double latency() { return m_latency; }

    //Input Handlers
    void registerHandler(utils::KeyHandler* handler);
    void registerHandler(utils::MouseHandler* handler);

    void keyHandler(int key, int scancode, int action, int mods);
    void mouseHandler(double xpos, double ypos);
    void mouseHandler(int button, int action, int mods);

    void setAsRenderTarget();

private:
    WindowManager(WindowManager const&) = delete;
    void operator=(WindowManager const&) = delete;

    bool create();

    std::unique_ptr<GLFWwindow, glfwWindowDeleter> m_window;

    //TODO: Add a way to remove these, also thread-safety
    std::vector<utils::KeyHandler*> m_keyHandlers;
    std::vector<utils::MouseHandler*> m_mouseHandlers;

    double m_latency {0.0};
    utils::Timer m_timer;
    GLuint m_vao;
};
}
