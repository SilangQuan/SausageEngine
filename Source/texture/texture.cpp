#include "texture.h"


Texture::Texture()
{
	isLoaded = false;

}


Texture::~Texture()
{
}

Texture::Texture(GLenum target, const QString& f)
{
	textureTarget = target;
	filePath = f;
	isLoaded = false;
	//surface = NULL;
}

bool Texture::load()
{
	QImage img(filePath);
	formatImage = QGLWidget::convertToGLFormat(img);

	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &textureObj);

	width = formatImage.width();
	height = formatImage.height();
	formatImage.format();
	bpp = formatImage.bytesPerLine() / formatImage.width();

	// work out what format to tell glTexImage2D to use...
	if (bpp == 3) { // RGB 24bit
		mode = GL_RGB;
	}
	else if (bpp == 4) { // RGBA 32bit
		mode = GL_RGBA;
	}

	glBindTexture(textureTarget, textureObj);
	glTexImage2D(textureTarget, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, formatImage.bits());
	setFiltering(GL_LINEAR, GL_LINEAR);

	isLoaded = true;

	return true;
}

// Sets magnification and minification texture filter.

void Texture::setFiltering(int a_tfMagnification, int a_tfMinification)
{
	glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, a_tfMinification);
	glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, a_tfMagnification);
}

void Texture::bind(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(textureTarget, textureObj);
}

/*-----------------------------------------------

Name:	DeleteTexture

Params:	none

Result:	Frees all memory used by texture.

/*---------------------------------------------*/

void Texture::deleteTexture()
{
}


int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}

int Texture::getBPP()
{
	return bpp;
}

unsigned char Texture::getTextureID()
{
	return textureObj;
}

QString Texture::getPath()
{
	return filePath;
}

bool Texture::hasLoaded()
{
	return isLoaded;
}