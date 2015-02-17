#include "HalfEdgeEntity.h"
#include "Utility.h"
#include "Camera.h"
#include<hash_map>
#include <time.h>
void __cdecl Log(const char* c);
//using namespace stdext;
HalfEdgeEntity::HalfEdgeEntity( ObjEntity* obj ):EntityImpl(obj)
{	
// 	clock_t start,end;
// 	start = clock();
// 	vector<Face*>* faces = obj->getFaces();
// 	vector<Vertex*>* vertexes = obj->m_vertexList;
// 	stdext::hash_map<char*, HE_edge*, hash_compare<const char*, CharLess> > edgeHashMap;
// 
// 	/* 防止顶点重复 */
// 	bool *vertexHasBeenHandle = new bool[vertexes->size()];
// 	memset(vertexHasBeenHandle,0,1);
// 	
// 	/* 先分配顶点 */
// 	for(int i = 0; i < vertexes->size(); i++)
// 	{
// 		HE_vert* hv = new HE_vert;
// 		Vertex* ov = vertexes->at(i);
// 		hv->init(ov->x, ov->y, ov->z);
// 		hv->index = i;
// 		_hvertsContainer.push_back(hv);
// 	}
// 
// 
// 	for(int i = 0; i < faces->size(); i++)
// 	{
// 		Face* face = faces->at(i);
// // 		if(i == 5595)
// // 			i = 5595;
// 		//handle one face
// 		//hface
// 
// 		HE_face* hface = new HE_face;
// 		//hvertex
// 		int faceVertCount = face->v.size();
// 		HE_vert** hverts = new HE_vert*[faceVertCount];
// 		for(int j = 0; j < faceVertCount; j++)
// 		{			
// 			int index = face->v.at(j);
// 			hverts[j] = _hvertsContainer.at(index-1);
// 		}
// 		//hedge
// 		/*HE_edge* hedges = new HE_edge[faceVertCount];*/
// 		for(int j = 0; j < faceVertCount; j++)
// 		{
// 			if(vertexHasBeenHandle[face->v.at(j)-1] == false)
// 			{
// 				HE_edge* hedge = new HE_edge;
// 				hverts[j]->edge = hedge;
// 				hedge->vert = hverts[(j+1)%faceVertCount];
// 				hedge->face = hface;
// 
// 
// 				vertexHasBeenHandle[face->v.at(j)-1] = true;
// 			}
// 			//init hvertex's edge
// 			//hverts[j]->edge = &hedges[j];
// 
// 			//hedges[j].vert = &hverts[(j+1)%faceVertCount];
// 			//hedges[j].face = hface;
// 			//寻找对称边
// 			char* key2 = _combine(face->v.at((j+1)%faceVertCount),face->v.at(j));
// 			if(edgeHashMap.find(key2) != edgeHashMap.end())
// 			{
// 				hedges[j].pair = edgeHashMap.at(key2);
// 				edgeHashMap.at(key2)->pair = &hedges[j];
// 				//erase edge from hashmap			
// 				edgeHashMap.erase(key2);
// 			}
// 			else
// 			{
// 				hedges->pair = NULL;
// 				//将边加入哈希表
// 				char* key1 = _combine(face->v.at(j),face->v.at((j+1)%faceVertCount));
// 				edgeHashMap.insert(stdext::hash_map<char*,HE_edge*, hash_compare<const char*, CharLess> >::value_type(
// 					key1,
// 					&hedges[j]
// 				));
// 			}
// 
// 		}
// 
// 		//init next edge
// 		for(int j = 0; j < faceVertCount; j++)
// 		{
// 			hedges[j].next = &hedges[(j+1)%faceVertCount];
// 		}
// 
// 		//hface's edge
// 		hface->edge = &hedges[0];
// 
// 		//add into vector
// 		for (int j = 0; j < faceVertCount; j++)
// 		{
// 			_hvertsContainer.push_back(&hverts[j]);
// 			_hedgesContainer.push_back(&hedges[j]);
// 			_visiableElemetnContainer.push_back(&hverts[j]);
// 			_visiableElemetnContainer.push_back(&hedges[j]);
// 		}
// 		_hfacesContainer.push_back(hface);
// 		_visiableElemetnContainer.push_back(hface);
// 	}
// 
// 	
// 	end = clock();
// 	int t = (end-start)/CLOCKS_PER_SEC;

	return;
}

HalfEdgeEntity::HalfEdgeEntity()
{

}

char* HalfEdgeEntity::_combine( int a, int b )
{
// 	int sub = a-b;	
// 	int sum = a+b;
/*	int d = a/b;*/
	char* ret = new char[20];
	sprintf_s(ret,20,"%d*%d",a,b);		 	
	return ret;
}

