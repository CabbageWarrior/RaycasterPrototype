#pragma once
#include <SDL.h>

class Surface
{
public:
	Surface(unsigned int Width, unsigned int Height, unsigned int Depth, uint32_t Format);
	Surface(SDL_Surface * SurfaceToOwn);
	SDL_Surface * const GetOwnedSurface() const;
	~Surface();

private:
	SDL_Surface * OwnedSurface;
};

