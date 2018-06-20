#include "../include/Game.h"
#include "../include/Sprite.h"
#include "../include/Music.h"
#include "../include/Resources.h"
#include "../include/InputManager.h"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

Game *Game::instance = nullptr;

Game::Game(std::string title, int width, int height) : storedState(nullptr), width(width), height(height) {
    // Start SDL

    // FLAGS
    // SDL_INIT_TIMER
    // SDL_INIT_GAMECONTROLLER
    // SDL_INIT_AUDIO
    // SDL_INIT_EVENTS
    // SDL_INIT_VIDEO
    // SDL_INIT_EVERYTHING
    // SDL_INIT_JOYSTICK
    // SDL_INIT_NOPARACHUTE
    // SDL_INIT_HAPTIC

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
		std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
		hasStarted = false;
		return;
	}

    // FLAGS
    // IMG_INIT_JPEG
    // IMG_INIT_PNG
    // IMG_INIT_TIF

	int flags_img = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    int init_img = IMG_Init(flags_img);
	if ((init_img&flags_img) != flags_img) {
		printf("Error IMG_Init: %s\n", IMG_GetError());
		SDL_Quit();
		hasStarted = false;
		return;
	}
    // FLAGS
    // MIX_INIT_FLAC
    // MIX_INIT_MP3
    // MIX_INIT_OGG
    // MIX_INIT_MOD
    // MIX_INIT_FLUIDSYNTH
    // MIX_INIT_MODPLUG

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
		              MIX_DEFAULT_CHANNELS, 1024) == -1) {
	    printf("Error Mix_OpenAudio: %s\n", Mix_GetError());
		Mix_Quit();
		SDL_Quit();
		hasStarted = false;
		return;
	}

	int flags_mix = MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG;
    int init_mix = Mix_Init(flags_mix);
	if ((init_mix&flags_mix) != flags_mix) {
		printf("Error Mix_Init: %s\n", Mix_GetError());
		SDL_Quit();
		hasStarted = false;
		return;
	}

    Mix_AllocateChannels(32);

	// Start Window
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		std::cerr << "Error SDL_CreateWindow: " << SDL_GetError() << std::endl;
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
		hasStarted = false;
		return;
	}
	// Set fullscreen
	/*if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0) {
		SDL_DestroyWindow(window);
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
		hasStarted = false;
		return;
	}*/


	// Start Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		std::cerr << "Error SDL_CreateRenderer: " << SDL_GetError() << std::endl;
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
		hasStarted = false;
		return;
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// Font Renderer
	if(TTF_Init()==-1) {
	    printf("TTF_Init: %s\n", TTF_GetError());
		SDL_DestroyWindow(window);
		std::cerr << "Error TTF_Init: " << SDL_GetError() << std::endl;
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
		hasStarted = false;
		return;
	}
	int w,h;
	SDL_GetWindowSize(window, &w,&h);
	std::cout<<"WINDOW SIZE: ("<<w<<','<<h<<')'<<std::endl;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

	srand(time(NULL));
	hasStarted = true;
	dt = 0;
	frameStart = 0;
	std::cout<<"Iniciou"<<std::endl;
}

Game::~Game() {
	if (storedState != nullptr) {
		delete storedState;
	}

	while(!stateStack.empty()) {
    	stateStack.pop();
	}

	Resources::Clear();

	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
	SDL_Quit();
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State &Game::GetCurrentState() {
    return *(stateStack.top());
}

Vec2 Game::GetWindowSize() {
	return Vec2(width, height);
}

Game &Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game("Stand Your Ground", SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    return *instance;
}

void Game::Run() {
	if (hasStarted){
		if (storedState != nullptr) {
			stateStack.push(std::unique_ptr<State>(storedState));
			storedState = nullptr;
			GetCurrentState().Start();
		}
		// GAME LOOP
	    while (!stateStack.empty()) {
			if (GetCurrentState().QuitRequested()) {
				std::cout<<"Saiu state"<<std::endl;
				stateStack.pop();
			}
			if (storedState != nullptr) {
				std::cout<<"Novo state"<<std::endl;
				if (!stateStack.empty()) {
					GetCurrentState().Pause();
				}
				stateStack.push(std::unique_ptr<State>(storedState));
		        GetCurrentState().Start();
				storedState = nullptr;
			}
			if (!stateStack.empty()) {
				GetCurrentState().Resume();

				CalculateDeltaTime();
				float dt = GetDeltaTime();
				InputManager::GetInstance().Update(dt);
		        GetCurrentState().Update(dt);
		        GetCurrentState().Render();
		        SDL_RenderPresent(renderer);
	        	SDL_Delay(33);
			}
	    }
	}
}

void Game::Push(State *state) {
	storedState = state;
}

float Game::GetDeltaTime() {
	return dt;
}

void Game::CalculateDeltaTime() {
	int current = SDL_GetTicks();
	dt = std::abs(frameStart - current)/1000.0;
	frameStart = current;
}
