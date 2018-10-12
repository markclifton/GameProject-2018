#include "context.h"

#include <GL/glew.h>

#include <iostream>

#include "../buffers/indexbuffer.h"
#include "../buffers/vertexbuffer.h"
#include "../managers/windowmanager.h"

Context::Context()
{
}

void Context::run()
{
    GLfloat Vertices [] = {
		0.0f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};

    GLuint Elements [] = {
		0, 1, 2
	};

    IndexBuffer i;
    i.buffer(sizeof(Elements), reinterpret_cast<void*>(Elements));

    VertexBuffer v;
    v.buffer(sizeof(Vertices), reinterpret_cast<void*>(Vertices));

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}
