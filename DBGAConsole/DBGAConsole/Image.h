#pragma once
#include "Vector3.h"
#include <vector>
#include "Surface.h"

class Image
{

private:
	
	std::vector<Vector3> Data;
	unsigned int Width = 0;
	unsigned int Height = 0;

public:

	Image(unsigned int Width, unsigned int Height);
	Vector3 & SetData(unsigned int X, unsigned int Y);
	Vector3 & operator[](unsigned int Index);
	Vector3 & operator[](std::pair<unsigned int, unsigned int> Coordinates);

	bool FillSurface(Surface & surface);
	bool FillSurface(SDL_Surface * const surface);

	inline unsigned int GetWitdh() { return Width; }
	inline unsigned int GetHeight() { return Height; }


	Image();
	

	~Image();


};

