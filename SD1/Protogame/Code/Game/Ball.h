#pragma once
#include "Engine/Math/Sphere3.hpp"
#include "Engine/Math/Plane3.hpp"



class Ball {
public:
	Ball();
	Ball(Vector3 initPosition, Vector3 initVelocity);
	~Ball() {};
	Vector3 GetVelocity();
	void SetVelocity(Vector3 newVelocity);
	void ScaleVelocity(Vector3 scaleVec);
	

	void Update(float deltaSeconds);
	void Render(bool chosenOne) const;

	Sphere3 sphere;
	float elasticity;


private:
	Vector3 velocity;
	

};