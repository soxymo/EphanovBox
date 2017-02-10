#include "Game/Ball.h"
#include "Game/GameCommon.hpp"
#include "Engine/Renderer/Renderer.hpp"


Ball::Ball():
floor(Vector3(0.f, 0.f, 1.f), 0)
{
	sphere.center.SetXYZ(0, 0, 10);
	sphere.radius = 2.f;
	velocity.SetXYZ(1, 1, 0);

}

void Ball::Update(float deltaSeconds) {

	float gravity = -1.f;

	velocity.z += gravity *deltaSeconds;
	sphere.center += velocity*deltaSeconds;

	if (!floor.IsPointInFront(sphere.center - Vector3(0, 0, sphere.radius))) {
		sphere.center.z = sphere.radius;
		velocity.z *= -1;
	}
}

void Ball::Render() const{
	g_theRenderer->TranslateDrawFrame3D(sphere.center);
	g_theRenderer->renderWireSphere(sphere.radius, 10.0, 10.0);
	g_theRenderer->PushDrawFrame();
}

