#include"menu.h"
button::button()
{
	buttonRect = { 0,0,0,0 };
	buttonTexture = NULL;
	buttonName = PLAY;
	inside = false;
}
void loadButtonTexture(SDL_Renderer* renderer, button* buttons)
{
	buttons[PLAY].buttonTexture = loadTexture("PLAY.png", renderer);
	buttons[PLAY].buttonName = PLAY;
	buttons[PLAY].buttonRect = { (640 - 130) / 2,640 / 2 - 70,130,70 };
	buttons[QUIT].buttonTexture = loadTexture("QUIT.png", renderer);
	buttons[QUIT].buttonName = QUIT;
	buttons[QUIT].buttonRect = { (640 - 130) / 2,640 / 2 + 70,130,70 };
}
void button::checkInside(SDL_Event* e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		inside = true;
		if (x < buttonRect.x)
		{
			inside = false;
		}
		else if (x > buttonRect.x + buttonRect.w)
		{
			inside = false;
		}
		else if (y < buttonRect.y)
		{
			inside = false;
		}
		else if (y > buttonRect.y + buttonRect.h)
		{
			inside = false;
		}
	}
}
void button::handleEvent(SDL_Event* e, bool& menu, bool& quit)
{
	checkInside(e);
	if (inside && e->type == SDL_MOUSEBUTTONDOWN)
	{
		switch (buttonName)
		{
		case PLAY:
			setFalse(menu);
			setFalse(quit);
			break;
		case QUIT:
			SDL_Quit();
			break;
		}
	}
}
void button::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);
	SDL_RenderPresent(renderer);
}