// DBGAConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include "CommandManager.h"
#include "Window.h"
#include <SDL.h>
#include <assert.h>
#include <random>
#include "Surface.h"
#include "Image.h"
#include "Vector3.h"
#include "Ray.h"
#include "Sphere.h"


bool isRunning = true;
CommandManager commandManager{};

struct RayMatrix
{
	int Width;
	int Height;

	std::vector<Ray> Rays;

};

//	void ParseCommand(std::string & cmd);

void RandomCommand()
{
	std::cout << "Hi i'm a command" << std::endl;
}

void GetCommands()
{
	std::pair<std::map<std::string, CommandDefinition>::const_iterator, std::map<std::string, CommandDefinition>::const_iterator> CommandPair = commandManager.GetCommands();
	while (CommandPair.first != CommandPair.second)
	{
		std::cout << "Command: " << CommandPair.first->second.name << " Description: " << CommandPair.first->second.Definition << std::endl;
		CommandPair.first++;
	}
}

void Scatter(const HitRecord & HitData, Ray & ScatteredRay)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> randomRange(0.0, 1.0);

	Vector3 RandomPoint{ (float)randomRange(gen), (float)randomRange(gen), (float)randomRange(gen) };

	do
	{
		RandomPoint = { (float)randomRange(gen), (float)randomRange(gen), (float)randomRange(gen) };
	} while (RandomPoint.SquaredLenght() >= 1);

	Vector3 RandomPointInHitUnitSphere = HitData.HitPoint + HitData.Normal + RandomPoint;

	Vector3 ReflectionDirection = (RandomPointInHitUnitSphere - HitData.HitPoint);
	ScatteredRay = { HitData.HitPoint, ReflectionDirection };
}

Vector3 GenerateColor(const Ray & ToIntersect, const Sphere & ThisSphere)
{
	Vector3 Color1{ 1, 1, 1 };
	Vector3 Color2{ .5f, .7f, 1 };

	HitRecord HitRec;

	Vector3 Color{};

	Vector3 ColorSphere{ 1, 1, 1 };

	if (ThisSphere.Hit(ToIntersect, HitRec))
	{
		Ray computedRay;
		
		Scatter(HitRec, computedRay);

		return Vector3{ 0.5f, 0.5f, 0.5f } * GenerateColor(computedRay, ThisSphere);

		/*Color = Vector3{
			(scattered.X() + 1.0f) * .5f,
			(scattered.Y() + 1.0f) * .5f,
			(scattered.Z() + 1.0f) * .5f
		};*/
	}
	else
	{
		float CurrentY = (HitRec.Normal.R() + 1) * .5;
		Vector3 CurrentColor = Color1 * (1 - CurrentY) + Color2 * CurrentY;

		Color = CurrentColor;
	}

	return Color;
}

void GenerateImage(Image & RaycastOutImage)
{
	Vector3 CameraOrigin{ 0, 0, 0 };
	Vector3 BottomLeftCorner{ -2, -1, -1 };
	Vector3 HorizontalSpan{ 4, 0, 0 };
	Vector3 VerticalSpan{ 0, 2, 0 };

	Sphere MySphere1{ Vector3{ 0, 0, -1 }, 0.5f };

	HitRecord MyHitRecord{};

	//We want to start from lower left y
	for (int y = RaycastOutImage.GetHeight() - 1; y >= 0; y--)
	{
		for (unsigned int x = 0; x < RaycastOutImage.GetWitdh(); x++)
		{
			float u = (float)x / (float)RaycastOutImage.GetWitdh();
			float v = (float)y / (float)RaycastOutImage.GetHeight();

			//Invert the y coord at which pixel are stored in the image so that we start from max height and not from  zero height (aka, last row at the bottom of the array)
			int invertedY = (-((float)y / (float)RaycastOutImage.GetHeight()) + 1.0f) * (RaycastOutImage.GetHeight() - 1);

			//Test gradient
			/*
			RaycastOutImage[invertedY * RaycastOutImage.GetWitdh() + x][0] = (float)x / (float)RaycastOutImage.GetWitdh();
			RaycastOutImage[invertedY * RaycastOutImage.GetWitdh() + x][1] = (float)y / (float)RaycastOutImage.GetHeight();
			RaycastOutImage[invertedY * RaycastOutImage.GetWitdh() + x][2] = 0.2f;
			*/

			// [Verza] Shot a ray.
			Vector3 ScreenPosition = BottomLeftCorner + (u * HorizontalSpan) + (v * VerticalSpan);
			Ray CameraRay{ CameraOrigin, ScreenPosition - CameraOrigin };

			Vector3 RayDirection = UnitVector(ScreenPosition - CameraOrigin);

			Vector3 Color = GenerateColor(CameraRay, MySphere1);

			RaycastOutImage[invertedY * RaycastOutImage.GetWitdh() + x][0] = Color.X();
			RaycastOutImage[invertedY * RaycastOutImage.GetWitdh() + x][1] = Color.Y();
			RaycastOutImage[invertedY * RaycastOutImage.GetWitdh() + x][2] = Color.Z();
		}
	}
}

int main(int argv, char ** argc)
{

	std::string cmd = "";

	commandManager.AddCommand("help", GetCommands, "Get all the commands");

	SDL_Init(SDL_INIT_EVERYTHING);

	const int WindowWidth = 200;
	const int WindowHeight = 100;

	Window myWindow("Raycaster",
		SDL_WINDOWPOS_UNDEFINED, // SDL_WINDOWPOS_CENTERED
		SDL_WINDOWPOS_UNDEFINED, // SDL_WINDOWPOS_CENTERED
		WindowWidth,
		WindowHeight,
		0);


	std::pair<unsigned int, unsigned int> size = myWindow.GetWindowSize();
	//Surface drawTarget {size.first, size.second, 32, SDL_PIXELFORMAT_RGB888 };
	Image RaycastOutImage{ size.first, size.second };




	while (isRunning)
	{
		bool rerunRaycast = false;

		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_MOUSEMOTION:
				std::cout << "x = " << event.motion.x << " y = " << event.motion.y << std::endl;
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
					rerunRaycast = true;
				break;
			}
		}


		if (rerunRaycast)
		{
			std::cout << "Starting Generation " << std::endl;
			int startTicks = SDL_GetTicks();

			GenerateImage(RaycastOutImage);

			RaycastOutImage.FillSurface(myWindow.GetWindowSurface());

			int endTicks = SDL_GetTicks() - startTicks;

			std::cout << "Generation Complete in " << endTicks << " milliseconds " << std::endl;

			rerunRaycast = false;
		}

		myWindow.UpdateWindowSurface();
	}

	SDL_Quit();

	return 0;
}



