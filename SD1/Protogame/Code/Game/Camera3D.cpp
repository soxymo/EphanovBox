#include "Game/Camera3D.hpp"
#include "Engine/Math/MathUtils.hpp"

//*******************************************************************
Camera3D::Camera3D()
	: m_position(0.f, 0.f, 0.f)
	, m_yawDegreesAboutZ(0.f)
	, m_pitchDegreesAboutY(0.f)
	, m_rollDegreesAboutX(0.f)
{
}

//*******************************************************************
Camera3D::Camera3D(Vector3 position)
	: m_position(position)
	, m_yawDegreesAboutZ(0.f)
	, m_pitchDegreesAboutY(0.f)
	, m_rollDegreesAboutX(0.f)
{
}

//*******************************************************************
Camera3D::~Camera3D()
{
}

//*******************************************************************
Vector3 Camera3D::GetForwardXYZ() const
{
	return Vector3(CosDegrees(m_yawDegreesAboutZ) * CosDegrees(m_pitchDegreesAboutY), SinDegrees(m_yawDegreesAboutZ) * CosDegrees(m_pitchDegreesAboutY), -1.f * SinDegrees(m_pitchDegreesAboutY));
}

//*******************************************************************
Vector3 Camera3D::GetForwardXY() const
{
	return Vector3(CosDegrees(m_yawDegreesAboutZ), SinDegrees(m_yawDegreesAboutZ), 0.f);
}

//*******************************************************************
Vector3 Camera3D::GetLeftXY() const
{
	return Vector3(-1.f*SinDegrees(m_yawDegreesAboutZ), CosDegrees(m_yawDegreesAboutZ), 0.f);
}

