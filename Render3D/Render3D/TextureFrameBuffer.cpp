#include "TextureFrameBuffer.h"



TextureFrameBuffer::TextureFrameBuffer(unsigned int texWidth, unsigned int texHeight):textureWidth(texWidth), textureHeight(texHeight)
{
	createFrameBuffer();
}


TextureFrameBuffer::~TextureFrameBuffer()
{
}

TextureFrameBuffer::PixelInfo TextureFrameBuffer::readPixel(unsigned int x, unsigned int y)
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, bufferFbo);
	glReadBuffer(GL_COLOR_ATTACHMENT0);

	PixelInfo Pixel;
	glReadPixels(x, textureHeight-y-1, 1, 1, GL_RGB, GL_FLOAT, &Pixel);

	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	return Pixel;
}

void TextureFrameBuffer::createFrameBuffer()
{
	//create framebuffer 
	glGenFramebuffers(1, &bufferFbo);
	glBindFramebuffer(GL_FRAMEBUFFER, bufferFbo);

	//create color texture attachment
	glGenTextures(1, &colorTextureFbo);
	glBindTexture(GL_TEXTURE_2D, colorTextureFbo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, textureWidth, textureHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTextureFbo, 0);

	//create depth texture attachment
	glGenTextures(1, &depthTextureFbo);
	glBindTexture(GL_TEXTURE_2D, depthTextureFbo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, textureWidth, textureHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextureFbo, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
