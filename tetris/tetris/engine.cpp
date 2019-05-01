#include "game.h"
using namespace sf;

game *Game;

void renderingThread()
{
	Game->window.setActive(true);
	
	while (Game->window.isOpen()) {
		Game->draw();
	}
}

int main()
{
	Game = new game();
	
	Game->window.create(VideoMode(w * blockSize, h * blockSize + 16), "TETRIS", Style::Default, ContextSettings(32));
	Game->window.setVerticalSyncEnabled(true);
	
	Event event;

	Game->window.setActive(false);

	Thread thread(&renderingThread);
	thread.launch();

	bool running = true;

	while (running)
	{
		Game->timer(Game->speed);

		while (Game->window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				running = false;

				Game->window.close();
				break;
			case Event::LostFocus:
				if (Game->getLVL() != menu_Code && Game->getLVL() != pause_Code)	Game->pause();
				break;
			case Event::GainedFocus:
				if (Game->getLVL() != menu_Code && Game->getLVL() != pause_Code)	Game->resume();
				break;
			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Escape:
					if (Game->getLVL() != menu_Code && Game->getLVL() != pause_Code)	Game->pause();
					else if (Game->getLVL() == pause_Code) Game->resume();
					else {
						running = false;
						Game->window.close();
					}
				break;
				case Keyboard::Space:
					if (Game->getLVL() != menu_Code && Game->getLVL() != pause_Code)	Game->rotate();
					else Game->menu_controll(MC_start);
				break;
				case Keyboard::Left:
					if (Game->getLVL() != menu_Code && Game->getLVL() != pause_Code)	Game->moveLeft();
					else Game->menu_controll(MC_left);
				break;
				case Keyboard::Right:
					if (Game->getLVL() != menu_Code && Game->getLVL() != pause_Code)	Game->moveRight();
					else Game->menu_controll(MC_right);
					break;
				case Keyboard::Up:
					if (Game->getLVL() != menu_Code && Game->getLVL() != pause_Code)	while (Game->moveDown(true) != 2);
					else Game->menu_controll(MC_up); 
					break;
				case Keyboard::Down:
					if (Game->getLVL() != menu_Code && Game->getLVL() != pause_Code)	Game->moveDown(false);
					else Game->menu_controll(MC_down); 
					break;
				}
				break;
			default:
				break;
			}
		}
	}

	return 0;
}