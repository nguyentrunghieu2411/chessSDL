#include"loadTexture.h"


SDL_Texture* loadTextTexture(string path, string chucai, SDL_Color color, int text_size, SDL_Renderer* renderer)
{
	SDL_Texture* ntexture = NULL;
	gFont = TTF_OpenFont(path.c_str(), text_size);
	if (gFont == NULL)
	{
		cout << "load font fail" << SDL_GetError() << endl;
	}
	SDL_Surface* loaded = TTF_RenderText_Solid(gFont, chucai.c_str(), color);
	if (loaded == NULL) {
		cout << "cant render text surface " << SDL_GetError() << endl;
	}
	else
	{
		ntexture = SDL_CreateTextureFromSurface(renderer, loaded);
		if (ntexture == NULL)
		{
			cout << "load text texture fail " << SDL_GetError() << endl;
		}
	}
	TTF_CloseFont(gFont);
	return ntexture;
}
SDL_Texture* loadTexture(string path, SDL_Renderer* renderer)
{
	SDL_Texture* ntexture = NULL;
	SDL_Surface* loaded = IMG_Load(path.c_str());
	if (loaded == NULL) {
		cout << "load file fail " << SDL_GetError() << endl;
	}
	else
	{
		ntexture = SDL_CreateTextureFromSurface(renderer, loaded);
		if (ntexture == NULL)
		{
			cout << "load texture fail " << SDL_GetError() << endl;
		}
	}

	return ntexture;
}
void setFalse(bool& x)
{
	x = false;
}
void pauseGame(SDL_Event e, SDL_Renderer* renderer/*, clock_t& start)*/)
{
	//auto begin = clock();
	bool stop = true;
	SDL_RenderCopy(renderer, pause, NULL, &pauseRect);
	SDL_RenderPresent(renderer);
	while (stop)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				stop = false;
			}
			else if (e.type == SDL_QUIT)
			{
				SDL_Quit();
			}
		}
	}
	/*auto stopTime = clock() - begin;
	start += stopTime;*/
}
void initTextTexture(SDL_Renderer* renderer, SDL_Rect& a)
{
	press = loadTextTexture("arial.ttf", string("PRESS ENTER TO BACK TO MENU"), whiteColor, 20, renderer);
	pause = loadTextTexture("arial.ttf", string("GAME PAUSE !! PRESS AN BUTTON TO CONTINUE"), whiteColor, 20, renderer);
	
}
void renderGameOver(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, press, NULL, &pressRect);
	SDL_RenderPresent(renderer);
}
