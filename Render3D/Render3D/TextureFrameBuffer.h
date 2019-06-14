#ifndef TEXTUREFRAMEBUFFER_H
#define TEXTUREFRAMEBUFFER_H

#include <glad/glad.h>
#include <iostream>

class TextureFrameBuffer
{
private:
	unsigned int bufferFbo, colorTextureFbo, depthTextureFbo;
	unsigned int textureWidth, textureHeight;

public:
	struct PixelInfo {
		float f1;
		float f2;
		float f3;

		PixelInfo() {
			f1 = 0.0f;
			f2 = 0.0f;
			f3 = 0.0f;
		}
	};

public:
	TextureFrameBuffer(unsigned int texWidth, unsigned int texHeight);
	virtual ~TextureFrameBuffer();
	unsigned int getFBO() const { return bufferFbo; };
	PixelInfo readPixel(unsigned int x, unsigned int y);

private:
	void createFrameBuffer();
};
#endif
