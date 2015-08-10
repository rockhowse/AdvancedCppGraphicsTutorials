#include "MainGame.h"

#include <iostream>
#include <string>
#include "Errors.h"

MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;

	_gameState = GameState::PLAY;
}

MainGame::~MainGame()
{
}

void MainGame::run() {
	initSystems();

	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

	gameLoop();
}

void MainGame::initSystems() {
	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Open an SDL window
	_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr) {
		fatalError("SDL Window could not be created.");
	}

	// Set up our OpenGL Context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);

	if (glContext == nullptr) {
		fatalError("SDL_GL Context could not be created.");
	}

	// Set up glew (optional but recommended
	// might help with compatabilty issues for some people
	// glewExperimental = true;
	
	GLenum error = glewInit();

	if (error != GLEW_OK) {
		fatalError("Could not initalize GLEW.");
	}

	//Tell SDL that we want a double buffered windo so we don't get any flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0, 0.0, 1.0, 1.0);

	// initialize the shaders
	initShaders();
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("./Shaders/colorShading.vert", "./Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.linkShaders();
}

void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		processInput();
		drawGame();
	}
}

void MainGame::processInput() {
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)){
		switch (evnt.type){
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
				break;
		}
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.use();

	_sprite.draw();

	_colorProgram.unuse();

	SDL_GL_SwapWindow(_window);
}

