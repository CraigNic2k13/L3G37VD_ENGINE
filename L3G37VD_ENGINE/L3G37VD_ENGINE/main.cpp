#include <iostream>
#include <SDL.h>
#include <btBulletDynamicsCommon.h>

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL NOT WORKING" << SDL_GetError() << std::endl;
	}
	
	

	btBoxShape* box = new btBoxShape(btVector3(1, 1, 1));
	system("pause");
	return EXIT_SUCCESS;

}