#include "geom.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
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

int currPoly = 0;
int n;
//the current polygons
vector <vector <point2D> > polygons;
vector <vector <lineSegment2D> > polysegs;
vector <point2D> polygon;
vector <lineSegment2D> segs;
vector <vector <graphNode> > polyNodes;
priority_queue<graphNode> pq;
graph web;
graphNode startNode;
graphNode endNode;
vector <vector <lineSegment2D> > pointsToSeg(vector <vector<point2D> > polygons);
//the start and end point
point2D start = {-10, -10}; //initialize off screen
point2D finish = {-10, -10};
//coordinates of last mouse click
//initialized to a point outside the window


void dijkstra();
//function declarations
void display(void);
void keypress(unsigned char key, int x, int y);
void timerfunc(); 
void mousepress(int button, int state, int x, int y);
void initialize_polygon();
void print_polygon(vector<point2D> poly);


const int WINDOWSIZE = 750; 
double mouse_x=-10, mouse_y=-10; 
int poly_init_mode = 0; 

void drawPolyNodes()
{
	for(int i = 0; i < polyNodes.size(); ++i)
	{
		for(int j = 0; j < polyNodes[i].size(); ++j)
		{
			glColor3fv(cyan);
			glLineWidth(1);
			for(int r = 0; r < polyNodes[i][j].iInd.size(); ++r)
			{
				glBegin(GL_LINES);
				glVertex2f(polyNodes[i][j].point.x, polyNodes[i][j].point.y);
				int badX = polyNodes[polyNodes[i][j].iInd[r]][polyNodes[i][j].jInd[r]].point.x;
				int badY = polyNodes[polyNodes[i][j].iInd[r]][polyNodes[i][j].jInd[r]].point.y;
				glVertex2f(badX, badY);
				glEnd();
			}
		}
	}
	return;
}


