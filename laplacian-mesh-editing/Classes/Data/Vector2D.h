#pragma once

template<typename TReal>
struct Vector2type
{
	TReal x,y;
	Vector2type(){}
	Vector2type(TReal _x, TReal _y):x(_x),y(_y){}
};
typedef Vector2type<double> Vector2D;