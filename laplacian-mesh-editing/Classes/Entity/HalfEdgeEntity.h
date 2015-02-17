#pragma once
#include "EntityImpl.h"
#include "MaterialDataManager.h"
#include "Vector3D.h"
#include "ObjEntity.h"
#include "Vector2D.h"
class VisiableElement
{
protected:
	bool _visible;
	float _color[3];
public:
	void setColor(float r,float g, float b);
	void getColor(float& r,float& g, float& b);
	VisiableElement();	
	void setVisible(bool v);
	bool isVisible();
	virtual void draw() = 0;
	virtual bool containPoint(Vector2D p) = 0;
};
class HE_edge;
class HE_face;
//Vertex
class HE_vert : public VisiableElement
{	
public:
	void draw();
	bool containPoint(Vector2D p);
	void init(float _x, float _y, float _z);
	float x;
	float y;
	float z;
	HE_vert();
	HE_edge* edge;  // one of the half-edges emantating from the vertex

	/* 该顶点在模型顶点数组的下标，用来构造邻接矩阵 */
	int index;
};

//Edge
class HE_edge : public VisiableElement
{
public:
	void draw();
	bool containPoint(Vector2D p);
	HE_vert* vert;   // vertex at the end of the half-edge
	HE_edge* pair;   // oppositely oriented adjacent half-edge 
	HE_face* face;   // face the half-edge borders
	HE_edge* next;   // next half-edge around the face
	HE_edge();
};

//Face
class HE_face : public VisiableElement
{
public:
	void draw();
	bool containPoint(Vector2D p);
	HE_edge* edge;  // one of the half-edges bordering the face
	HE_face();
};
struct CharLess : public binary_function<const char*, const char*, bool>
{
public:
    result_type operator()(const first_argument_type& _Left, const second_argument_type& _Right) const
    {
        return(strcmp(_Left, _Right) < 0 ? true : false);
    }
};

class HalfEdgeEntity : public EntityImpl
{
public:
 	vector<HE_vert*> _hvertsContainer;
 	vector<HE_edge*> _hedgesContainer;
 	vector<HE_face*> _hfacesContainer;
	vector<VisiableElement*> _visiableElemetnContainer;
	//Data	

	//************************************
	// Method:    handleMousePoint
	// FullName:  HalfEdgeEntity::handleMousePoint
	// Access:    public 
	// Returns:   bool (if something need to be drawed, it return true, or false)
	// Qualifier:
	// Parameter: Vector2D p
	//************************************
	void handleMousePoint(Vector2D p);

	HalfEdgeEntity(ObjEntity* obj);
	HalfEdgeEntity();
	~HalfEdgeEntity();
	
	void OnDraw();	
private:
	char* _combine(int a, int b);
};
