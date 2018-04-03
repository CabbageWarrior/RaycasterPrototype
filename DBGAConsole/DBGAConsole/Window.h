#pragma once
#include <SDL.h>
#include <string>
#include <tuple>


class Window
{
public:
	Window(const std::string & WindowName,  int XPos,  int YPos,  int W,  int H,  Uint32 Flags);
	~Window();
	
	SDL_Surface   *	const			GetWindowSurface()		const;
	const Uint32					GetWindowPixelFormat()	const;
	std::pair<unsigned int, unsigned int>				GetWindowSize()			const;

	void							UpdateWindowSurface();

private:
	SDL_Window* WindowPtr;
	
};

