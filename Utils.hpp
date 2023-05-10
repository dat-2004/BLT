#pragma once

#include "LTexture.hpp"
#include "Global.hpp"
#include "Constants.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Button.hpp"

using namespace std;

extern bool init();

extern bool loadMedia();

extern void close();

extern void ScrollingBackground( vector <double> &offsetSpeed , LTexture(&gBackgroundTexture)[ BACKGROUND_LAYERS ] );

extern void ScrollingGround ( int& speed , const int acceleration , LTexture &gGroundTexture );

extern bool checkCollision ( Enemy enemy , Player knight );

extern void handleMenuButton ( SDL_Event e , LTexture& gInstructionTexture , Button& escButton ,
                              Mix_Chunk* gPress , Mix_Music* gInstructionMusic ,
                              bool& menu , bool& play , bool& quit );

extern void handleContinueButton ( SDL_Event e , Button& PauseAndContinueButton , bool& gameRunning , bool& quit , bool& playAgain );

extern void handlePauseButton ( SDL_Event e , Button& PauseAndContinueButton , Mix_Chunk* gPause , bool& gameRunning , bool& quit , bool& playAgain );

extern void loadEnemyTexture ( Enemy& stone , Enemy& bat1 , Enemy& bat2 , SDL_Rect(&gBatClips)[ BAT_FRAMES ] );

extern string loadHighScoreFromFile ( string path );

extern void updateHighScore ( string path , const int& score , const string& old_high_score );

extern int updateTimeAndScore ( int& time , int& speed , int& score );

extern void renderPlayerScore ( LTexture& gYourScoreTextTexture , LTexture& gScoreTexture , const int& score );

extern void renderHighScore ( LTexture& gHighScoreTextTexture , LTexture& gHiScoreTexture , const string& highScore );

extern void renderGameOver ( LTexture& gGameOverTexture , Mix_Chunk* gPress , SDL_Event e , bool& playAgain , bool& menu );

extern void controlBatFrame ( int& frame );
