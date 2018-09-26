#include "../../_Header/Startup_And_Close/Window.h"
Window::Window()
{
	std::cout << "             SYSTEM-STARTUP             \n" << std::endl;

	initSystem();												// Setup engine subsystems. 
	setOpenGLAttributes();										// Set all attributes before context/window creation. 

	this->window = SDL_CreateWindow("L3G37VD ENGINE C++",		// Window name.
								  SDL_WINDOWPOS_CENTERED,		// Window position.
								  SDL_WINDOWPOS_CENTERED,		// ...
											 windowWidth,		// Static window width defined.
											windowHeight,		// Static window height defined. 
									  SDL_WINDOW_OPENGL |       // Must be included for use with OpenGL constructs. 
								   SDL_WINDOW_RESIZABLE |       // Allows window to be resized i.e. move the window as you like. 
								   SDL_WINDOW_MINIMIZED |		// Allow the window to be minimised. 
								    SDL_WINDOW_MAXIMIZED);		// Allow the window to be maximised. 

	if (!window)
	{
		std::cout << "ERROR: Unable to create window.\n" 
				  <<  "SDL_ERROR: " << SDL_GetError() 
				  <<  std::endl;
		isRunning = false;
	}
	else
	{
		systemStateCheck();										// Check all SDL sub systems. 
		initOpenGL(window);										// Startup and attach GL Context.
		SDL_GL_SetSwapInterval(1);
		glewExperimental = GL_TRUE;
		glewInit();
		SDL_GL_MakeCurrent(this->window, this->GL_Context);		// Forcing the window and context to map. 
		SDL_Check();											// Checking all assigned values within SDL. 
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
	std::cout << "_________ SDL SUB-SYSTEM CHECKS ___________" << std::endl;

	subSystem_Init = SDL_WasInit(SDL_INIT_EVERYTHING);										// See if all systems are active. 

	// Audio System.																		// Throw flags to see if systems have initialised or failed. 
	if (subSystem_Init & SDL_INIT_AUDIO)
	{
		printf("| SDL_Audio............... is initialised |\n");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Audio\n");
		isRunning = false;
	}

	// Events System.
	if (subSystem_Init & SDL_INIT_EVENTS)
	{
		printf("| SDL_Events.............. is initialised |\n");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Events\n");
		isRunning = false;
	}

	// Game Controller System.
	if (subSystem_Init & SDL_INIT_GAMECONTROLLER)
	{
		printf("| SDL_GameController...... is initialised |\n");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_GameController\n");
		isRunning = false;
	}

	// Haptic System.
	if (subSystem_Init & SDL_INIT_HAPTIC)
	{
		printf("| SDL_Haptic.............. is initialised |\n");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Haptic\n");
		isRunning = false;
	}

	// SDL_JoyStick System.
	if (subSystem_Init & SDL_INIT_JOYSTICK)
	{
		printf("| SDL_JoyStick............ is initialised |\n");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_JoyStick\n");
		isRunning = false;
	}

	// SDL_Timer System.
	if (subSystem_Init & SDL_INIT_TIMER)
	{
		printf("| SDL_Timer............... is initialised |\n");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Timer\n");
		isRunning = false;
	}

	// SDL_Video System.
	if (subSystem_Init & SDL_INIT_VIDEO)
	{
		printf("| SDL_Video............... is initialised |\n");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Video\n");
		isRunning = false;
	}

	if (counter == 7)
	{
		printf("|_______ALL SDL SUB-SYSTEMS ACTIVE________|\n\n");
		isRunning = true;																		// Current engine state is positive. 
	}
}
void Window::SDL_Check()
{
	std::cout << "___________ SDL ATTRIBUTE CHECKS __________" << std::endl;

	SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &r);												// Find current SDL Red value. 
	std::cout << "| Red Size......................... " << r << std::endl;

	SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &g);												// Find current SDL Green value. 
	std::cout << "| Green Size....................... " << g << std::endl;

	SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &b);												// Find current SDL Blue value. 
	std::cout << "| Blue Size........................ " << b << std::endl;

	SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &a);												// Find current SDL Alpha value. 
	std::cout << "| Alpha Size....................... " << a << std::endl;

	SDL_GL_GetAttribute(SDL_GL_BUFFER_SIZE, &buffer);
	std::cout << "| SDL Buffer Size.................. " << buffer << std::endl;

	SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &dblBuffer);
	if (dblBuffer != 1)
	{
		std::cout << "| SDL Double Buffer................ DISABLED" << std::endl;
		isRunning = false;
	}
	else
	{
		std::cout << "| SDL Double Buffer................ ENABLED" << std::endl;
	}

	SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &depthSize);
	std::cout << "| SDL Depth Size................... " << depthSize << std::endl;

	std::cout << "| GL_Version........... "
		<< glGetString(GL_VERSION) << std::endl;											// Find current GL context version.

	std::cout << "Finishing adding all the attribute checks to the window to see what's active and working etc. " << std::endl;



	// http://www.devshed.com/c/a/multimedia/using-opengl-with-sdl-for-game-programming/


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
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);									// ... 

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);												// All values are a minimum allowance, can be higher on different machines. 
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);												// i.e. 8 is miniumum, some machines might have 16. 
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

