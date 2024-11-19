#include "Game.h" 
#include <string>

Game::Game() : gameEnd(false), Ball(), Player1(), Player2(), SceneManager(WelcomeScene), keyPressed(false)
{

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Could not initialize SDL, Error message: " << SDL_GetError() << std::endl;
		gameEnd = true;
	}
	if (TTF_Init() == -1)
	{
		std::cout << "Could not initialize SDL_TTF, Error message: " << TTF_GetError() << std::endl;
		gameEnd = true;
	}

	//Initialize Utils class
	Utils::init();

	//Initialize SDL_Windows
	if (!Utils::Window)
	{
		std::cout << "Could not create the window, Error message: " << SDL_GetError() << std::endl;
		gameEnd = true;
	}

	//Initialize SDL_Renderer
	if (!Utils::Renderer)
	{
		std::cout << "Could not create the renderer, Error message: " << SDL_GetError() << std::endl;
		gameEnd = true;
	}

	//Assing positions for objects
	Player1.rect = { 10, 250, 20, 100 };
	Player2.rect = { 770, 250, 20, 100 };
	
	Ball.rect = { 390, 290, 20, 20 };
	Ball.ballSpeed = 5;

	Player1.score, Player2.score = 0;
	
	Player1.isAi = false;
	Player2.isAi = false;
	srand(static_cast<unsigned>(time(0)));
}

Game::~Game()
{
	//Free Renderer and Window
	SDL_DestroyRenderer(Utils::Renderer);
	SDL_DestroyWindow(Utils::Window);
	Utils::Renderer = nullptr;
	Utils::Window = nullptr;

	//Free Fonts
	TTF_CloseFont(Utils::WelcomeFont);
	TTF_CloseFont(Utils::InGameFont);
	Utils::WelcomeFont = nullptr;
	Utils::InGameFont = nullptr;
}

void Game::Update()
{
	// Set background color to white and clear the screen
	SDL_SetRenderDrawColor(Utils::Renderer, 255, 255, 255, 255);
	SDL_RenderClear(Utils::Renderer);

	HandleEvents();

	if (SceneManager == WelcomeScene)
	{
		WelcomeScreen();
	}
	else
	{
		GameLoop();
	}

	SDL_RenderPresent(Utils::Renderer);
}

