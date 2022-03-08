#pragma once
#include <SDL.h>
#include <string>
class Window
{
public:
	Window(std::string title, int windowWidth, int windowHeight);

	//Returns surface
	SDL_Surface* getSurface();

	//Returns the window size
	void GetWindowSize(int*w, int*h);

	//Returns the window
	SDL_Window* GetWindow();

	//Update surface
	void updateSurface();

	~Window();
private:
	SDL_Window* window;
};

