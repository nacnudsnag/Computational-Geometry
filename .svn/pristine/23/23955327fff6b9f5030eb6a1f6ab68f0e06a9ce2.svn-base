/* 

intersect.cpp

Laura Toma

What it does:  

Draws a set of horizontal and vertical line segments in the default 2D
projection. Then it pretends to compute their intersections using the
line sweep algorithm, and simulates the sweep line moving from left to
right.

*/

#include "geom.h"
#include "rtimer.h"

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



GLfloat red[3] = {1.0, 0.0, 0.0};
GLfloat green[3] = {0.0, 1.0, 0.0};
GLfloat blue[3] = {0.0, 0.0, 1.0};
GLfloat black[3] = {0.0, 0.0, 0.0};
GLfloat white[3] = {1.0, 1.0, 1.0};
GLfloat gray[3] = {0.5, 0.5, 0.5};
GLfloat yellow[3] = {1.0, 1.0, 0.0};
GLfloat magenta[3] = {1.0, 0.0, 1.0};
GLfloat cyan[3] = {0.0, 1.0, 1.0};





/* forward declarations of functions */
void display(void);
void keypress(unsigned char key, int x, int y);
void timerfunc(); 

void initialize_segments_random(); 
void initialize_segments_horizontal(); 
void print_segments(); 

//renders the sweep line 
void draw_sweep_line();

//renders the active structure
void draw_active_structure();

//renders the intersection points 
void draw_intersection_points();





/* global variables */
const int WINDOWSIZE = 500; 

//we got two test cases so far: random and horizontal; add more!
int init_case = 0; 
const int NB_TEST_CASES = 2; 

//NOTE: all the structures below need to be global so that they can be rendered

//number of segments requested by user 
int n; 

//the array of  segments
vector<segment2D>  segments;

//the active structure that stores the segments intersecting the sweep line 
vector<segment2D> as;

//the intersections points of the segments 
vector<point2D> intpoints; 


//the events. do we need this??
vector<sweepEvent> events; 

int k = 0; //used to index through the events list alongside the sweep_line_x

//current position of sweep line; this is used to animate the sweep line moving 
int sweep_line_x = 0; 


typedef multimap<int, segment2D, less<int> > Map; //multimap to store the active structures
Map bst; //create one 

//compare function for sorting the events 
bool compareByX(const sweepEvent &a, const sweepEvent &b) {
	return a.x < b.x;
}
void init_segs_hash() {
	segments.clear();
	events.clear();
	bst.clear();
	int i;
	int offset = 100;
	int len = 200;
	int pad = len/2;
	point2D a, b;
	segment2D s;
	int j = 0;
	for (i = 0; i < n; i++) {
		if (i % 3 == 0) {
			a.x = 40 + j;
			a.y = 20;
			b.x = 40 + j;
			b.y = 480;
			j = j + 1;
		}
		if (i % 3 == 1) {
			a.x = 38;
			b.x = 462;
			a.y = 200 + j;
			b.y = 200 + j;
			j++;
		}
		if (i % 3 == 2) {
			a.x = 260 - j;
			a.y = 20;
			b.y = 480;
			b.x = 260 - j;
			j++;
		}
		s.start = a;
		s.end = b;
		segments.push_back(s);		
	}
}
void initialize_segments_worst_case() {
    //clear the vector
    segments.clear();
    int i;
    int offset = 100;
    int length = 300;
    int pad = length / (n/2);
    point2D a, b;
    segment2D s;

    // printf("pad = %d\n", pad);

    int count1 = 0, count2 = 0;

    for (i = 0; i < n; i++) {

        if (i % 2 == 0) {
            // horizontal segment
            a.x = offset;
            a.y = offset + pad * count1;
            b.x = offset + length;
            b.y = offset + pad * count1;
            s.start = a;
            s.end = b;
            count1++;
        }
        else {
            // vertical segment
            a.x = offset + pad * count2;
            a.y = offset;
            b.x = offset + pad * count2;
            b.y = offset + length;
            s.start = a;
            s.end = b;
            count2++;
        }

        // insert the segment in the array of segments
        segments.push_back(s);
    }
}


/* ************************************************** */
//fills global variable "segments" with n segments 
void initialize_segments() {

  switch (init_case)  {
      
    case 0: 
      initialize_segments_random(); 
      break;
      
    case 1: 
      initialize_segments_horizontal(); 
      break; 
      
    default: 
      initialize_segments_random(); 
    }

  init_case = (init_case+1) % NB_TEST_CASES;
  return; 
}




