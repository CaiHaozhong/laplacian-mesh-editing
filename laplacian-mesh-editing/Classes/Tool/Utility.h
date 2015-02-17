#pragma once
#include "Vector3D.h"
#include "Vector2D.h"
class Utility
{
public:
	Utility();
	~Utility();

	//************************************
	// Method:    project
	// FullName:  Utility::project
	// Access:    public static 
	// Returns:   CPoint(in screen coordinate, the origin is at leftTop)
	// Qualifier:
	// Parameter: Point p
	//************************************
	static Vector2D project(Vector3D p);


	static double pointDistance(Vector2D p1, Vector2D p2);

	static double modelViewMatrix[16];
private:

};

