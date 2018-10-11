#include "WindowManager.h"

#include <iostream>

#include "../states/State.h"

WindowManager::WindowManager()
{
    if( !create() )
    {
        std::cout << "Failed to create window\n";
        return;
    }

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glDeleteVertexArrays(1, &m_vao);
}

WindowManager::~WindowManager()
{
	glDeleteVertexArrays(1, &m_vao);
}

void WindowManager::run()
{
	while (!glfwWindowShouldClose(window.get()))
	{
        if(m_activeState != nullptr)
        {
            m_activeState->run();
        }
		glfwSwapBuffers(window.get());
		glfwPollEvents();
	}
}

void WindowManager::setTitle(const std::string& title)
{
    glfwSetWindowTitle(window.get(), title.c_str());
}

void WindowManager::setState(State* state)
{
    m_activeState = state;
}

bool WindowManager::create()
{
	if (! glfwInit())
		return false;

    window.reset(glfwCreateWindow(640, 480, "Hello World", NULL, NULL));
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

