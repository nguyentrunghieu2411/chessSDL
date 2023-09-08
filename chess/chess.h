#ifndef CHESS_H_
#define CHESS_H_
#include"loadTexture.h"
//#include"board.h"
enum WhitecChesses
{
	VUA = 1,
	HAU,
	TUONG,
	MA,
	XE,
	TOT
};

static SDL_Texture* chessTextures;
static SDL_Rect chessRects[6];
static SDL_Rect BlackRects[6];
class chess
{
public:
	int type;
	bool white = true;
	int dong, cot;
	vector<SDL_Point> legalPos;
	chess();
	void render(SDL_Renderer* renderer);
	void setPos(int _cot, int _dong);
	void moveTo(int _cot, int _dong);
	void getLegalPos();
	void eat(chess* c);
	void resetLegalPos();
};
static chess none;
static chess tot[16];
static chess tuong[4];
static chess ma[4];
static chess xe[4];
static chess vua, vuaden;
static chess hau, hauden;

static vector<chess> whiteChess;
static vector<chess> blackChess;
void loadChessTextures(SDL_Renderer* renderer);

#endif CHESS_H_
