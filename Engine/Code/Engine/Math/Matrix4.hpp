#pragma once
#include "Engine/Math/Vector4.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Vector2.hpp"


class Matrix4 {
public:

	union {
		float data[16];
		Vector4 rows[4];
		struct {
			Vector4 m_iBasis;
			Vector4 m_jBasis;
			Vector4 m_kBasis;
			Vector4 m_translation;
		};
	};

	Matrix4();
	Matrix4(const Matrix4& copy);
	explicit Matrix4(const float* arrayOfFloats);//assuming column base
	explicit Matrix4(const Vector2& iBasis, const Vector2& jBasis, const Vector2& translation = Vector2(0.f, 0.f));
	explicit Matrix4(const Vector3& iBasis, const Vector3& jBasis, const Vector3& kBasis, const Vector3& translation = Vector3(0.f, 0.f, 0.f));
	explicit Matrix4(const Vector4& iBasis, const Vector4& jBasis, const Vector4& kBasis, const Vector4& translation = Vector4(0.f, 0.f, 0.f, 1.f));


	
	void MakeIdentity();
	void ConcatenateTransform(const Matrix4& tran);
	Matrix4 GetTransformed(const Matrix4& transMatrix) const;
	const float* GetAsFloatArray() const;	// Used when the Matrix4 in question in const
	float* 	 GetAsFloatArray();	// Used when the Matrix4 is not const

	Vector2 TransformPosition(const Vector2& position2D) const; // Assumes z=0, w=1
	Vector3 TransformPosition(const Vector3& position3D) const; // Assumes w=1
	Vector2 TransformDirection(const Vector2& direction2D) const; // Assumes z=0, w=0
	Vector3 TransformDirection(const Vector3& direction3D) const; // Assumes w=0
	Vector4 TransformVector(const Vector4& homogeneousVector) const; // w is provided
	Matrix4 GetTransposed();


	//change these to use static function?
	void Translate(const Vector2& translation2D); // z translation assumed to be 0
	void Translate(const Vector3& translation3D);
	void Scale(float uniformScale);
	void Scale(const Vector2& nonUniformScale2D); // z scale assumed to be 1
	void Scale(const Vector3& nonUniformScale3D);
	void RotateDegreesAboutX(float degrees);
	void RotateDegreesAboutY(float degrees);
	void RotateDegreesAboutZ(float degrees); // Possibly also offered as RotateDegrees2D
	void RotateRadiansAboutX(float radians);
	void RotateRadiansAboutY(float radians);
	void RotateRadiansAboutZ(float radians); // Possibly also 
	void Transpose();


	static Matrix4 CreateTranslation(const Vector2& translation2D); // z translation assumed to be 0
	static Matrix4 CreateTranslation(const Vector3& translation3D);
	static Matrix4 CreateScale(float uniformScale);
	static Matrix4 CreateScale(const Vector2& nonUniformScale2D); // z scale assumed to be 1
	static Matrix4 CreateScale(const Vector3& nonUniformScale3D);
	static Matrix4 CreateRotationDegreesAboutX(float degrees);
	static Matrix4 CreateRotationDegreesAboutY(float degrees);
	static Matrix4 CreateRotationDegreesAboutZ(float degrees); // a.k.a. CreateRotationDegrees2D
	static Matrix4 CreateRotationRadiansAboutX(float radians);
	static Matrix4 CreateRotationRadiansAboutY(float radians);
	static Matrix4 CreateRotationRadiansAboutZ(float radians); // a.k.a. CreateRotationRadians2D

	//SD3 stuff;
	static Matrix4 MatrixMakeOrthoProjection(float nx, float fx, float ny, float fy,
		float nz = 0.0f, float fz = 1.0f);

	void operator= (const Matrix4& source);




};