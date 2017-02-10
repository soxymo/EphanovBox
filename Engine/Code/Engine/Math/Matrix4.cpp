#include "Engine/Math/Matrix4.hpp"
#include <math.h>
#include "Engine/Math/MathUtils.hpp"

Matrix4::Matrix4() {
	m_iBasis.SetXYZW(1.f, 0.f, 0.f, 0.f);
	m_jBasis.SetXYZW(0.f, 1.f, 0.f, 0.f);
	m_kBasis.SetXYZW(0.f, 0.f, 1.f, 0.f);
	m_translation.SetXYZW(0.f, 0.f, 0.f, 1.f);
}

Matrix4::Matrix4(const Matrix4& copy) {
	m_iBasis = copy.m_iBasis;
	m_jBasis = copy.m_jBasis;
	m_kBasis = copy.m_kBasis;
	m_translation = copy.m_translation;

}



Matrix4::Matrix4(const Vector2& iBasis, const Vector2& jBasis, const Vector2& translation /*= Vector2(0.f, 0.f)*/) {
	m_iBasis.SetXYZW(iBasis.x, iBasis.y, 0.f, 0.f);
	m_jBasis.SetXYZW(jBasis.x, jBasis.y, 0.f, 0.f);
	m_kBasis.SetXYZW(0.f,0.f, 1.f, 0.f);
	m_translation.SetXYZW(translation.x, translation.y, 0.f, 1.f);
}

Matrix4::Matrix4(const Vector3& iBasis, const Vector3& jBasis, const Vector3& kBasis, const Vector3& translation /*= Vector3(0.f, 0.f, 0.f)*/) {
	m_iBasis.SetXYZW(iBasis.x, iBasis.y, iBasis.z, 0.f);
	m_jBasis.SetXYZW(jBasis.x, jBasis.y, jBasis.z, 0.f);
	m_kBasis.SetXYZW(kBasis.x, kBasis.y, kBasis.z, 0.f);
	m_translation.SetXYZW(translation.x, translation.y, translation.z, 1.f);
}

Matrix4::Matrix4(const Vector4& iBasis, const Vector4& jBasis, const Vector4& kBasis, const Vector4& translation /*= Vector4(0.f, 0.f, 0.f, 1.f)*/) {
	m_iBasis.SetXYZW(iBasis.x, iBasis.y, iBasis.z, iBasis.w);
	m_jBasis.SetXYZW(jBasis.x, jBasis.y, jBasis.z, jBasis.w);
	m_kBasis.SetXYZW(kBasis.x, kBasis.y, kBasis.z, kBasis.w);
	m_translation.SetXYZW(translation.x, translation.y, translation.z, translation.w);
}

Matrix4::Matrix4(const float* arrayOfFloats) {
	m_iBasis.SetXYZW(arrayOfFloats[0], arrayOfFloats[4], arrayOfFloats[8], arrayOfFloats[12]);
	m_jBasis.SetXYZW(arrayOfFloats[1], arrayOfFloats[5], arrayOfFloats[9], arrayOfFloats[13]);
	m_iBasis.SetXYZW(arrayOfFloats[2], arrayOfFloats[6], arrayOfFloats[10], arrayOfFloats[14]);
	m_iBasis.SetXYZW(arrayOfFloats[3], arrayOfFloats[7], arrayOfFloats[11], arrayOfFloats[15]);
}

void Matrix4::MakeIdentity() {
	m_iBasis.SetXYZW(1.f, 0.f, 0.f, 0.f);
	m_jBasis.SetXYZW(0.f, 1.f, 0.f, 0.f);
	m_iBasis.SetXYZW(0.f, 0.f, 1.f, 0.f);
	m_translation.SetXYZW(0.f, 0.f, 0.f, 1.f);
}