/* ************************************************** */
//fills global variable "segments" with n horizontal segments 
void initialize_segments_horizontal() {

  int i; 
  point2D a,b;
  segment2D s; 

  //clear the vector of segments 
  segments.clear(); 

  //a long horizontal segment 
  a.x = 1; 
  a.y = WINDOWSIZE/2; 
  b.x = WINDOWSIZE - 10; 
  b.y = a.y; 

  s.start = a; s.end = b; 
  segments.push_back(s);  

  //n-1 vertical segments 
  for (i=0; i<n-1; i++) {
    
    a.x = i*WINDOWSIZE/n; 
    a.y = WINDOWSIZE/2 - random() % ((int)(.4*WINDOWSIZE)); 
    b.x = a.x; 
    b.y = WINDOWSIZE/2 + random() % ((int)(.4*WINDOWSIZE)); 
    s.start = a; s.end = b; 
   segments.push_back(s); 
  }

}


/* ****************************** */
//fills global variable "segments" with n random segments, half horizontal and half vertical 
void initialize_segments_random() {
  
  //clear the vector 
  segments.clear(); 

  int i; 
  point2D a, b; 
  segment2D s; 
  for (i=0; i<n; i++) {
    if (random()%2 == 0) {
      //horizontal segment
      a.x = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE)); 
      a.y =  (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE));
      b.y = a.y; 
      b.x = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE)); 

      if (a.x < b.x) {
	s.start = a; s.end = b; 
      } else {
	s.start = b; s.end = a; 
      } 
 
    } else {
      //vertical segment 
      a.x = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE)); 
      b.x = a.x; 
      a.y = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE)); 
      b.y = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE)); 

      if (a.y < b.y) {
	s.start = a; s.end = b; 
      } else {
	s.start = b; s.end = a; 
      }
    }

    //insert the segment in the array of segments 
    segments.push_back (s); 
  } //for i
}




/* ************************************************** */
void print_segments() {

  for (int i=0; i<segments.size(); i++) {
    printf("segment %d: [(%d,%d), (%d,%d)]\n",
	   i, segments[i].start.x, segments[i].start.y, segments[i].end.x, segments[i].end.y);

  }
}
/*

Function to convert all segments into events and places them in an event vector

*/

void sweeps()
{
	for(int i = 0; i < segments.size(); ++i)
	{
		//if vertical segment
		if (segments[i].start.x == segments[i].end.x)
		{	
			sweepEvent toAdd; //create a new sweep event
			toAdd.type = 3; //set the type 
			toAdd.x = segments[i].start.x; //add x value
			toAdd.seg = segments[i]; //Adds segment to event
			events.push_back(toAdd);
		}
		//horizontal segment
		else
		{       
			sweepEvent toAddstart; 
			toAddstart.type = 1;
			toAddstart.x = segments[i].start.x;
			toAddstart.seg = segments[i];
			events.push_back(toAddstart);
			
			sweepEvent toAddend;	
			toAddend.type = 2;
			toAddend.x = segments[i].end.x;
			toAddend.seg = segments[i];
			events.push_back(toAddend);
		}	
	}
	
	sort(events.begin(), events.end(), compareByX);
	for(int i = 0; i < events.size(); ++i)
	{

	}
} 
/* 
Function to calculate the intersects in time with the sweep line

Parameters: the x value of the sweep line

Returns: returns the index for the next event

*/

int find_intersects(int i)
{
  if (sweep_line_x == events[i].x) {  //if the sweepline has hit an event
	if (events[i].type == 1) {	
		bst.insert(pair<int, segment2D>(events[i].seg.start.y, events[i].seg));
		draw_active_structure();
	}
	else if (events[i].type == 2) {
		bst.erase(events[i].seg.start.y);
	}
	else 
	{
		int yupper = events[i].seg.end.y; //set the upper y value range to the end of the vertical segment
		int ylower = events[i].seg.start.y; //set the lower y value of the range to the start of the vertical segment
		for(int j = ylower; j <= yupper; ++j)//anything is bst in range of y will will intersect with this vertical line
		{
			if (bst.find(j) != bst.end())//check if y key is in bst
			{
				point2D intersection; //create a new point2D
				intersection.x = events[i].seg.start.x; //find the x value
				intersection.y = j; //iterating by y
				intpoints.push_back(intersection);
			}
		}
	}
	if(events[i].x == events[i + 1].x)
	{
  
		sweep_line_x = sweep_line_x - 1;  //Makes it so sweep line doesn't move forward, helps degenerate case when there is two events with the same x value.
						  //By moving the sweep line back one, it forces the function to look at every instance.
	}
	return i + 1;

  }
	return i;
}
/* ****************************** */
int main(int argc, char** argv) {

  //read number of points from user
  if (argc!=2) {
    printf("usage: viewPoints <nbPoints>\n");
    exit(1); 
  }
  n = atoi(argv[1]); 
  printf("you entered n=%d\n", n);
  assert(n >0); 

  //the default is to initialize the segments randomly 
  initialize_segments_random();
  print_segments();

 
  sweeps();

  /* initialize GLUT  */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WINDOWSIZE, WINDOWSIZE);
  glutInitWindowPosition(100,100);
  glutCreateWindow(argv[0]);

  /* register callback functions */
  glutDisplayFunc(display); 
  glutKeyboardFunc(keypress);

  /* init GL */
  /* set background color black*/
  glClearColor(0, 0, 0, 0);   

  
  /* give control to event handler */
  glutMainLoop();
  return 0;
}




