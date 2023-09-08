#include"board.h"

SDL_Rect pick = { 0,0,0,0 };
void board::init()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			manager[i][j] = 0;
			pos[i][j] = { 80 * i,80 * j,80,80 };
		}
	}
}

board::board()
{
	init();
}

void board::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 205, 133, 63, 255);
	SDL_RenderClear(renderer);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i % 2 == j % 2)
			{
				SDL_SetRenderDrawColor(renderer, 245, 245, 245, 0);

			}
			else
			{
				SDL_SetRenderDrawColor(renderer,105 ,105 ,105,0);
			}
			SDL_RenderFillRect(renderer, &pos[i][j]);
		}
	}
	SDL_SetRenderDrawColor(renderer, 99, 184, 255,0);
	SDL_RenderFillRect(renderer, &pick);
}
SDL_Rect board::choosen(SDL_Event e)
{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if ( (x > pos[i][j].x) && (x < pos[i][j].x + pos[i][j].w) && (y > pos[i][j].y) && (y < pos[i][j].y + pos[i][j].h) )
				{ 
					pick = pos[i][j];
					
					//waiting = true;
					
				}
			}
		}
		return pick;
}
void board::update(chess c)
{
	manager[c.dong][c.cot] = c.type;
}
