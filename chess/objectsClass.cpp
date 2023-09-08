#include"objectsClass.h"

SDL_Rect pick = { 0,0,0,0 };
SDL_Rect r = { 0,0,80,80 };
void board::init()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			manager[j][i] = 0;
			pos[j][i] = { 80 * i,80 * j,80,80 };
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
				SDL_SetRenderDrawColor(renderer, 248, 220, 180, 0);

			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 184, 140, 100,0);
			}
			SDL_RenderFillRect(renderer, &pos[j][i]);
		}
	}
	
}
void board::renderPick(chess* c, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 208, 212, 108, 0);
	SDL_RenderFillRect(renderer, &pick);
	for (int i = 0; i < current->legalPos.size(); i++)
	{
		cout << "ma";
		r.x = current->legalPos[i].x; r.y = current->legalPos[i].y;
		SDL_RenderFillRect(renderer, &r);
	}
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
			if ((x > pos[j][i].x) && (x < pos[j][i].x + pos[j][i].w) && (y > pos[j][i].y) && (y < pos[j][i].y + pos[j][i].h))
			{
				pick = pos[j][i];

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
chess::chess()
{
	type = 0;
}
void loadChessTextures(SDL_Renderer* renderer)
{
	chessTextures = loadTexture("chesses.png", renderer);
	for (int i = 0; i < 6; i++)
	{
		chessRects[i] = { i * 80, 0, 80,80 };
	}
	for (int i = 0; i < 6; i++)
	{
		BlackRects[i] = { i * 80, 80, 80,80 };
	}
}
void chess::setPos(int _cot, int _dong)
{
	this->cot = _cot;
	this->dong = _dong;
}
void chess::render(SDL_Renderer* renderer)
{
	SDL_Rect des = { 80 * cot,80 * dong,80,80 };
	if (white)
	{
		SDL_RenderCopy(renderer, chessTextures, &chessRects[type - 1], &des);
	}
	else
	{
		SDL_RenderCopy(renderer, chessTextures, &BlackRects[-type - 1], &des);
	}

}
void chess::moveTo(int _cot, int _dong)
{
	setPos(cot, dong);
}

void chess::resetLegalPos()
{
	while (legalPos.size() != 0)
	{
		legalPos.pop_back();
	}
}
void chess::renderLegalPos(SDL_Renderer* renderer)
{
	
	if (legalPos.size() > 0)
	{
		
	}
	else
	{
		cout << "ngu";
	}
}