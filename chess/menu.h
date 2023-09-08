#ifndef MENU_H_
#define MENU_H_
#include"loadTexture.h"

static bool menu = true;
static bool playAgain = true;

enum buttonList
{
	PLAY,
	QUIT,
	TOTAL
};

class button
{
public:
	button();
	void handleEvent(SDL_Event* e, bool& menu, bool& quit);
	void checkInside(SDL_Event* e);
	void render(SDL_Renderer* renderer);
	SDL_Rect buttonRect;
	SDL_Texture* buttonTexture;
	int buttonName;
	bool inside;
};

static button buttonList[TOTAL];
void loadButtonTexture(SDL_Renderer* renderer, button* button);
static SDL_Texture* Menu;

#endif MENU_H_


