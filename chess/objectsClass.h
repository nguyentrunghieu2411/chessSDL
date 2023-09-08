#ifndef OBJECT_H_
#define OBJECT_H_
#include"loadTexture.h"
enum WhitecChesses
{
	VUA = 1,
	HAU,
	TUONG,
	MA,
	XE,
	TOT
};	
enum BlackChesses
{
	TOTDEN = -6,
	XEDEN,
	MADEN,
	TUONGDEN,
	HAUDEN,
	VUADEN
};

static SDL_Texture* chessTextures;
static SDL_Rect chessRects[6];
static SDL_Rect BlackRects[6];
static bool waiting = false;
static bool whiteTurn = true;
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
	void eat(chess* c);
	void resetLegalPos();
	void renderLegalPos(SDL_Renderer* renderer);
};
class board
{
public:
	int manager[8][8];
	SDL_Rect pos[8][8];
	/*SDL_Color white = {255,255,255,255};
	SDL_Color black = { 0,0,0,0 };*/
	board();
	void init();
	
	void render(SDL_Renderer* renderer);
	SDL_Rect choosen(SDL_Event e);
	void handleEvent(SDL_Event e,SDL_Renderer* renderer,bool & waiting,bool & quit);
	void update(chess c);
	chess* getChess(int cot, int dong);
	bool ischeck(bool white);
	void renderPick(chess* c, SDL_Renderer* renderer);
	void renderLegalMoves(chess* c, SDL_Renderer* renderer);
};
void getLegalPos(board game, chess* c);
static board game;
static chess none;
static chess tot[16];
static chess tuong[4];
static chess ma[4];
static chess xe[4];
static chess vua, vuaden;
static chess hau, hauden;

static vector<chess> whiteChess;
static vector<chess> blackChess;
static chess* current = &none;
void loadChessTextures(SDL_Renderer* renderer);
void pushLegal(int _cot, int _dong);
#endif OBJECT_H_
