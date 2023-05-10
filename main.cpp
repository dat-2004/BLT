#include "LTexture.hpp"
#include "Global.hpp"
#include "Utils.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Button.hpp"
#include "Constants.hpp"

using namespace std;

int main ( int argc , char* args[] )
{
    if ( !init() )
    {
        cout << "Failed to initialize!" << endl;
    }
    else
    {
        if ( !loadMedia() )
        {
            cout << "Failed to load media!" << endl;
        }
        else
        {
            bool playAgain = false;
            bool menu = true;
            bool quit = false;

            SDL_Event e;

            Mix_PlayMusic ( gMenuMusic , LOOP );

            while ( menu )
            {
                //the button
                Button escButton( 22 , 30 );

                while ( SDL_PollEvent ( &e ) != 0 )
                {
                    if ( e.type == SDL_QUIT )
                    {
                        quit = true;
                        menu = false;
                    }

                    //handle menu keys
                    handleMenuButton ( e , gInstructionTexture , escButton ,
                                      gPress , gInstructionMusic ,
                                      menu , playAgain , quit );
                }

                gMenuTexture.render ( 0 , 0 );

                SDL_RenderPresent ( gRenderer );
            }

            while ( playAgain )
            {
                //set random number for enemy positions
                srand((int) time(0));

                //game status
                int score = 0;
                int acceleration = 0;
                int time = 0;
                int frame = 0;
                string highscore = loadHighScoreFromFile ( "HighScore.txt" );

                //main loop flag
                bool quit = false;
                bool gameRunning = true;

                //the character
                Player knight;

                //the enemy
                Enemy stone( ON_GROUND );
                Enemy bat1( IN_AIR );
                Enemy bat2( MID_AIR );

                //Offset speed scrolling
                int OffsetSpeed_Ground = BASE_OFFSET_SPEED;
                vector <double> offsetSpeed_BG ( BACKGROUND_LAYERS , BASE_OFFSET_SPEED );

                //in game buttons
                Button PauseAndContinueButton ( 10 , 10 );

                //frame
                Uint32 framestart;
                int frameTime;

                Mix_PlayMusic ( gBackgroundMusic , LOOP );

                loadEnemyTexture ( stone , bat1 , bat2 , gBatClips );

                while ( !quit )
                {
                    if ( gameRunning )
                    {
                        framestart = SDL_GetTicks();

                        updateTimeAndScore ( time , acceleration , score );

                        while ( SDL_PollEvent ( &e ) != 0 )
                        {
                            if ( e.type == SDL_QUIT )
                            {
                                quit = true;
                                playAgain = false;
                                gameRunning = false;
                            }

                            handlePauseButton ( e , PauseAndContinueButton , gPause , gameRunning , quit , playAgain );

                            knight.handleEvent( e , gJump );
                        }

                        SDL_SetRenderDrawColor ( gRenderer , 0xFF , 0xFF , 0xFF , 0xFF );
                        SDL_RenderClear ( gRenderer );

                        ScrollingBackground ( offsetSpeed_BG , gBackgroundTexture );
                        ScrollingGround ( OffsetSpeed_Ground , acceleration , gGroundTexture );

                        knight.move();

                        knight.render();

                        stone.setPosition ( acceleration );
                        bat1.setPosition ( acceleration );
                        bat2.setPosition ( acceleration );

                        stone.render ();
                        bat1.render ( &gBatClips [ frame / 6 ] );
                        bat2.render ( &gBatClips [ frame / 6 ] );

                        PauseAndContinueButton.render ( &gPauseAndContinueClips[ PauseAndContinueButton.currentSprite ] , gPauseAndContinueTexture );

                        renderPlayerScore ( gYourScoreTextTexture , gScoreTexture , score );
                        renderHighScore ( gHighScoreTextTexture , gHiScoreTexture , highscore );

                        //check if the player hit the enemy
                        if ( checkCollision ( stone , knight ) || checkCollision ( bat1 , knight ) || checkCollision ( bat2 , knight ) )
                        {
                            Mix_HaltMusic();
                            Mix_PlayChannel( -1 , gGameOver , NOT_LOOP );
                            updateHighScore ( "HighScore.txt" , score , highscore );
                            quit = true;
                        }

                        SDL_RenderPresent ( gRenderer );

                        controlBatFrame ( frame );

                        frameTime = SDL_GetTicks() - framestart;

                        if ( FrameDelay > frameTime )
                        {
                            SDL_Delay ( FrameDelay - frameTime );
                        }
                    }

                }

                renderGameOver ( gGameOverTexture , gPress ,  e , playAgain , menu );

                if ( !playAgain )
                {
                    stone.free();
                    bat1.free();
                    bat2.free();
                }
            }

        }
    }

    close();

    return 0;
}
