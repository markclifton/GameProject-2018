#include "windowmanager.h"

#include <iostream>

namespace
{
    void key_forwarder(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        WindowManager* windowManager = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        windowManager->keyHandler(key, scancode, action, mods);
    }
}

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
	glDeleteVertexArrays(1, &m_vao);
}

void WindowManager::setTitle(const std::string& title)
{
    glfwSetWindowTitle(m_window.get(), title.c_str());
}

bool WindowManager::shouldClose()
{
    return glfwWindowShouldClose(m_window.get());
}

void WindowManager::refresh()
{
    glfwSwapBuffers(m_window.get());
    glfwPollEvents();
}

void WindowManager::registerHandler(std::unique_ptr<utils::KeyHandler> handler)
{
    m_keyHandlers.push_back(std::move(handler));
}

void WindowManager::keyHandler(int key, int scancode, int action, int mods)
{
    for(auto& handler : m_keyHandlers)
    {
        handler->process(key, scancode, action, mods);
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
    
    glfwSetWindowUserPointer(m_window.get(), this);
    glfwSetKeyCallback(m_window.get(), key_forwarder);

    glfwMakeContextCurrent(m_window.get());

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return false;
	}
    return true;
}
