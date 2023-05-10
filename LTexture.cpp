#include "LTexture.hpp"

using namespace std;

LTexture::LTexture()
{
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile ( string path )
{
    free();

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

bool LTexture::loadFromRenderedText ( string textureText , SDL_Color textColor )
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont , textureText.c_str() , textColor );
    if( textSurface == nullptr )
    {
        cout << "Unable to render text surface!" << TTF_GetError() << endl;
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface( gRenderer , textSurface );
        if( mTexture == nullptr )
        {
            cout << "Unable to create texture from rendered text!" << SDL_GetError() << endl;
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        SDL_FreeSurface( textSurface );
    }

    return mTexture != nullptr;
}

void LTexture::free()
{
    if ( mTexture != nullptr )
    {
        SDL_DestroyTexture ( mTexture );
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render( int x , int y , SDL_Rect* clip )
{
    SDL_Rect renderQuad = { x , y , mWidth , mHeight };

    if ( clip != nullptr )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy ( gRenderer , mTexture , clip , &renderQuad );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}
