#pragma once
template <typename TReal>
class Vector3type 
{
public:

	Vector3type () : x(), y(), z() {}
	Vector3type (TReal _x, TReal _y, TReal _z) : x(_x), y(_y), z(_z) {}
	explicit Vector3type (TReal _xyz) : x(_xyz), y(_xyz), z(_xyz) {}
	Vector3type (const Vector3type& o) : x(o.x), y(o.y), z(o.z) {}

public:

	// combined operators
	const Vector3type& operator += (const Vector3type& o);
	const Vector3type& operator -= (const Vector3type& o);
	const Vector3type& operator *= (TReal f);
	const Vector3type& operator /= (TReal f);

	// transform vector by matrix
// 	Vector3type& operator *= (const aiMatrix3x3t<TReal>& mat);
// 	Vector3type& operator *= (const aiMatrix4x4t<TReal>& mat);

	// access a single element
	TReal operator[](unsigned int i) const;
	TReal& operator[](unsigned int i);

	// comparison
	bool operator== (const Vector3type& other) const;
	bool operator!= (const Vector3type& other) const;
	bool operator < (const Vector3type& other) const;

	bool Equal(const Vector3type& other, TReal epsilon = 1e-6) const;

	template <typename TOther>
	operator Vector3type<TOther> () const;

public:

	/** @brief Set the components of a vector
	 *  @param pX X component
	 *  @param pY Y component
	 *  @param pZ Z component  */
	void Set( TReal pX, TReal pY, TReal pZ);

	/** @brief Get the squared length of the vector
	 *  @return Square length */
	TReal SquareLength() const;


	/** @brief Get the length of the vector
	 *  @return length */
	TReal Length() const;


	/** @brief Normalize the vector */
	Vector3type& Normalize();

	
	/** @brief Componentwise multiplication of two vectors
	 *  
	 *  Note that vec*vec yields the dot product.
	 *  @param o Second factor */
	const Vector3type SymMul(const Vector3type& o);

	TReal x, y, z;	
};

// ------------------------------------------------------------------------------------------------
typedef Vector3type<double> Vector3D;
typedef Vector3D Vertex;
typedef Vector3D NormalVector;
typedef Vector3D TextureCoordinate;
typedef Vector3type<float> Color3f;