void Matrix4::ConcatenateTransform(const Matrix4& tran) {
	Matrix4 old = *this;
	m_iBasis.x = (old.m_iBasis.x*tran.m_iBasis.x) + (old.m_jBasis.x*tran.m_iBasis.y) + (old.m_kBasis.x*tran.m_iBasis.z) + (old.m_translation.x* tran.m_iBasis.w);
	m_jBasis.x = (old.m_iBasis.x*tran.m_jBasis.x) + (old.m_jBasis.x*tran.m_jBasis.y) + (old.m_kBasis.x*tran.m_jBasis.z) + (old.m_translation.x* tran.m_jBasis.w);
	m_kBasis.x = (old.m_iBasis.x*tran.m_kBasis.x) + (old.m_jBasis.x*tran.m_kBasis.y) + (old.m_kBasis.x*tran.m_kBasis.z) + (old.m_translation.x* tran.m_kBasis.w);
	m_translation.x = (old.m_iBasis.x*tran.m_translation.x) + (old.m_jBasis.x*tran.m_translation.y) + (old.m_kBasis.x*tran.m_translation.z) + (old.m_translation.x* m_translation.w);

	m_iBasis.y = (old.m_iBasis.y*tran.m_iBasis.x) + (old.m_jBasis.y*tran.m_iBasis.y) + (old.m_kBasis.y*tran.m_iBasis.z) + (old.m_translation.y* tran.m_iBasis.w);
	m_jBasis.y = (old.m_iBasis.y*tran.m_jBasis.x) + (old.m_jBasis.y*tran.m_jBasis.y) + (old.m_kBasis.y*tran.m_jBasis.z) + (old.m_translation.y* tran.m_jBasis.w);
	m_kBasis.y = (old.m_iBasis.y*tran.m_kBasis.x) + (old.m_jBasis.y*tran.m_kBasis.y) + (old.m_kBasis.y*tran.m_kBasis.z) + (old.m_translation.y* tran.m_kBasis.w);
	m_translation.y = (old.m_iBasis.y*tran.m_translation.x) + (old.m_jBasis.y*tran.m_translation.y) + (old.m_kBasis.y*tran.m_translation.z) + (old.m_translation.y* m_translation.w);

	m_iBasis.z = (old.m_iBasis.z*tran.m_iBasis.x) + (old.m_jBasis.z*tran.m_iBasis.y) + (old.m_kBasis.z*tran.m_iBasis.z) + (old.m_translation.z* tran.m_iBasis.w);
	m_jBasis.z = (old.m_iBasis.z*tran.m_jBasis.x) + (old.m_jBasis.z*tran.m_jBasis.y) + (old.m_kBasis.z*tran.m_jBasis.z) + (old.m_translation.z* tran.m_jBasis.w);
	m_kBasis.z = (old.m_iBasis.z*tran.m_kBasis.x) + (old.m_jBasis.z*tran.m_kBasis.y) + (old.m_kBasis.z*tran.m_kBasis.z) + (old.m_translation.z* tran.m_kBasis.w);
	m_translation.z = (old.m_iBasis.z*tran.m_translation.x) + (old.m_jBasis.z*tran.m_translation.y) + (old.m_kBasis.z*tran.m_translation.z) + (old.m_translation.z* m_translation.w);

	m_iBasis.w = (old.m_iBasis.w*tran.m_iBasis.x) + (old.m_jBasis.w*tran.m_iBasis.y) + (old.m_kBasis.w*tran.m_iBasis.z) + (old.m_translation.w* tran.m_iBasis.w);
	m_jBasis.w = (old.m_iBasis.w*tran.m_jBasis.x) + (old.m_jBasis.w*tran.m_jBasis.y) + (old.m_kBasis.w*tran.m_jBasis.z) + (old.m_translation.w* tran.m_jBasis.w);
	m_kBasis.w = (old.m_iBasis.w*tran.m_kBasis.x) + (old.m_jBasis.w*tran.m_kBasis.y) + (old.m_kBasis.w*tran.m_kBasis.z) + (old.m_translation.w* tran.m_kBasis.w);
	m_translation.w = (old.m_iBasis.w*tran.m_translation.x) + (old.m_jBasis.w*tran.m_translation.y) + (old.m_kBasis.w*tran.m_translation.z) + (old.m_translation.w* m_translation.w);


}

Matrix4 Matrix4::GetTransformed(const Matrix4& transMatrix) const{
	Matrix4 transformed = *this;
	transformed.ConcatenateTransform(transMatrix);
	return transformed;
}

const float* Matrix4::GetAsFloatArray() const {
	return &m_iBasis.x;
}

