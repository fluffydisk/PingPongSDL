#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

class Utils
{
public:
	#define BLACK SDL_Color { 0, 0, 0, 255 }
	#define WHITE SDL_Color { 255, 255, 255, 255 }
	static void init();

	static constexpr int ScreenWidth = 800;
	static constexpr int ScreenHeight = 600;



	static SDL_Window* Window;
	static SDL_Renderer* Renderer;
	static SDL_Event Events;
	static TTF_Font* WelcomeFont;
	static TTF_Font* InGameFont;

	static SDL_Texture* WelcomeGame;
	static SDL_Texture* OnePlayer;
	static SDL_Texture* TwoPlayer;
	static SDL_Texture* OnePlayerPoint;
	static SDL_Texture* TwoPlayerPoint;
	static SDL_Texture* PressKeyWarning;
	static SDL_Texture* UnDefetableBot;
	static SDL_Texture* Player1;
	static SDL_Texture* Player2;

	static void UpdateTexture(std::string point, TTF_Font* font, SDL_Texture*& oldTexture, SDL_Color color);

	static int MouseX, MouseY;
	static bool MouseLeft, MouseRight;
};

