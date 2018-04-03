#include "stdafx.h"
#include "Surface.h"


Surface::Surface(unsigned int Width, unsigned int Height, unsigned int Depth, uint32_t Format)
{
	OwnedSurface = SDL_CreateRGBSurfaceWithFormat(0, Width, Height, Depth, Format);
}


Surface::Surface(SDL_Surface * SurfaceToOwn) : OwnedSurface(SurfaceToOwn)
{

}

SDL_Surface * const Surface::GetOwnedSurface() const
{
	return OwnedSurface;
}

Surface::~Surface()
{
	if (OwnedSurface)
	{
		SDL_FreeSurface(OwnedSurface);
	}
}
