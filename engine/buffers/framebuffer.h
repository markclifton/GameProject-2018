#pragma once

#include "glad/gl.h"

namespace buffers
{
class FrameBufferObject
{
public:
    FrameBufferObject(int width, int height)
        : m_width( width )
        , m_height( height )
    {
        glGenFramebuffers(1, &m_fbo);
        bind();

        glGenTextures(1, &renderedTexture);
        glBindTexture(GL_TEXTURE_2D, renderedTexture);
        glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, renderedTexture, 0);

        unbind();
    }

    ~FrameBufferObject()
    {
        glDeleteTextures(1, &renderedTexture);
        glDeleteRenderbuffers(1, &depthrenderbuffer);
        glDeleteFramebuffers(1, &m_fbo);
    }

    void bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
        glViewport(0, 0, m_width, m_height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void bindColor()
    {
        bind();

        // Set the list of draw buffers.
        //GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
        //glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
        glDrawBuffer(GL_NONE);
    }

    void bindAsTexture()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, renderedTexture);
    }

    void unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, 640, 480);
    }

private:
    int m_width;
    int m_height;

    GLuint m_fbo;
    GLuint renderedTexture;

    GLuint depthrenderbuffer;
};
}
