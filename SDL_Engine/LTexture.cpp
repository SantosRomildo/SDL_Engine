#include "pch.h"
#include "framework.h"
#include "LTexture.h"


LTexture::LTexture() : mTexture{ nullptr }, mWidth{ 0 }, mHeight{ 0 }
{

}

LTexture::~LTexture()
{
	//Clean up texture
	destroy();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
	//Clean up texture if it already exists
	destroy();

	//Load surface
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		//Color key image
		if (!SDL_SetSurfaceColorKey(loadedSurface, true, SDL_MapSurfaceRGB(loadedSurface, 0x00, 0xFF, 0xFF)))
		{
			SDL_Log("Unable to color key! SDL error: %s", SDL_GetError());
		}
		else
		{
			//Create texture from surface
			mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
			if (mTexture == nullptr)
			{
				SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());

			}
			else
			{
				//Get image dimensions
				mWidth = loadedSurface->w;
				mHeight = loadedSurface->h;
			}
		}
		//Clean up loaded surface
		SDL_DestroySurface(loadedSurface);
	}

	//return success if texture loaded
	return mTexture != nullptr;
}

void LTexture::destroy() 
{
	//Clean up texture
	SDL_DestroyTexture(mTexture);
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;

}

void LTexture::render(float x, float y, SDL_Renderer* gRenderer)
{
	//Set texture position
	SDL_FRect dstRect = { x,y, static_cast<float>(mWidth), static_cast<float>(mHeight) };

	//Render texture
	SDL_RenderTexture(gRenderer, mTexture, nullptr, &dstRect);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}