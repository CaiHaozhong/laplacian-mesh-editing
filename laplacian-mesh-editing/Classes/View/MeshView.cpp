#include "MeshView.h"
#include "ObjDrawerPrimitive.h"
#include "Utility.h"
#include <math.h>
#include "ObjUtility.h"
#include "HalfEdgeEntity.h"
#include <fstream>
void print(double m[16],ofstream& o)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			o << m[j*4+i] << ' ';
		}
		o << endl;
	}
	o << endl;
}
// #define PI 3.14159
// #define DegreeToRadius(d) ((PI/180.0)*d)
// #define RadiusToDegree(r) ((180.0/PI)*r)

MeshView::MeshView(int x,int y,int w,int h,const char *l)
            : Fl_Gl_Window(x,y,w,h,l)
{

    mControlSize = 1.0;    
	mMesh = NULL;	
	mRotateMatrix[0] = 1; mRotateMatrix[4] = 0; mRotateMatrix[8] = 0; mRotateMatrix[12] = 0;
	mRotateMatrix[1] = 0; mRotateMatrix[5] = 1; mRotateMatrix[9] = 0; mRotateMatrix[13] = 0;
	mRotateMatrix[2] = 0; mRotateMatrix[6] = 0; mRotateMatrix[10] = 1; mRotateMatrix[14] = 0;
	mRotateMatrix[3] = 0; mRotateMatrix[7] = 0; mRotateMatrix[11] = 0; mRotateMatrix[15] = 1;

	mDragType = DRAG_VIEW;
	mMeshProcessor = nullptr;
}

void MeshView::draw() 
{
	if(mMesh == NULL)
	{
		int ret;
		ObjEntity* mesh = ObjUtility::createObjEntity("result.obj",ret);
		Size3D size = mesh->getSize();
		double m = max(max(size.x,size.y),max(size.x,size.z));
		mScale = 15.0/m;
		//HalfEdgeEntity* halfEdgeMesh = new HalfEdgeEntity(mesh);
		this->setMesh(mesh);
		ObjDrawerPrimitive *drawer = new ObjDrawerPrimitive(mMesh);
		drawer->setPointColor(Color3f(1.0f,0,0));
		drawer->setPointSize(2.0f);
		mMeshDrawer = drawer;
	}

    if (!valid()) {
		glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
        glViewport(0,0,w(),h());
        glOrtho(-10,10,-10,10,1,10000);
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    //glTranslatef(10, 20, 0);
    //glRotatef(xAng,1,0,0); glRotatef(yAng,0,1,0);glRotatef(zAng,0,0,1);
	glTranslatef(0,0,-100);

	/* UI控件控制大小 */
	glScalef(mControlSize,mControlSize,mControlSize);

	/* 缩放使其完全显示 */
	glScalef(mScale,mScale,mScale);
	

	glMultMatrixd(mRotateMatrix);

	Vector3D meshCenter = mMesh->getCenter();
	glTranslatef(-meshCenter.x,-meshCenter.y,-meshCenter.z);
	//glPushMatrix();    
	//glTranslatef(1,2, 0);
	
	glGetDoublev(GL_MODELVIEW_MATRIX,Utility::modelViewMatrix);
// 	double modelViewMatrix[16];
// 	double projMatrix[16];
// 	double viewPort[4];
// 	glGetDoublev(GL_MODELVIEW_MATRIX,modelViewMatrix);
// 	glGetDoublev(GL_PROJECTION_MATRIX,projMatrix);
// 	glGetDoublev(GL_VIEWPORT,viewPort);
// 	ofstream o("tmp.txt",ios::app);
// 	print(modelViewMatrix,o);
// 	print(projMatrix,o);
// 	o.close();

    //drawMesh();
	if(mMeshDrawer)
		mMeshDrawer->drawMesh();
    //glPopMatrix();

    glPopMatrix();
}

void MeshView::setMesh( EntityImpl* mesh )
{
	mMesh = mesh;
}

int MeshView::handle( int event )
{
		switch(event) 
		{
		case FL_RELEASE:
			printf("pos:%d,%d\n",Fl::event_x(),Fl::event_y());
			if(mIsDrag == true)
			{
				if(mDragType == DRAG_VIEW)
					mTrackball.storeLastRotation();
			}
			if(mIsDrag == false)
			{
				//((HalfEdgeEntity*)mMesh)->handleMousePoint(Vector2D(Fl::event_x(),this->h()-Fl::event_y()));
				//redraw();
			}
			if(mMeshProcessor)
				mMeshProcessor->mouseRelease(Fl::event_button(),Fl::event_x(),this->h()-Fl::event_y());
			break;
		case FL_PUSH:
			mIsDrag = false;
			double m[16];
			//glGetDoublev(GL_MODELVIEW_MATRIX,m);
			startMouseX = Fl::event_x()-this->w()/2;
			startMouseY = this->h()/2-Fl::event_y();
			if(mMeshProcessor)
				mMeshProcessor->mousePush(Fl::event_button(),Fl::event_x(),this->h()-Fl::event_y());
			break;
		case FL_DRAG:
			mIsDrag = true;
			if(mDragType == DRAG_VIEW)
			{				
				int endMouseX = Fl::event_x()-this->w()/2;
				int endMouseY = this->h()/2-Fl::event_y();
				mTrackball.getRotateMatrix(startMouseX,startMouseY,endMouseX,endMouseY,mRotateMatrix);
				redraw();				
			}
			else if(mDragType == DRAG_EDIT)
			{
				if(mMeshProcessor)
					mMeshProcessor->mouseDrag(Fl::event_button(),Fl::event_x(),this->h()-Fl::event_y());
			}
			break;
		}
	

	Fl_Gl_Window::handle(event);
	return 1;
}


//
// End of "$Id: MeshView.cxx 8500 2011-03-03 09:20:46Z bgbnbigben $".
//