#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include "LTexture.h"
#include "EngineInitialization.h"

/* Constants*/
//The PNG image we will render
LTexture gFooTexture;
//The PNG image we will render
LTexture gBackgroundTexture;

bool loadMedia() 
{
	bool success{ true };

	//Load splash image
	success = gFooTexture.loadFromFile("data/images/foo.png", gRenderer);
	if (!success)
	{
		SDL_Log("Unable to load foo image!\n");
	}

	success = gBackgroundTexture.loadFromFile("data/images/background.png", gRenderer);
	if (!success)
	{
		SDL_Log("Unable to load background image!\n");
	}
	return success;
}

int main(int argc, char* args[])
{
	//Final exit code
	int exitCode{ 0 };
	std::string gameName = "SDL Tutorial";
	//Initialize
	if (!initEngine("SDL Tutorial"))
	{
		SDL_Log("Unable to initialize program!\n");
		exitCode = 1;
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			SDL_Log("Unable to load media!\n");
			exitCode = 2;
		}
		else
		{
			//the quit flag
			bool quit{ false };

			//The event data
			SDL_Event e;
			SDL_zero(e);

			//the main loop
			while (quit == false)
			{
				//Get event data
				while (SDL_PollEvent(&e))
				{
					//Quit Type
					if (e.type == SDL_EVENT_QUIT) 
					{
						quit = true;
					}
					else if (e.type == SDL_EVENT_KEY_DOWN)
					{
						//Set texture
						if (e.key.key == SDLK_UP)
						{
							SDL_Log("Press Key: UP\n");
						}
						else if (e.key.key == SDLK_DOWN)
						{
							SDL_Log("Press Key: Down\n");
						}
						else if (e.key.key == SDLK_LEFT)
						{
							SDL_Log("Press Key: Left\n");
						}
						else if (e.key.key == SDLK_RIGHT)
						{
							SDL_Log("Press Key: Right\n");
						}
					}
				}

				//Fill the background white
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render image on screen
				gBackgroundTexture.render(0.f, 0.f, gRenderer);
				gFooTexture.render(340.f, 190.f, gRenderer);


				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Clean up texture
	gFooTexture.destroy();
	gBackgroundTexture.destroy();
	//Clean up
	closeEngine();

	return exitCode;
}