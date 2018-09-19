#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include <SDL.h>
#include <glew.h>
class Window
{
public:
	Window();
	~Window();

	void			handleEvents();
	void			update();
	void			render();
	void			cleanUp();
	bool			running();

private:
	// Methods.
	void			initSystem();
	void			systemStateCheck();
	void			initOpenGL(SDL_Window* w);
	void			setOpenGLAttributes();

	int windowWidth = 1200;
	int windowHeight = 800;


	// Variables. 
	bool			isRunning;
	SDL_Window*		window;
	SDL_GLContext	GL_Context;
	Uint32			subSystem_Init;
};
#endif  WINDOW_H

