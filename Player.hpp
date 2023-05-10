#pragma once

#include "LTexture.hpp"
#include "Global.hpp"
#include "Constants.hpp"

#define NORMAL 0
#define CROUCH 1

class Player
{
public:
    Player ();

    bool OnGround();

    void handleEvent ( SDL_Event& e , Mix_Chunk* gJump = nullptr );

    void move();

    void render();

    int getStatus();

    int getPosX();
    int getPosY();

private:
    int mPosX, mPosY;

    bool running, jumping , falling , crouching;

    int runCounter , jumpCounter , fallCounter , crouchCounter;

};
