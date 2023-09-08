#include"game.h"
SDL_Rect from = { 0,0,0,0 };
SDL_Rect des = { 0,0,0,0 };
chess* eaten;
SDL_Rect p = { 0,0,80,80 };
SDL_Texture* legal;
SDL_Texture* death;
SDL_Texture* kingDeath;
Mix_Chunk* moveEffect;
SDL_Point pastPos = { 0,0 };
void initPos(SDL_Renderer* renderer, board& game)
{
	while (whiteChess.size() > 0 || blackChess.size() > 0)
	{
		whiteChess.pop_back();
		blackChess.pop_back();
	}
	ma[0].setPos(1, 7); ma[1].setPos(6, 7); ma[2].setPos(1, 0); ma[3].setPos(6, 0);
	tuong[0].setPos(2, 7); tuong[1].setPos(5, 7); tuong[2].setPos(2, 0); tuong[3].setPos(5, 0);
	xe[0].setPos(0, 7); xe[1].setPos(7, 7); xe[2].setPos(0, 0); xe[3].setPos(7, 0);
	vua.setPos(4, 7); hau.setPos(3, 7); vuaden.setPos(4, 0); hauden.setPos(3, 0);
	for (int i = 0; i < 8; i++)
	{
		tot[i].setPos(i, 6);
		tot[i + 8].setPos(i, 1);
	}
	for (int i = 0; i < 8; i++)
	{
		whiteChess.push_back(tot[i]);
		blackChess.push_back(tot[i + 8]);
	}
	for (int i = 0; i < 2; i++)
	{
		whiteChess.push_back(ma[i]);
		whiteChess.push_back(tuong[i]);
		whiteChess.push_back(xe[i]);

		blackChess.push_back(ma[i + 2]);
		blackChess.push_back(tuong[i + 2]);
		blackChess.push_back(xe[i + 2]);
	}
	whiteChess.push_back(hau); whiteChess.push_back(vua);
	blackChess.push_back(hauden); blackChess.push_back(vuaden);
	for (int i = 0; i < blackChess.size(); i++)
	{
		blackChess[i].white = false;
	}
	for (int i = 0; i < whiteChess.size(); i++)
	{
		game.update(whiteChess[i]);
		game.update(blackChess[i]);
	}
}
void initChess(SDL_Renderer* renderer,board & game)
{
	legal = loadTexture("legalMove.png",renderer);
	death = loadTexture("death.png", renderer);
	kingDeath = loadTexture("kingDeath.png", renderer);
	loadChessTextures(renderer);
	vua.type = VUA; vuaden.type = VUADEN;
	hau.type = HAU; hauden.type = HAUDEN;
	for (int i = 0; i < 2; i++)
	{
		ma[i].type = MA; ma[i + 2].type = MADEN;
		tuong[i].type = TUONG; tuong[i + 2].type = TUONGDEN;
		xe[i].type = XE; xe[i + 2].type = XEDEN;
	}
	for (int i = 0; i < 8; i++)
	{
		tot[i].type = TOT;
		tot[i + 8].type = TOTDEN;
	}
	initPos(renderer, game);
	
}
void renderChesses(SDL_Renderer* renderer,board game)
{
	for (int i = 0; i < whiteChess.size(); i++)
	{
		whiteChess[i].render(renderer);
		blackChess[i].render(renderer);
	}
}
chess* board::getChess(int cot, int dong)
{
	for (int i = 0; i < whiteChess.size(); i++)
	{
		if (whiteChess[i].cot == cot && whiteChess[i].dong == dong)
		{
			return &whiteChess[i];
		}
		else if (blackChess[i].cot == cot && blackChess[i].dong == dong)
		{
			return &blackChess[i];
		}
	}
	return &none;
}
void board::renderLegalMoves(chess* c, SDL_Renderer* renderer)
{
	if (whiteTurn == current->white)
	{	
		for (int i = 0; i < current->legalPos.size(); i++)
		{
			
			if (manager[current->legalPos[i].y][current->legalPos[i].x] != 0)
			{
				p.x = current->legalPos[i].x * 80; p.y = current->legalPos[i].y * 80;
				if (manager[current->legalPos[i].y][current->legalPos[i].x] == VUADEN || manager[current->legalPos[i].y][current->legalPos[i].x] == VUA)
				{
					SDL_RenderCopy(renderer, kingDeath, NULL, &p);
				}
				else
				{
					SDL_RenderCopy(renderer, death, NULL, &p);
				}
			}
			else
			{
				p.x = current->legalPos[i].x * 80; p.y = current->legalPos[i].y * 80;
				SDL_RenderCopy(renderer, legal, NULL, &p);
			}
		}
	}
}
void board::handleEvent(SDL_Event e, SDL_Renderer* renderer,bool & waiting,bool & quit)
{
	if (!waiting)
	{
		from = choosen(e);
		if (manager[from.y / 80][from.x / 80] != 0)
		{
			current = getChess(from.x / 80, from.y / 80);
			if (whiteTurn == current->white)
			{
				waiting = true;
				getLegalPos(*this, current);
			}
		}
	}
	else
	{
		des = choosen(e);
		if (des.x == from.x && des.y == from.y)
		{
			waiting = false;
			handleEvent(e, renderer,waiting,quit);
		}
		else
		{
			for (int i = 0; i < current->legalPos.size(); i++)
			{
				if (des.x / 80 == current->legalPos[i].x && des.y / 80 == current->legalPos[i].y)
				{
					if (manager[des.y / 80][des.x / 80] != 0)
					{
						eaten = getChess(des.x / 80, des.y / 80);
						eaten->setPos(10, 10);
						if (eaten->type == VUA || eaten->type == VUADEN)
						{
							quit = true;
						}
					}
					current->setPos(des.x / 80, des.y / 80);
					update(*current);
					manager[from.y / 80][from.x / 80] = 0;
					if (ischeck(!whiteTurn))
					{
						current->setPos(from.x/80, from.y/80);
						update(*current);
						manager[des.y / 80][des.x / 80] = 0;
						break;
					}					
					Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
					moveEffect = Mix_LoadWAV("moveSound.mp3");
					Mix_PlayChannel(-1, moveEffect, 0);
					whiteTurn = !whiteTurn;
					//if (whiteTurn) {// cout << " trang danh \n"; }
					//else {// cout << "den danh\n"; }
					if ((current->type == TOT && current->dong == 0) || (current->type == TOTDEN && current->dong == 7))
					{
						promote(current,renderer);
					}
					waiting = false;
					break;
				}
			}
			if (waiting)
			{
				waiting = false;
				handleEvent(e, renderer,waiting,quit);
			}
		}
	}
}
bool board::ischeck(bool white)
{
	if (white)
	{
		for (int i = 0; i < whiteChess.size(); i++)
		{
			if (whiteChess[i].cot < 8)
			{
				getLegalPos(*this, &whiteChess[i]);
				if (whiteChess[i].legalPos.size() > 0)
				{
					for (int j = 0; j < whiteChess[i].legalPos.size(); j++)
					{
						if (manager[whiteChess[i].legalPos[j].y][whiteChess[i].legalPos[j].x] == VUADEN)
						{
							return true;
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < blackChess.size(); i++)
		{
			if (blackChess[i].cot < 8)
			{
				getLegalPos(*this, &blackChess[i]);
				if (blackChess[i].legalPos.size() > 0)
				{
					for (int j = 0; j < blackChess[i].legalPos.size(); j++)
					{
						if (manager[blackChess[i].legalPos[j].y][blackChess[i].legalPos[j].x] == VUA)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
void canEat(int _cot, int _dong, chess* c, board game)
{
	if (_cot <= 7 && _cot >= 0 && _dong >= 0 && _dong <= 7)
	{
		if (game.manager[_dong][_cot] != 0)
		{
			if (game.manager[_dong][_cot] * c->type < 0)
			{
				c->legalPos.push_back({ _cot,_dong });
			}
		}
		else
		{
			c->legalPos.push_back({ _cot,_dong });
		}
	}
}
void getLegalPos(board game, chess* c)
{
	while (c->legalPos.size() > 0)
	{
		c->legalPos.pop_back();
	}
	if (c->type > 0)
	{
		switch (c->type)
		{
		case TOT: pawnLegalMoves(c, game); break;
		case MA: knightLegalMoves(c, game); break;
		case TUONG: bishopLegalMoves(c, game); break;
		case XE: rockLegalMoves(c, game); break;
		case VUA: kingLegalMoves(c, game); break;
		case HAU: queenLegalMoves(c, game); break;
		}
	}
	else if (c->type < 0)
	{
		switch (-c->type)
		{
		case TOT: pawnLegalMoves(c, game); break;
		case MA: knightLegalMoves(c, game); break;
		case TUONG: bishopLegalMoves(c, game); break;
		case XE: rockLegalMoves(c, game); break;
		case VUA: kingLegalMoves(c, game); break;
		case HAU: queenLegalMoves(c, game); break;
		}
	}
}
void rockLegalMoves(chess* c, board game)
{
	SDL_Point p;
	for (int i = c->dong + 1; i < 8; i++)
	{
		if (game.manager[i][c->cot] == 0)
		{
			p = { c->cot,i };
			c->legalPos.push_back(p);
		}
		else
		{
			if (game.manager[i][c->cot] * c->type < 0)
			{
				p = { c->cot,i };
				c->legalPos.push_back(p);
			}
			break;
		}
	}
	for (int i = c->dong - 1; i >= 0; i--)
	{
		if (game.manager[i][c->cot] == 0)
		{
			p = { c->cot,i };
			c->legalPos.push_back(p);
		}
		else
		{
			if (game.manager[i][c->cot] * c->type < 0)
			{
				p = { c->cot,i };
				c->legalPos.push_back(p);
			}
			break;
		}
	}
	for (int j = c->cot + 1; j < 8; j++)
	{
		if (game.manager[c->dong][j] == 0)
		{
			p = { j,c->dong };
			c->legalPos.push_back(p);
		}
		else
		{
			if (game.manager[c->dong][j] * c->type < 0)
			{
				p = { j,c->dong };
				c->legalPos.push_back(p);
			}
			break;
			
		}
	}
	for (int j = c->cot - 1; j >= 0; j--)
	{
		if (game.manager[c->dong][j] == 0)
		{
			p = { j,c->dong };
			c->legalPos.push_back(p);
		}
		else
		{
			if (game.manager[c->dong][j] * c->type < 0)
			{
				p = { j,c->dong };
				c->legalPos.push_back(p);
			}
			break;
		}
	}
}
void bishopLegalMoves(chess* c, board game)
{
	SDL_Point p;
	for (int i = c->cot + 1, j = c->dong + 1; i < 8 && j < 8; i++, j++)
	{
		if (game.manager[j][i] == 0)
		{
			p = { i,j };
			c->legalPos.push_back(p);
		}
		else
		{
			if (c->type * game.manager[j][i] < 0)
			{
				p = { i,j };
				c->legalPos.push_back(p);
			}
			break;
		}
	}
	for (int i = c->cot - 1, j = c->dong - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (game.manager[j][i] == 0)
		{
			p = { i,j };
			c->legalPos.push_back(p);
		}
		else
		{
			if (c->type * game.manager[j][i] < 0)
			{
				p = { i,j };
				c->legalPos.push_back(p);
			}
			break;
		}
	}
	for (int i = c->cot - 1, j = c->dong + 1; i >= 0 && j < 8; i--, j++)
	{
		if (game.manager[j][i] == 0)
		{
			p = { i,j };
			c->legalPos.push_back(p);
		}
		else
		{
			if (c->type * game.manager[j][i] < 0)
			{
				p = { i,j };
				c->legalPos.push_back(p);
			}
			break;
		}
	}
	for (int i = c->cot + 1, j = c->dong - 1; i < 8 && j >= 0; i++, j--)
	{
		if (game.manager[j][i] == 0)
		{
			p = { i,j };
			c->legalPos.push_back(p);
		}
		else
		{
			if (c->type * game.manager[j][i] < 0)
			{
				p = { i,j };
				c->legalPos.push_back(p);
			}
			break;
		}
	}
	
}
void pawnLegalMoves(chess* c, board game)
{
	if (c->dong < 7 && c->dong > 0)
	{
		if (c->white)
		{
			if (c->dong == 6)
			{
				if (game.manager[c->dong - 2][c->cot] == 0 && game.manager[c->dong - 1][c->cot] == 0)
				{
					c->legalPos.push_back({ c->cot,c->dong - 2 });
				}
			}
			if (game.manager[c->dong - 1][c->cot] == 0)
			{
				c->legalPos.push_back({ c->cot,c->dong - 1 });
			}
			if (game.manager[c->dong - 1][c->cot - 1] < 0)
			{
				c->legalPos.push_back({ c->cot - 1,c->dong - 1 });
			}
			if (game.manager[c->dong - 1][c->cot + 1] < 0)
			{
				c->legalPos.push_back({ c->cot + 1,c->dong - 1 });
			}
		}
		else
		{
			if (c->dong == 1)
			{
				if (game.manager[c->dong + 2][c->cot] == 0 && game.manager[c->dong + 1][c->cot] == 0)
				{
					c->legalPos.push_back({ c->cot,c->dong + 2 });
				}
			}
			if (game.manager[c->dong + 1][c->cot] == 0)
			{
				c->legalPos.push_back({ c->cot,c->dong + 1 });
			}
			if (game.manager[c->dong + 1][c->cot + 1] > 0)
			{
				c->legalPos.push_back({ c->cot + 1,c->dong + 1 });
			}
			if (game.manager[c->dong + 1][c->cot - 1] > 0)
			{
				c->legalPos.push_back({ c->cot - 1,c->dong + 1 });
			}
		}
    }
}
void knightLegalMoves(chess* c, board game)
{
	canEat(c->cot + 2, c->dong + 1, c, game);
	canEat(c->cot - 2, c->dong + 1, c, game);
	canEat(c->cot - 2, c->dong - 1, c, game);
	canEat(c->cot + 2, c->dong - 1, c, game);
	canEat(c->cot + 1, c->dong + 2, c, game);
	canEat(c->cot - 1, c->dong + 2, c, game);
	canEat(c->cot + 1, c->dong - 2, c, game);
	canEat(c->cot - 1, c->dong - 2, c, game);
	
}
void kingLegalMoves(chess* c, board game)
{
	int _cot = c->cot, _dong = c->dong;
	canEat(_cot + 1, _dong + 1, c, game);
	canEat(_cot - 1, _dong + 1, c, game);
	canEat(_cot - 1, _dong - 1, c, game);
	canEat(_cot + 1, _dong - 1, c, game);
	canEat(_cot + 1, _dong , c, game);
	canEat(_cot , _dong + 1, c, game);
	canEat(_cot - 1, _dong , c, game);
	canEat(_cot , _dong - 1, c, game);
}
void queenLegalMoves(chess* c, board game)
{
	rockLegalMoves(c, game);
	bishopLegalMoves(c, game);
}
void promote(chess* c,SDL_Renderer* renderer)
{
	initChossen(renderer);
	bool stop = true;
	for (int i = 0; i < 4; i++)
	{
		SDL_RenderCopy(renderer, chooses[i].buttonTexture,NULL,&chooses[i].buttonRect);
	}
	SDL_RenderPresent(renderer);
	while (stop)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				for (int i = 0; i < 4; i++)
				{
					chooses[i].checkInside(&e);
					if (chooses[i].inside)
					{
						c->type = c->type / 6 * chooses[i].buttonName;
					}
					stop = false;
				}
			}
			else if (e.type == SDL_QUIT)
			{
				SDL_Quit();
			}
		}
	}
}
void initChossen(SDL_Renderer* renderer)
{
	chooses[0].buttonName = HAU;
	chooses[0].buttonRect = { gWidth / 2 - 140 - 40,gHeight / 2 - 140 - 40,140,140 };
	chooses[0].buttonTexture = loadTexture("whiteQueen.png", renderer);
	
	chooses[1].buttonName = MA;
	chooses[1].buttonRect = { gWidth / 2 + 40,gHeight / 2 - 140 - 40,140,140 };
	chooses[1].buttonTexture = loadTexture("whiteKnight.png", renderer);
	
	chooses[2].buttonName = XE;
	chooses[2].buttonRect = { gWidth / 2 - 140 - 40,gHeight / 2 + 40,140,140 };
	chooses[2].buttonTexture = loadTexture("whiteRock.png", renderer);
	
	chooses[3].buttonName = TUONG;
	chooses[3].buttonRect = { gWidth / 2 + 40,gHeight / 2 + 40,140,140 };
	chooses[3].buttonTexture = loadTexture("whiteBishop.png", renderer);
}