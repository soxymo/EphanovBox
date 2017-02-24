#include "Game/Ball.h"
#include "Game/GameCommon.hpp"
#include "Engine/Renderer/Renderer.hpp"


Ball::Ball()
{
	sphere.center.SetXYZ(5, 0, 0);
	sphere.radius = 2.f;
	velocity.SetXYZ(-6, 4, 0);
	elasticity = .5f;

}

Ball::Ball(Vector3 initPosition, Vector3 initVelocity)
	:velocity(initVelocity)
{
	sphere.center = initPosition;
	sphere.radius = 2.f;
	elasticity = .5f;
}

Vector3 Ball::GetVelocity()
{
	return velocity;
}

void Ball::SetVelocity(Vector3 newVelocity) {
	velocity = newVelocity;
}

void Ball::ScaleVelocity(Vector3 scaleVec) {
	velocity.ScaleNonUniform(scaleVec);
}

void Ball::Update(float deltaSeconds) {

	float gravity = -1.f;

	velocity.z += gravity *deltaSeconds;
	sphere.center += velocity*deltaSeconds;
}

void Ball::Render() const{
	g_theRenderer->TranslateDrawFrame3D(sphere.center);
	g_theRenderer->renderWireSphere(sphere.radius+.3f, 10, 10);
	g_theRenderer->PushDrawFrame();
}