void initialize_polygon()
{
	point2D helper1;
	polygon.clear();
helper1.x = 283;
helper1.y = 110;
polygon.push_back(helper1);
helper1.x = 320;
helper1.y = 127;
polygon.push_back(helper1);
helper1.x = 272;
helper1.y = 143;
polygon.push_back(helper1);
helper1.x = 201;
helper1.y = 187;
polygon.push_back(helper1);
helper1.x = 138;
helper1.y = 247;
polygon.push_back(helper1);
helper1.x = 109;
helper1.y = 319;
polygon.push_back(helper1);
helper1.x = 90;
helper1.y = 414;
polygon.push_back(helper1);
helper1.x = 98;
helper1.y = 510;
polygon.push_back(helper1);
helper1.x = 111;
helper1.y = 588;
polygon.push_back(helper1);
helper1.x = 129;
helper1.y = 619;
polygon.push_back(helper1);
helper1.x = 170;
helper1.y = 640;
polygon.push_back(helper1);
helper1.x = 248;
helper1.y = 653;
polygon.push_back(helper1);
helper1.x = 349;
helper1.y = 659;
polygon.push_back(helper1);
helper1.x = 436;
helper1.y = 658;
polygon.push_back(helper1);
helper1.x = 524;
helper1.y = 634;
polygon.push_back(helper1);
helper1.x = 562;
helper1.y = 599;
polygon.push_back(helper1);
helper1.x = 587;
helper1.y = 530;
polygon.push_back(helper1);
helper1.x = 626;
helper1.y = 422;
polygon.push_back(helper1);
helper1.x = 621;
helper1.y = 361;
polygon.push_back(helper1);
helper1.x = 596;
helper1.y = 315;
polygon.push_back(helper1);
helper1.x = 569;
helper1.y = 264;
polygon.push_back(helper1);
helper1.x = 543;
helper1.y = 241;
polygon.push_back(helper1);
helper1.x = 472;
helper1.y = 222;
polygon.push_back(helper1);
helper1.x = 428;
helper1.y = 223;
polygon.push_back(helper1);
helper1.x = 398;
helper1.y = 221;
polygon.push_back(helper1);
helper1.x = 343;
helper1.y = 220;
polygon.push_back(helper1);
helper1.x = 288;
helper1.y = 230;
polygon.push_back(helper1);
helper1.x = 220;
helper1.y = 278;
polygon.push_back(helper1);
helper1.x = 202;
helper1.y = 325;
polygon.push_back(helper1);
helper1.x = 185;
helper1.y = 385;
polygon.push_back(helper1);
helper1.x = 176;
helper1.y = 444;
polygon.push_back(helper1);
helper1.x = 170;
helper1.y = 505;
polygon.push_back(helper1);
helper1.x = 194;
helper1.y = 549;
polygon.push_back(helper1);
helper1.x = 218;
helper1.y = 563;
polygon.push_back(helper1);
helper1.x = 275;
helper1.y = 586;
polygon.push_back(helper1);
helper1.x = 343;
helper1.y = 585;
polygon.push_back(helper1);
helper1.x = 382;
helper1.y = 570;
polygon.push_back(helper1);
helper1.x = 441;
helper1.y = 530;
polygon.push_back(helper1);
helper1.x = 467;
helper1.y = 486;
polygon.push_back(helper1);
helper1.x = 476;
helper1.y = 444;
polygon.push_back(helper1);
helper1.x = 474;
helper1.y = 389;
polygon.push_back(helper1);
helper1.x = 447;
helper1.y = 353;
polygon.push_back(helper1);
helper1.x = 386;
helper1.y = 340;
polygon.push_back(helper1);
helper1.x = 305;
helper1.y = 364;
polygon.push_back(helper1);
helper1.x = 270;
helper1.y = 403;
polygon.push_back(helper1);
helper1.x = 250;
helper1.y = 461;
polygon.push_back(helper1);
helper1.x = 273;
helper1.y = 514;
polygon.push_back(helper1);
helper1.x = 307;
helper1.y = 530;
polygon.push_back(helper1);
helper1.x = 335;
helper1.y = 516;
polygon.push_back(helper1);
helper1.x = 346;
helper1.y = 484;
polygon.push_back(helper1);
helper1.x = 353;
helper1.y = 462;
polygon.push_back(helper1);
helper1.x = 343;
helper1.y = 444;
polygon.push_back(helper1);
helper1.x = 309;
helper1.y = 437;
polygon.push_back(helper1);
helper1.x = 293;
helper1.y = 454;
polygon.push_back(helper1);
helper1.x = 300;
helper1.y = 478;
polygon.push_back(helper1);
helper1.x = 299;
helper1.y = 484;
polygon.push_back(helper1);
helper1.x = 282;
helper1.y = 482;
polygon.push_back(helper1);
helper1.x = 277;
helper1.y = 471;
polygon.push_back(helper1);
helper1.x = 279;
helper1.y = 452;
polygon.push_back(helper1);
helper1.x = 290;
helper1.y = 433;
polygon.push_back(helper1);
helper1.x = 311;
helper1.y = 424;
polygon.push_back(helper1);
helper1.x = 350;
helper1.y = 421;
polygon.push_back(helper1);
helper1.x = 376;
helper1.y = 435;
polygon.push_back(helper1);
helper1.x = 380;
helper1.y = 474;
polygon.push_back(helper1);
helper1.x = 367;
helper1.y = 514;
polygon.push_back(helper1);
helper1.x = 342;
helper1.y = 538;
polygon.push_back(helper1);
helper1.x = 307;
helper1.y = 549;
polygon.push_back(helper1);
helper1.x = 276;
helper1.y = 543;
polygon.push_back(helper1);
helper1.x = 239;
helper1.y = 523;
polygon.push_back(helper1);
helper1.x = 215;
helper1.y = 488;
polygon.push_back(helper1);
helper1.x = 218;
helper1.y = 464;
polygon.push_back(helper1);
helper1.x = 236;
helper1.y = 425;
polygon.push_back(helper1);
helper1.x = 305;
helper1.y = 343;
polygon.push_back(helper1);
helper1.x = 365;
helper1.y = 315;
polygon.push_back(helper1);
helper1.x = 416;
helper1.y = 311;
polygon.push_back(helper1);
helper1.x = 490;
helper1.y = 336;
polygon.push_back(helper1);
helper1.x = 498;
helper1.y = 391;
polygon.push_back(helper1);
helper1.x = 501;
helper1.y = 434;
polygon.push_back(helper1);
helper1.x = 496;
helper1.y = 485;
polygon.push_back(helper1);
helper1.x = 485;
helper1.y = 528;
polygon.push_back(helper1);
helper1.x = 475;
helper1.y = 544;
polygon.push_back(helper1);
helper1.x = 415;
helper1.y = 600;
polygon.push_back(helper1);
helper1.x = 376;
helper1.y = 606;
polygon.push_back(helper1);
helper1.x = 313;
helper1.y = 613;
polygon.push_back(helper1);
helper1.x = 271;
helper1.y = 611;
polygon.push_back(helper1);
helper1.x = 222;
helper1.y = 601;
polygon.push_back(helper1);
helper1.x = 176;
helper1.y = 566;
polygon.push_back(helper1);
helper1.x = 163;
helper1.y = 545;
polygon.push_back(helper1);
helper1.x = 148;
helper1.y = 521;
polygon.push_back(helper1);
helper1.x = 138;
helper1.y = 493;
polygon.push_back(helper1);
helper1.x = 132;
helper1.y = 445;
polygon.push_back(helper1);
helper1.x = 134;
helper1.y = 390;
polygon.push_back(helper1);
helper1.x = 144;
helper1.y = 347;
polygon.push_back(helper1);
helper1.x = 175;
helper1.y = 267;
polygon.push_back(helper1);
helper1.x = 191;
helper1.y = 249;
polygon.push_back(helper1);
helper1.x = 214;
helper1.y = 230;
polygon.push_back(helper1);
helper1.x = 240;
helper1.y = 203;
polygon.push_back(helper1);
helper1.x = 266;
helper1.y = 186;
polygon.push_back(helper1);
helper1.x = 297;
helper1.y = 172;
polygon.push_back(helper1);
helper1.x = 323;
helper1.y = 162;
polygon.push_back(helper1);
helper1.x = 362;
helper1.y = 143;
polygon.push_back(helper1);
helper1.x = 380;
helper1.y = 97;
polygon.push_back(helper1);
helper1.x = 374;
helper1.y = 77;
polygon.push_back(helper1);
helper1.x = 362;
helper1.y = 56;
polygon.push_back(helper1);
helper1.x = 337;
helper1.y = 48;
polygon.push_back(helper1);
helper1.x = 293;
helper1.y = 54;
polygon.push_back(helper1);
helper1.x = 245;
helper1.y = 74;
polygon.push_back(helper1);
helper1.x = 201;
helper1.y = 105;
polygon.push_back(helper1);
helper1.x = 173;
helper1.y = 122;
polygon.push_back(helper1);
helper1.x = 149;
helper1.y = 141;
polygon.push_back(helper1);
helper1.x = 98;
helper1.y = 178;
polygon.push_back(helper1);
helper1.x = 85;
helper1.y = 203;
polygon.push_back(helper1);
helper1.x = 72;
helper1.y = 236;
polygon.push_back(helper1);
helper1.x = 65;
helper1.y = 266;
polygon.push_back(helper1);
helper1.x = 55;
helper1.y = 311;
polygon.push_back(helper1);
helper1.x = 39;
helper1.y = 390;
polygon.push_back(helper1);
helper1.x = 36;
helper1.y = 481;
polygon.push_back(helper1);
helper1.x = 32;
helper1.y = 555;
polygon.push_back(helper1);
helper1.x = 37;
helper1.y = 642;
polygon.push_back(helper1);
helper1.x = 64;
helper1.y = 690;
polygon.push_back(helper1);
helper1.x = 140;
helper1.y = 703;
polygon.push_back(helper1);
helper1.x = 249;
helper1.y = 706;
polygon.push_back(helper1);
helper1.x = 423;
helper1.y = 712;
polygon.push_back(helper1);
helper1.x = 503;
helper1.y = 707;
polygon.push_back(helper1);
helper1.x = 572;
helper1.y = 690;
polygon.push_back(helper1);
helper1.x = 596;
helper1.y = 662;
polygon.push_back(helper1);
helper1.x = 612;
helper1.y = 641;
polygon.push_back(helper1);
helper1.x = 622;
helper1.y = 620;
polygon.push_back(helper1);
helper1.x = 675;
helper1.y = 483;
polygon.push_back(helper1);
helper1.x = 684;
helper1.y = 420;
polygon.push_back(helper1);
helper1.x = 693;
helper1.y = 333;
polygon.push_back(helper1);
helper1.x = 690;
helper1.y = 249;
polygon.push_back(helper1);
helper1.x = 678;
helper1.y = 185;
polygon.push_back(helper1);
helper1.x = 653;
helper1.y = 141;
polygon.push_back(helper1);
helper1.x = 620;
helper1.y = 116;
polygon.push_back(helper1);
helper1.x = 582;
helper1.y = 95;
polygon.push_back(helper1);
helper1.x = 513;
helper1.y = 78;
polygon.push_back(helper1);
helper1.x = 456;
helper1.y = 109;
polygon.push_back(helper1);
helper1.x = 488;
helper1.y = 138;
polygon.push_back(helper1);
helper1.x = 538;
helper1.y = 157;
polygon.push_back(helper1);
helper1.x = 566;
helper1.y = 187;
polygon.push_back(helper1);
helper1.x = 624;
helper1.y = 277;
polygon.push_back(helper1);
helper1.x = 643;
helper1.y = 309;
polygon.push_back(helper1);
helper1.x = 665;
helper1.y = 400;
polygon.push_back(helper1);
helper1.x = 642;
helper1.y = 490;
polygon.push_back(helper1);
helper1.x = 609;
helper1.y = 567;
polygon.push_back(helper1);
helper1.x = 550;
helper1.y = 658;
polygon.push_back(helper1);
helper1.x = 452;
helper1.y = 679;
polygon.push_back(helper1);
helper1.x = 323;
helper1.y = 687;
polygon.push_back(helper1);
helper1.x = 134;
helper1.y = 673;
polygon.push_back(helper1);
helper1.x = 84;
helper1.y = 635;
polygon.push_back(helper1);
helper1.x = 72;
helper1.y = 599;
polygon.push_back(helper1);
helper1.x = 64;
helper1.y = 567;
polygon.push_back(helper1);
helper1.x = 62;
helper1.y = 541;
polygon.push_back(helper1);
helper1.x = 61;
helper1.y = 485;
polygon.push_back(helper1);
helper1.x = 61;
helper1.y = 453;
polygon.push_back(helper1);
helper1.x = 64;
helper1.y = 393;
polygon.push_back(helper1);
helper1.x = 62;
helper1.y = 359;
polygon.push_back(helper1);
helper1.x = 69;
helper1.y = 331;
polygon.push_back(helper1);
helper1.x = 80;
helper1.y = 297;
polygon.push_back(helper1);
helper1.x = 98;
helper1.y = 257;
polygon.push_back(helper1);
helper1.x = 107;
helper1.y = 226;
polygon.push_back(helper1);
helper1.x = 155;
helper1.y = 180;
polygon.push_back(helper1);
helper1.x = 219;
helper1.y = 146;
polygon.push_back(helper1);
polygons.push_back(polygon);
}


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


