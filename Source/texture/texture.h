#pragma once
#include "common.h"
#include <QString>
#include <QImage>
#include <QGLWidget>

enum ETextureFiltering
{
	TEXTURE_FILTER_MAG_NEAREST = 0, // Nearest criterion for magnification
	TEXTURE_FILTER_MAG_BILINEAR, // Bilinear criterion for magnification
	TEXTURE_FILTER_MIN_NEAREST, // Nearest criterion for minification
	TEXTURE_FILTER_MIN_BILINEAR, // Bilinear criterion for minification
	TEXTURE_FILTER_MIN_NEAREST_MIPMAP, // Nearest criterion for minification, but on closest mipmap
	TEXTURE_FILTER_MIN_BILINEAR_MIPMAP, // Bilinear criterion for minification, but on closest mipmap
	TEXTURE_FILTER_MIN_TRILINEAR, // Bilinear criterion for minification on two closest mipmaps, then averaged
};

class Texture
{
public:
	Texture();
	Texture(GLenum textureTarget, const QString& filrPath);
	~Texture();

	bool load();
	void bind(GLenum textureUnit = 0);

	void setFiltering(int a_tfMagnification, int a_tfMinification);
	void setSamplerParameter(GLenum parameter, GLenum value);

	int getWidth();
	int getHeight();
	int getBPP();
	QString getPath();
	unsigned char getTextureID();

	void deleteTexture();
	bool hasLoaded();

private:
	int width, height, bpp; // Texture width, height, and bytes per pixel
	GLenum textureTarget;
	GLuint textureObj;
	QString filePath;
	int mode;
	bool isLoaded;
	QImage formatImage;
};

