#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include "../../_Header/Startup_And_Close/EngineState.h"


class Window
{
public:
	Window();
	~Window();

	void gameLoop();


private:
	// Methods.
	void			handleEvents();
	void			update();
	void			render();
	void			cleanUp();
	void			shutDown();

	void			initSystem();
	void			systemStateCheck();
	void			SDL_Check();
	void			initOpenGL(SDL_Window* w);
	void			setOpenGLAttributes();

	void			printProgramLog(GLuint program);
	void			printShaderLog(GLuint shader);

	int				windowWidth = 1200;
	int				windowHeight = 800;


	// Variables. 
	SDL_Window*		window;
	SDL_GLContext	GL_Context;
	Uint32			subSystem_Init;
	EngineState		currentState;
	SDL_Event		e;
	GLuint			gProgram = 0;
	GLint			gVertexPos2DLocation = -1;
	GLuint			gVBO = 0;
	GLuint			gIBO = 0;
	int r, g, b, a, minor, major, visual, depthSize, stencil, buffer, dblBuffer, core, flags;
};
#endif  WINDOW_H

