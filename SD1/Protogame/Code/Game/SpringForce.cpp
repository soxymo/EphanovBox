#include "Game/SpringForce.hpp"
#include "Game/GameCommon.hpp"
#include "Engine/Renderer/Renderer.hpp"

SpringForce::SpringForce(Vector3 startPoint, Vector3 endPoint, float stiff, float unLength)
	:stiffness(stiff)
	,unstretchedLength(unLength)
{
	line.start = startPoint; //start point not moving at this point
	line.end = endPoint;

}

Vector3 SpringForce::ComputeForce(const Vector3& startPoint, const Vector3& endPoint) {
	//the spring force is directed along the line that connects
	//the endPoint2 -> endPoint1.
	Vector3 direction = endPoint - startPoint;

	//make it a unit vector, compute the norm 
	double length = direction.Normalize();

	//subtract displacement for string length with no tension
	//This spring acts more like a rope: its force is 0 if the
	//total length of the spring is less than the unstretched length.
	double displacement = std::fabs(length) > unstretchedLength ? fabs(length - unstretchedLength) : 0.0;

	//use Hook's law for the linear-proportional spring
	Vector3 force = stiffness * displacement * direction;
	return force;
}

void SpringForce::Render() const {
	g_theRenderer->DrawLine(line.start, line.end, Rgba(1.f, 0.f, 0.f, 1.f));
}


