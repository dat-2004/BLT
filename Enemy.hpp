#pragma once

#include "LTexture.hpp"
#include "Global.hpp"
#include "Constants.hpp"

#define ON_GROUND 0
#define MID_AIR 1
#define IN_AIR 2

using namespace std;

class Enemy
{
public:
    Enemy( int _type = 0 );

    void free();

    bool loadFromFile ( string path );

    void setPosition( const int& acceleration );

    void render ( SDL_Rect* clip = nullptr );

    int getType();

    int getPosX();
    int getPosY();

    int getWidth();
    int getHeight();

private:
    SDL_Texture* mTexture;

    int type;

    int mPosX , mPosY;

    int mWidth , mHeight;
};
