#include "geom.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <map>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>

using namespace std;

//colors for glut
GLfloat red[3] = {1.0, 0.0, 0.0};
GLfloat green[3] = {0.0, 1.0, 0.0};
GLfloat blue[3] = {0.0, 0.0, 1.0};
GLfloat black[3] = {0.0, 0.0, 0.0};
GLfloat white[3] = {1.0, 1.0, 1.0};
GLfloat gray[3] = {0.5, 0.5, 0.5};
GLfloat yellow[3] = {1.0, 1.0, 0.0};
GLfloat magenta[3] = {1.0, 0.0, 1.0};
GLfloat cyan[3] = {0.0, 1.0, 1.0};

GLint fillmode = 0;

double speed = 5;
int randMove = 1;
vector<point2D> points; //vector to store points to be make into area
vector<Triangle> vip; //Very important Polygons
vector<Triangle> vip1;
int n; //Amount of Points
//the current polygon 
vector<point2D>  poly;
//the gaurd point
point2D guard = {-10, -10}; //initialize off screen
point2D guard2 = {-10, -10};
//coordinates of last mouse click
//initialized to a point outside the window

//function declarations
void draw_segments();
void display(void);
void keypress(unsigned char key, int x, int y);
void timerfunc(); 
void mousepress(int button, int state, int x, int y);
void print_vp(vector<Triangle> tris);
void initialize_polygon();
void print_polygon(vector<point2D> poly);
const int WINDOWSIZE = 750; 
double mouse_x=-10, mouse_y=-10; 
int poly_init_mode = 0; 

void draw_circle(double x, double y){
  glColor3fv(blue);   
  int precision = 100;
  double r = 4; 
  double theta = 0;
  glBegin(GL_POLYGON);
  for(int i = 0; i < precision; i++){
    theta = i * 2 * M_PI/precision;
    glVertex2f(x + r*cos(theta), y + r*sin(theta));
  }
  glEnd();
}

void draw_guard(double x, double y){
  glColor3fv(red);   
  int precision = 100;
  double r = 4;
  double theta = 0;
  glBegin(GL_POLYGON);
  for(int i = 0; i < precision; i++){
    theta = i * 2 * M_PI/precision;
    glVertex2f(x + r*cos(theta), y + r*sin(theta));
  }
  glEnd();
}

void mousepress(int button, int state, int x, int y) {


  if(state == GLUT_DOWN) {

    mouse_x = x;
    mouse_y = y;
    //(x,y) are in wndow coordinates, where the origin is in the upper
    //left corner; our reference system has the origin in lower left
    //corner, this means we have to reflect y
    mouse_y = WINDOWSIZE - mouse_y; 
    
    printf("mouse click at (x=%d, y=%d)\n", (int)mouse_x, (int)mouse_y);
    if (poly_init_mode ==1) {
      point2D p = {mouse_x, mouse_y}; 
      poly.push_back(p);
    }
    if (poly_init_mode == 2) 
    {
	guard.x = mouse_x;
	guard.y = mouse_y; 
    }
    if (poly_init_mode == 3)
    {
	guard2.x = mouse_x;
	guard2.y = mouse_y;
    }  
    cout << "guard at " << guard.x << " " <<guard.y << endl;
    glutPostRedisplay();
  }

}


void initialize_polygon() {
  
  //clear the vector, in case something was there 
  poly.clear(); 
  int n = 10; //size of polygon 
  double rad = 100; 
  double step = 2 * M_PI / n;
  point2D p; 
  for (int i=0; i<n; i++) {

    p.x = WINDOWSIZE/2 + rad * cos (i * step); 
    p.y = WINDOWSIZE/2 + rad * sin (i * step); 


    //insert the segment in the array of segments 
    poly.push_back (p); 
  } //for i
}

void print_polygon(vector<point2D> poly) {

  for (unsigned int i=0; i<poly.size()-1; i++) {
    printf("edge %d: [(%d,%d), (%d,%d)]\n",
     i, poly[i].x, poly[i].y, poly[i+1].x, poly[i+1].y);
  }
  //print last edge from last point to first point 
  int last = poly.size()-1; 
    printf("edge %d: [(%d,%d), (%d,%d)]\n",
     last, poly[last].x, poly[last].y, poly[0].x, poly[0].y);

}

//function to draw the colored squares for the Mondrian visual 
void draw_segments() {
  //set polygons style: filled or contour 
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glLineWidth(1);
} 


		

int main(int argc, char** argv){
	if (argc != 2)
	{
		cout << "enter a number pretty please" << endl;
		return 0;
	}
	n = atoi(argv[1]);
	assert(n>0);
	//printPoints(points);
 	initialize_polygon();
  print_polygon(poly);

  
  /* initialize GLUT  */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WINDOWSIZE, WINDOWSIZE);
  glutInitWindowPosition(100,100);
  glutCreateWindow(argv[0]);

  /* register callback functions */
  glutDisplayFunc(display); 
  glutKeyboardFunc(keypress);
  glutMouseFunc(mousepress); 
  //  glutIdleFunc(timerfunc); 

  /* init GL */
  /* set background color black*/
  glClearColor(0, 0, 0, 0);   
  /* here we can enable depth testing and double buffering and so
     on */

  
  /* give control to event handler */
  glutMainLoop();
  return 0;

}

