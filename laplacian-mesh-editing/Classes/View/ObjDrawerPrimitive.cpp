#include "ObjDrawerPrimitive.h"

ObjDrawerPrimitive::ObjDrawerPrimitive()
{
	mPointSize = 1.0f;
	mPointColor[0] = 1.0f;
	mPointColor[1] = 1.0f;
	mPointColor[2] = 1.0f;
}

ObjDrawerPrimitive::ObjDrawerPrimitive( EntityImpl* mesh ) :MeshDrawerImpl(mesh)
{
	mPointSize = 1.0f;
	mPointColor[0] = 1.0f;
	mPointColor[1] = 1.0f;
	mPointColor[2] = 1.0f;
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
	float colorBackUp[4];		
	glGetFloatv(GL_POINT_SIZE,&pointSizeBackUp);
	glGetFloatv(GL_CURRENT_COLOR,colorBackUp);
	glPointSize(mPointSize);
	glColor3fv(mPointColor);
	glBegin(GL_POINTS);
	for (int i = 0; i < vertexContainer->size(); i++)
	{
		Vertex* ver = vertexContainer->at(i);
		glVertex3d(ver->x,ver->y,ver->z);
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
	mPointColor[0] = color.x;
	mPointColor[1] = color.y;
	mPointColor[2] = color.z;
}