void draw_start(double x, double y){
  glColor3fv(green);   
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


void draw_end(double x, double y){
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

//function to convert a polygon of points to a polygon of line segments
vector < vector <lineSegment2D> > pointsToSeg(vector < vector < point2D > > polygons)
{
        vector < vector < lineSegment2D > > toReturn;
        for (int i = 0; i < polygons.size(); ++i)
        {
                vector < lineSegment2D > polySeg;
                lineSegment2D toAdd;
                toAdd.p1 = polygons[i][polygons[i].size()-1];
                toAdd.p2 = polygons[i][0];
                polySeg.push_back(toAdd);
                for( int h = 1; h < polygons[i].size(); ++h)
                {
                        toAdd.p1 = polygons[i][h - 1];
                        toAdd.p2 = polygons[i][h];
                        polySeg.push_back(toAdd);
                }
                toReturn.push_back(polySeg);
        }
        return toReturn;
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
    if (poly_init_mode == 1) {
      cout << "In Poly init mode" << endl;
      point2D p = {mouse_x, mouse_y}; 
      polygons[currPoly].push_back(p);
    }
    if (poly_init_mode == 2) 
    {
	start.x = mouse_x;
	start.y = mouse_y; 
	startNode.point = start;
	startNode.currDist = 0;
	poly_init_mode = 3;
    }
    if (poly_init_mode == 3)
    {
	finish.x = mouse_x;
	finish.y = mouse_y;
	endNode.point = finish;
	endNode.currDist = INT_MAX;
    }  
    glutPostRedisplay();
  }

}


int main(int argc, char** argv){
  initialize_polygon();
  /* initialize GLUT  */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WINDOWSIZE, WINDOWSIZE);
  glutInitWindowPosition(100,100);
  glutCreateWindow(argv[0]);
  /* register callback functions */
  glutDisplayFunc(display); 

  glutMouseFunc(mousepress); 
  glutKeyboardFunc(keypress);

  /* init GL */
  /* set background color black*/
  glClearColor(0, 0, 0, 0);   
  /* here we can enable depth testing and double buffering and so
     on */

  
  /* give control to event handler */
  glutMainLoop();
  return 0;

}