/* draw the segments stored in global variable segments
   NOTE: We draw in the local coordinate system (0,0) to (WINSIZE,WINSIZE)
*/
void draw_segments(){

  //set color 
  glColor3fv(yellow);   
  
  int i;
  for (i=0; i<segments.size(); i++) {
    glBegin(GL_LINES);
    glVertex2f(segments[i].start.x, segments[i].start.y); 
    glVertex2f(segments[i].end.x, segments[i].end.y);
    glEnd();
  }
}



/* 
   draw the sweep line
   NOTE: We draw in the local coordinate system (0,0) to (WINSIZE,WINSIZE)
*/
void draw_sweep_line() {
  
  //sweep line color 
  glColor3fv(red); 
  
  //the current position of sweep line is sweep_line_x; assume it's a
  //segment from y=0 to y=windowsize;
  glBegin(GL_LINES); 
  glVertex2f(sweep_line_x, 0); 
  glVertex2f(sweep_line_x, WINDOWSIZE); 
  glEnd();
}


/* draw a segment with current color
   NOTE: We draw in the local coordinate system (0,0) to (WINSIZE,WINSIZE)
*/
void draw_segment(segment2D s) {
  glBegin(GL_LINES);
  glVertex2f(s.start.x, s.start.y); 
  glVertex2f(s.end.x, s.end.y);
  glEnd();
}


/* draw all the elements in the active structure 
   NOTE: we draw in the local coordinate system (0,0) to (WINSIZE,WINSIZE)
*/
void draw_active_structure() {
   glColor3fv(magenta);
   for (multimap<int, segment2D>::iterator it = bst.begin(); it != bst.end(); ++it)
   {
	segment2D seg = (*it).second;
	draw_segment(seg); 
   }

   glColor3fv(red);
}



/* draw all the elements in intpoints 
   NOTE: we draw in the local coordinate system  (0,0) to (WINSIZE,WINSIZE)
*/
void draw_intersection_points() {
	glColor3fv(cyan);
	int R = 3;
	for (int i = 0; i < intpoints.size(); i++) {
		glBegin(GL_POLYGON);
		int x = intpoints[i].x;
		int y = intpoints[i].y;
		glVertex2f(x - R, y - R); //draw small square around where intersect point is
		glVertex2f(x + R, y - R);
		glVertex2f(x + R, y + R);
		glVertex2f(x - R, y + R);
		glEnd();
	}
	glColor3fv(red);		
}




/* ****************************** */
void display(void) {

  //clear everything, start from scratch 
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity(); 


  /* The default GL window is [-1,1]x[-1,1] with the origin in the center. 
     
     The points are in the range (0,0) to (WINSIZE,WINSIZE). This is our local coordinate system. 

     We first transform our local coordinate system to [-1,1] x [-1,1]
  */
  glScalef(2.0/WINDOWSIZE, 2.0/WINDOWSIZE, 1.0);  
  glTranslatef(-WINDOWSIZE/2, -WINDOWSIZE/2, 0); 
  
  glutIdleFunc(timerfunc);  //<--------note we got an idle function, we'll use it to animate 
	
  //draw my scene in the local coordinate system (0,0) to (WINSIZE,WINSIZE)
  draw_segments();
  draw_sweep_line(); 
  draw_active_structure();
  draw_intersection_points();
  /* execute the drawing commands */
  glFlush();
}



/* ****************************** */
void keypress(unsigned char key, int x, int y) {
  switch(key) {
  case 'q':
    exit(0);
    break;

  case 'i':
    sweep_line_x = 0;
    k = 0;
    events.clear();
    bst.clear();
    intpoints.clear();
    segments.clear(); 
    initialize_segments(); 
    sweeps();
    glutPostRedisplay();
    break; 
  
  case '1':
	sweep_line_x = 0;
    	k = 0;
    	events.clear();
    	bst.clear();
    	intpoints.clear();
    	segments.clear();
	initialize_segments_worst_case();
	sweeps();
	glutPostRedisplay();
	break; 
  case '2':
	sweep_line_x = 0;
        k = 0;
        events.clear();
        bst.clear();
        intpoints.clear();
        init_segs_hash();
	sweeps();
        glutPostRedisplay();
        break;
   }
}


void timerfunc() {
   
  k = find_intersects(k);
  sweep_line_x++; 
  
  glutPostRedisplay(); 
}



/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
     
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   gluOrtho2D(0.0, (GLdouble) width, 0.0, (GLdouble) height); 
}




