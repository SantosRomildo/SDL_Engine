#pragma once

#include <string>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

class LTexture
{
public:
    //Initializes texture variables
    LTexture();

    //Cleans up texture variables
    ~LTexture();

    //Remove copy constructor
    LTexture(const LTexture&) = delete;

    //Remove copy assignment
    LTexture& operator=(const LTexture&) = delete;

    //Remove move constructor
    LTexture(LTexture&&) = delete;

    //Remove move assignment
    LTexture& operator=(LTexture&&) = delete;

    //Loads texture from disk
    bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

    //Cleans up texture
    void destroy();

    //Draws texture
    void render(float x, float y, SDL_Renderer* gRenderer);

    //Gets texture dimensions
    int getWidth();
    int getHeight();

private:
    //Contains texture data
    SDL_Texture* mTexture;

    //Texture dimensions
    int mWidth;
    int mHeight;
};