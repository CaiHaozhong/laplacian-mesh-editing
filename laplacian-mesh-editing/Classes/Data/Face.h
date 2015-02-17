#pragma once
#include<vector>
class Face
{
public:
	/* Vertex indices */
	std::vector<unsigned int> v;

	/* Texture Coordinate indices */
	std::vector<unsigned int> vt;

	/* Normal indices */
	std::vector<unsigned int> vn;

	int getVertexNum(){ return v.size(); }
};