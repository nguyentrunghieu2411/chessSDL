#include"game.h"
#include"menu.h"
//nguon anh itch.io

void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	gWindow = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gWidth , gHeight, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		cout << "ko tao duoc window " << SDL_GetError() << endl;
		//return false;
	}
	else
	{
		gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
		if (gRenderer == NULL)
		{
			cout << "ko tao dc renderer " << SDL_GetError() << endl;
			//return false;
		}
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "ko khoi tao dc mixer " << SDL_GetError() << endl;
		//return  false;
	}
	TTF_Init();

	//return true;
}
int main(int argc, char* argv[])
{
	init();
	Menu = loadTexture("menu.jpg", gRenderer);
	initChess(gRenderer,game);
	loadButtonTexture(gRenderer, buttonList);
	initTextTexture(gRenderer,pressRect);
	while (GAME)
	{
		initPos(gRenderer,game);
		while (menu)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					SDL_Quit();
				}
				for (int i = 0; i < TOTAL; i++)
				{
					buttonList[i].handleEvent(&e, menu, quit);
				}
			}
			SDL_RenderCopy(gRenderer, Menu, NULL, NULL);
			for (int i = 0; i < TOTAL; ++i)
			{
				buttonList[i].render(gRenderer);
			}
			SDL_RenderPresent(gRenderer);
		}
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					SDL_Quit();
				}
				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					game.handleEvent(e, gRenderer, waiting,quit);
					cout << quit << " ";
				}
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p)
				{
					pauseGame(e, gRenderer/*, start */);
				}
			}
			game.render(gRenderer);
			game.renderPick(current, gRenderer);
			game.renderLegalMoves(current, gRenderer);
			renderChesses(gRenderer, game);
			SDL_RenderPresent(gRenderer);
		}
		bool gameOver = quit;
		cout << "end";
		while (gameOver)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					SDL_Quit();
				}
				else if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN)
					{
						gameOver = false;
						menu = true;
						quit = false;
					}
					else if (e.key.keysym.sym == SDLK_ESCAPE)
					{
						SDL_Quit();
					}
				}
			}
			renderGameOver(gRenderer);
		}
		
	}
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << game.manager[i][j] << " ";
		}
		cout << endl; 
	}

	return 0;
}