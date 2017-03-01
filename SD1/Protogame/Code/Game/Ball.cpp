#include "Game/Ball.h"
#include "Game/GameCommon.hpp"
#include "Engine/Renderer/Renderer.hpp"
#include "Engine/Math/MathUtils.hpp"
#include "Engine/Core/Rgba.hpp"


Ball::Ball()
{
	sphere.center.SetXYZ(GetRandomFloatInRange(2.f, 18.f), GetRandomFloatInRange(2.f, 18.f), GetRandomFloatInRange(5, 30));
	sphere.radius = 2.f;
	velocity.SetXYZ(GetRandomFloatInRange(-3, -3), GetRandomFloatInRange(-3, -3), GetRandomFloatInRange(-2, -1));
	elasticity = .8f;
	//GetRandomFloatInRange(-3, -3)
		

}

Ball::Ball(Vector3 initPosition, Vector3 initVelocity)
	:velocity(initVelocity)
{
	sphere.center = initPosition;
	sphere.radius = 2.f;
	elasticity = .8f;
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

void Ball::Render(bool chosenOne) const
{
	g_theRenderer->PushDrawFrame();
	g_theRenderer->TranslateDrawFrame3D(sphere.center);
	if (chosenOne){
		g_theRenderer->renderWireSphere(sphere.radius + .3f, 10, 10, Rgba(.5f, 1.f, .5f, 1.f));
	}
	else {
		g_theRenderer->renderWireSphere(sphere.radius + .3f, 10, 10, Rgba());
	}
	g_theRenderer->PopDrawFrame();
}

