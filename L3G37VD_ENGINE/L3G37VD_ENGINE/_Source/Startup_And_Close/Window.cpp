#include "../../_Header/Startup_And_Close/Window.h"
Window::Window()
{
	initSystem();										// Setup engine subsystems. 
	setOpenGLAttributes();								// Set all attributes before context/window creation. 

	this->window = SDL_CreateWindow("L3G37VD ENGINE C++", 
								  SDL_WINDOWPOS_CENTERED, 
							      SDL_WINDOWPOS_CENTERED, 
											 windowWidth, 
											windowHeight, 
									  SDL_WINDOW_OPENGL);

	if (!window)
	{
		std::cout << "ERROR: Unable to create window.\n" 
				  <<  SDL_GetError() 
				  <<  std::endl;
		isRunning = false;
	}
	else
	{
		systemStateCheck();
		initOpenGL(window);										// Startup and attach GL Context.
		SDL_GL_SetSwapInterval(1);
		glewExperimental = GL_TRUE;
		glewInit();
	}
}

Window::~Window()
{
	SDL_GL_DeleteContext(GL_Context);
	SDL_DestroyWindow(window);
}

void Window::handleEvents()
{

}

void Window::update()
{

}

void Window::render()
{

}

void Window::cleanUp()
{

}

bool Window::running()
{
	return false;
}


/* Private Class Methods */
void Window::initSystem()																	// Initialise SDL subsystems for window. 
{
	SDL_Init(SDL_INIT_AUDIO  | SDL_INIT_EVENTS   | SDL_INIT_GAMECONTROLLER |				// Starts them all up.
			 SDL_INIT_HAPTIC | SDL_INIT_JOYSTICK | SDL_INIT_TIMER	       |
			 SDL_INIT_VIDEO);

}
void Window::systemStateCheck()
{
	int counter = 0;

	subSystem_Init = SDL_WasInit(SDL_INIT_EVERYTHING);										// See if all systems are active. 

	// Audio System.																		// Throw flags to see if systems have initialised or failed. 
	if (subSystem_Init & SDL_INIT_AUDIO)
	{
		printf("SDL_Audio is initialised");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Audio");
		isRunning = false;
	}

	// Events System.
	if (subSystem_Init & SDL_INIT_EVENTS)
	{
		printf("SDL_Events is initialised");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Events");
		isRunning = false;
	}

	// Game Controller System.
	if (subSystem_Init & SDL_INIT_GAMECONTROLLER)
	{
		printf("SDL_GameController is initialised");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_GameController");
		isRunning = false;
	}

	// Haptic System.
	if (subSystem_Init & SDL_INIT_HAPTIC)
	{
		printf("SDL_Haptic is initialised");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Haptic");
		isRunning = false;
	}

	// SDL_JoyStick System.
	if (subSystem_Init & SDL_INIT_JOYSTICK)
	{
		printf("SDL_JoyStick is initialised");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_JoyStick");
		isRunning = false;
	}

	// SDL_Timer System.
	if (subSystem_Init & SDL_INIT_TIMER)
	{
		printf("SDL_Timer is initialised");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Timer");
		isRunning = false;
	}

	// SDL_Video System.
	if (subSystem_Init & SDL_INIT_HAPTIC)
	{
		printf("SDL_Haptic is initialised");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Haptic");
		isRunning = false;
	}

	if (counter == 7)
	{
		printf("All Systems Initialised.");
		isRunning = true;																		// Current engine state is positive. 
	}
}
void Window::initOpenGL(SDL_Window* w)
{
	GL_Context = SDL_GL_CreateContext(w);
	if (!GL_Context)
	{
		std::cout << "Error: Could not deploy GL CONTEXT."
			<< SDL_GetError()
			<< std::endl;
		SDL_Quit();
	}
}
void Window::setOpenGLAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);			// Forcing the engine to use only modern openGL functions. 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);									// Forcing the context version to be 3.2 removing legacy code. 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);									// ... 

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

}

