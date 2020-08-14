#include "sokoban.h"
#include <fstream>
#include <iostream>

sokoban::sokoban()
{
	m_row = 0;
	m_col = 0;
	m_boxNum = 1;
	m_currentState = 1;

	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;
	
	zoom = -15;
}

sokoban::~sokoban()
{

}

void sokoban::initMap(const char * fileName)
{
	ifstream infile(fileName);
	for (int k = 0; k < m_currentState; k++)
	{
		infile >> m_row;
		infile >> m_col;
		infile >> m_boxNum;

		for (int i = 0; i < m_row; i++)
			for (int j = 0; j < m_col; j++)
				infile >> Map[i][j];

		for (int i = 0; i < m_boxNum; i++)
		{
			infile >> m_boxPosition[i].x;
			infile >> m_boxPosition[i].y;
		}
		infile >> m_peoplePosition.x;
		infile >> m_peoplePosition.y;
	}
	infile.close();
	initBox();
}

bool sokoban::initBox()
{
	m_reachBox = 0;
	int tempx, tempy;
	for (int i = 0; i < m_boxNum; i++)
	{
		tempx = m_boxPosition[i].x;
		tempy = m_boxPosition[i].y;
		if (Map[tempx][tempy] == MAP_DEST)
			m_reachBox++;
	}
	return TRUE;
}

