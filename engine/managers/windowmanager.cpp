#include "windowmanager.h"

#include <iostream>

#include "utils/keyhandler.h"
#include "utils/mousehandler.h"

namespace
{
    void key_forwarder(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        managers::WindowManager* windowManager = static_cast<managers::WindowManager*>(glfwGetWindowUserPointer(window));
        windowManager->keyHandler(key, scancode, action, mods);
    }

    void cursor_forwarder(GLFWwindow* window, double xpos, double ypos)
    {
        managers::WindowManager* windowManager = static_cast<managers::WindowManager*>(glfwGetWindowUserPointer(window));
        windowManager->mouseHandler(xpos,ypos);
    }

    void mouse_forwarder(GLFWwindow* window, int button, int action, int mods)
    {
        managers::WindowManager* windowManager = static_cast<managers::WindowManager*>(glfwGetWindowUserPointer(window));
        windowManager->mouseHandler(button, action, mods);
    }
}

namespace managers
{
    WindowManager::WindowManager()
    {
        if( !create() )
        {
            std::cout << "Failed to create window\n";
            return;
        }

        glGenVertexArrays(1, &m_vao);
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
        glClearColor(.2f,.3f,.8f,0.f);
        glfwSwapBuffers(m_window.get());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        m_latency = (59*m_latency+m_timer.reset())/60.;
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

    bool WindowManager::create()
    {
        if (! glfwInit())
            return false;

        glfwWindowHint(GLFW_SAMPLES, 4);

        m_window.reset(glfwCreateWindow(640, 480, "ProjectSane", nullptr, nullptr));
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
        glfwSwapInterval( 1 );

        if (!gladLoadGL(glfwGetProcAddress)) {
            return false;
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);

        return true;
    }
}
