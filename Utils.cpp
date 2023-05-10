#include "Utils.hpp"

bool init()
{
    //initialization flag
    bool success = true;

    //initialize SDL
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "Could not initialize SDL!" << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        //set filtering texture to linear
        if ( !SDL_SetHint ( SDL_HINT_RENDER_SCALE_QUALITY , "1" ) )
        {
            cout << "Warning: Linear filtering texture not enabled!" << endl;
        }

        //create window
        gWindow = SDL_CreateWindow ( "Knight Jumper" , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_SHOWN );
        if ( gWindow == nullptr )
        {
            cout << "Could not create window!" << endl;
            success = false;
        }
        else
        {
            //create renderer from window
            gRenderer = SDL_CreateRenderer ( gWindow , -1 , SDL_RENDERER_ACCELERATED  );
            if ( gRenderer == nullptr )
            {
                cout << "Could not create renderer!" << endl;
                success = false;
            }
            else
            {
                //set renderer color
                SDL_SetRenderDrawColor ( gRenderer , 0xFF , 0xFF , 0xFF , 0xFF );

                //initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if ( !( IMG_Init ( imgFlags ) && imgFlags ) )
                {
                    cout << "Could not initialize SDL image!" << IMG_GetError() << endl;
                    success = false;
                }

                //initialize mixer
                if ( Mix_OpenAudio( 44100 , MIX_DEFAULT_FORMAT , 2 , 2048 ) < 0 )
                {
                    cout << "Could not initialize SDL mixer!" << Mix_GetError() << endl;
                }

                //initialize SDL ttf
                if( TTF_Init() == -1 )
                {
                    cout << "SDL_ttf could not initialize!" << TTF_GetError() << endl;
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load player running texture
    if ( !gRunTexture.loadFromFile ( "assets/player/_Run.png") )
    {
        cout << "Unable to load player running texture!" << endl;
        success = false;
    }
    else
    {
        for (int i = 0 ; i < RUN_ANIMATION_FRAMES ; i++ )
        {
            gRunClips[ i ] = { i * 240 , 0 , 240 , 160 };
        }
    }

    //Load player jumping texture
    if ( !gJumpTexture.loadFromFile ( "assets/player/_Jump.png") )
    {
        cout << "Unable to load player jumping texture!" << endl;
        success = false;
    }
    else
    {
        for ( int i = 0 ; i < JUMP_ANIMATION_FRAMES ; i++ )
        {
            gJumpClips[ i ] = { i * 240 , 0 , 240 , 160 };
        }
    }

    //Load player falling texture
    if ( !gFallTexture.loadFromFile ( "assets/player/_Fall.png") )
    {
        cout << "Unable to load player falling texture!" << endl;
        success = false;
    }
    else
    {
        for ( int i = 0 ; i < FALL_ANIMATION_FRAMES ; i++ )
        {
            gFallClips[ i ] = { i * 240 , 0 , 240 , 160 };
        }
    }

    //Load player crouching texture
    if ( !gCrouchTexture.loadFromFile ( "assets/player/_CrouchWalk.png") )
    {
        cout << "Unable to load player crouching texture!" << endl;
        success = false;
    }
    else
    {
        for ( int i = 0 ; i < CROUCH_ANIMATION_FRAMES ; i++ )
        {
            gCrouchClips[ i ] = { i * 240 , 0 , 240 , 160 };
        }
    }

    //Load background layers
    for ( int i = 0 ; i < BACKGROUND_LAYERS ; i++ )
    {
        if ( !gBackgroundTexture[ i ].loadFromFile ( BACKGROUND_FILE[ i ].c_str() ) )
        {
            cout << "Unable to load background texture at layer " << i + 1 << "!" << endl;
            success = false;
        }
    }

    //Load ground texture
    if ( !gGroundTexture.loadFromFile ( "assets/Background layers/ground.png" ) )
    {
        cout << "Unable to load ground texture!" << endl;
        success = false;
    }

    //Load menu texture
    if ( !gMenuTexture.loadFromFile ( "assets/Menu/menu.png" ) )
    {
        cout << "Unable to load menu texture!" << endl;
        success = false;
    }

    //load instruction texture
    if ( !gInstructionTexture.loadFromFile ( "assets/Menu/instruction.png" ) )
    {
        cout << "Unable to load instruction texture!" << endl;
        success = false;
    }

    //load esc texture
    if ( !gEscTexture.loadFromFile ( "assets/Button/Esc.png" ) )
    {
        cout << "Unable to load space texture!" << endl;
        success = false;
    }
    else
    {
        for ( int i = 0 ; i < TOTAL_BUTTON ; i++ )
        {
            gEscClips[ i ] = { i * 50 , 0 , 50 , 50 };
        }
    }

    //load pause and continue button
    if ( !gPauseAndContinueTexture.loadFromFile ( "assets/Button/Pause_and_continue.png" ) )
    {
        cout << "Unable to load pause and continue button texture!" << endl;
        success = false;
    }
    else
    {
        for ( int i = 0 ; i < TOTAL_BUTTON ; i++ )
        {
            gPauseAndContinueClips[ i ] = { i * 50 , 0 , 50 , 50 };
        }
    }

    //load game over texture
    if ( !gGameOverTexture.loadFromFile ( "assets/Menu/gameover.png" ) )
    {
        cout << "Unable to load game over texture!" << endl;
        success = false;
    }

    //load fonts
    gFont = TTF_OpenFont ( "assets/Font/fibberish.ttf" , 28 );
    if ( gFont == nullptr )
    {
        cout << "Unable to load font!" << TTF_GetError() << endl;
        success = false;
    }
    else
    {
        //load your score text
        if ( !gYourScoreTextTexture.loadFromRenderedText ( "Score:" , textColor ) )
        {
            cout << "Unable to render your score text!" << endl;
            success = false;
        }

        //load high score text
        if ( !gHighScoreTextTexture.loadFromRenderedText ( "HighScore:" , textColor ) )
        {
            cout << "Unable to load high score text!" << endl;
            success = false;
        }
    }

    //load key press sound
    gPress = Mix_LoadWAV ( "sfx/press.wav" );
    if ( gPress == nullptr )
    {
        cout << "Unable to load key press sound!" << Mix_GetError() << endl;
        success = false;
    }

    //load jump sound
    gJump = Mix_LoadWAV ( "sfx/jump.wav" );
    if ( gJump == nullptr )
    {
        cout << "Unable to load jump sound!" << Mix_GetError() << endl;
        success = false;
    }

    //load pause sound
    gGameStart = Mix_LoadWAV ( "sfx/game_start.wav" );
    if ( gGameStart == nullptr )
    {
        cout << "Unable to load game start sound!" << Mix_GetError() << endl;
        success = false;
    }

    //load pause sound
    gPause = Mix_LoadWAV ( "sfx/pause.wav" );
    if ( gPause == nullptr )
    {
        cout << "Unable to load pause sound!" << Mix_GetError() << endl;
        success = false;
    }

    //load game over sound
    gGameOver = Mix_LoadWAV ( "sfx/game_over.wav" );
    if ( gGameOver == nullptr )
    {
        cout << "Unable to load game over sound!" << Mix_GetError() << endl;
        success = false;
    }

    //load menu music
    gMenuMusic = Mix_LoadMUS ( "sfx/menu.wav" );
    if ( gMenuMusic == nullptr )
    {
        cout << "Unable to load menu music!" << Mix_GetError() << endl;
        success = false;
    }

    //load instruction music
    gInstructionMusic = Mix_LoadMUS ( "sfx/instruction.wav" );
    if ( gInstructionMusic == nullptr )
    {
        cout << "Unable to load instruction music!" << Mix_GetError() << endl;
        success = false;
    }

    //load background music
    gBackgroundMusic = Mix_LoadMUS ( "sfx/background.wav" );
    if ( gBackgroundMusic == nullptr )
    {
        cout << "Unable to load background music!" << Mix_GetError() << endl;
        success = false;
    }

    return success;
}

void close()
{
    gRunTexture.free();
    gJumpTexture.free();
    gFallTexture.free();
    gCrouchTexture.free();
    gGroundTexture.free();
    gMenuTexture.free();
    gInstructionTexture.free();
    gEscTexture.free();
    gPauseAndContinueTexture.free();
    gYourScoreTextTexture.free();
    gHighScoreTextTexture.free();

    for ( int i = 0 ; i < BACKGROUND_LAYERS ; i++ )
    {
        gBackgroundTexture[ i ].free();
    }

    TTF_CloseFont ( gFont );
    gFont = nullptr;

    Mix_FreeChunk ( gJump );
    Mix_FreeChunk ( gPress );
    Mix_FreeChunk ( gPause );
    Mix_FreeChunk ( gGameStart );
    Mix_FreeChunk ( gGameOver );
    gJump = nullptr;
    gPress = nullptr;
    gPause = nullptr;
    gGameStart = nullptr;
    gGameOver = nullptr;

    Mix_FreeMusic ( gMenuMusic );
    Mix_FreeMusic ( gInstructionMusic );
    Mix_FreeMusic ( gBackgroundMusic );
    gMenuMusic = nullptr;
    gInstructionMusic = nullptr;
    gBackgroundMusic = nullptr;

    SDL_DestroyWindow ( gWindow );
    gWindow = nullptr;
    SDL_DestroyRenderer ( gRenderer );
    gRenderer = nullptr;

    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

void ScrollingBackground( vector <double> &offsetSpeed , LTexture(&gBackgroundTexture)[ BACKGROUND_LAYERS ] )
{
    vector <double> layer_speed;
    layer_speed.push_back( LAYER_1_SPEED );
    layer_speed.push_back( LAYER_2_SPEED );
    layer_speed.push_back( LAYER_3_SPEED );
    layer_speed.push_back( LAYER_4_SPEED );


    for ( int i = 0 ; i < BACKGROUND_LAYERS ; i++ )
    {
        offsetSpeed[ i ] -= layer_speed[ i ];
        if ( offsetSpeed[ i ] < -gBackgroundTexture[ i ].getWidth() )
        {
            offsetSpeed[ i ] = 0;
        }

        gBackgroundTexture[ i ].render ( offsetSpeed[ i ] , 0 );
        gBackgroundTexture[ i ].render ( offsetSpeed[ i ] + gBackgroundTexture[ i ].getWidth() , 0 );
    }
}

void ScrollingGround ( int& speed , const int acceleration , LTexture &gGroundTexture )
{
    speed -= GROUND_SPEED + acceleration;
    if ( speed < -gGroundTexture.getWidth()  )
    {
        speed = 0;
    }

    gGroundTexture.render ( speed , 0 );
    gGroundTexture.render ( speed + gGroundTexture.getWidth() , 0 );
}

bool checkCollision ( Enemy enemy , Player knight )
{
    bool collide = false;

    int left_a , right_a , top_a , bottom_a;
    int left_b , right_b , top_b , bottom_b;


    if ( knight.getStatus() == NORMAL )
    {
        left_a = knight.getPosX() + 91;
        right_a = knight.getPosX() + 240 - 110;
        top_a = knight.getPosY() + 84;
        bottom_a = knight.getPosY() + 160;
    }
    else if ( knight.getStatus() == CROUCH )
    {
        left_a = knight.getPosX() + 91;
        right_a = knight.getPosX() + 240 - 110;
        top_a = knight.getPosY() + 108;
        bottom_a = knight.getPosY() + 160;
    }

    if ( enemy.getType() == ON_GROUND )
    {
        left_b = enemy.getPosX();
        right_b = enemy.getPosX() + enemy.getWidth();
        top_b = enemy.getPosY();
        bottom_b = enemy.getPosY() + enemy.getHeight();

        if ( right_a >= left_b && left_a <= right_b )
		{
			if ( bottom_a >= top_b )
			{
				collide = true;
			}
		}
    }

    else if ( enemy.getType() == IN_AIR || enemy.getType() == MID_AIR )
    {
        left_b = enemy.getPosX() + 8;
        right_b = enemy.getPosX() + enemy.getWidth() - 248;
        top_b = enemy.getPosY() + 6;
        bottom_b = enemy.getPosY() + enemy.getHeight() - 18;

        if ( right_a >= left_b && left_a <= right_b )
		{
			if ( top_a <= bottom_b && bottom_a >= top_b )
			{
				collide = true;
			}
		}
    }

    return collide;
}

void handleMenuButton ( SDL_Event e , LTexture& gInstructionTexture , Button& escButton ,
                       Mix_Chunk* gPress , Mix_Music* gInstructionMusic ,
                       bool& menu , bool& play , bool &quit )
{
    if ( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch ( e.key.keysym.sym )
        {
        case SDLK_SPACE:
            {
                Mix_HaltMusic();
                Mix_PlayChannel ( -1 , gGameStart , NOT_LOOP );
                SDL_Delay ( 2000 );
                menu = false;
                play = true;
                break;
            }
        case SDLK_i:
            {
                Mix_PlayChannel( -1 , gPress , NOT_LOOP );
                break;
            }
        case SDLK_ESCAPE:
            {
                Mix_PlayChannel ( -1 , gPress , NOT_LOOP );
                menu = false;
                quit = true;
                break;
            }
        }
    }

    if ( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch ( e.key.keysym.sym )
        {
        case SDLK_i:
            {

                bool instruction = true;

                Mix_PlayMusic ( gInstructionMusic , LOOP );

                while ( instruction )
                {

                    while ( SDL_PollEvent ( &e ) != 0 )
                    {
                        if ( e.type == SDL_QUIT )
                        {
                            instruction = false;
                            menu = false;
                            return;
                        }

                        else if ( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
                        {
                            switch ( e.key.keysym.sym )
                            {
                            case SDLK_ESCAPE:
                                escButton.currentSprite = BUTTON_PRESSED;
                                Mix_PlayChannel ( -1 , gPress , NOT_LOOP );
                                break;
                            }
                        }

                        else if ( e.type == SDL_KEYUP && e.key.repeat == 0 )
                        {
                            switch ( e.key.keysym.sym )
                            {
                            case SDLK_ESCAPE:
                                escButton.currentSprite = BUTTON_NOT_PRESSED;
                                Mix_PlayMusic ( gMenuMusic , LOOP );
                                instruction = false;
                                break;
                            }
                        }
                    }

                    gInstructionTexture.render ( 0 , 0 );

                    //render buttons
                    escButton.render ( &gEscClips[ escButton.currentSprite ] , gEscTexture );

                    SDL_RenderPresent ( gRenderer );
                }

                break;
            }
        }
    }
}

void handleContinueButton ( SDL_Event e , Button& PauseAndContinueButton , bool& gameRunning , bool& quit , bool& playAgain )
{
    bool backToGame = false;
    while ( !backToGame )
    {
        while ( SDL_PollEvent ( &e ) != 0 )
        {
            if ( e.type == SDL_QUIT )
            {
                gameRunning = false;
                quit = true;
                playAgain = false;
                return;
            }

            if ( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
            {
                switch ( e.key.keysym.sym )
                {
                case SDLK_p:
                    {
                        Mix_ResumeMusic();
                        gameRunning = true;
                        backToGame = true;
                        PauseAndContinueButton.currentSprite = BUTTON_NOT_PRESSED;
                        break;
                    }
                }
            }
        }

        PauseAndContinueButton.render ( &gPauseAndContinueClips[ PauseAndContinueButton.currentSprite ] , gPauseAndContinueTexture );

        SDL_RenderPresent ( gRenderer );

    }
}

void handlePauseButton ( SDL_Event e , Button& PauseAndContinueButton , Mix_Chunk* gPause , bool& gameRunning , bool& quit , bool& playAgain )
{
    if ( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch ( e.key.keysym.sym )
        {
        case SDLK_p:
            {
                Mix_PlayChannel ( -1 , gPause , NOT_LOOP );
                Mix_PauseMusic ();
                gameRunning = false;
                PauseAndContinueButton.currentSprite = BUTTON_PRESSED;
                handleContinueButton ( e, PauseAndContinueButton , gameRunning , quit , playAgain );
                break;
            }
        }
    }
}

void loadEnemyTexture ( Enemy& stone , Enemy& bat1 , Enemy& bat2 , SDL_Rect(&gBatClips)[ BAT_FRAMES ] )
{
    //Load stone texture
    if ( !stone.loadFromFile ( "assets/Enemy/stone.png" ) )
    {
        cout << "Unable to load stone texture!" << endl;
    }

    //Load bat texture
    if ( !bat1.loadFromFile ( "assets/Enemy/bat.png" ) || !bat2.loadFromFile ( "assets/Enemy/bat.png" ) )
    {
        cout << "Unable to load bat texture!" << endl;
    }
    else
    {
        for ( int i = 0 ; i < BAT_FRAMES ; i++ )
        {
            gBatClips[ i ] = { i * 48 , 0 , 48 , 48 };
        }
    }
}

string loadHighScoreFromFile ( string path )
{
    std::fstream HighScoreFile;
    string highScore;

    HighScoreFile.open ( path , std::ios::in );
    HighScoreFile >> highScore;

    return highScore;
}

void updateHighScore ( string path , const int& score , const string& old_high_score )
{
    int oldHighScore = 0;
    std::fstream HighScoreFile;
    string newHighScore;
    std::stringstream ConvertToInt ( old_high_score );

    HighScoreFile.open ( path , std::ios::out );

    ConvertToInt >> oldHighScore;
    if ( score > oldHighScore )
    {
        oldHighScore = score;
    }
    newHighScore = std::to_string ( oldHighScore );

    HighScoreFile << newHighScore;
}

int updateTimeAndScore ( int& time , int& speed , int& score )
{
    if ( time == 1700 )
    {
        speed += 1;
    }

    if ( time > 1700 )
    {
        time = 0;
    }

    if ( time % 10 == 0 )
    {
        score++;
    }

    time++;

    return time;
}

void renderPlayerScore ( LTexture& gYourScoreTextTexture , LTexture& gScoreTexture , const int& score )
{
    gYourScoreTextTexture.render ( 918 , 15 );

    if ( gScoreTexture.loadFromRenderedText ( std::to_string( score ) , textColor ) )
    {
        gScoreTexture.render ( 1000 , 15 );
    }
}

void renderHighScore ( LTexture& gHighScoreTextTexture , LTexture& gHiScoreTexture , const string& highScore )
{
    gHighScoreTextTexture.render ( 870 , 55 );

    if ( gHiScoreTexture.loadFromRenderedText ( highScore , textColor ) )
    {
        gHiScoreTexture.render ( 1000 , 55 );
    }
}

void renderGameOver ( LTexture& gGameOverTexture , Mix_Chunk* gPress , SDL_Event e , bool& playAgain , bool& menu )
{
    if ( playAgain )
    {
        bool gameOver = false;

        while ( !gameOver )
        {
            while ( SDL_PollEvent ( &e ) != 0 )
            {
                if ( e.type == SDL_QUIT )
                {
                    gameOver = true;
                    playAgain = false;
                }

                else if ( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
                {
                    switch ( e.key.keysym.sym )
                    {
                    case SDLK_SPACE:
                        {
                            Mix_HaltChannel( -1 );
                            Mix_PlayChannel( -1 , gPress , NOT_LOOP );
                            playAgain = true;
                            gameOver = true;
                            break;
                        }
                    case SDLK_ESCAPE:
                        {
                            Mix_PlayChannel( -1 , gPress , NOT_LOOP );
                            gameOver = true;
                            playAgain = false;
                            menu = true;
                            break;
                        }
                    }
                }
            }

            gGameOverTexture.render ( 0 , 0 );

            SDL_RenderPresent ( gRenderer );
        }
    }
}

void controlBatFrame ( int& frame )
{
    frame++;
    if ( frame / 6 >= BAT_FRAMES )
    {
        frame = 0;
    }
}
