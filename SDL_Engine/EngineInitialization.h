#include "pch.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>

/* Constants*/
//Screen dimension constants
constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

/*Function Prototypes*/
//Starts up SDL and creates window
bool initEngine(const char* gameName);

//Frees media and shuts down sdl
void closeEngine();

/* Global Variables */
//The window we'll be rendering to
SDL_Window* gWindow{ nullptr };
//The surface contained by the window
SDL_Surface* gScreenSurface{ nullptr };
//The image we will load and show on the screen
SDL_Surface* gHelloWorld{ nullptr };
//The renderer used to draw to the window
SDL_Renderer* gRenderer{ nullptr };

bool initEngine(const char* gameName)
{
	//initialization flag
	bool success{ true };

	//Initialize SDL
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window with renderer
		if (!SDL_CreateWindowAndRenderer(gameName, kScreenWidth, kScreenHeight, 0, &gWindow, &gRenderer))
		{
			SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
			success = false;
		}
	}
	return success;
}

void closeEngine()
{
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}