#include"chess.h"
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
	cot = _cot;
	dong = _dong;
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
		SDL_RenderCopy(renderer, chessTextures, &BlackRects[type - 1], &des);
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
