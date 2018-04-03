#include "stdafx.h"
#include "Image.h"
#include <assert.h>


Image::Image()
{
}


Image::Image(unsigned int Width, unsigned int Height) : Width(Width), Height(Height), Data(Width * Height)
{
}

Vector3 & Image::SetData(unsigned int X, unsigned int Y)
{
	assert(X < Width && Y < Height);
	return Data[Y * Width + X];
}

Vector3 & Image::operator[](unsigned int Index)
{
	assert(Index < Width * Height);
	return Data[Index];
}

Vector3 & Image::operator[](std::pair<unsigned int, unsigned int> Coordinates)
{
	return SetData(Coordinates.first, Coordinates.second); 
}

bool Image::FillSurface(Surface & surface)
{
	return FillSurface(surface.GetOwnedSurface());
}

bool Image::FillSurface(SDL_Surface * const surface)
{
	assert(surface);

	SDL_Surface * ownedSDLSurface = surface;

	if (SDL_MUSTLOCK(ownedSDLSurface) && !SDL_LockSurface(ownedSDLSurface))
	{
		return false;
	}

	//As we have to convert between formats a direct memcpy cannot be done, but each value must be remapped
	for (unsigned int i = 0; i < Width * Height; i++)
	{
		Uint32 * p = (Uint32 *)ownedSDLSurface->pixels + i;
		*p = SDL_MapRGB(surface->format, Data[i].R() * 255, Data[i].G() * 255, Data[i].B() * 255);
	}

	SDL_UnlockSurface(ownedSDLSurface);

	return true;
}

Image::~Image()
{
}
