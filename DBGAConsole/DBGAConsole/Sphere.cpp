#include "stdafx.h"
#include "Sphere.h"

Sphere::Sphere(const Vector3 & MyCenter, float MyRadius)
{
	Center = MyCenter;
	Radius = MyRadius;
}

const Vector3 Sphere::GetCenter() const {
	return Center;
}
const float Sphere::GetRadius() const {
	return Radius;
}
const bool Sphere::Hit(const Ray & MyRay, HitRecord & MyHitRecord) const
{
	float A = 0, B = 0, C = 0;

	A = Dot(MyRay.GetDirection(), MyRay.GetDirection());
	B = 2 * Dot(MyRay.GetDirection(), MyRay.GetOrigin() - Center);
	C = Dot(MyRay.GetOrigin() - Center, MyRay.GetOrigin() - Center) - Radius * Radius;

	if (B * B - 4 * A * C >= 0)
	{
		float x = (- B - sqrt(B * B - 4 * A * C)) / (2 * A);

		Vector3 CollisionPoint = MyRay.GetPointAtDistance(x);

		MyHitRecord = {
			CollisionPoint,
			CollisionPoint - Center
		};
		return true;
	}
	return false;
}