#pragma once
#include "Vector3.h"
#include "Ray.h"

struct HitRecord
{
	Vector3 HitPoint{};
	Vector3 Normal{};
};

class Sphere
{
private:
	Vector3 Center{};
	float Radius;

public:
	Sphere(const Vector3 & MyCenter, float MyRadius);

	const Vector3 GetCenter() const;
	const float GetRadius() const;

	const bool Hit(const Ray & MyRay, HitRecord & MyHitRecord) const;
};

