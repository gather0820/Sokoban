#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include "gl\GLU.H"
#include "gl\GL.H"
#include  "gl\GLAUX.H"
#include  "math.h"
#include "gl\GLUT.H"

#include "sokoban.h"
#include "skybox.h"
#include "camera.h"


sokoban m_sokoban;
skybox  m_skyBox;
Camera m_Camera;

#define PI 3.141592

float x_view = 0, y_view = 0, z_view = 0;
 
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	glPushMatrix();

	m_Camera.setLook();
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);			
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);		

	m_sokoban.showGame();
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	m_skyBox.renderSkyBox();
	glPopMatrix();


	glutSwapBuffers();
}

void init(void)
{
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);

	m_skyBox.setTextures("Data/Front.bmp");
	m_skyBox.setTextures("Data/Right.bmp");
	m_skyBox.setTextures("Data/Left.bmp");
	m_skyBox.setTextures("Data/Top.bmp");
	m_skyBox.setTextures("Data/Bottom.bmp");
	m_skyBox.setTextures("Data/Back.bmp");

	if (!m_sokoban.setTextures())
	{
		printf("LoadGLTextures()");
		return;
	}
	m_sokoban.initMap("Data/map.txt");
	m_sokoban.setList();

 
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	
	PlaySound("Data/skyCity.wav", NULL, SND_ASYNC | SND_LOOP);

	m_Camera.setCamera(0.0f, 1.5f, 6.0f, 0.0f, 1.5f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void myReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, float(w) / float(h), 1, 9999);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case  'w':
		if (m_sokoban.isMoveOver(DIR_UP))
		{
			m_sokoban.moveUP();
		}
		break;
	case  'a':
		if (m_sokoban.isMoveOver(DIR_LEFT))
		{
			m_sokoban.moveLeft();
		}
		break;
	case  'd':
		if (m_sokoban.isMoveOver(DIR_RIGHT))
		{
			m_sokoban.moveRight();
		}
		break;
	case  's':
		if (m_sokoban.isMoveOver(DIR_DOWN))
		{
			m_sokoban.moveDown();
		}
		break;
	case  '1':
		m_Camera.setSpeed(0.2f);
		break;
	case  '2':
		m_Camera.setSpeed(2.0f);
		break;
	case  '3':
		m_Camera.moveCamera(m_Camera.getSpeed());
		break;
	case  '4':
		m_Camera.moveCamera(-m_Camera.getSpeed());
		break;
	case  '5':
		m_Camera.yawCamera(-m_Camera.getSpeed());
		break;
	case  '6':
		m_Camera.yawCamera(m_Camera.getSpeed());
		break;
	case  '7':
		m_sokoban.setReStart();
		break;
	case  '8':
		m_sokoban.setNextLevel();
		break;
	case  '9':
		m_sokoban.setUpLevel();
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void special_func(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_END:
		exit(0);
		break; 
	default:
		break;
	}
	glutPostRedisplay();
}

void motion(int x, int y)
{
	m_Camera.setViewByMouse();

	glutPostRedisplay();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(400, 100); 
	glutCreateWindow("Sokoban");
	 
	init();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_func);
	glutMotionFunc(motion);
	glutMainLoop();
	return 0;
}

