#include "game.h"
#include <time.h>
#include <string>
#include <functional>

using namespace std;

void Lerp(short *A, short B, float sec) {
	Clock clock;
	clock.restart();
	float t, C = *A;

	B -= *A;

	while ((t = clock.getElapsedTime().asSeconds()) <= sec)
	{
		*A = B * t / sec + C;
	}

	*A = B + C;
}

short game::getLVL() {
	return lvl;
}

void game::reset() {
	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			map[i][j] = 0;
		}
	}

	score = 0;
	multi = 0;
	addPoints = false;
	alpha = 0;

	switch (lvl)
	{
	case 1:
		speed = 1;
		break;
	case 2:
		speed = 0.7;
		break;
	case 3:
		speed = 0.7;
		break;
	}

	newObject();
}

void game::timer(float sec) {
	if (clock.getElapsedTime().asSeconds() >= sec) {
		moveDown(true);

		clock.restart();
	}
}

game::game() {
	srand(time(0));

	if (!font.loadFromFile("bit_char.ttf"))
	{
		// ошибка...
	}
	

	text.setFont(font);
	text.setCharacterSize(16);
	
	rect.setSize(Vector2f(blockSize, blockSize));
	rect.setOutlineColor(Black);

	FullScreen.setSize(Vector2f(w * blockSize, h * blockSize + 16));
	banner.setSize(Vector2f(w * blockSize, 16));

	FullScreen.setPosition(Vector2f(0,0));
	banner.setPosition(Vector2f(0, 0));

	banner.setFillColor(Black);

	objList[0] = new rect_1x1();
	objList[1] = new rect_1x2();
	objList[2] = new rect_2x2();
	objList[3] = new rect_1x3();
	objList[4] = new rect_1x4();
	objList[5] = new ladder_1();
	objList[6] = new ladder_2();
	objList[7] = new ladder_3();

	menu_words[0].setFont(font);
	menu_words[0].setCharacterSize(32);
	menu_words[0].setPosition(Vector2f(w * blockSize / 3, h/4 * blockSize));

	menu_words[1].setFont(font);
	menu_words[1].setCharacterSize(24);
	menu_words[1].setPosition(Vector2f(w * blockSize / 2.5, h / 2 * blockSize));

	menu_words[2].setFont(font);
	menu_words[2].setCharacterSize(24);
	menu_words[2].setPosition(Vector2f(w * blockSize / 2.5, h / 1.5 * blockSize));

	reset();
}

void game::pause() {
	if (lvl != pause_Code) {
		lvl = pause_Code;

		tmp = speed;
		speed = 9999;

		lerpAlpha = new Thread(bind(&Lerp, &alpha, 200, 0.2));
		lerpAlpha->launch();
	}
	else resume();
}

void game::resume() {
	lvl = play_Code;
	
	lerpAlpha = new Thread(bind(&Lerp, &alpha, 0, 0.2));
	lerpAlpha->launch();
	
	speed = tmp;
}

void game::menu() {
	menu_words[0].setString("TETRIS");
	menu_words[0].setFillColor(Black);

	menu_words[1].setString("PLAY");
	menu_words[1].setFillColor(Black);
	
	switch (x)
	{
	case 0:
		menu_words[2].setString("EASY");
		k = 1;
		break;
	case 1:
		menu_words[2].setString("MIDDLE");
		k = 2;
		break;
	case 2:
		menu_words[2].setString("HARD");
		k = 3;
		break;
	}

	menu_words[2].setFillColor(Black);

	FullScreen.setFillColor(White);
	window.draw(FullScreen);

	window.draw(menu_words[0]);
	window.draw(menu_words[1]);
	window.draw(menu_words[2]);
}

void game::menu_controll(short comand) {
	switch (comand)
	{
	case MC_up:
		menu_words[2].setStyle(Text::Regular);
		menu_words[1].setStyle(Text::Underlined);
		y = 1;
		break;
	case MC_down:
		menu_words[1].setStyle(Text::Regular);
		menu_words[2].setStyle(Text::Underlined);
		y = 2;
		break;
	case MC_left:
		if (lvl == menu_Code) {
			if (y == 2) {
				if (x <= 0) x = 2;
				else --x;
			}
		}
		break;
	case MC_right:
		if (lvl == menu_Code) {
			if (y == 2) {
				if (x >= 2) x = 0;
				else ++x;
			}
		}
		break;
	case MC_start:
		if (y == 1) {
			lvl = k;
			reset();
			break;
		}

		if (lvl == pause_Code) {
			if (y == 2) {
				alpha = 0;
				speed = 9999;
				lvl = menu_Code;
				break;
			}
		}
	}
}