void draw_segments(vector <lineSegment2D> segs)
{
	glColor3fv(red);
	glLineWidth(2.5);
	for (int i = 0;i < segs.size(); i++)
	{
		glBegin(GL_LINES);
		glVertex2f(segs[i].p1.x, segs[i].p1.y);
		glVertex2f(segs[i].p2.x, segs[i].p2.y);
		glEnd();
	}
}

void draw_polygon(vector<point2D> poly){
  
  if (poly.size() == 0) return; 

  //set color 
  glColor3fv(yellow);   
  glLineWidth(2);
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
    cout << "Myahh" << endl;
  if (polygons.size() > 0)
  {
	for (int i = 0; i < polygons.size(); i++)
	{
		if (polygons[i].size() > 0)
		{
  			draw_polygon(polygons[i]); 
		}
	}
  }
  //draw a circle where the mouse was last clicked. Note that this
  //point is stored as a global variable and is modified by the mouse handler function 
  if (poly_init_mode != 2)
  {
	draw_circle(mouse_x, mouse_y); 
  } 
  drawPolyNodes();
  draw_segments(segs);
  draw_start(start.x, start.y);
  draw_end(finish.x, finish.y);
  /* execute the drawing commands */
  glFlush();
}

//fucntion to convert a vector of polygons expressed as point2D's to a vector of 
//polygons expressed as graphNode's
vector <vector <graphNode> > polyToNodes(vector <vector <point2D> > polygon)
{
	vector <vector <graphNode > > toReturn;
	graphNode nodeAdd;
	vector <graphNode> poly;
	for( int i = 0; i < polygons.size(); ++i)
        {
		poly.clear();
                for(int j = 0; j < polygons[i].size(); ++j)
                {
			nodeAdd.poly = i;
			nodeAdd.completed = 0;
			nodeAdd.myI = i;
			nodeAdd.myJ = j;
			nodeAdd.currDist = INT_MAX;
                        nodeAdd.point = polygons[i][j];
			poly.push_back(nodeAdd);
		}
		n = i;
		toReturn.push_back(poly);
	}
	poly.clear();
        poly.push_back(endNode);
        toReturn.push_back(poly);
	poly.clear();
	poly.push_back(startNode);
	toReturn.push_back(poly);
	return toReturn;
}

