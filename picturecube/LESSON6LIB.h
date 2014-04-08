#include <gl\gl.h>		// Header File For The OpenGL32 Library
#include <gl\glu.h>		// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The GLaux Library
#include <registry.hpp>

//---------------------------------------------------------------------------
#ifndef LESSON6LIBH
#define LESSON6LIBH
//---------------------------------------------------------------------------
int speed;
GLvoid ReSizeGLScene(GLsizei width, GLsizei height);	// Resize And Initialize The GL Window
int InitGL(GLvoid);					// All Setup For OpenGL Goes Here
int DrawGLScene(GLvoid);						// Here's Where We Do All The Drawing
GLvoid KillGLWindow(HGLRC hRC,HDC hDC,HWND hWnd);	
BOOL CreateGLWindow(HWND hWnd,HDC *hDC,HGLRC	*hRC,int width, int height, int bits, bool *fullscreenflag);


#endif
