#include "Game/Ball.h"
#include "Game/GameCommon.hpp"
#include "Engine/Renderer/Renderer.hpp"


Ball::Ball()
{
	sphere.center.SetXYZ(5, 5, 5);
	sphere.radius = 2.f;
	velocity.SetXYZ(-6, -4, 0);

}

Ball::Ball(Vector3 initPosition, Vector3 initVelocity)
	:velocity(initVelocity)
{
	sphere.center = initPosition;
	sphere.radius = 2.f;
}

void Ball::Update(float deltaSeconds) {

	float gravity = -1.f;

	velocity.z += gravity *deltaSeconds;
	sphere.center += velocity*deltaSeconds;
}

void Ball::Render() const{
	g_theRenderer->TranslateDrawFrame3D(sphere.center);
	g_theRenderer->renderWireSphere(sphere.radius, 10.0, 10.0);
	g_theRenderer->PushDrawFrame();
}