//creates a graph of the vectors to search for shortest path on
void createGraph(vector<vector<lineSegment2D> > polysegs, int iIndex, int jIndex)
{
        cout << "Point Using" << polyNodes[iIndex][jIndex].point.x << ", " << polyNodes[iIndex][jIndex].point.y << endl;
        if (polyNodes[iIndex][jIndex].completed)
        {
                cout << "HERE I AM" << endl;
                return;
        }
        polyNodes[iIndex][jIndex].completed = 1;
        for( int i = 0; i < polyNodes.size(); ++i)
        {
                for(int j = 0; j < polyNodes[i].size(); ++j)
                {
                        int isvis = 1;
                        for (int r = 0; r < polysegs.size(); r++)
                        {
                                if (polyNodes[iIndex][jIndex].poly == i)
                                {
                                        if (checkSegInsidePolygon(polysegs[r], polyNodes[i][j].point, polyNodes[iIndex][jIndex].point))
                                        {
                                                isvis = 0;
                                        }
                                }
                                for (int t = 0; t < polysegs[r].size(); t++)
                                {
                                        if (!isVisible(polysegs[r][t].p1, polysegs[r][t].p2, polyNodes[i][j].point, polyNodes[iIndex][jIndex].point))
                                        {
                                                isvis = 0;
                                        }
                                }
                        }
                        if (isvis)
                        {
                                if (!checkTwoPoints(polyNodes[iIndex][jIndex].point, polyNodes[i][j].point))
                                {
                                        polyNodes[iIndex][jIndex].iInd.push_back(i);
                                        polyNodes[iIndex][jIndex].jInd.push_back(j);
                                }
                        }
                }
        }
        for (int i = 0; i < polyNodes[iIndex][jIndex].iInd.size(); i++)
        {
                if (!checkTwoPoints(polyNodes[polyNodes[iIndex][jIndex].iInd[i]][polyNodes[iIndex][jIndex].jInd[i]].point, polyNodes[iIndex][jIndex].point))
                {
                        createGraph(polysegs, polyNodes[iIndex][jIndex].iInd[i], polyNodes[iIndex][jIndex].jInd[i]);
                }
        }
        return;
}


