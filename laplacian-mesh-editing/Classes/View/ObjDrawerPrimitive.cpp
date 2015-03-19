#include "ObjDrawerPrimitive.h"

ObjDrawerPrimitive::ObjDrawerPrimitive()
{
	mPointSize = 1.0f;
	mPointColor = Color3f(1.0f,1.0f,1.0f);
}

ObjDrawerPrimitive::ObjDrawerPrimitive( EntityImpl* mesh, Fl_Gl_Window* context ) :MeshDrawerImpl(mesh,context)
{
	mPointSize = 1.0f;
	mPointColor = Color3f(1.0f,1.0f,1.0f);
}

void ObjDrawerPrimitive::drawMesh()
{
	ObjEntity* objMesh = dynamic_cast<ObjEntity*>(mMesh);
	if(objMesh == nullptr)
	{
		printf("error: wrong mesh type in ObjDrawerPrimitive\n");
		return;
	}
	std::vector<Face*>* faceContainer = objMesh->getFaces();
	std::vector<Vertex*>* vertexContainer = objMesh->m_vertexList;
	drawVertexes(vertexContainer);
	for (int i = 0; i < faceContainer->size(); i++)
	{
		Face* face = faceContainer->at(i);					
		glBegin(GL_LINE_LOOP);
		for (int vI = 0; vI < face->getVertexNum(); vI++)
		{
			Vertex* ver = vertexContainer->at(face->v.at(vI)-1);
			glVertex3d(ver->x,ver->y,ver->z);
		}
		glEnd();
	}
}

void ObjDrawerPrimitive::drawVertexes( std::vector<Vertex*>* vertexContainer )
{
	float pointSizeBackUp;
	
	glGetFloatv(GL_POINT_SIZE,&pointSizeBackUp);	
	glPointSize(mPointSize);
	float colorBackUp[4];
	glGetFloatv(GL_CURRENT_COLOR,colorBackUp);
	glBegin(GL_POINTS);
	int vertexColorArrayIndex = 0;
	for (int i = 0; i < vertexContainer->size(); i++)
	{
		Vertex* ver = vertexContainer->at(i);
		if(vertexColor.size() > vertexColorArrayIndex && i == vertexColor.at(vertexColorArrayIndex).index)
		{
			drawVertexWithColor(ver,vertexColor.at(vertexColorArrayIndex).color);
			vertexColorArrayIndex++;
		}
		else
			drawVertexWithColor(ver,mPointColor);
	}
	glEnd();
	glPointSize(pointSizeBackUp);
	glColor3fv(colorBackUp);
}

void ObjDrawerPrimitive::setPointSize( float size )
{
	mPointSize = size;
}

void ObjDrawerPrimitive::setPointColor( Color3f color )
{
	mPointColor = color;
}

void ObjDrawerPrimitive::setVertexColorWithIndex( int index, const Color3f& c)
{
	vertexColor.push_back(_VertexColor(index,c));
	std::sort(vertexColor.begin(),vertexColor.end());	
}

void ObjDrawerPrimitive::drawVertexWithColor( Vertex* ver, Color3f c )
{
	glColor3f(c.x,c.y,c.z);
	glVertex3d(ver->x,ver->y,ver->z);
}

void ObjDrawerPrimitive::clearVerticesColor()
{
	vertexColor.clear();
}

