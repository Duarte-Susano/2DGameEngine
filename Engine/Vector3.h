#pragma once
#include <iostream>

struct Vector3
{
public:
	
	float x;
	float y;
	float z;

	Vector3():x{0}, y{0}, z{0} {}
	//constructor with floats
	Vector3(float x, float y, float z) : x{ x }, y{ y }, z{z} {}
	//constructor with ints
	Vector3(int x, int y, int z) : x{ (float)x }, y{ (float)y}, z{(float)z} {}

	//static vectors
	static Vector3 Right() { return Vector3{ 1,0,0 }; }
	static Vector3 Left() { return Vector3{ -1,0,0 }; }
	static Vector3 Up() { return Vector3{ 0,1,0 }; }
	static Vector3 Down() { return Vector3{ 0,-1,0 }; }
	static Vector3 Forward() { return Vector3{ 0,0,1 }; }
	static Vector3 Backward() { return Vector3{ 0,0,-1 }; }
	static Vector3 Zero() { return Vector3{ 0,0,0 }; }
	static Vector3 One() { return Vector3{ 1,1,1 }; }

	//returns magnitude
	float Magnitude();
	//returns sqr magnitude
	float sqrMagnitude();
	//returns the vector normalized
	Vector3 Normalize();
	//returns the vector normalized by the sqrmagnitude
	Vector3 sqrNormalize();

	//operators
	bool operator==(const Vector3& otherv) const;
	bool operator!=(const Vector3& otherv) const;

	Vector3& operator =(const Vector3& otherv);

	Vector3& operator +(const Vector3& otherv);
	Vector3& operator -(const Vector3& otherv);
	Vector3& operator *(const Vector3& otherv);
	Vector3& operator /(const Vector3& otherv);

	Vector3& operator +=(const Vector3& otherv);
	Vector3& operator -=(const Vector3& otherv);
	Vector3& operator *=(const Vector3& otherv);
	Vector3& operator /=(const Vector3& otherv);

	Vector3& operator +(float f);
	Vector3& operator -(float f);
	Vector3& operator *(float f);
	Vector3& operator /(float f);

	Vector3& operator +=(float f);
	Vector3& operator -=(float f);
	Vector3& operator *=(float f);
	Vector3& operator /=(float f);

	Vector3& operator +(int i);
	Vector3& operator -(int i);
	Vector3& operator *(int i);
	Vector3& operator /(int i);

	Vector3& operator +=(int i);
	Vector3& operator -=(int i);
	Vector3& operator *=(int i);
	Vector3& operator /=(int i);

	friend std::ostream& operator<<(std::ostream& ostr, const Vector3& vec);

};