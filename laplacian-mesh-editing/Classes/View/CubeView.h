#ifndef CUBEVIEW_H
#define CUBEVIEW_H 1

//#include <config.h>

//#include <fltk/run.h>

#  include <FL/Fl_Gl_Window.h>
#  include <GL/gl.h>

#include <stdlib.h>

class CubeView : public Fl_Gl_Window {


public:
    CubeView(int x,int y,int w,int h,const char *l=0);

    /* Set the rotation about the vertical (y ) axis.
     *
     * This function is called by the horizontal roller in CubeViewUI and the
     * initialize button in CubeViewUI.
     */
    void v_angle(float angle) { vAng=angle; }
    
    // Return the rotation about the vertical (y) axis.
    float v_angle() { return vAng; }

    /* Set the rotation about the horizontal (x) axis.
     *
     * This function is called by the vertical roller in CubeViewUI
     */
    void h_angle(float angle) { hAng=angle; }

    // the rotation about the horizontal (x) axis.
    float h_angle() { return hAng; }

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
    void setsize(float v) { size=v; }

    /*The widget class draw() override.
     *
     *The draw() function initialize Gl for another round o f drawing
     * then calls specialized functions for drawing each of the
     * entities displayed in the cube view.
     *
     */
    void draw();    

private:
    /* Draw the cube boundaries
     *
     * Draw the faces of the cube using the boxv[] vertices, using
     * GL_LINE_LOOP for the faces. The color is \#defined by CUBECOLOR.
     */

    void drawCube();


    // this value determines the scaling factor used to draw the cube.
    double size;
    
    float vAng, hAng;
    float xshift, yshift;

    float boxv0[3]; float boxv1[3];
    float boxv2[3]; float boxv3[3];
    float boxv4[3]; float boxv5[3];
    float boxv6[3]; float boxv7[3];
};

#endif

//
// End of "$Id: CubeView.h 8500 2011-03-03 09:20:46Z bgbnbigben $".
//