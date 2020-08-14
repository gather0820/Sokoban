#include "gl/GLAUX.H"
#include "gl/GLUT.H"
#include <windows.h>
#include <stdio.h>
#include "gl/GL.H"
#include "gl/GLU.H"
#include "math.h"

#define MAX_TEXTURE_NUM	(10)

#pragma once
class skybox
{
public:
	skybox();
	~skybox();

public:
	void renderSkyBox();
	int setTextures(const char *Filename);
private:

	AUX_RGBImageRec * initBmpData(const char * Filename);

private:
	GLuint	 m_texture[MAX_TEXTURE_NUM];
	int		 m_listnum;
};