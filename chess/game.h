#ifndef GAME_H_
#define GAME_H_

#include"objectsClass.h"
#include"menu.h"
static button chooses[4];
void initPos(SDL_Renderer* renderer, board& game);
void initChess(SDL_Renderer* renderer, board& game);
void renderChesses(SDL_Renderer* renderer,board game);
void runGame(SDL_Renderer* renderer);
void canEat(int _cot, int _dong, chess* c, board game);
void rockLegalMoves(chess* c, board game);
void bishopLegalMoves(chess* c, board game);
void pawnLegalMoves(chess* c, board game);
void knightLegalMoves(chess* c, board game);
void kingLegalMoves(chess* c, board game);
void queenLegalMoves(chess* c, board game);
void promote(chess* c,SDL_Renderer* renderer);
void initChossen(SDL_Renderer* renderer);
#endif GAME_H_