#include "Global.hpp"

SDL_Window* gWindow = nullptr;

SDL_Renderer* gRenderer = nullptr;

TTF_Font* gFont = nullptr;

LTexture gRunTexture;
SDL_Rect gRunClips [ RUN_ANIMATION_FRAMES ];

LTexture gJumpTexture;
SDL_Rect gJumpClips [ JUMP_ANIMATION_FRAMES ];

LTexture gFallTexture;
SDL_Rect gFallClips [ FALL_ANIMATION_FRAMES ];

LTexture gCrouchTexture;
SDL_Rect gCrouchClips [ CROUCH_ANIMATION_FRAMES ];

LTexture gBackgroundTexture[ BACKGROUND_LAYERS ];

LTexture gGroundTexture;

SDL_Rect gBatClips[ BAT_FRAMES ];

LTexture gMenuTexture;

LTexture gInstructionTexture;

LTexture gPauseAndContinueTexture;
SDL_Rect gPauseAndContinueClips[ TOTAL_BUTTON ];

LTexture gEscTexture;
SDL_Rect gEscClips[ TOTAL_BUTTON ];

LTexture gYourScoreTextTexture;
LTexture gHighScoreTextTexture;

LTexture gScoreTexture;
LTexture gHiScoreTexture;

LTexture gGameOverTexture;

SDL_Color textColor = { 255 , 255 , 255 };

Mix_Chunk* gJump = nullptr;
Mix_Chunk* gPress = nullptr;
Mix_Chunk* gPause = nullptr;
Mix_Chunk* gGameStart = nullptr;
Mix_Chunk* gGameOver = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Music* gInstructionMusic = nullptr;
Mix_Music* gBackgroundMusic = nullptr;