void draw_polygon(vector<point2D> poly){
  
  if (poly.size() == 0) return; 

  //set color 
  glColor3fv(yellow);   
  
  int i;
  for (i=0; i<poly.size()-1; i++) {
    glBegin(GL_LINES);
    glVertex2f(poly[i].x, poly[i].y); 
    glVertex2f(poly[i+1].x, poly[i+1].y);
    glEnd();
  }
  //render last segment between last point and forst point 
  int last=poly.size()-1; 
    glBegin(GL_LINES);
    glVertex2f(poly[last].x, poly[last].y); 
    glVertex2f(poly[0].x, poly[0].y);
    glEnd();
}


void print_triangle(Triangle tri)
{
	draw_circle(tri.b.x, tri.b.y);
	draw_circle(tri.c.x, tri.c.y);
	if (checkTwoPoints(tri.a, guard))
	{
		glColor3fv(cyan);
	}
	else
	{
		glColor3fv(magenta);
	}
	glBegin(GL_LINES);
	glVertex2f(tri.b.x, tri.b.y);
	glVertex2f(tri.c.x, tri.c.y);
	glEnd(); 
}


void print_vp(vector<Triangle> tris)
{
	for (int i = 0; i < tris.size(); i++) 
	{
		print_triangle(tris[i]);
	}
}	


void display(void) {

  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity(); //clear the matrix


  /* The default GL window is [-1,1]x[-1,1] with the origin in the
     center. 
     
     Our system of coordinates (in which we generate our points) is
     (0,0) to (WINSIZE,WINSIZE), with the origin in the lower left
     corner.

     We need to map the points to [-1,1] x [-1,1]  

     Assume we are the local coordinate system. 

     First we scale down to [0,2] x [0,2] */ 
  glScalef(2.0/WINDOWSIZE, 2.0/WINDOWSIZE, 1.0);  
  /* Then we translate so the local origin goes in the middle of teh
     window to (-WINDOWSIZE/2, -WINDOWSIZE/2) */
  glTranslatef(-WINDOWSIZE/2, -WINDOWSIZE/2, 0); 
  
  //now we draw in our local coordinate system (0,0) to
  //(WINSIZE,WINSIZE), with the origin in the lower left corner.

  draw_polygon(poly); 
  //draw a circle where the mouse was last clicked. Note that this
  //point is stored as a global variable and is modified by the mouse handler function 
  if (poly_init_mode != 2)
  {
	draw_circle(mouse_x, mouse_y); 
  } 
  print_vp(vip1);
  print_vp(vip);
  draw_guard(guard.x, guard.y);
  draw_guard(guard2.x, guard2.y);
  /* execute the drawing commands */
  glFlush();
}



/* ****************************** */
void keypress(unsigned char key, int x, int y) {
  switch(key) {
  case 'q':
    exit(0);
    break;

    //expected behaviour: press 's', then click on the points you
    //want, and press 'e' when you're done. the points will be saved
    //in global 'poly'
    
  case 'z': 
    vip.clear();
    vip1.clear();
    guard2.x, guard2.y = -10, -10;
    guard.x, guard.y = -10, -10;
    //start re-initializeing polygon 
    poly.clear();
    mouse_x = mouse_y=0; 
    poly_init_mode = 1; 
    glutPostRedisplay();
    break; 
  case 'g':
    //place guard into polygon
    poly_init_mode = 2;
    glutPostRedisplay();
    break;
  case 'h':
    poly_init_mode = 3;
    glutPostRedisplay();
    break;
  case 'x': 
    poly_init_mode=0; 
    glutPostRedisplay();
    break; 

  case 'c':
    vip = compute_vp(poly, guard);
    print_vp(vip);
    vip1 = compute_vp(poly, guard2);
    print_vp(vip1);
    glutPostRedisplay();
    break;

  case 'i':
    guard2.y += speed;
    vip1 = compute_vp(poly, guard2);
    print_vp(vip1);
    glutPostRedisplay();
    break;

  case 'k':
    guard2.y -= speed;
    vip1 = compute_vp(poly, guard2);
    print_vp(vip1);
    glutPostRedisplay();
    break;

  case 'j':
    guard2.x -= speed;
    vip1 = compute_vp(poly, guard2);
    print_vp(vip1);
    glutPostRedisplay();
    break;

  case 'l':
    guard2.x += speed;
    vip1 = compute_vp(poly, guard2);
    print_vp(vip1);
    glutPostRedisplay();
    break;

  case 'w':
    guard.y += speed;
    vip = compute_vp(poly, guard);
    print_vp(vip);
    glutPostRedisplay();
    break;

  case 's':
    guard.y -= speed;
    vip = compute_vp(poly, guard);
    print_vp(vip);
    glutPostRedisplay();
    break; 

  case 'a':
    guard.x -= speed;
    vip = compute_vp(poly, guard);
    print_vp(vip);
    glutPostRedisplay();
    break; 

  case 'd':
    guard.x += speed;
    vip = compute_vp(poly, guard);
    print_vp(vip);
    glutPostRedisplay();
    break; 
  case 'e':
    speed = speed * 1.2;
    break;
  case 'r':
    speed = speed * .8;
    break;	
  } 
}

/*whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
     
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   gluOrtho2D(0.0, (GLdouble) width, 0.0, (GLdouble) height); 
}










