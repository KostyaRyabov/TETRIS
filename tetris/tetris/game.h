#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "object.h"

using namespace sf;

#define Black Color(0, 0, 0, 255)
#define Orange Color(255, 153, 0, 255)
#define Brown Color(102, 51, 0, 255)
#define Red Color(204, 51, 0, 255)
#define Yellow Color(230, 184, 0, 255)
#define Green Color(89, 179, 0, 255)
#define Blue Color(0, 102, 255, 255)
#define Purple Color(102, 0, 255, 255)
#define Pink Color(255, 102, 255, 255)
#define White Color(255, 255, 255, 255)

#define w 8
#define h 16
#define blockSize 32

#define pause_Code 0
#define menu_Code -1
#define play_Code 1

#define MC_up 101
#define MC_down 102
#define MC_left 103
#define MC_right 104
#define MC_start 105

class game
{
private:
	short score,i,j,lvl = menu_Code,c,k = 1,x = 0,y = 0,alpha, tmp, M1 = 0, M2 = 0, M3 = 0, sM1, sM2, sM3, height = -1;
	short map[w][h];
	short objType;
	int multi,R;
	
	object *objList[8];

	Color color[10] = { White, Orange, Brown, Red, Yellow, Green, Blue, Purple, Pink, Black};
	Font font;
	Text text,	menu_words[3];
	Clock clock;
	RectangleShape rect, banner,FullScreen;

	Thread *lerpM1, *lerpM2, *lerpAlpha, *lerpM3;

	bool addPoints;
	
	void setScore();
	void moveAllDown(short y);
	void check();
	void reset();
	void newObject();
public:
	void menu_controll(short comand);
	float speed = 9999;

	RenderWindow window;
	object *obj;

	short getLVL();

	game();
	void timer(float sec);
	void draw();
	void pause();
	void resume();
	void menu();
	void play();
	
	void rotate();
	short moveDown(bool fall);
	void moveLeft();
	void moveRight();
	
	~game();
};