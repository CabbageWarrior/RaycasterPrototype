#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>

class Vector3 {


public:
	Vector3() {}
	Vector3(float e0, float e1, float e2) { Elements[0] = e0; Elements[1] = e1; Elements[2] = e2; }
	inline float X() const { return Elements[0]; }
	inline float Y() const { return Elements[1]; }
	inline float Z() const { return Elements[2]; }
	inline float R() const { return Elements[0]; }
	inline float G() const { return Elements[1]; }
	inline float B() const { return Elements[2]; }

	inline const Vector3& operator+() const { return *this; }
	inline Vector3 operator-() const { return Vector3(-Elements[0], -Elements[1], -Elements[2]); }
	inline float operator[](int i) const { return Elements[i]; }
	inline float& operator[](int i) { return Elements[i]; };

	inline Vector3& operator+=(const Vector3 &v2);
	inline Vector3& operator-=(const Vector3 &v2);
	inline Vector3& operator*=(const Vector3 &v2);
	inline Vector3& operator/=(const Vector3 &v2);
	inline Vector3& operator*=(const float t);
	inline Vector3& operator/=(const float t);

	inline float Lenght() const { return sqrt(Elements[0] * Elements[0] + Elements[1] * Elements[1] + Elements[2] * Elements[2]); }
	inline float SquaredLenght() const { return Elements[0] * Elements[0] + Elements[1] * Elements[1] + Elements[2] * Elements[2]; }
	inline void MakeUnitVector();
	inline void Zero() { Elements[0] = 0;  Elements[1] = 0; Elements[2] = 0; };

	float Elements[3] = {0,0,0};
};



inline std::istream& operator>>(std::istream &is, Vector3 &t) {
	is >> t.Elements[0] >> t.Elements[1] >> t.Elements[2];
	return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vector3 &t) {
	os << t.Elements[0] << " " << t.Elements[1] << " " << t.Elements[2];
	return os;
}

inline void Vector3::MakeUnitVector() {
	float k = 1.0 / sqrt(Elements[0] * Elements[0] + Elements[1] * Elements[1] + Elements[2] * Elements[2]);
	Elements[0] *= k; Elements[1] *= k; Elements[2] *= k;
}

inline Vector3 operator+(const Vector3 &v1, const Vector3 &v2) {
	return Vector3(v1.Elements[0] + v2.Elements[0], v1.Elements[1] + v2.Elements[1], v1.Elements[2] + v2.Elements[2]);
}

inline Vector3 operator-(const Vector3 &v1, const Vector3 &v2) {
	return Vector3(v1.Elements[0] - v2.Elements[0], v1.Elements[1] - v2.Elements[1], v1.Elements[2] - v2.Elements[2]);
}

inline Vector3 operator*(const Vector3 &v1, const Vector3 &v2) {
	return Vector3(v1.Elements[0] * v2.Elements[0], v1.Elements[1] * v2.Elements[1], v1.Elements[2] * v2.Elements[2]);
}

inline Vector3 operator/(const Vector3 &v1, const Vector3 &v2) {
	return Vector3(v1.Elements[0] / v2.Elements[0], v1.Elements[1] / v2.Elements[1], v1.Elements[2] / v2.Elements[2]);
}

inline Vector3 operator*(float t, const Vector3 &v) {
	return Vector3(t*v.Elements[0], t*v.Elements[1], t*v.Elements[2]);
}

inline Vector3 operator/(Vector3 v, float t) {
	return Vector3(v.Elements[0] / t, v.Elements[1] / t, v.Elements[2] / t);
}

inline Vector3 operator*(const Vector3 &v, float t) {
	return Vector3(t*v.Elements[0], t*v.Elements[1], t*v.Elements[2]);
}

inline float Dot(const Vector3 &v1, const Vector3 &v2) {
	return v1.Elements[0] * v2.Elements[0] + v1.Elements[1] * v2.Elements[1] + v1.Elements[2] * v2.Elements[2];
}

inline Vector3 Reflect(const Vector3 & V, const Vector3 & Normal)
{ 
	return  V - 2 * Dot(V, Normal) * Normal;
};

inline Vector3 Cross(const Vector3 &v1, const Vector3 &v2) {
	return Vector3((v1.Elements[1] * v2.Elements[2] - v1.Elements[2] * v2.Elements[1]),
		(-(v1.Elements[0] * v2.Elements[2] - v1.Elements[2] * v2.Elements[0])),
		(v1.Elements[0] * v2.Elements[1] - v1.Elements[1] * v2.Elements[0]));
}


inline Vector3& Vector3::operator+=(const Vector3 &v) {
	Elements[0] += v.Elements[0];
	Elements[1] += v.Elements[1];
	Elements[2] += v.Elements[2];
	return *this;
}

inline Vector3& Vector3::operator*=(const Vector3 &v) {
	Elements[0] *= v.Elements[0];
	Elements[1] *= v.Elements[1];
	Elements[2] *= v.Elements[2];
	return *this;
}

inline Vector3& Vector3::operator/=(const Vector3 &v) {
	Elements[0] /= v.Elements[0];
	Elements[1] /= v.Elements[1];
	Elements[2] /= v.Elements[2];
	return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& v) {
	Elements[0] -= v.Elements[0];
	Elements[1] -= v.Elements[1];
	Elements[2] -= v.Elements[2];
	return *this;
}

inline Vector3& Vector3::operator*=(const float t) {
	Elements[0] *= t;
	Elements[1] *= t;
	Elements[2] *= t;
	return *this;
}

inline Vector3& Vector3::operator/=(const float t) {
	float k = 1.0f / t;

	Elements[0] *= k;
	Elements[1] *= k;
	Elements[2] *= k;
	return *this;
}

inline Vector3 UnitVector(Vector3 v) {
	return v / v.Lenght();
}