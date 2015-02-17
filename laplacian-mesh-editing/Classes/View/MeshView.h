#ifndef MESHVIEW_H
#define MESHVIEW_H 1
#  include <FL/Fl.H>
#  include <FL/Fl_Gl_Window.h>
#  include <GL/gl.h>

#include <stdlib.h>
#include "EntityImpl.h"
#include "Trackball.h"
#include "MeshDrawerImpl.h"

class MeshView : public Fl_Gl_Window {


public:
    MeshView(int x,int y,int w,int h,const char *l=0);

    /* Set the rotation about the vertical (y ) axis.
     *
     * This function is called by the horizontal roller in CubeViewUI and the
     * initialize button in CubeViewUI.
     */
    void v_angle(float angle) { yAng=angle; }
    
    // Return the rotation about the vertical (y) axis.
    float v_angle() { return yAng; }

    /* Set the rotation about the horizontal (x) axis.
     *
     * This function is called by the vertical roller in CubeViewUI
     */
    void h_angle(float angle) { xAng=angle; }

    // the rotation about the horizontal (x) axis.
    float h_angle() { return xAng; }

    /* Sets the x shift of the cube view camera.
     *
     * This function is called by the slider in CubeViewUI
     */
    void panx(float x) { xshift=x; }

    /* Sets the y shift of the cube view camera.
     *
     * This function is called by the slider in CubeViewUI
     */
    void pany(float y) { yshift=y; }

    /* Sets the scale factor of the cube view camera.
     *
     * This function is called by the slider in CubeViewUI
     */
    void setControlSize(float v) { mControlSize=v; }

	

    /*The widget class draw() override.
     *
     *The draw() function initialize Gl for another round o f drawing
     * then calls specialized functions for drawing each of the
     * entities displayed in the cube view.
     *
     */
    void draw();

	int handle(int event);

	void setMesh(EntityImpl* mesh);
private:

    // this value determines the scaling factor used to draw the cube.
    double mControlSize;
    
    float yAng, xAng, zAng;
    float xshift, yshift;
		
	EntityImpl* mMesh;
private:
	int startMouseX, startMouseY;

	Trackball mTrackball;
	double mRotateMatrix[16];

	double mScale;

	/*  Û±Í «∑ÒÕœ∂Ø */
	bool mIsDrag;

	MeshDrawerImpl* mMeshDrawer;
};

#endif

//
// End of "$Id: CubeView.h 8500 2011-03-03 09:20:46Z bgbnbigben $".
//