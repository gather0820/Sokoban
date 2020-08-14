#pragma once
#include "gl\GLAUX.H"
#include "gl\GLUT.H"

using namespace std;
#define	MAX_BUF_SIZE	(32)

typedef struct Point {
	int x, y;
}Point_S;

enum BoxDirect { 
	DIR_UP=0,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
};

enum BoxMap { 
	MAP_NONE,
	MAP_WALL,
	MAP_DEST
};

class sokoban
{
public:
	sokoban();
	~sokoban();

public:
	void initMap(const char *fileName);
private:
	bool initBox();
private:
	int m_row;
	int m_col;
	int m_boxNum;
	int m_currentState;

	
	int Map[MAX_BUF_SIZE][MAX_BUF_SIZE];

	int m_reachBox;
private:
	Point_S  m_boxPosition[100];
	Point_S  m_peoplePosition;
private:
	AUX_RGBImageRec * initBmpData(const char * Filename);

public:
	int		setTextures();
	GLvoid  setList();
	void    showGame();

private:
	GLuint	m_texture[3];
	GLuint	m_box, m_dest;	
	
public:
	bool moveDown(void);
	bool moveUP(void);
	BOOL moveLeft(void);
	BOOL moveRight(void);
	void setX(GLfloat x);
	void setY(GLfloat y);
	void setZ(GLfloat z);
	void setReStart();
	void setNextLevel();
	void setUpLevel();

	BOOL isMoveOver(int Direct);
private:
	bool isBox(int i, int j);
	
	Point_S* GetBoxPosition(int i, int j);
private:
	GLfloat m_x;
	GLfloat m_y;
	GLfloat m_z;
	GLfloat zoom;

	GLfloat xpos;
	GLfloat ypos;
};