HalfEdgeEntity::~HalfEdgeEntity()
{

}

void HalfEdgeEntity::OnDraw()
{	

	//do Transform
	//include translation and rotation
	//doTransform();
// 	glColor3d(1.0,0,0);
// 	//正方形
// 	glBegin(GL_POLYGON);
// 	glVertex3d(-2,-2,-8);
// 	glVertex3d(2,-2,-8);
// 	glVertex3d(2,2,-8);
// 	glVertex3d(-2,2,-8);
// 	glEnd();
// 	//三角形
// 	glColor3d(0,1,0);
// 	glBegin(GL_TRIANGLES);
// 	glVertex3d(-3,-3,-10);
// 	glVertex3d(3,-3,-10);
// 	glVertex3d(0,3,-10);
// 	glEnd();
	// 	char si[30];
	// 	sprintf_s(si,"size:%d\n",_hedgesContainer.size());
	// 	Log(si);
	// 	int c = 0;
// 	glPointSize(3.0f);
// 	glBegin(GL_POINTS);
// 	glVertex2f(0.0f,0.0f);
// 	glVertex2f(1.0f,0.0f);
// 	glVertex2f(0.0f,1.0f);
// 	glEnd();
	for(int i = 0; i < _hedgesContainer.size(); i++)
	{
		HE_edge* edge = _hedgesContainer.at(i);
		if(edge->pair == NULL)
			continue;
		HE_vert* v1 = edge->pair->vert;
		HE_vert* v2 = edge->vert;
		//c++;
		//glLineWidth(3.0f);
		glColor3f(0.0f,0,1);
		glBegin(GL_LINES);
		glVertex3d(v1->x,v1->y,v1->z);
		glVertex3d(v2->x,v2->y,v2->z);
		glEnd();		
	}
	//draw three type of elements
// 	int i;
// 	char lc[100];
// 	sprintf_s(lc,"size:%d\n",_visiableElemetnContainer.size());
// 	Log(lc);
	
	for(int i = 0; i < _visiableElemetnContainer.size(); i++)
	{
// 		sprintf_s(lc,"i:%d\n",i);
// 		Log(lc);
		VisiableElement* v = _visiableElemetnContainer.at(i);				
		v->draw();					
	}
	int j = 0;
// 	for(i = 0; i < _hedgesContainer.size(); i++)
// 	{
// 		// 		sprintf_s(lc,"i:%d\n",i);
// 		// 		Log(lc);
// 		VisiableElement* v = _hedgesContainer.at(i);				
// 		v->draw();					
// 	}
// 	char si2[30];
// 	sprintf_s(si2,"count:%d\n",c);
// 	Log(si2);	

}

void HalfEdgeEntity::handleMousePoint( Vector2D p )
{	
	//在矩形外，直接返回
	//TO DO

	for(int i = 0; i < _visiableElemetnContainer.size(); i++)
	{
		VisiableElement* v = _visiableElemetnContainer.at(i);
		if(v->containPoint(p))		
			v->setVisible(true);										
		else
			v->setVisible(false);
	}	
}

void HE_vert::init( float _x, float _y, float _z )
{
	x = _x;
	y = _y;
	z = _z;
	edge = NULL;
	
}

bool HE_vert::containPoint( Vector2D p )
{
	Vector2D projPoint = Utility::project(Vector3D(x,y,z));
	if(Utility::pointDistance(p,projPoint) < 4)
		return true;
	return false;
}

void HE_vert::draw()
{
	if(!_visible)
		return;
	float prePointSize;
	glGetFloatv(GL_POINT_SIZE,&prePointSize);	
	glPushAttrib(GL_CURRENT_BIT);	
	glPointSize(5.0f);
	glColor3f(0.0f,1.0f,0.0f);
	glBegin(GL_POINTS);
	glVertex3d(x,y,z);
	glEnd();
	glPopAttrib();
	glPointSize(prePointSize);		
	
	//draw adjacent edge
	HE_edge* edge1 = this->edge;
	edge1->setVisible(true);
	edge1->draw();
	if(edge1->pair != NULL)
	{
		HE_edge* tmp = edge1->pair->next;
		while(tmp != edge1)
		{
			tmp->setVisible(true);
			tmp->draw();
			if(tmp->pair == NULL)
				break;
			tmp = tmp->pair->next;
		}
	}


}

HE_vert::HE_vert() :edge(NULL),index(-1)
{
	setColor(0.0f,1.0f,0.0f);
}

