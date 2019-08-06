#include "../../_Header/Startup_And_Close/Window.h"
Window::Window()
{
	std::cout << "             SYSTEM-STARTUP             \n" << std::endl;

	initSystem();												// Setup engine subsystems. 
	setOpenGLAttributes();										// Set all attributes before context/window creation. 

	this->window = SDL_CreateWindow("L3G37VD ENGINE C++",		// Window name.
		SDL_WINDOWPOS_CENTERED,									// Window position.
		SDL_WINDOWPOS_CENTERED,									// ...
		windowWidth,											// Static window width defined.
		windowHeight,											// Static window height defined. 
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE				// Must be included for use with OpenGL constructs. 
		);														// Allows window to be resized i.e. move the window as you like. 
	

	if (this->window == nullptr)
	{
		std::cout << "ERROR: Unable to create window.\n" 
				  <<  "SDL_ERROR: " << SDL_GetError() 
				  <<  std::endl;
		currentState = EngineState::EXIT;						// Global ENUM to determine current state of engine. 
	}
	else
	{
		systemStateCheck();										// Check all SDL sub systems. 
		initOpenGL(this->window);								// Startup and attach GL Context.
		SDL_GL_MakeCurrent(this->window, this->GL_Context);		// Forcing the window and context to map. 
		SDL_Check();											// Checking all assigned values within SDL. 
	}

	if (currentState == EngineState::EXIT)						// if the window is ok, but something goes wrong with SDL, force quit all systems. 
	{
		shutDown();
	}
}

Window::~Window()
{
	
}

void Window::gameLoop()
{
	while(currentState == EngineState::RUNNING)
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)						// broken 
			{
				currentState = EngineState::EXIT;
			}

			handleEvents();
			update();
			render();
		}

	cleanUp();				// Clean up the system once game ends. 
}
void Window::handleEvents()
{

}
void Window::update()
{

}
void Window::render()
{
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);


	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(this->window);
}
void Window::cleanUp()
{
	SDL_GL_DeleteContext(GL_Context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void Window::shutDown()
{
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	atexit(SDL_Quit);
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
		printf("| SDL_Audio...............	  ENABLED |\n");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Audio\n");
		currentState = EngineState::EXIT;
	}

	// Events System.
	if (subSystem_Init & SDL_INIT_EVENTS)
	{
		printf("| SDL_Events..............	  ENABLED |\n");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Events\n");
		currentState = EngineState::EXIT;
	}

	// Game Controller System.
	if (subSystem_Init & SDL_INIT_GAMECONTROLLER)
	{
		printf("| SDL_GameController......	  ENABLED |\n");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_GameController\n");
		currentState = EngineState::EXIT;
	}

	// Haptic System.
	if (subSystem_Init & SDL_INIT_HAPTIC)
	{
		printf("| SDL_Haptic..............	  ENABLED |\n");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Haptic\n");
		currentState = EngineState::EXIT;
	}

	// SDL_JoyStick System.
	if (subSystem_Init & SDL_INIT_JOYSTICK)
	{
		printf("| SDL_JoyStick............	  ENABLED |\n");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_JoyStick\n");
		currentState = EngineState::EXIT;
	}

	// SDL_Timer System.
	if (subSystem_Init & SDL_INIT_TIMER)
	{
		printf("| SDL_Timer...............	  ENABLED |\n");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Timer\n");
		currentState = EngineState::EXIT;
	}

	// SDL_Video System.
	if (subSystem_Init & SDL_INIT_VIDEO)
	{
		printf("| SDL_Video...............	  ENABLED |\n");
		counter++;
	}
	else
	{
		printf("Error: Failed to initialise SDL_Video\n");
		currentState = EngineState::EXIT;
	}

	if (counter == 7)
	{
		printf("|_______ALL SDL SUB-SYSTEMS ACTIVE________|\n\n");
		currentState = EngineState::RUNNING;																// Current engine state is positive. 
	}
}
void Window::SDL_Check()
{
	std::cout << "___________ SDL ATTRIBUTE CHECKS __________" << std::endl;

	SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &r);												// Find current SDL Red value. 
	std::cout << "| Red Size............................. " << r << " |" << std::endl;

	SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &g);												// Find current SDL Green value. 
	std::cout << "| Green Size........................... " << g << " |" << std::endl;

	SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &b);												// Find current SDL Blue value. 
	std::cout << "| Blue Size............................ " << b << " |" << std::endl;

	SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &a);												// Find current SDL Alpha value. 
	std::cout << "| Alpha Size........................... " << a << " |" << std::endl;

	SDL_GL_GetAttribute(SDL_GL_BUFFER_SIZE, &buffer);
	std::cout << "| SDL Buffer Size...................... " << buffer << "|" << std::endl;

	SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &dblBuffer);									// Enabling double buffering for graphics. 
	if (dblBuffer != 1)
	{
		std::cout << "| SDL Double Buffer............. DISABLED |" << std::endl;
		currentState = EngineState::EXIT;
	}
	else
	{
		std::cout << "| SDL Double Buffer............... ENABLED|" << std::endl;
	}

	SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &depthSize);										// Forcing depth to be 16 or 24 depending on machine, anyhting over 24 can cause issues. 
	if ((depthSize == 16) || (depthSize == 24))
	{
		std::cout << "| SDL Depth Size....................... " << depthSize 
				  << "|" << std::endl;

	}
	else
	{
		std::cout << "| SDL Depth Size................... ERROR |" << std::endl;
		currentState = EngineState::EXIT;
	}
	
	std::cout << "| GL_Version.......... "
		<< glGetString(GL_VERSION) << "|" << std::endl;								// Find current GL context version.

	std::cout << "|_________________________________________|" << std::endl;

}
void Window::initOpenGL(SDL_Window* w)
{
	GL_Context = SDL_GL_CreateContext(w);
	if (GL_Context == nullptr)
	{
		std::cout << "Error: Could not deploy GL CONTEXT."
			<< SDL_GetError()
			<< std::endl;
		currentState = EngineState::EXIT;
		SDL_Quit();
	}
	else
	{
		// Initialise GLEW
		glewExperimental = GL_TRUE;
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{
			std::cout << "Error initialising GLEW! " << glewGetErrorString(glewError) << std::endl;
			currentState = EngineState::EXIT;
			SDL_Quit();
		}

		// Using Vsync 
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			std::cout << "Warning: unable to set Vsync! SDL Error: " << SDL_GetError() << std::endl;
			currentState = EngineState::EXIT;
			SDL_Quit();
		}

		// add initGLU here? 
		
	}

}
void Window::setOpenGLAttributes()
{
	 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);									// Forcing the context version to be 3.3 removing legacy code. 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);									// ... 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);			// Forcing the engine to use only modern openGL functions.

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);												// All values are a minimum allowance, can be higher on different machines. 
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);												// i.e. 8 is miniumum, some machines might have 16. 
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void Window::printProgramLog(GLuint program)
{
}

void Window::printShaderLog(GLuint shader)
{
}

