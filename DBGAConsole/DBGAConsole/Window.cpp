#include "stdafx.h"
#include "Window.h"
#include <iostream>
#include <cassert>

Window::Window(const std::string & WindowName,  int XPos,  int YPos,  int W,  int H,  Uint32 Flags)
{
	WindowPtr = SDL_CreateWindow(WindowName.c_str(), XPos, YPos, W, H, Flags);
	
	if (!WindowPtr)
	{
		std::cout << "Errors in windows creation " << SDL_GetError() << std::endl;
		assert(nullptr);
	}
}


Window::~Window()
{
	SDL_DestroyWindow(WindowPtr);
}

SDL_Surface * const Window::GetWindowSurface() const
{
	SDL_Surface * screenSuface = SDL_GetWindowSurface( WindowPtr );
	return screenSuface;
}

const Uint32 Window::GetWindowPixelFormat() const
{
	return SDL_GetWindowPixelFormat(WindowPtr);
}

std::pair<unsigned int, unsigned int> Window::GetWindowSize() const
{
	int w, h;
	SDL_GetWindowSize(WindowPtr, &w, &h);
	return std::pair<unsigned int, unsigned int>( static_cast<unsigned int>(w), static_cast<unsigned int>(h));
}

void Window::UpdateWindowSurface()
{
	SDL_UpdateWindowSurface( WindowPtr );
}