//Welcome Screen loop
void Game::WelcomeScreen()
{
	SDL_Rect TwoPlayerRect, OnePlayerRect;

	OnePlayerRect = { 0, 0, Utils::ScreenWidth / 2,  Utils::ScreenHeight };
	TwoPlayerRect = { Utils::ScreenWidth / 2, 0, Utils::ScreenWidth / 2,  Utils::ScreenHeight };

	SDL_SetRenderDrawColor(Utils::Renderer, 0, 255, 0, 255);	
	SDL_RenderFillRect(Utils::Renderer, &OnePlayerRect);

	SDL_SetRenderDrawColor(Utils::Renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(Utils::Renderer, &TwoPlayerRect);

	static SDL_Rect OnePlayerTextRect{ 50, 250, 300, 40 };
	static SDL_Rect TwoPlayerTextRect{ 450, 250, 300, 40 };
	static bool ShrinkOne = false;
	static bool ShrinkTwo = false;


	if (Utils::MouseX > OnePlayerRect.x && Utils::MouseX < OnePlayerRect.x + OnePlayerRect.w)
	{
		if (Utils::MouseLeft)
		{
			SceneManager = OnePlayerGame;
		}

		//Animation effect
		if (ShrinkOne) {
			OnePlayerTextRect.w += 2;
			OnePlayerTextRect.h += 2;
			OnePlayerTextRect.x -= 1;
			OnePlayerTextRect.y -= 1;
			if (OnePlayerTextRect.w >= 335)
			{
				ShrinkOne = false;
			}
		}
	}
	else
	{
		if (!ShrinkOne)
		{
			OnePlayerTextRect.w -= 2;
			OnePlayerTextRect.h -= 2;
			OnePlayerTextRect.x += 1;
			OnePlayerTextRect.y += 1;
			if (OnePlayerTextRect.w <= 300)
			{
				ShrinkOne = true;
				OnePlayerTextRect = { 50, 250, 300, 40 };
			}
		}
	}

	if (Utils::MouseX > TwoPlayerRect.x && Utils::MouseX < TwoPlayerRect.x + TwoPlayerRect.w-1)
	{
		if (Utils::MouseLeft)
		{
			SceneManager = TwoPlayerGame;
		}
		//Animation effect
		if (ShrinkTwo) {
			TwoPlayerTextRect.w += 2;
			TwoPlayerTextRect.h += 2;
			TwoPlayerTextRect.x -= 1;
			TwoPlayerTextRect.y -= 1;
			if (TwoPlayerTextRect.w >= 335)
			{
				ShrinkTwo = false;
			}
		}
	}
	else
	{
		if (!ShrinkTwo)
		{
			TwoPlayerTextRect.w -= 2;
			TwoPlayerTextRect.h -= 2;
			TwoPlayerTextRect.x += 1;
			TwoPlayerTextRect.y += 1;
			if (TwoPlayerTextRect.w <= 300)
			{
				TwoPlayerTextRect = { 450, 250, 300, 40 };
				ShrinkTwo = true;
			}
		}
	}

	
	std::cout << OnePlayerTextRect.w << std::endl;

	SDL_RenderCopy(Utils::Renderer, Utils::OnePlayer, NULL, &OnePlayerTextRect);
	SDL_RenderCopy(Utils::Renderer, Utils::TwoPlayer, NULL, &TwoPlayerTextRect);
}

//Game Loop
void Game::GameLoop()
{
	RestartGameIfNeeded();

	if (SceneManager == OnePlayerGame)
	{
		Player2.isAi = true;
	}
	else
	{
		Player2.isAi = false;
	}

	Player1.UpdatePosition(Ball);
	Player2.UpdatePosition(Ball);


	Ball.UpdatePosition(Ball);
	BallLogic();

	SDL_Rect OnePlayerPointRect = { 300, 100, 60, 100 };
	SDL_Rect TwoPlayerPointRect = { 400, 100, 60, 100 };

	SDL_RenderCopy(Utils::Renderer, Utils::OnePlayerPoint, NULL, &OnePlayerPointRect);
	SDL_RenderCopy(Utils::Renderer, Utils::TwoPlayerPoint, NULL, &TwoPlayerPointRect);

	//Set the renderer color black for drawing objects
	SDL_SetRenderDrawColor(Utils::Renderer, 0, 0, 0, 255); 
	
	//Render objects
	SDL_RenderFillRect(Utils::Renderer, &Player1.rect);
	SDL_RenderFillRect(Utils::Renderer, &Player2.rect);
	SDL_RenderFillRect(Utils::Renderer, &Ball.rect);
}

//Takes cares of SDL_Event
void Game::HandleEvents()
{
	const Uint8* currentKeyState = SDL_GetKeyboardState(NULL); // Get current key states

	while (SDL_PollEvent(&Utils::Events))
	{
		// Quit
		if (Utils::Events.type == SDL_QUIT)
		{
			gameEnd = true;
		}

		if (Utils::Events.type == SDL_KEYDOWN && keyPressed != 2)
		{
			keyPressed = 1;
		}

		

		// Update mouse position
		SDL_GetMouseState(&Utils::MouseX, &Utils::MouseY);

		// Mouse clicks
		if (Utils::Events.type == SDL_MOUSEBUTTONDOWN)
		{
			if (Utils::Events.button.button == SDL_BUTTON_LEFT)
			{
				Utils::MouseLeft = true;
			}
			if (Utils::Events.button.button == SDL_BUTTON_RIGHT)
			{
				Utils::MouseRight = true;
			}
		}
		if (Utils::Events.type == SDL_MOUSEBUTTONUP)
		{
			if (Utils::Events.button.button == SDL_BUTTON_LEFT)
			{
				Utils::MouseLeft = false;
			}
			if (Utils::Events.button.button == SDL_BUTTON_RIGHT)
			{
				Utils::MouseRight = false;
			}
		}

		// Player1 controls (press to start moving, release to stop)
		if (SceneManager != WelcomeScene)
		{
			if (currentKeyState[SDL_SCANCODE_W]) // W key pressed
			{
				Player1.velocityY = -10; // Move up
			}
			else if (currentKeyState[SDL_SCANCODE_S]) // S key pressed
			{
				Player1.velocityY = 10; // Move down
			}
			else
			{
				Player1.velocityY = 0; // Stop movement when no key is pressed
			}

			// Player2 controls
			if (SceneManager != OnePlayerGame)
			{
				if (currentKeyState[SDL_SCANCODE_UP]) // Up arrow pressed
				{
					Player2.velocityY = -10; // Move up
				}
				else if (currentKeyState[SDL_SCANCODE_DOWN]) // Down arrow pressed
				{
					Player2.velocityY = 10; // Move down
				}
				else
				{
					Player2.velocityY = 0; // Stop movement when no key is pressed
				}
			}
		}
	}
}

//Checks if Ball collided with the given Paddle, returns bool
bool Game::InColission(Rect Ball, Rect Paddle)
{
	return Ball.rect.x < Paddle.rect.x + Paddle.rect.w &&
		Ball.rect.x + Ball.rect.w > Paddle.rect.x &&
		Ball.rect.y < Paddle.rect.y + Paddle.rect.h &&
		Ball.rect.y + Ball.rect.h > Paddle.rect.y;

}

//Does the reflection effect at the corners and the Paddles
void Game::BallLogic()
{

	if (Ball.rect.x <= 0 || Ball.rect.x + Ball.rect.w >= Utils::ScreenWidth)
	{
		if (Ball.rect.x <= 0)
		{
			keyPressed = 0;
			Player2.score++;
			Utils::UpdateTexture(std::to_string(Player2.score), Utils::TwoPlayerPoint);
		}
		else if (Ball.rect.x + Ball.rect.w >= Utils::ScreenWidth)
		{
			keyPressed = 0;
			Player1.score++;
			Utils::UpdateTexture(std::to_string(Player1.score), Utils::OnePlayerPoint);

		}
		Ball.velocityX = Ball.velocityX * -1;
	}

	if (Ball.rect.y <= 0 || Ball.rect.y + Ball.rect.h >= Utils::ScreenHeight - 1)
	{
		Ball.velocityY = Ball.velocityY * -1;
		
	}

	if (InColission(Ball, Player1))
	{
		// Generate a random velocityY while preserving speed
		Ball.velocityY = ((rand() % 17) - 8); // Random Y component in range [-8, 8]

		// Clamp velocityY to ensure it's within the allowable range
		if (Ball.velocityY > Ball.ballSpeed)
			Ball.velocityY = Ball.ballSpeed - 1;
		else if (Ball.velocityY < -Ball.ballSpeed)
			Ball.velocityY = -Ball.ballSpeed + 1;

		// Recalculate velocityX while preserving direction and speed
		float remainingSpeedSquared = Ball.ballSpeed * Ball.ballSpeed - Ball.velocityY * Ball.velocityY;
		Ball.velocityX = (remainingSpeedSquared > 0) ? sqrt(remainingSpeedSquared) : 0;

		// Ensure X velocity is positive (moving to the right after hitting Player1)
		Ball.velocityX = fabs(Ball.velocityX);
	}
	else if (InColission(Ball, Player2))
	{
		// Generate a random velocityY while preserving speed
		Ball.velocityY = ((rand() % 17) - 8); // Random Y component in range [-8, 8]

		// Clamp velocityY to ensure it's within the allowable range
		if (Ball.velocityY > Ball.ballSpeed)
			Ball.velocityY = Ball.ballSpeed - 1;
		else if (Ball.velocityY < -Ball.ballSpeed)
			Ball.velocityY = -Ball.ballSpeed + 1;

		// Recalculate velocityX while preserving direction and speed
		float remainingSpeedSquared = Ball.ballSpeed * Ball.ballSpeed - Ball.velocityY * Ball.velocityY;
		Ball.velocityX = (remainingSpeedSquared > 0) ? sqrt(remainingSpeedSquared) : 0;

		// Ensure X velocity is negative (moving to the left after hitting Player2)
		Ball.velocityX = -fabs(Ball.velocityX);
	}
}

void Game::RestartGameIfNeeded()
{
	static int lastPlayer1Score = 0, lastPlayer2Score = 0;

	// Check if scores have changed or if a new game has started
	if (Player1.score != lastPlayer1Score || Player2.score != lastPlayer2Score)
	{
		if (Ball.ballSpeed < 10)
		{
			Ball.ballSpeed++;
		}
		ResetBallPosition();

		// Display the "Press any key" warning
		

		// Update the last recorded scores
		lastPlayer1Score = Player1.score;
		lastPlayer2Score = Player2.score;
		keyPressed = 0;
	}

	// Start the ball movement when a key is pressed
	if (keyPressed==0) 	
		DisplayPressKeyWarning();
	if (keyPressed == 1)
	{
		StartBallMovement();
		keyPressed = 2; // Ensure this block runs only once
	}

}

// Helper function to reset the ball's position
void Game::ResetBallPosition()
{
	Ball.rect.x = 390;
	Ball.rect.y = 290;
	Ball.velocityX = 0;
	Ball.velocityY = 0;
}

// Helper function to display the "Press any key" warning
void Game::DisplayPressKeyWarning()
{
	SDL_Rect rect = { 30, 500, 740, 50 };
	SDL_RenderCopy(Utils::Renderer, Utils::PressKeyWarning, NULL, &rect);
}

// Helper function to start the ball movement
void Game::StartBallMovement()
{
	// Generate a random angle, ensuring it avoids 60��120� and 240��300�
	int randomAngle = rand() % 360;
	if (randomAngle >= 60 && randomAngle <= 120) randomAngle += 60;    // Shift to valid range
	if (randomAngle >= 240 && randomAngle <= 300) randomAngle += 60;  // Shift to valid range

	double angle = randomAngle * (M_PI / 180.0); // Convert to radians

	Ball.velocityX = Ball.ballSpeed * cos(angle);
	Ball.velocityY = Ball.ballSpeed * sin(angle);
}





//Checks the borders and updates the position as its velocity
void Game::Rect::UpdatePosition(Rect &Ball)
{
	if (!this->isAi)
	{
		//Update y Pos
		if (this->rect.y >= 0 && this->rect.y + this->rect.h <= Utils::ScreenHeight)
		{
			this->rect.y += velocityY;
		}
		if (this->rect.y < 0)
		{
			this->rect.y = 0;
		}
		if (this->rect.y + this->rect.h > Utils::ScreenHeight)
		{
			this->rect.y = Utils::ScreenHeight - this->rect.h;
		}


		//Update x Pos
		if (this->rect.x >= 0 && this->rect.x + this->rect.w <= Utils::ScreenWidth)
		{
			this->rect.x += velocityX;
		}
		if (this->rect.x < 0)
		{
			this->rect.x = 0;
		}
		if (this->rect.x + this->rect.w > Utils::ScreenWidth)
		{
			this->rect.x = Utils::ScreenWidth - this->rect.w;
		}
	}
	else
	{
		this->rect.y = Ball.rect.y - Ball.rect.h;
	}
	if (this->rect.y < 0)
	{
		this->rect.y = 0;
	}
	if (this->rect.y + this->rect.h > Utils::ScreenHeight)
	{
		this->rect.y = Utils::ScreenHeight - this->rect.h;
	}
}

//Returns if game ended
bool Game::GameEnd()
{
	return gameEnd;
}