void game::play() {
	sM1 = M1;
	sM2 = M2;
	sM3 = M3;

	if (sM1 == 0) height = -1;
	
	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			c = map[i][j];

			if (c < 10) {
				rect.setFillColor(color[c]);

				if (j <= height)
				rect.setPosition(Vector2f(i * blockSize, j * blockSize + 16 + sM1));
				else rect.setPosition(Vector2f(i * blockSize, j * blockSize + 16));

				if (c == 0) rect.setOutlineThickness(0);
				else rect.setOutlineThickness(1);

				window.draw(rect);
			}
		}
	}
	
	for (i = -1; i < obj->size; i++) {
		rect.setOutlineThickness(1);
		rect.setFillColor(color[objType - 10]);
		rect.setPosition(Vector2f(obj->pos[i].x * blockSize + sM3, obj->pos[i].y * blockSize + 16 + sM2));

		window.draw(rect);
	}

	window.draw(banner);

	text.setFillColor(White);
	text.setPosition(Vector2f(3, -5));

	text.setString(to_string(score));
	window.draw(text);

	FullScreen.setFillColor(Color(0, 0, 0, alpha));
	window.draw(FullScreen);

	if (lvl == pause_Code) {
		menu_words[0].setString("pause");
		menu_words[0].setFillColor(Color(255, 255, 255, alpha));

		menu_words[1].setString("RESTART");
		menu_words[1].setFillColor(Color(255, 255, 255, alpha));

		menu_words[2].setString("MENU");
		menu_words[2].setFillColor(Color(255, 255, 255, alpha));

		window.draw(menu_words[0]);
		window.draw(menu_words[1]);
		window.draw(menu_words[2]);
	}
}

void game::draw() {
	window.clear(White);

	if (lvl == menu_Code) menu();
	else play();

	window.display();
}

void game::check() {
	for (y = h - 1; y >= 0; y--)
	{
		for (x = 0; x < w; ++x)
		{
			if (map[x][y] == 0)
			{
				break;
			}
		}

		if (x >= w)
		{
			moveAllDown(y);
			++y;
		}
	}

	addPoints = (addPoints)?false:true;
}

void game::setScore() {
	if (lvl == 3) if (speed >= 0.11) speed -= 0.1;

	multi++;
	
	if (addPoints) {
		R += multi;
		addPoints = false;
	}
	else if (!addPoints){
		R = multi;
		addPoints = true;
	}

	score += R;

	
	text.setString(to_string(score));
}

void game::moveAllDown(short y) {
	setScore(); 
	
	height = y;

	M1 = -blockSize;
	for (; y >= 0; y--) {
		for (k = 0; k < w; k++) {
			if (y > 0) {
				if (map[k][y - 1] == objType) {
					if (map[k][y] == objType) map[k][y] = objType;
					else map[k][y] = 0;
				}
				else {
					map[k][y] = map[k][y - 1];
				}
			}
			else {
				map[k][y] = 0;
			}
		}
	}
	
	lerpM1 = new Thread(bind(&Lerp, &M1, 0, 0.2));
	lerpM1->launch();

	lerpM1->wait();
	k = 0;
}

void game::newObject() {
	objType = rand() % 8;

	obj = objList[objType];
	obj->reset();

	objType = objType + 11;

	if (moveDown(false) == 0) reset();
}

