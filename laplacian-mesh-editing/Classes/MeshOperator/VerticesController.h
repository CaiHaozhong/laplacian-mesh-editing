#pragma once
#include "Eigen/Dense"
#include "EntityImpl.h"
#include "MeshDrawerImpl.h"
#include "Vector2D.h"
#include <vector>
#include "Utility.h"
#include "ObjEntity.h"
#include "ObjDrawerPrimitive.h"
class VerticesController
{
public:
	VerticesController(EntityImpl* mesh, MeshDrawerImpl* drawer):mMesh(mesh),mDrawer(drawer){};
	VerticesController();
	~VerticesController();
	
	/* x,y are in OpenGL Coordinate */
	void mousePush(int button, int x, int y)
	{		
		lastCoordinate = Vector2D(x,y);

		selectedVertices.clear();
		std::vector<Vertex*>* vertices = ((ObjEntity*)mMesh)->m_vertexList;
		std::vector<unsigned int> selected;
		for (int i = 0; i < vertices->size(); i++)
		{
			Vertex* v = vertices->at(i);
			if(isVertexSelected(v,Vector2D(x,y)))
				selected.push_back(i);
		}
		if(selected.size() > 0)
		{
			if(selected.size() == 1)
			{
				selectedVertices.push_back(selected.at(0));				
			}
			else
			{
				/* Find Max Z */
				double maxZ = vertices->at(selected.at(0))->z;
				int ret = selected.at(0);
				for (int i = 0; i < selected.size(); i++)
				{
					double vz = vertices->at(selected.at(i))->z;
					if(vz > maxZ)
					{
						ret = i;
						maxZ = vz;
					}
				}
				selectedVertices.push_back(ret);
			}
		}
	}

	void mouseRelease(int button, int x, int y){}

	void mouseDrag(int button, int x, int y)
	{
 		if (selectedVertices.size() == 0)
 			return;
		Vector2D dragVector2D = getNormalizedDragVector(lastCoordinate,Vector2D(x,y));
		Vector3D translate3D = computeTranslationVector(dragVector2D);
		fprintf(stdout,"translate3D:%lf,%lf,%lf\n",translate3D.x,translate3D.y,translate3D.z);
		Vertex* selectVertex = ((ObjEntity*)mMesh)->m_vertexList->at(selectedVertices.at(0));
		selectVertex->x += translate3D.x;
		selectVertex->y += translate3D.y;
		selectVertex->z += translate3D.z;
		mDrawer->postRedraw();
		lastCoordinate = Vector2D(x,y);
	}
	Vector2D getNormalizedDragVector(const Vector2D& coord01, const Vector2D& coord02)
	{
		Vector2D normalized01 = normalizePoint(coord01);
		Vector2D normalized02 = normalizePoint(coord02);
		return Vector2D(normalized02.x - normalized01.x, normalized02.y - normalized01.y);
	}
	EntityImpl* getMesh() const { return mMesh; }

	void setMesh(EntityImpl* val) { mMesh = val; }

	bool isVertexSelected(Vertex* v, const Vector2D& point)
	{
		Vector2D projectV = Utility::project(*v);
		if(Utility::pointDistance(projectV,point) <= 1.0f)
			return true;
		return false;
	}

	std::vector<unsigned int> getSelectedVertices()
	{
		return selectedVertices;
	}
private:
	std::vector<unsigned int> selectedVertices;
	EntityImpl* mMesh;
	MeshDrawerImpl* mDrawer;
	Vector2D lastCoordinate;
	Vector2D normalizePoint(const Vector2D& p)
	{
		Vector2D screenSize = Utility::getScreenSize();
		return Vector2D(p.x/screenSize.x,p.y/screenSize.y);
	}
	Vector3D computeTranslationVector(const Vector2D& translate2D)
	{
		Eigen::Vector4d translate3D(translate2D.x*2,translate2D.y*2,0,0);
		GLdouble projview[16];		
		glGetDoublev(GL_PROJECTION_MATRIX,projview);
		Eigen::Matrix<double,4,4> projmatrix = getEigenMatrix(projview);
		Eigen::Matrix<double,4,4> modelViewmatrix = getEigenMatrix(Utility::modelViewMatrix);
		Eigen::Vector4d t = modelViewmatrix.inverse()*projmatrix.inverse()*translate3D;
		return Vector3D(t(0),t(1),t(2));
	}

	Eigen::Matrix4d getEigenMatrix(double matrix[16])
	{
		Eigen::Matrix4d ret;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				ret(i,j) = matrix[j*4+i];
			}
		}
		return ret;
	}
};