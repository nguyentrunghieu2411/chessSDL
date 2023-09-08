#ifndef BOARD_H_
#define BOARD_H_
#include"chess.h"
#include"loadTexture.h"

class board
{
public:
	int manager[8][8];
	SDL_Rect pos[8][8];
	/*SDL_Color white = {255,255,255,255};
	SDL_Color black = { 0,0,0,0 };*/
	board();
	void init();
	
	void render(SDL_Renderer* renderer);
	SDL_Rect choosen(SDL_Event e);
	void handleEvent(SDL_Event e);
	void update(chess c);
	chess* getChess(int cot, int dong);
	void moveChess(SDL_Event e);
};
static board game;
static bool waiting = false;
static bool whiteTurn = true;
#endif BOARD_H_
