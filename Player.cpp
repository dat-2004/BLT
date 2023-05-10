#include "Player.hpp"

using namespace std;

Player::Player()
{
    mPosX = 250;
    mPosY = GROUND;

    running = true;

    falling = jumping = crouching = false;

    runCounter = jumpCounter = fallCounter = crouchCounter = 0;
}

bool Player::OnGround()
{
    return mPosY == GROUND;
}

void Player::handleEvent ( SDL_Event& e , Mix_Chunk* gJump )
{
    if ( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch ( e.key.keysym.sym )
        {
        case SDLK_SPACE:
            {
                if ( OnGround() )
                {
                    Mix_PlayChannel ( -1 , gJump , NOT_LOOP );
                    running = false;
                    jumping = true;
                    crouching = false;
                }
                break;
            }
        case SDLK_s:
            {
                if ( OnGround() )
                {
                    running = false;
                    crouching = true;
                }
                break;
            }
        }
    }

    else if ( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch ( e.key.keysym.sym )
        {
        case SDLK_s:
            {
                if ( OnGround() )
                {
                    crouching = false;
                    running = true;
                }
                break;
            }
        }
    }
}

void Player::move()
{
    //player jump
    if ( jumping && mPosY >= MAX_HEIGHT )
    {
        mPosY -= JUMP_VEL;
    }

    //if player reaches the max height
    if ( mPosY <= MAX_HEIGHT )
    {
        jumping = false;
        falling = true;
        running = false;
    }

    //player falling
    if ( falling && mPosY < GROUND )
    {
        mPosY += FALL_VEL;
    }

    if ( OnGround() )
    {
        if ( falling )
        {
            falling = false;
            running = true;
            crouching = false;
        }
    }
}

void Player::render()
{
    if ( running )
    {
        gRunTexture.render( mPosX , mPosY , &gRunClips[ runCounter / 10 ] );
        runCounter++;
        if ( runCounter / 10 >= RUN_ANIMATION_FRAMES ) runCounter = 0;

    }

    if ( jumping )
    {
        gJumpTexture.render( mPosX , mPosY , &gJumpClips[ jumpCounter / 3 ] );
        jumpCounter++;
        if ( jumpCounter / 3 >= JUMP_ANIMATION_FRAMES ) jumpCounter = 0;
    }

    if ( falling )
    {
        gFallTexture.render( mPosX , mPosY , &gFallClips[ fallCounter / 3 ] );
        fallCounter++;
        if ( fallCounter / 3 >= FALL_ANIMATION_FRAMES ) fallCounter = 0;
    }

    if ( crouching )
    {
        gCrouchTexture.render( mPosX , mPosY , &gCrouchClips[ crouchCounter / 8 ] );
        crouchCounter++;
        if ( crouchCounter / 8 >= CROUCH_ANIMATION_FRAMES ) crouchCounter = 0;
    }
}

int Player::getStatus()
{
    int status;

    if ( running || jumping || falling )
    {
        status = NORMAL;
    }
    else if ( crouching )
    {
        status = CROUCH;
    }

    return status;
}

int Player::getPosX()
{
    return mPosX;
}

int Player::getPosY()
{
    return mPosY;
}
