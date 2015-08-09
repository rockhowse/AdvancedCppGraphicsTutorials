#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include "Sprite.h"

enum class GameState {PLAY, EXIT};
class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;

	GameState _gameState;

	void initSystems();
	void gameLoop();
	void processInput();
	void drawGame();

	Sprite _sprite;
};

