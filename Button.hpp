#pragma once

#include "LTexture.hpp"
#include "Constants.hpp"

using namespace std;

class Button
{
public:
    ButtonSprite currentSprite;

    Button ( int x , int y );

    void render ( SDL_Rect* currrentClip , LTexture& gButtonTexture );
private:
    int mPosX , mPosY;
};
