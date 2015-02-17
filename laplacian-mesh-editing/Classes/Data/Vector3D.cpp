#include "Vector3D.h"
#include<cmath>
// ------------------------------------------------------------------------------------------------
template <typename TReal>
void Vector3type<TReal>::Set( TReal pX, TReal pY, TReal pZ) { 
	x = pX; y = pY; z = pZ; 
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
TReal Vector3type<TReal>::SquareLength() const {
	return x*x + y*y + z*z; 
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
TReal Vector3type<TReal>::Length() const {
	return ::sqrt( SquareLength()); 
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
Vector3type<TReal>& Vector3type<TReal>::Normalize() { 
	*this /= Length(); return *this;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
const Vector3type<TReal>& Vector3type<TReal>::operator += (const Vector3type<TReal>& o) {
	x += o.x; y += o.y; z += o.z; return *this; 
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
const Vector3type<TReal>& Vector3type<TReal>::operator -= (const Vector3type<TReal>& o) {
	x -= o.x; y -= o.y; z -= o.z; return *this;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
const Vector3type<TReal>& Vector3type<TReal>::operator *= (TReal f) {
	x *= f; y *= f; z *= f; return *this; 
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
const Vector3type<TReal>& Vector3type<TReal>::operator /= (TReal f) {
	x /= f; y /= f; z /= f; return *this; 
}

// ------------------------------------------------------------------------------------------------
template <typename TReal>
TReal Vector3type<TReal>::operator[](unsigned int i) const {
	return *(&x + i);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
TReal& Vector3type<TReal>::operator[](unsigned int i) {
	return *(&x + i);
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
bool Vector3type<TReal>::operator== (const Vector3type<TReal>& other) const {
	return x == other.x && y == other.y && z == other.z;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
bool Vector3type<TReal>::operator!= (const Vector3type<TReal>& other) const {
	return x != other.x || y != other.y || z != other.z;
}
// ---------------------------------------------------------------------------
template<typename TReal>
bool Vector3type<TReal>::Equal(const Vector3type<TReal>& other, TReal epsilon) const {
	return
		std::abs(x - other.x) <= epsilon &&
		std::abs(y - other.y) <= epsilon &&
		std::abs(z - other.z) <= epsilon;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
bool Vector3type<TReal>::operator < (const Vector3type<TReal>& other) const {
	return x != other.x ? x < other.x : y != other.y ? y < other.y : z < other.z;
}
// ------------------------------------------------------------------------------------------------
template <typename TReal>
const Vector3type<TReal> Vector3type<TReal>::SymMul(const Vector3type<TReal>& o) {
	return Vector3type<TReal>(x*o.x,y*o.y,z*o.z);
}
// ------------------------------------------------------------------------------------------------
// symmetric addition
template <typename TReal>
Vector3type<TReal> operator + (const Vector3type<TReal>& v1, const Vector3type<TReal>& v2)	{
	return Vector3type<TReal>( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
// ------------------------------------------------------------------------------------------------
// symmetric subtraction
template <typename TReal>
Vector3type<TReal> operator - (const Vector3type<TReal>& v1, const Vector3type<TReal>& v2)	{
	return Vector3type<TReal>( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
// ------------------------------------------------------------------------------------------------
// scalar product
template <typename TReal>
TReal operator * (const Vector3type<TReal>& v1, const Vector3type<TReal>& v2)	{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
// ------------------------------------------------------------------------------------------------
// scalar multiplication
template <typename TReal>
Vector3type<TReal> operator * ( TReal f, const Vector3type<TReal>& v)	{
	return Vector3type<TReal>( f*v.x, f*v.y, f*v.z);
}
// ------------------------------------------------------------------------------------------------
// and the other way around
template <typename TReal>
Vector3type<TReal> operator * ( const Vector3type<TReal>& v, TReal f)	{
	return Vector3type<TReal>( f*v.x, f*v.y, f*v.z);
}
// ------------------------------------------------------------------------------------------------
// scalar division
template <typename TReal>
Vector3type<TReal> operator / ( const Vector3type<TReal>& v, TReal f)	{
	return v * (1/f);
}
// ------------------------------------------------------------------------------------------------
// vector division
template <typename TReal>
Vector3type<TReal> operator / ( const Vector3type<TReal>& v, const Vector3type<TReal>& v2)	{
	return Vector3type<TReal>(v.x / v2.x,v.y / v2.y,v.z / v2.z);
}
// ------------------------------------------------------------------------------------------------
// cross product
template <typename TReal>
Vector3type<TReal> operator ^ ( const Vector3type<TReal>& v1, const Vector3type<TReal>& v2)	{
	return Vector3type<TReal>( v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}
// ------------------------------------------------------------------------------------------------
// vector negation
template <typename TReal>
Vector3type<TReal> operator - ( const Vector3type<TReal>& v)	{
	return Vector3type<TReal>( -v.x, -v.y, -v.z);
}
