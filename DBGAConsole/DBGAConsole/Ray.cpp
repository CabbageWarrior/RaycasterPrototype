#include "stdafx.h"
#include "Ray.h"
#include <assert.h>

Ray::Ray()
{
}
Ray::Ray(const Vector3 & NewOrigin, const Vector3 & NewDirection)
{
	Origin = NewOrigin;
	Direction = NewDirection;
}

const Vector3 Ray::GetOrigin() const
{
	return Origin;
}
const Vector3 Ray::GetDirection() const
{
	return Direction;
}

Vector3 Ray::GetPointAtDistance(float Distance) const
{
	assert(Distance >= 0);
	return Origin + (Direction * Distance);
}