float* Matrix4::GetAsFloatArray() {
	return &m_iBasis.x;
}

Vector2 Matrix4::TransformPosition(const Vector2& position2D) const {
	Matrix4 vectorHolder(position2D, Vector2(0.f,0.f));
	vectorHolder.m_iBasis.w = 1.f; //make w=1;
	const Matrix4 transformed = GetTransformed(vectorHolder);
	return Vector2(transformed.m_iBasis.x, transformed.m_iBasis.y);
}

Vector3 Matrix4::TransformPosition(const Vector3& position3D) const {
	Matrix4 vectorHolder(position3D, Vector3(0.f,0.f,0.f), Vector3(0.f, 0.f, 0.f));
	vectorHolder.m_iBasis.w = 1.f;//make w=1;
	const Matrix4 transformed = GetTransformed(vectorHolder);
	return Vector3(transformed.m_iBasis.x, transformed.m_iBasis.y, transformed.m_iBasis.z);
}

Vector2 Matrix4::TransformDirection(const Vector2& direction2D) const {
	Matrix4 vectorHolder(direction2D, Vector2(0.f, 0.f));
	const Matrix4 transformed = GetTransformed(vectorHolder);
	return Vector2(transformed.m_iBasis.x, transformed.m_iBasis.y);
}

Vector3 Matrix4::TransformDirection(const Vector3& direction3D) const {
	Matrix4 vectorHolder(direction3D, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f));
	const Matrix4 transformed = GetTransformed(vectorHolder);
	return Vector3(transformed.m_iBasis.x, transformed.m_iBasis.y, transformed.m_iBasis.z);
}

Vector4 Matrix4::TransformVector(const Vector4& homogeneousVector) const {
	Matrix4 vectorHolder(homogeneousVector, Vector4(0.f, 0.f, 0.f, 0.f), Vector4(0.f, 0.f, 0.f, 0.f));
	const Matrix4 transformed = GetTransformed(vectorHolder);
	return Vector4(transformed.m_iBasis.x, transformed.m_iBasis.y, transformed.m_iBasis.z, transformed.m_iBasis.w);
}

Matrix4 Matrix4::GetTransposed() {
	Matrix4 transposed = *this;
	transposed.Transpose();
	return transposed;
}

void Matrix4::Translate(const Vector2& translation2D) {
	Matrix4 translation;
	translation.m_translation.x = translation2D.x;
	translation.m_translation.y = translation2D.y;
	ConcatenateTransform(translation);
}

void Matrix4::Translate(const Vector3& translation3D) {
	Matrix4 translation;
	translation.m_translation.x = translation3D.x;
	translation.m_translation.y = translation3D.y;
	translation.m_translation.z = translation3D.z;
	ConcatenateTransform(translation);
}

void Matrix4::Scale(float uniformScale) {
	Matrix4 scaleMatrix;
	scaleMatrix.m_iBasis *= uniformScale;
	scaleMatrix.m_jBasis *= uniformScale;
	scaleMatrix.m_kBasis *= uniformScale;
	ConcatenateTransform(scaleMatrix);
}

void Matrix4::Scale(const Vector2& nonUniformScale2D) {
	Matrix4 scaleMatrix;
	scaleMatrix.m_iBasis *= nonUniformScale2D.x;
	scaleMatrix.m_jBasis *= nonUniformScale2D.y;
	ConcatenateTransform(scaleMatrix);
}

void Matrix4::Scale(const Vector3& nonUniformScale3D) {
	Matrix4 scaleMatrix;
	scaleMatrix.m_iBasis *= nonUniformScale3D.x;
	scaleMatrix.m_jBasis *= nonUniformScale3D.y;
	scaleMatrix.m_kBasis *= nonUniformScale3D.z;
	ConcatenateTransform(scaleMatrix);
}

void Matrix4::RotateDegreesAboutX(float degrees) {
	Matrix4 xRotate;
	xRotate.m_jBasis.y = (float)cos(ConvertDegreesToRadians(degrees));
	xRotate.m_kBasis.y = (float)-sin(ConvertDegreesToRadians(degrees));
	xRotate.m_jBasis.z = (float)sin(ConvertDegreesToRadians(degrees));
	xRotate.m_kBasis.z = (float)cos(ConvertDegreesToRadians(degrees));
	ConcatenateTransform(xRotate);
}

