#ifndef MESHVIEW_H
#define MESHVIEW_H 1
#  include <FL/Fl.H>
#  include <FL/Fl_Gl_Window.h>
#  include <GL/gl.h>

#include <stdlib.h>
#include "EntityImpl.h"
#include "Trackball.h"
#include "MeshDrawerImpl.h"
#include "MeshProcessor.h"

class MeshView : public Fl_Gl_Window {


public:
    MeshView(int x,int y,int w,int h,const char *l=0);


    void setControlSize(float v) { mControlSize=v; }

	
    void draw();

	int handle(int event);

	void setMesh(EntityImpl* mesh);

	MeshProcessor* getMeshProcessor() const { return mMeshProcessor; }

	void setMeshProcessor(MeshProcessor* processor) { mMeshProcessor = processor; }

public:
	/* 鼠标拖动的功能 */
	const static int DRAG_VIEW = 0x01;
	const static int DRAG_EDIT = 0x02;
	void setDragType(int dragType){mDragType = dragType;}
private:

    // this value determines the scaling factor used to draw the cube.
    double mControlSize;
    
		
	EntityImpl* mMesh;

	int startMouseX, startMouseY;

	Trackball mTrackball;
	double mRotateMatrix[16];

	double mScale;

	/* 鼠标是否拖动 */
	bool mIsDrag;

	int mDragType;

	MeshDrawerImpl* mMeshDrawer;

	MeshProcessor* mMeshProcessor;

};

#endif

//
// End of "$Id: CubeView.h 8500 2011-03-03 09:20:46Z bgbnbigben $".
//