#include "skybox.h"

int		 m_position = 200;
GLfloat m_skyBoxPositon[][3] = {
	{ -m_position, m_position, m_position },{ -m_position, m_position, -m_position },
	{ m_position, m_position, -m_position },{ m_position, m_position, m_position },
	{ -m_position, -m_position, m_position },{ -m_position, -m_position, -m_position },
	{ m_position, -m_position, -m_position },{ m_position, -m_position, m_position }
};
skybox::skybox()
{
	m_position = 200;
	m_listnum = 0;
}


skybox::~skybox()
{

}

void skybox::renderSkyBox()
{
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glColor3f(1, 1, 1);  

	glBindTexture(GL_TEXTURE_2D, m_texture[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3fv(m_skyBoxPositon[3]);
	glTexCoord2f(1, 1); glVertex3fv(m_skyBoxPositon[2]);
	glTexCoord2f(1, 0); glVertex3fv(m_skyBoxPositon[1]);
	glTexCoord2f(0, 0); glVertex3fv(m_skyBoxPositon[0]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_texture[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3fv(m_skyBoxPositon[0]);
	glTexCoord2f(1, 1); glVertex3fv(m_skyBoxPositon[1]);
	glTexCoord2f(1, 0); glVertex3fv(m_skyBoxPositon[5]);
	glTexCoord2f(0, 0); glVertex3fv(m_skyBoxPositon[4]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3fv(m_skyBoxPositon[1]);
	glTexCoord2f(1, 1); glVertex3fv(m_skyBoxPositon[2]);
	glTexCoord2f(1, 0); glVertex3fv(m_skyBoxPositon[6]);
	glTexCoord2f(0, 0); glVertex3fv(m_skyBoxPositon[5]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_texture[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3fv(m_skyBoxPositon[2]);
	glTexCoord2f(1, 1); glVertex3fv(m_skyBoxPositon[3]);
	glTexCoord2f(1, 0); glVertex3fv(m_skyBoxPositon[7]);
	glTexCoord2f(0, 0); glVertex3fv(m_skyBoxPositon[6]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_texture[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3fv(m_skyBoxPositon[3]);
	glTexCoord2f(1, 1); glVertex3fv(m_skyBoxPositon[0]);
	glTexCoord2f(1, 0); glVertex3fv(m_skyBoxPositon[4]);
	glTexCoord2f(0, 0); glVertex3fv(m_skyBoxPositon[7]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, m_texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0); glVertex3fv(m_skyBoxPositon[7]);
	glTexCoord2f(0, 0); glVertex3fv(m_skyBoxPositon[4]);
	glTexCoord2f(0, 1); glVertex3fv(m_skyBoxPositon[5]);
	glTexCoord2f(1, 1); glVertex3fv(m_skyBoxPositon[6]);
	glEnd();
	
}

AUX_RGBImageRec * skybox::initBmpData(const char * Filename)
{
	FILE *File = NULL;  
	if (!Filename)		 
		return NULL;
	File = fopen(Filename, "r");	
	if (File)
	{
		fclose(File);	
		File = NULL;   
		return auxDIBImageLoad(Filename);  
	}
	return NULL;			 
}

int	skybox::setTextures(const char *Filename)  
{
	int Status = FALSE;		
	AUX_RGBImageRec *TextureImage[1];		
	memset(TextureImage, 0, sizeof(void *) * 1);	

	if (TextureImage[0] = initBmpData(Filename))
	{
		Status = TRUE;   
		glGenTextures(1, &m_texture[m_listnum]);	
		glBindTexture(GL_TEXTURE_2D, m_texture[m_listnum++]);   

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureImage[0]->sizeX, TextureImage[0]->sizeY,
			0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}

	return Status;  
}
