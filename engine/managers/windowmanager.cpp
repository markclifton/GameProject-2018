#include "windowmanager.h"

#include <iostream>

#include "../contexts/context.h"

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
    glfwSetWindowTitle(window.get(), title.c_str());
}

bool WindowManager::shouldClose()
{
    return glfwWindowShouldClose(window.get());
}

void WindowManager::refresh()
{
    glfwSwapBuffers(window.get());
    glfwPollEvents();
}

bool WindowManager::create()
{
	if (! glfwInit())
		return false;

    window.reset(glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr));
	if (!window.get())
	{
		glfwTerminate();
		return false;
	}
    
    glfwMakeContextCurrent(window.get());

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return false;
	}
    return true;
}

