
#ifndef LOADTEX_H_
#define LOADTEX_H_
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<iostream>
#include<deque>
#include<algorithm>
#include<vector>
#include<time.h>
#include<string>
#include<stdlib.h>
using namespace std;

const int gWidth = 640;
const int gHeight = 640;
static const int size = 80;
static bool quit = true;

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event e;
static TTF_Font* gFont = NULL;
static SDL_Color whiteColor = { 255,255,255,255 };
//static Mix_Chunk* moveEffect = Mix_LoadWAV("moveSound.mp3");
static bool GAME = true;
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);
SDL_Texture* loadTextTexture(string path, string chucai, SDL_Color color, int text_size, SDL_Renderer* renderer);
static SDL_Texture* press;
static SDL_Texture* pause;
static SDL_Rect pressRect = { (gWidth - 500) / 2, (gHeight - 75) / 2 ,500, 75 };
static SDL_Rect pauseRect = { (gWidth - 600) / 2, (gHeight - 75) / 2 ,600, 75 };
//static SDL_Texture* Menu = loadTexture("menu.png", gRenderer);

void setFalse(bool& x);
void pauseGame(SDL_Event e, SDL_Renderer* renderer/*, clock_t& start*/);
void initTextTexture(SDL_Renderer* renderer,SDL_Rect& a);
void renderGameOver(SDL_Renderer* renderer);
#endif LOADTEXT_H_
