#include "windowmanager.h"

#include <iostream>

#include "ps/utils/keyhandler.h"
#include "ps/utils/mousehandler.h"

namespace ps
{
namespace
{
void key_forwarder(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    WindowManager* windowManager = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
    windowManager->keyHandler(key, scancode, action, mods);
}

void cursor_forwarder(GLFWwindow* window, double xpos, double ypos)
{
    WindowManager* windowManager = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
    windowManager->mouseHandler(xpos,ypos);
}

void mouse_forwarder(GLFWwindow* window, int button, int action, int mods)
{
    WindowManager* windowManager = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
    windowManager->mouseHandler(button, action, mods);
}
}

WindowManager::WindowManager()
{
    if( !create() )
    {
        std::cerr << "Failed to create window\n";
        return;
    }

    glGenVertexArrays(1, &m_vao);

    if(m_vao == 0)
    {
        std::cerr << "OpenGL isn't working correctly\n";
        abort();
    }

    glBindVertexArray(m_vao);
}

WindowManager::~WindowManager()
{
    close();
}

void WindowManager::setTitle(const std::string& title)
{
    glfwSetWindowTitle(m_window.get(), title.c_str());
}

void WindowManager::close()
{
    if(m_vao != 0)
    {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }

    if(m_window)
    {
        m_window = nullptr;
    }
}

bool WindowManager::shouldClose()
{
    return glfwWindowShouldClose(m_window.get());
}

void WindowManager::refresh()
{
    //glClearColor(.2f,.3f,.8f,0.f);
    glfwSwapBuffers(m_window.get());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
    m_latency = (9*m_latency+m_timer.reset())/10.;
}

void WindowManager::registerHandler(utils::KeyHandler* handler)
{
    m_keyHandlers.push_back(handler);
}

void WindowManager::registerHandler(utils::MouseHandler* handler)
{
    m_mouseHandlers.push_back(handler);
}

void WindowManager::keyHandler(int key, int scancode, int action, int mods)
{
    for(auto& handler : m_keyHandlers)
    {
        handler->process(key, scancode, action, mods);
    }
}

void WindowManager::mouseHandler(double xpos, double ypos)
{
    for(auto& handler : m_mouseHandlers)
    {
        handler->process(xpos, ypos);
    }
}

void WindowManager::mouseHandler(int button, int action, int mods)
{
    for(auto& handler : m_mouseHandlers)
    {
        handler->process(button, action, mods);
    }
}

void WindowManager::setAsRenderTarget()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 1280, 720); //TODO: Window Size...
}

bool WindowManager::create()
{
    if (! glfwInit())
        return false;

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    glfwWindowHint(GLFW_SAMPLES, 4);

    m_window.reset(glfwCreateWindow(1280, 720, "ProjectSane", nullptr, nullptr));
    if (!m_window.get())
    {
        glfwTerminate();
        return false;
    }

    // Set Callbacks for input
    glfwSetWindowUserPointer(m_window.get(), this);
    glfwSetKeyCallback(m_window.get(), key_forwarder);
    glfwSetCursorPosCallback(m_window.get(), cursor_forwarder);
    glfwSetMouseButtonCallback(m_window.get(), mouse_forwarder);

    glfwMakeContextCurrent(m_window.get());
    glfwSwapInterval( 0 );

    if (!gladLoadGL(glfwGetProcAddress)) {
        return false;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    //glEnable(GL_DEPTH_CLAMP);

    return true;
}
}