void HE_edge::draw()
{
	
	if(pair == NULL)
		return;
	if(!_visible)
		return;
	HE_vert* _p1 = pair->vert;
	HE_vert* _p2 = vert;	
	float preLineWidth;
	glGetFloatv(GL_LINE_WIDTH,&preLineWidth);	
	glLineWidth(3.0f);
	glPushAttrib(GL_CURRENT_BIT);		
	glColor3f(_color[0],_color[1],_color[2]);

	glBegin(GL_LINES);
	glVertex3d(_p1->x,_p1->y,_p1->z);
	glVertex3d(_p2->x,_p2->y,_p2->z);
	glEnd();

	glPopAttrib();
	glLineWidth(preLineWidth);

	//draw adjacent face
	this->face->setVisible(true);
	this->face->draw();
	if(this->pair != NULL)
	{
		this->pair->face->setVisible(true);
		this->pair->face->draw();
	}

}

HE_edge::HE_edge() :vert(NULL),pair(NULL),face(NULL),next(NULL)
{
	setColor(1.0f,0.0f,0.0f);
}

bool HE_edge::containPoint( Vector2D p )
{
	if(pair == NULL)
		return false;
	HE_vert* _p1 = pair->vert;
	HE_vert* _p2 = vert;
	Vector2D p1,p2;
	p1 = Utility::project(Vector3D(_p1->x,_p1->y,_p1->z));
	p2 = Utility::project(Vector3D(_p2->x,_p2->y,_p2->z));

	//x在p1和p2外面
	if(p1.x < p2.x)	
	{	
		if(p.x < p1.x || p.x > p2.x)
			return false;
	}
	else
	{
		if(p.x > p1.x || p.x < p2.x)
			return false;
	}
	//y在p1和p2外面
	if(p1.y < p2.y)	
	{	
		if(p.y < p1.y || p.y > p2.y)
			return false;
	}
	else
	{
		if(p.y > p1.y || p.y < p2.y)
			return false;
	}
	

	if(p.x == p1.x && p.x == p2.x)
		return true;
// 	double a = (p.y-p2.y)*(p.x-p1.x);
//     double b = (p.y-p1.y)*(p.x-p2.x);
	double slope1 = ((double)(p.y-p1.y))/(p.x-p1.x);
	double slope2 = ((double)(p.y-p2.y))/(p.x-p2.x);
	if(fabs(slope1 - slope2) <= 0.5f)
	{		
		return true;
	}
		
	return false;
}

void VisiableElement::setColor( float r,float g, float b )
{
	_color[0] = r;
	_color[1] = g;
	_color[2] = b;
}

void VisiableElement::getColor( float& r,float& g, float& b )
{
	r = _color[0];
	g = _color[1];
	b = _color[2];
}

VisiableElement::VisiableElement() :_visible(false)
{
	_color[0] = 0;
	_color[1] = 0;
	_color[2] = 0;
}

void VisiableElement::setVisible( bool v )
{
	_visible = v;
}

bool VisiableElement::isVisible()
{
	return _visible;
}

HE_face::HE_face() :edge(NULL)
{
	setColor(1.0,1.0f,0.0f);	
}

bool HE_face::containPoint( Vector2D p )
{
	/*
	vector<HE_vert*> verts;
	HE_edge* edge1 = this->edge;
	verts.push_back(edge1->vert);
	HE_edge* tmp = edge1->next;	
	while(tmp != edge1)
	{
		verts.push_back(tmp->vert);
		tmp = tmp->next;
	}
	assert(verts.size() == 4 || verts.size() == 3);
	vector<Vector2D> Point2Ds;	
	for (int i = 0; i < verts.size(); i++)
	{
		HE_vert* v = verts.at(i);
		Point2Ds.push_back(Utility::project(Vector3D(v->x,v->y,v->z)));
	}

	*/
	return false;
}

void HE_face::draw()
{
	if(!_visible)
		return;
	//Get Vertexes
	vector<HE_vert*> verts;
	HE_edge* edge1 = this->edge;
	verts.push_back(edge1->vert);
	HE_edge* tmp = edge1->next;	
	while(tmp != edge1)
	{
		verts.push_back(tmp->vert);
		tmp = tmp->next;
	}

	//draw			
	glPushAttrib(GL_CURRENT_BIT);		
	glColor3f(_color[0],_color[1],_color[2]);
	if(verts.size() == 3)
		glBegin(GL_TRIANGLES);
	else 
		glBegin(GL_POLYGON);
	for (int i = 0; i < verts.size(); i++)
	{
		HE_vert* v = verts.at(i);
		glVertex3d(v->x,v->y,v->z);
	}
	glEnd();

	glPopAttrib();	
	
}