//function to calculate the shortest path from the start to end node
void shortPath(int i, int j)
{
	for (int r = 0; r < polyNodes[i][j].iInd.size(); r++)
	{
	
		int distance = dist(polyNodes[i][j].point, polyNodes[polyNodes[i][j].iInd[r]][polyNodes[i][j].jInd[r]].point);
		if(distance + polyNodes[i][j].currDist < polyNodes[polyNodes[i][j].iInd[r]][polyNodes[i][j].jInd[r]].currDist)
		{
			//instead of using pointers we kept track of the adjacency list with a vector of vertices that have neighbors indicated by
			//vectors of indices
			polyNodes[polyNodes[i][j].iInd[r]][polyNodes[i][j].jInd[r]].currDist = polyNodes[i][j].currDist + distance;
			polyNodes[polyNodes[i][j].iInd[r]][polyNodes[i][j].jInd[r]].iPrev = i;
			polyNodes[polyNodes[i][j].iInd[r]][polyNodes[i][j].jInd[r]].jPrev = j;
			shortPath(polyNodes[i][j].iInd[r], polyNodes[i][j].jInd[r]);		
			//pq.push(polyNodes[polyNodes[i][j].iInd[r]][polyNodes[i][j].jInd[r]]);
		}
	}	
	/*
	while (!pq.empty())
	{
		cout  << pq.size() << endl;
		graphNode next = pq.top();
		pq.pop();
		shortPath(next.myI, next.myJ);
	}
	*/

}

//retraces the shortest path and updates the seg vector to be the shortest path
void dijkstra()
{
	segs.clear();
	//pq = priority_queue <graphNode>();
        shortPath(polyNodes.size() - 1, 0);
	cout << "I Made it " << endl;
        int aI = polyNodes.size() - 2; //start at end point
        int aJ = 0; 
        int bI = polyNodes[aI][aJ].iPrev; //next point on shortest path to the endpoint
        int bJ = polyNodes[aI][aJ].jPrev;
	lineSegment2D segment; 
	cout  << "Right Before" << endl;
        while (!checkTwoPoints(polyNodes[bI][bJ].point, startNode.point))
        {	
                segment.p1 = polyNodes[aI][aJ].point;
                segment.p2 = polyNodes[bI][bJ].point;
		segs.push_back(segment);
                aI = bI;
                aJ = bJ;
                bI = polyNodes[aI][aJ].iPrev;
                bJ = polyNodes[aI][aJ].jPrev;
        }
	segment.p1 = startNode.point;
        segment.p2 = polyNodes[aI][aJ].point;
        segs.push_back(segment);
        return;

}

//function to print out the coordinates of a polygon 
//a tool to save a premade polygon
//only used for creating the default polygon
/*
void prints(vector <vector <lineSegment2D> > segs)
{
	for (int i = 0; i < segs.size(); i++)
	{
		cout << "polygon.clear()" << ";" << endl;
		for (int j = 0; j < segs[i].size(); j++)
		{
			cout << "helper1.x = " << segs[i][j].p1.x << ";" <<endl;
			cout << "helper1.y = " << segs[i][j].p1.y << ";" <<endl;
			cout << "polygon.push_back(helper1)" << ";" <<endl;
		}
		cout << "polygons.push_back(polygon)" << ";" <<endl;
	}	
}
*/

//function to keep track of keypresses using a switch for each case
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
    //start re-initializeing polygon 
    polyNodes.clear();
    polygons.clear();
    polygon.clear();
    segs.clear();
    currPoly = 0;
    n = 0;
    polygons.push_back(polygon);
    poly_init_mode = 1; 
    glutPostRedisplay();
    break;
  case 's':
    //place guard into polygon
    poly_init_mode = 2;
    glutPostRedisplay();
    break;
  case 'd':
    segs.clear();
    if (polyNodes.size() > 0)
    {
       dijkstra();
       draw_segments(segs);
       glutPostRedisplay();

    }
    break;
  case 'x': 
    poly_init_mode=0; 
    glutPostRedisplay();
    break; 
  case 'v':
    segs.clear();
    if (polygons.size() > 0)
    {
       polysegs = pointsToSeg(polygons);
       cout << "Right Before" << endl;
       polyNodes = polyToNodes(polygons);
       cout << "HERE" << endl;
       createGraph(polysegs, n + 2, 0);
	
    }
    glutPostRedisplay();
    break;
  case 'c':
    polygons.push_back(polygon);
    polygon.clear();
    poly_init_mode = 1;
    currPoly += 1;
    glutPostRedisplay();
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