void game::rotate() {
	Point minP(w - 1, h - 1), maxP(0, 0), dP(0, 0), tempP[4]{Point(0,0), Point(0,0), Point(0,0), Point(0,0)};
	bool reload = false;

	for (k = 0; k < obj->size; k++)
	{
		if (minP.x > obj->pos[k].x) minP.x = obj->pos[k].x;
		if (minP.y > obj->pos[k].y) minP.y = obj->pos[k].y;
	}

	for (k = 0; k < obj->size; k++)
	{
		tempP[k] = obj->pos[k];

		map[obj->pos[k].x][obj->pos[k].y] = 0;

		dP.x = obj->pos[k].x - minP.x;
		dP.y = obj->pos[k].y - minP.y;

		if (maxP.x > dP.x) maxP.x = dP.x;
		if (maxP.y > dP.y) maxP.y = dP.y;

		dP.swap();
		dP.x *= -1;

		obj->pos[k].x = minP.x + dP.x;
		obj->pos[k].y = minP.y + dP.y;
	}

	for (k = 0; k < obj->size; k++)
	{
		obj->pos[k].x += obj->dist;

		if (obj->pos[k].x >= w || obj->pos[k].x < 0 || obj->pos[k].y >= h || obj->pos[k].y < 0 || map[obj->pos[k].x][obj->pos[k].y] != 0 && map[obj->pos[k].x][obj->pos[k].y] != objType) reload = true;
	}

	for (k = 0; k < obj->size; k++)
	{
		if (reload) {
			obj->pos[k].x = tempP[k].x;
			obj->pos[k].y = tempP[k].y;
		}

		map[obj->pos[k].x][obj->pos[k].y] = objType;
	}
}

short game::moveDown(bool fall) {
	if (M2 == 0) {
		for (k = 0; k < obj->size; )
		{
			if (obj->pos[k].y + 1 >= h) break;
			if (map[obj->pos[k].x][obj->pos[k].y + 1] != 0 && map[obj->pos[k].x][obj->pos[k].y + 1] != objType)
			{
				if (obj->pos[k].y == obj->Start_pos[k].y) return 0;
				else break;
			}
			k++;
		}

		if (k == obj->size) {
			M2 = -blockSize;
			for (k = 0; k < obj->size; k++)
			{
				if (obj->pos[k].y >= 0)	map[obj->pos[k].x][obj->pos[k].y] = 0;
			}

			for (k = 0; k < obj->size; k++)
			{
				map[obj->pos[k].x][++obj->pos[k].y] = objType;
			}


			lerpM2 = new Thread(bind(&Lerp, &M2, 0, speed * (fall)?0.05:0.1));
			lerpM2->launch();

			lerpM2->wait();

			return 1;
		}
		else {
			for (k = 0; k < obj->size; k++)
			{
				map[obj->pos[k].x][obj->pos[k].y] = objType - 10;
			}


			newObject();

			check();

			return 2;
		}
	}

	return 0;
}

void game::moveLeft() {
	for (k = 0; k < obj->size; )
	{
		if (obj->pos[k].x <= 0) break;

		if (map[obj->pos[k].x - 1][obj->pos[k].y] != 0 && map[obj->pos[k].x - 1][obj->pos[k].y] != objType) break;

		k++;
	}

	if (k == obj->size) {
		for (k = 0; k < obj->size; k++)
		{
			map[obj->pos[k].x][obj->pos[k].y] = 0;
		}

		for (k = 0; k < obj->size; k++)
		{
			M3 = blockSize;
			if (lvl == 1) map[(--obj->pos[k].x) % 8][obj->pos[k].y] = objType;
			else map[--obj->pos[k].x][obj->pos[k].y] = objType;
		}

		lerpM3 = new Thread(bind(&Lerp, &M3, 0, speed * 0.1));
		lerpM3->launch();

		lerpM3->wait();
	}
}

void game::moveRight() {
	for (k = 0; k < obj->size; )
	{
		if (obj->pos[k].x + 1 >= w) break;

		if (map[obj->pos[k].x + 1][obj->pos[k].y] != 0 && map[obj->pos[k].x + 1][obj->pos[k].y] != objType) break;

		k++;
	}

	if (k == obj->size) {
		for (k = 0; k < obj->size; k++)
		{
			map[obj->pos[k].x][obj->pos[k].y] = 0;
		}

		for (k = 0; k < obj->size; k++)
		{
			M3 = -blockSize;
			if (lvl == 1) map[(++obj->pos[k].x) % 8][obj->pos[k].y] = objType;
			else map[++obj->pos[k].x][obj->pos[k].y] = objType;
		}

		lerpM3 = new Thread(bind(&Lerp, &M3, 0, speed * 0.1));
		lerpM3->launch();

		lerpM3->wait();
	}
}