void Matrix4::RotateDegreesAboutY(float degrees) {
	Matrix4 yRotate;
	yRotate.m_iBasis.x = (float)cos(ConvertDegreesToRadians(degrees));
	yRotate.m_kBasis.x = (float)sin(ConvertDegreesToRadians(degrees));
	yRotate.m_iBasis.z = (float)-sin(ConvertDegreesToRadians(degrees));
	yRotate.m_kBasis.z = (float)cos(ConvertDegreesToRadians(degrees));
	ConcatenateTransform(yRotate);
}

void Matrix4::RotateDegreesAboutZ(float degrees) {
	Matrix4 zRotate;
	zRotate.m_iBasis.x = (float)cos(ConvertDegreesToRadians(degrees));
	zRotate.m_jBasis.x = (float)-sin(ConvertDegreesToRadians(degrees));
	zRotate.m_iBasis.y = (float)sin(ConvertDegreesToRadians(degrees));
	zRotate.m_jBasis.y = (float)cos(ConvertDegreesToRadians(degrees));
	ConcatenateTransform(zRotate);
}

void Matrix4::RotateRadiansAboutX(float radians) {
	Matrix4 xRotate;
	xRotate.m_jBasis.y = (float)cos(radians);
	xRotate.m_kBasis.y = (float)-sin(radians);
	xRotate.m_jBasis.z = (float)sin(radians);
	xRotate.m_kBasis.z = (float)cos(radians);
	ConcatenateTransform(xRotate);
}

void Matrix4::RotateRadiansAboutY(float radians) {
	Matrix4 yRotate;
	yRotate.m_iBasis.x = (float)cos(radians);
	yRotate.m_kBasis.x = (float)sin(radians);
	yRotate.m_iBasis.z = (float)-sin(radians);
	yRotate.m_kBasis.z = (float)cos(radians);
	ConcatenateTransform(yRotate);
}

void Matrix4::RotateRadiansAboutZ(float radians) {
	Matrix4 zRotate;
	zRotate.m_iBasis.x = (float)cos(radians);
	zRotate.m_jBasis.x = (float)-sin(radians);
	zRotate.m_iBasis.y = (float)sin(radians);
	zRotate.m_jBasis.y = (float)cos(radians);
	ConcatenateTransform(zRotate);
}

template <typename T> inline void Swap(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}

void Matrix4::Transpose() {
	const Matrix4 copy = *this;
	Swap(m_iBasis.y, m_jBasis.x);
	Swap(m_iBasis.z, m_kBasis.x);
	Swap(m_jBasis.z, m_kBasis.y);
	Swap(m_iBasis.w, m_translation.x);
	Swap(m_jBasis.w, m_translation.y);
	Swap(m_kBasis.w, m_translation.z);
}

Matrix4 Matrix4::CreateTranslation(const Vector2& translation2D) {
	Matrix4 translation;
	translation.m_translation.x = translation2D.x;
	translation.m_translation.y = translation2D.y;
	return translation;
}

Matrix4 Matrix4::CreateTranslation(const Vector3& translation3D) {
	Matrix4 translation;
	translation.m_translation.x = translation3D.x;
	translation.m_translation.y = translation3D.y;
	translation.m_translation.z = translation3D.z;
	return translation;
}

Matrix4 Matrix4::CreateScale(float uniformScale) {
	Matrix4 scaleMatrix;
	scaleMatrix.m_iBasis *= uniformScale;
	scaleMatrix.m_jBasis *= uniformScale;
	scaleMatrix.m_kBasis *= uniformScale;
	return scaleMatrix;
}

Matrix4 Matrix4::CreateScale(const Vector2& nonUniformScale2D) {
	Matrix4 scaleMatrix;
	scaleMatrix.m_iBasis *= nonUniformScale2D.x;
	scaleMatrix.m_jBasis *= nonUniformScale2D.y;
	return scaleMatrix;
}

