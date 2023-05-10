#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define BASE_OFFSET_SPEED 0

#define LOOP -1
#define NOT_LOOP 0

using namespace std;

//The window dimensions
const int SCREEN_WIDTH = 1152;
const int SCREEN_HEIGHT = 648;

//player velocity
const int JUMP_VEL = 4;
const int FALL_VEL = 4;
const int MAX_HEIGHT = 181;
const int GROUND = 356;

//animation frame
const int RUN_ANIMATION_FRAMES = 10;
const int JUMP_ANIMATION_FRAMES = 3;
const int FALL_ANIMATION_FRAMES = 3;
const int CROUCH_ANIMATION_FRAMES = 8;
const int BAT_FRAMES = 6;

//the background layers and its offset speed
const int BACKGROUND_LAYERS = 4;

const double LAYER_1_SPEED = 0.0;
const double LAYER_2_SPEED = 0.25;
const double LAYER_3_SPEED = 0.5;
const double LAYER_4_SPEED = 0.75;

//the ground and its offset speed
const int GROUND_SPEED = 2;
const int ENEMY_SPEED = 2;
const int acceleration = 0;

//total button
const int TOTAL_BUTTON = 2;

//Frame rate
const int FPS = 60;
const int FrameDelay = 1000 / FPS;

enum ButtonSprite
{
	BUTTON_NOT_PRESSED = 0,
	BUTTON_PRESSED = 1,
	BUTTON_TOTAL = 2
};
