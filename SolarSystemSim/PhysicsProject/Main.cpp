//======================================================================
//File: Main.cpp
//Author: Matt Struble
//======================================================================
#include <iostream>
#include <Windows.h>
#include <gl\glut.h>
#include "GlutTime.h"
#include "Game.h"
#include <time.h>
//======================================================================
using namespace std;
//======================================================================
void init();
void idle();
void display();
void cleanUp();
void update(float gameTime);
void initalize();
void handleMouse(int x, int y);
void handleMousePassive(int x, int y);
void handleKeyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
//======================================================================
GlutTime* gp_GlutTime;
Game* gp_Game;

const Vector2D INITIAL_SCREEN_SIZE = Vector2D(720, 720);
Vector2D g_ScreenSize = INITIAL_SCREEN_SIZE;

const int ESCAPE_KEY = 27;

bool g_MouseFree;
int g_Window;
//======================================================================
int main(int argc, char** argv) {
	
	glutInit(&argc, argv);                 
	initalize();

	srand(time(NULL));

	return 0;
}

//--------------------------------------------------------------------------------
void initalize()
{
	atexit(cleanUp);

	srand((unsigned int)time(0));

	gp_GlutTime = new GlutTime();
	gp_GlutTime->Init();

	gp_Game = new Game();
	gp_Game->Init(g_ScreenSize.X, g_ScreenSize.Y);

	glutInitWindowSize(g_ScreenSize.X, g_ScreenSize.Y);
	glutInitWindowPosition(0, 0);
	g_Window = glutCreateWindow("Solar System Simulation");
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	glutIgnoreKeyRepeat(1);
	glutPassiveMotionFunc(handleMouse);
	glutKeyboardFunc(handleKeyboard);
	glutReshapeFunc(reshape);

	glutSetCursor(GLUT_CURSOR_NONE);
	SetCursorPos((int)(g_ScreenSize.X / 2.0f), (int)(g_ScreenSize.Y / 2.0f));

	glutMainLoop(); 

	g_MouseFree = false;
}

//--------------------------------------------------------------------------------
void idle()
{
	//glutSetWindow(g_Window);
	if (gp_GlutTime->UpdateTime())
	{
		update(gp_GlutTime->GetDeltaTime());
		gp_GlutTime->IncrementFrame();
	}
}

//--------------------------------------------------------------------------------
void update(float gameTime)
{
	gp_Game->Update(gameTime);
	glutPostRedisplay(); 

	//if (!g_MouseFree)
		//SetCursorPos((int)(g_ScreenSize.X / 2.0f), (int)(g_ScreenSize.Y / 2.0f));
}

//--------------------------------------------------------------------------------
void handleMouse(int x, int y)
{
	//if (!g_MouseFree)
		gp_Game->HandleMouse(Vector2D((float)x, (float)y));
}

void handleMousePassive(int x, int y)
{
	gp_Game->HandleMousePassive(x, y);
}

//--------------------------------------------------------------------------------
void handleKeyboard(unsigned char key, int x, int y)
{
	gp_Game->HandleKey(key);

	if (key == ESCAPE_KEY)
	{
		exit(0);
	}

	if (key == 'l' || key == 'L')
	{
		g_MouseFree = !g_MouseFree;

		if (g_MouseFree) glutSetCursor(GLUT_CURSOR_INHERIT);
		else glutSetCursor(GLUT_CURSOR_NONE);
	}
}



//--------------------------------------------------------------------------------
void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	gp_Game->Draw();

	glutSwapBuffers();
}

//--------------------------------------------------------------------------------
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
		glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
		glMatrixMode(GL_MODELVIEW);

}

//--------------------------------------------------------------------------------
void cleanUp()
{
	delete gp_GlutTime;
	gp_GlutTime = NULL;

	if (gp_Game != NULL)
	{
		gp_Game->CleanUp();
	}
	delete gp_Game;
	gp_Game = NULL;
}
//================================================================================