Matrix4 Matrix4::CreateScale(const Vector3& nonUniformScale3D) {
	Matrix4 scaleMatrix;
	scaleMatrix.m_iBasis *= nonUniformScale3D.x;
	scaleMatrix.m_jBasis *= nonUniformScale3D.y;
	scaleMatrix.m_kBasis *= nonUniformScale3D.z;
	return scaleMatrix;
}

Matrix4 Matrix4::CreateRotationDegreesAboutX(float degrees) {
	Matrix4 xRotate;
	xRotate.m_jBasis.y = (float)cos(ConvertDegreesToRadians(degrees));
	xRotate.m_kBasis.y = (float)-sin(ConvertDegreesToRadians(degrees));
	xRotate.m_jBasis.z = (float)sin(ConvertDegreesToRadians(degrees));
	xRotate.m_kBasis.z = (float)cos(ConvertDegreesToRadians(degrees));
	return xRotate;
}

Matrix4 Matrix4::CreateRotationDegreesAboutY(float degrees) {
	Matrix4 yRotate;
	yRotate.m_iBasis.x = (float)cos(ConvertDegreesToRadians(degrees));
	yRotate.m_kBasis.x = (float)sin(ConvertDegreesToRadians(degrees));
	yRotate.m_iBasis.z = (float)-sin(ConvertDegreesToRadians(degrees));
	yRotate.m_kBasis.z = (float)cos(ConvertDegreesToRadians(degrees));
	return yRotate;
}

Matrix4 Matrix4::CreateRotationDegreesAboutZ(float degrees) {
	Matrix4 zRotate;
	zRotate.m_iBasis.x = (float)cos(ConvertDegreesToRadians(degrees));
	zRotate.m_jBasis.x = (float)-sin(ConvertDegreesToRadians(degrees));
	zRotate.m_iBasis.y = (float)sin(ConvertDegreesToRadians(degrees));
	zRotate.m_jBasis.y = (float)cos(ConvertDegreesToRadians(degrees));
	return zRotate;
}

Matrix4 Matrix4::CreateRotationRadiansAboutX(float radians) {
	Matrix4 xRotate;
	xRotate.m_jBasis.y = (float)cos(radians);
	xRotate.m_kBasis.y = (float)-sin(radians);
	xRotate.m_jBasis.z = (float)sin(radians);
	xRotate.m_kBasis.z = (float)cos(radians);
	return xRotate;
}

Matrix4 Matrix4::CreateRotationRadiansAboutY(float radians) {
	Matrix4 yRotate;
	yRotate.m_iBasis.x = (float)cos(radians);
	yRotate.m_kBasis.x = (float)sin(radians);
	yRotate.m_iBasis.z = (float)-sin(radians);
	yRotate.m_kBasis.z = (float)cos(radians);
	return yRotate;
}

Matrix4 Matrix4::CreateRotationRadiansAboutZ(float radians) {
	Matrix4 zRotate;
	zRotate.m_iBasis.x = (float)cos(radians);
	zRotate.m_jBasis.x = (float)-sin(radians);
	zRotate.m_iBasis.y = (float)sin(radians);
	zRotate.m_jBasis.y = (float)cos(radians);
	return zRotate;
}

Matrix4 Matrix4::MatrixMakeOrthoProjection(float nx, float fx, float ny, float fy, float nz /*= 0.0f*/, float fz /*= 1.0f*/) {
	Matrix4 mat;
	float sx = 1.0f / (fx - nx);
	float sy = 1.0f / (fy - ny);
	float sz = 1.0f / (fz - nz);

	mat.m_iBasis = Vector4(2.0f*sx, 0.0f, 0.0f, 0.0f);
	mat.m_jBasis = Vector4(0.0f, 2.0f*sy, 0.0f, 0.0f);
	mat.m_kBasis = Vector4(0.0f, 0.0f, sz, 0.0f);
	mat.m_translation = Vector4(-(fx + nx)*sx, -(fy + ny)*sy, -nz*sz, 1.0f);
	return mat;
}

void  Matrix4::operator=(const Matrix4& source) {
	m_iBasis = source.m_iBasis;
	m_jBasis = source.m_jBasis;
	m_kBasis = source.m_kBasis;
	m_translation = source.m_translation;
}
