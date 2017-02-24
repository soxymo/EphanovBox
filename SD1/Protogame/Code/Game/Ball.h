#pragma once
#include "Engine/Math/Sphere3.hpp"
#include "Engine/Math/Plane3.hpp"



class Ball {
public:
	Ball();
	Ball(Vector3 initPosition, Vector3 initVelocity);
	~Ball() {};

	void Update(float deltaSeconds);
	void Render() const;

	Sphere3 sphere;
	Vector3 velocity;
	float elasticity;

};