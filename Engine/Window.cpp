#include "Window.h"
#include "InitError.h"

Window::Window(std::string title, int windowWidth, int windowHeight)
{
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	if (window == nullptr)
	{
		throw InitError();
	}
}

SDL_Surface* Window::getSurface()
{
	return SDL_GetWindowSurface(window);
}

void Window::GetWindowSize(int* w, int* h)
{
	SDL_GetWindowSize(window, w, h);
}

SDL_Window* Window::GetWindow()
{
	return window;
}

void Window::updateSurface()
{
	SDL_UpdateWindowSurface(window);
}

Window::~Window()
{
	SDL_DestroyWindow(window);
}
