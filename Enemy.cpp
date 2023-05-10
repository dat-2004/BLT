#include "Enemy.hpp"

Enemy::Enemy( int _type )
{
    mWidth = mHeight = 0;

    type = _type;

    if ( type == ON_GROUND )
    {
        mPosX = + ( SCREEN_WIDTH ) + ( rand() % ( SCREEN_WIDTH + 50 ) );
        mPosY = GROUND + 103;
    }
    else if ( type == MID_AIR )
    {
        mPosX = + ( SCREEN_WIDTH + 100 ) + ( rand() % ( SCREEN_WIDTH + 200 ) );
        mPosY = GROUND + 60;
    }
    else if ( type == IN_AIR )
    {
        mPosX = + ( SCREEN_WIDTH + 200 ) + ( rand() % ( SCREEN_WIDTH + 300 ) );
        mPosY = GROUND + 20;
    }
}

void Enemy::free()
{
    mWidth = mHeight = 0;
    mPosX = mPosY = 0;
    type = 0;
    if ( mTexture != nullptr )
    {
        SDL_DestroyTexture ( mTexture );
        mTexture = nullptr;
    }

}

bool Enemy::loadFromFile ( string path )
{
    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load ( path.c_str() );
    if ( loadedSurface == nullptr )
    {
        cout << "Unable to load image!" << IMG_GetError() << endl;
    }
    else
    {
        SDL_SetColorKey ( loadedSurface , SDL_TRUE , SDL_MapRGB ( loadedSurface->format , 0 , 255 , 255 ) );

        newTexture = SDL_CreateTextureFromSurface ( gRenderer , loadedSurface );
        if ( newTexture == nullptr )
        {
            cout << "Unable to create texture from surface!" << SDL_GetError() << endl;
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        SDL_FreeSurface ( loadedSurface );
    }

    mTexture = newTexture;
    return mTexture != nullptr;
}

void Enemy::setPosition( const int& acceleration )
{
    mPosX += - ( ENEMY_SPEED + acceleration );
    if ( mPosX + mWidth < 0 )
    {
        if ( type == ON_GROUND )
        {
            mPosX = + ( SCREEN_WIDTH ) + ( rand() % ( SCREEN_WIDTH + 50 ) );
        }
        else if ( type == MID_AIR )
        {
            mPosX = + ( SCREEN_WIDTH + 250 ) + ( rand() % ( SCREEN_WIDTH + 300 ) );
        }
        else if ( type == IN_AIR )
        {
            mPosX = + ( SCREEN_WIDTH + 450 ) + ( rand() % ( SCREEN_WIDTH + 500 ) );
        }

    }
}

void Enemy::render ( SDL_Rect* clip )
{
    SDL_Rect renderQuad = { mPosX , mPosY , mWidth , mHeight };

    if ( clip != nullptr )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy ( gRenderer , mTexture , clip , &renderQuad );
}

int Enemy::getType()
{
    return type;
}

int Enemy::getPosX()
{
    return mPosX;
}

int Enemy::getPosY()
{
    return mPosY;
}

int Enemy::getWidth()
{
    return mWidth;
}

int Enemy::getHeight()
{
    return mHeight;
}
