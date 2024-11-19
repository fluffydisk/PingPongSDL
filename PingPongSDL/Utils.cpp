#include "Utils.h"

SDL_Window* Utils::Window = nullptr;
SDL_Renderer* Utils::Renderer = nullptr;
SDL_Event Utils::Events;
TTF_Font* Utils::WelcomeFont = nullptr;
TTF_Font* Utils::InGameFont = nullptr;

SDL_Texture* Utils::OnePlayer = nullptr; 
SDL_Texture* Utils::TwoPlayer = nullptr;
SDL_Texture* Utils::PressKeyWarning = nullptr;

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

	SDL_Surface* tempSurface1 = TTF_RenderText_Solid(WelcomeFont, "One Player (Against Computer)", SDL_Color{255, 255, 255, 255});
	SDL_Surface* tempSurface2 = TTF_RenderText_Solid(WelcomeFont, "Two Players (Against Human)", SDL_Color{ 255, 255, 255, 255 });
	SDL_Surface* tempSurface3 = TTF_RenderText_Solid(WelcomeFont, "0", SDL_Color{ 0, 0, 0, 255 });
	SDL_Surface* tempSurface4 = TTF_RenderText_Solid(WelcomeFont, "0", SDL_Color{ 0, 0, 0, 255 });
	SDL_Surface* tempSurface5 = TTF_RenderText_Solid(WelcomeFont, "Press any key to start the game!", SDL_Color{ 0, 0, 0, 255 });

	if (!tempSurface1 || !tempSurface2)
	{
		std::cout << "Couldnt create Surface from Font" << std::endl;
		SDL_FreeSurface(tempSurface1);
		SDL_FreeSurface(tempSurface2);
		SDL_FreeSurface(tempSurface3);
		SDL_FreeSurface(tempSurface4);
		SDL_FreeSurface(tempSurface5);
		tempSurface1 = nullptr;
		tempSurface2 = nullptr;
		tempSurface3 = nullptr;
		tempSurface4 = nullptr;
		tempSurface5 = nullptr;
	}
	else
	{
		OnePlayer = SDL_CreateTextureFromSurface(Renderer, tempSurface1);	
		TwoPlayer = SDL_CreateTextureFromSurface(Renderer, tempSurface2);
		OnePlayerPoint = SDL_CreateTextureFromSurface(Renderer, tempSurface3);
		TwoPlayerPoint = SDL_CreateTextureFromSurface(Renderer, tempSurface4);
		PressKeyWarning = SDL_CreateTextureFromSurface(Renderer, tempSurface5);


		SDL_FreeSurface(tempSurface1);
		SDL_FreeSurface(tempSurface2);
		SDL_FreeSurface(tempSurface3);
		SDL_FreeSurface(tempSurface4);
		SDL_FreeSurface(tempSurface5);
		tempSurface1 = nullptr;
		tempSurface2 = nullptr;
		tempSurface3 = nullptr;
		tempSurface4 = nullptr;
		tempSurface5 = nullptr;
	}
}

void Utils::UpdateTexture(std::string point, SDL_Texture*& oldTexture)
{
	// Destroy the old texture
	if (oldTexture) {
		SDL_DestroyTexture(oldTexture);
		oldTexture = nullptr; // Avoid dangling pointer
	}

	// Create a new surface
	SDL_Surface* tempSurface = TTF_RenderText_Solid(InGameFont, point.c_str(), SDL_Color{ 0, 0, 0, 255 });
	if (!tempSurface)
	{
		std::cout << "Could not create Surface from Font: " << TTF_GetError() << std::endl;
		return; // Exit early
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