AUX_RGBImageRec * sokoban::initBmpData(const char * Filename)
{
	FILE *File = NULL;									 
	if (!Filename)	return NULL;
	File = fopen(Filename, "r");		
	
	if (File)											
	{
		fclose(File);									
		return auxDIBImageLoad(Filename);				
	}
	return NULL;
}
int sokoban::setTextures()
{
	int Status = FALSE;									 

	AUX_RGBImageRec *TextureImage[1];					 

	memset(TextureImage, 0, sizeof(void *) * 1);           	 
											 
	if (TextureImage[0] = initBmpData("Data/wall.bmp"))
	{
		Status = TRUE;	
		glGenTextures(1, &m_texture[0]);
		glBindTexture(GL_TEXTURE_2D, m_texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	if (TextureImage[0] = initBmpData("Data/box.bmp"))
	{
		Status = TRUE;									
		glGenTextures(1, &m_texture[1]);															
		glBindTexture(GL_TEXTURE_2D, m_texture[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	if (TextureImage[0] = initBmpData("Data/people.bmp"))
	{
		Status = TRUE;									
		glGenTextures(1, &m_texture[2]);																
		glBindTexture(GL_TEXTURE_2D, m_texture[2]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	if (TextureImage[0])									
	{
		if (TextureImage[0]->data)		free(TextureImage[0]->data);
		free(TextureImage[0]);								
	}
	return Status;
}
GLvoid sokoban::setList()
{
	
	m_box = glGenLists(2);									
	glNewList(m_box, GL_COMPILE);							
	glBegin(GL_QUADS);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	glEndList();
	m_dest = m_box + 1;
	glNewList(m_dest, GL_COMPILE);							 
	glEndList();
}

void sokoban::showGame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, m_texture[0]);

	glPushMatrix();
	
	glTranslatef(xpos, ypos, zoom);
	glRotatef(m_x, 1.0, 0.0, 0.0);
	glRotatef(m_y, 0.0, 1.0, 0.0);
	glRotatef(m_z, 0.0, 0.0, 1.0);

	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			switch (Map[i][j])
			{
			case MAP_NONE:
				break;
			case MAP_WALL:
				glBindTexture(GL_TEXTURE_2D, m_texture[0]);
				glPushMatrix();
				glTranslatef((i - m_row / 2) * 2, (j - m_col / 2) * 2, 0);
				glCallList(m_box);
				glPopMatrix();
				break;
			case MAP_DEST:
				glPushMatrix();
				glTranslatef((i - m_row / 2) * 2, (j - m_col / 2) * 2, 0);
				glutSolidSphere(1, 50, 50);
				glPopMatrix();
			}
		}
	}
	
	for (int i = 0; i < m_boxNum; i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_texture[1]);
		glPushMatrix();
		glTranslatef((m_boxPosition[i].x - m_row / 2) * 2, (m_boxPosition[i].y - m_col / 2) * 2, 0);
		if (Map[m_boxPosition[i].x][m_boxPosition[i].y] == MAP_DEST)
		{
			glEnable(GL_BLEND);		
			
			glEnable(GL_DEPTH_TEST);
		}
		glCallList(m_box);
		glPopMatrix();

		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}

	glBindTexture(GL_TEXTURE_2D, m_texture[2]);
	glPushMatrix();
	glTranslatef((m_peoplePosition.x - m_row / 2) * 2, (m_peoplePosition.y - m_col / 2) * 2, 0);
	glCallList(m_box);
	glPopMatrix();

	glDisable(GL_BLEND);		
	glEnable(GL_DEPTH_TEST);	

	glPopMatrix();

	if (m_reachBox == m_boxNum)
	{
		m_currentState++;
		initMap("Data/map.txt");
		glutPostRedisplay();
	}
}

bool sokoban::isBox(int i, int j)
{
	for (int k = 0; k<m_boxNum; k++)
	{
		if (m_boxPosition[k].x == i && m_boxPosition[k].y == j)
			return TRUE;
	}
	return FALSE;
}

BOOL sokoban::isMoveOver(int Direct)
{
	int curx = m_peoplePosition.x;
	int cury = m_peoplePosition.y;
	
	switch (Direct)
	{
	case DIR_DOWN:
		if (cury == 0 || (Map[curx][cury - 1] == MAP_WALL) || (isBox(curx, cury - 1) && (cury - 1 == 0 || (Map[curx][cury - 2] == MAP_WALL) || isBox(curx, cury - 2))))
			return FALSE;
		break;
	case DIR_UP:
		if (cury == m_col - 1 || (Map[curx][cury + 1] == MAP_WALL) || (isBox(curx, cury + 1) && (cury + 1 == m_col - 1 || (Map[curx][cury + 2] == MAP_WALL) || isBox(curx, cury + 2))))
			return FALSE;
		break;
	case DIR_LEFT:
		if (curx == 0 || (Map[curx - 1][cury] == MAP_WALL) || (isBox(curx - 1, cury) && (curx - 1 == 0 || (Map[curx - 2][cury] == MAP_WALL) || isBox(curx - 2, cury))))
			return FALSE;
		break;
	case DIR_RIGHT:
		if (curx == m_row - 1 || (Map[curx + 1][cury] == MAP_WALL) || (isBox(curx + 1, cury) && (curx + 1 == m_row - 1 || (Map[curx + 2][cury] == MAP_WALL) || isBox(curx + 2, cury))))
			return FALSE;
		break;
	}
	return TRUE;
}

Point_S * sokoban::GetBoxPosition(int i, int j)
{
	for (int k = 0; k<m_boxNum; k++)
	{
		if (m_boxPosition[k].x == i && m_boxPosition[k].y == j)
			return &m_boxPosition[k];
	}
	return NULL;
}

bool sokoban::moveDown(void)
{
	int curx = m_peoplePosition.x;
	int cury = m_peoplePosition.y;
	m_peoplePosition.y -= 1;

	if (Map[curx][cury - 1] == MAP_DEST && isBox(curx, cury - 1))
		m_reachBox -= 1;
	if (isBox(curx, cury - 1))
	{
		Point_S *temp = GetBoxPosition(curx, cury - 1);
		temp->y -= 1;
		if (Map[curx][cury - 2] == MAP_DEST)
			m_reachBox += 1;
	}
	return TRUE;
}

bool  sokoban::moveUP(void)
{
	int curx = m_peoplePosition.x;
	int cury = m_peoplePosition.y;
	m_peoplePosition.y += 1;
	if (isBox(curx, cury + 1) && Map[curx][cury + 1] == MAP_DEST)
		m_reachBox -= 1;
	if (isBox(curx, cury + 1))
	{
		Point_S *temp = GetBoxPosition(curx, cury + 1);
		temp->y += 1;
		if (Map[curx][cury + 2] == MAP_DEST)
			m_reachBox += 1;
	}
	return TRUE;
}

BOOL  sokoban::moveLeft(void)
{
	int curx = m_peoplePosition.x;
	int cury = m_peoplePosition.y;
	m_peoplePosition.x -= 1;
	if (isBox(curx - 1, cury) && Map[curx - 1][cury] == MAP_DEST)
		m_reachBox -= 1;
	if (isBox(curx - 1, cury))
	{
		Point_S *temp = GetBoxPosition(curx - 1, cury);
		temp->x -= 1;
		if (Map[curx - 2][cury] == MAP_DEST)
			m_reachBox += 1;
	}
	return TRUE;
}

BOOL sokoban::moveRight(void)
{
	int curx = m_peoplePosition.x;
	int cury = m_peoplePosition.y;
	m_peoplePosition.x += 1;
	if (isBox(curx + 1, cury) && Map[curx + 1][cury] == MAP_DEST)
		m_reachBox -= 1;
	if (isBox(curx + 1, cury))
	{
		Point_S *temp = GetBoxPosition(curx + 1, cury);
		temp->x += 1;
		if (Map[curx + 2][cury] == MAP_DEST)
			m_reachBox += 1;
	}
	return TRUE;
}

void sokoban::setX(GLfloat x)
{
	m_x = x;
}

void sokoban::setY(GLfloat y)
{
	m_y = y;
}

void sokoban::setZ(GLfloat z)
{
	m_z = z;
}

void sokoban::setReStart()
{
	initMap("Data/map.txt");
}

void sokoban::setNextLevel()
{
	m_currentState += 1;
	initMap("Data/map.txt");
}

void sokoban::setUpLevel()
{
	m_currentState -= 1;
	initMap("Data/map.txt");
}
