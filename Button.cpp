#include "Button.hpp"

using namespace std;

Button::Button( int x , int y )
{
    mPosX = x;
    mPosY = y;

    currentSprite = BUTTON_NOT_PRESSED;
}

void Button::render( SDL_Rect* currentClips , LTexture& gButtonTexture )
{
    gButtonTexture.render ( mPosX , mPosY , currentClips );
}
