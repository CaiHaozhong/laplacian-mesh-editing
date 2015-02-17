#include "ObjEntity.h"
#include "Camera.h"
#include "BMP.h"
ObjEntity::ObjEntity()
{
}

ObjEntity::~ObjEntity()
{
	for(int i = 0; i < m_vertexList->size(); i++)		
		delete m_vertexList->at(i);
	m_vertexList->clear();	
	delete m_vertexList;

	for(int i = 0; i < m_normalVectorList->size(); i++)
		delete m_normalVectorList->at(i);
	m_normalVectorList->clear();
	delete m_normalVectorList;

	for(int i = 0; i < m_textureCoordinateList->size(); i++)
		delete m_textureCoordinateList->at(i);
	m_textureCoordinateList->clear();
	delete m_textureCoordinateList;

	for(int i = 0; i < m_faceList->size(); i++)
		delete m_faceList->at(i);
	m_faceList->clear();
	delete m_faceList;

	delete materialDataManager;
}
Vertex* ObjEntity::vertexAt( int i )
{
	return m_vertexList->at(i);
}

TextureCoordinate* ObjEntity::textureCoordinateAt( int i )
{
	return m_textureCoordinateList->at(i);
}

NormalVector* ObjEntity::normalVectorAt( int i )
{
	return m_normalVectorList->at(i);
}

vector<Face*> * ObjEntity::getFaces()
{
	return m_faceList;
}
void ObjEntity::OnDraw()
{	
	if(!m_vertexList || m_vertexList->size() == 0)
		return;
	//glPushMatrix();

	//do Transform
	//include translation and rotation
	//doTransform();

	glEnable(GL_TEXTURE_2D);	
	vector<Face*>* faces = m_faceList;
	materialDataManager->initCurrentIndex();
	for(int i = 0; i < faces->size(); i++)
	{
		if(i == materialDataManager->getCurrentIndex())
		{
			useMaterial(materialDataManager->getMaterialDataByIndex(i));
			materialDataManager->next();
		}
		Face* f = faces->at(i);
		if(f->getVertexNum() == 3)
		{
			glBegin(GL_TRIANGLES);
		}
		else
		{
			glBegin(GL_POLYGON);
		}

		for(int i = 0; i < f->v.size(); i++)
		{
			NormalVector* vn = normalVectorAt(f->vn.at(i)-1);
			glNormal3d(vn->x,vn->y,vn->z);
			Vertex* v = vertexAt(f->v.at(i)-1);		

			if(f->vt.at(i) != -1)
			{
				TextureCoordinate* tc = textureCoordinateAt(f->vt.at(i)-1);
				//if(tc->x != -1 && tc->y != -1)
				glTexCoord2f(tc->x,tc->y);
			}
			glVertex3d(v->x,v->y,v->z);
		}
		glEnd();		
	}
	glDisable(GL_TEXTURE_2D);
	//glPopMatrix();
}

void ObjEntity::useMaterial( MaterialData* mData )
{
	GLfloat gl_ambient[] = {mData->ka[0],mData->ka[1],mData->ka[2],1.0f};
	GLfloat gl_diffuse[] = {mData->kd[0],mData->kd[1],mData->kd[2],1.0f};
	GLfloat gl_specular[] = {mData->ks[0],mData->ks[1],mData->ks[2],1.0f};
	glMaterialfv(GL_FRONT,GL_AMBIENT,gl_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,gl_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,gl_specular);
	GLfloat ns = mData->ns * 128.0f/1000.0f;
	glMaterialf(GL_FRONT,GL_SHININESS,ns);

	if(mData->hasTexture())
	{
		glBindTexture(GL_TEXTURE_2D,mData->getTexture());
	}
}

int ObjEntity::getVertexCount()
{
	return m_vertexList->size();
}
