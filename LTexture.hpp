#pragma once

#include "Global.hpp"
#include "Constants.hpp"

using namespace std;

class LTexture
{
public:

    LTexture();

    ~LTexture();

    bool loadFromFile ( string path );

    bool loadFromRenderedText( string textureText, SDL_Color textColor );

    void free();

    void render ( int x , int y , SDL_Rect* clip = nullptr );

    int getWidth();
    int getHeight();
private:

    SDL_Texture* mTexture;

    int mWidth, mHeight;
};
