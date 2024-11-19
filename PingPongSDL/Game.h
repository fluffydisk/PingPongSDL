#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <cstdlib>
#include <ctime>

#include <iostream>
#include "Utils.h"

class Game
{
public:
	
	Game();
	~Game();

	bool GameEnd();
	void Update();

private:
	struct Rect
	{
		bool isAi;
		int ballSpeed;
		SDL_Rect rect;
		int velocityY;
		int velocityX;
		void UpdatePosition(Rect &Ball);
		int score;
	};
	Rect Player1;
	Rect Player2;
	Rect Ball;

	enum Scene{WelcomeScene, OnePlayerGame, TwoPlayerGame};
	Scene SceneManager;

	bool InColission(Rect Ball, Rect Paddle);

	int keyPressed;
	void ResetPositions();
	void DisplayPressKeyWarning();
	void StartBallMovement();

	void ExpandAnimation(SDL_Rect &trasform, bool& animationController);
	void ShrinkAnimation(SDL_Rect &trasform, bool& animationController);

	void WelcomeScreen();
	void GameLoop();
	void BallLogic();
	void RestartGameIfNeeded();

	void HandleEvents();
	bool gameEnd;

};

