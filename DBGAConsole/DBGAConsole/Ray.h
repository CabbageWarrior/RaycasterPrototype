#pragma once
#include "Vector3.h"

class Ray
{
private:
	Vector3 Origin{};
	Vector3 Direction{};

public:
	Ray();
	Ray(const Vector3 & NewOrigin, const Vector3 & NewDirection);

	const Vector3 GetOrigin() const;
	const Vector3 GetDirection() const;

	Vector3 GetPointAtDistance(float Distance) const;
};

