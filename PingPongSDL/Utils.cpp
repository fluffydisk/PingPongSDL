#include "Utils.h"

SDL_Window* Utils::Window = nullptr;
SDL_Renderer* Utils::Renderer = nullptr;
SDL_Event Utils::Events;
TTF_Font* Utils::WelcomeFont = nullptr;
TTF_Font* Utils::InGameFont = nullptr;

SDL_Texture* Utils::OnePlayer = nullptr; 
SDL_Texture* Utils::TwoPlayer = nullptr;
SDL_Texture* Utils::PressKeyWarning = nullptr;
SDL_Texture* Utils::UnDefetableBot = nullptr;
SDL_Texture* Utils::Player1 = nullptr;
SDL_Texture* Utils::Player2 = nullptr;
SDL_Texture* Utils::WelcomeGame = nullptr;

SDL_Texture* Utils::OnePlayerPoint = nullptr;
SDL_Texture* Utils::TwoPlayerPoint = nullptr;

bool Utils::MouseLeft = false;
bool Utils::MouseRight = false;
int Utils::MouseX = 0;
int Utils::MouseY = 0;

void Utils::init()
{
	Window = SDL_CreateWindow("PingPongSDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenWidth, ScreenHeight, NULL);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	WelcomeFont = TTF_OpenFont("Dependencies/Fonts/WelcomeScreenFont.ttf", 24);
	InGameFont = TTF_OpenFont("Dependencies/Fonts/InGameFont.ttf", 24);

	UpdateTexture("Welcome to PingPongSDL game, please choose an option to start", InGameFont, WelcomeGame, WHITE);
	UpdateTexture("Press any key to start the game!", InGameFont,PressKeyWarning, BLACK);
	UpdateTexture("One Player(Against Computer)", WelcomeFont, OnePlayer, BLACK);
	UpdateTexture("Two Players (Against Human)", WelcomeFont, TwoPlayer, BLACK);
	UpdateTexture("0", InGameFont,OnePlayerPoint, BLACK);
	UpdateTexture("0", InGameFont,TwoPlayerPoint, BLACK);
	UpdateTexture("Undefeatable Bot", InGameFont,UnDefetableBot, BLACK);
	UpdateTexture("Controls: W and S keys)", InGameFont,Player1, BLACK);
	UpdateTexture("Controls: Up and Down arrows", InGameFont,Player2, BLACK);
}

void Utils::UpdateTexture(std::string point, TTF_Font* font, SDL_Texture*& oldTexture, SDL_Color color)
{
	// Destroy the old texture
	if (oldTexture)
	{
		SDL_DestroyTexture(oldTexture);
		oldTexture = nullptr;
	}

	// Create a new surface
	SDL_Surface* tempSurface = TTF_RenderText_Solid(font, point.c_str(), color);
	if (!tempSurface)
	{
		std::cout << "Could not create Surface from Font: " << TTF_GetError() << std::endl;
		return;
	}

	// Create a new texture from the surface
	oldTexture = SDL_CreateTextureFromSurface(Renderer, tempSurface);
	if (!oldTexture)
	{
		std::cout << "Could not create Texture from Surface: " << SDL_GetError() << std::endl;
	}

	// Free the surface
	SDL_FreeSurface(tempSurface);
}
