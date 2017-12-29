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
const int WINDOWSIZE = 500;

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


vector<MondrianSeg> squares; //vector of squres to be drawn
vector<Point2D> points; //vector to store points to be make into kdtree
int n; //Amount of Points

//function declarations
void draw_segments();
void display(void);

//vector to compute the lines to be drawn in the Mondtrian style representation
vector<MondrianSeg> segs;

//initialize random points to text the kd tree on
void initializePointsRandom(int n){
	for(int i = 0; i < n; ++i){
		Point2D newPoint;
		newPoint.x = -1 + ((2) * ( (double)rand() / (double)RAND_MAX ));
		newPoint.y = -1 + ((2) * ( (double)rand() / (double)RAND_MAX ));
		points.push_back(newPoint);

	}
}
void initiallize_points_circle(){
	double radius = (WINDOWSIZE / 5);
	Point2D p;
	for (int i = 0; i < n; i++){
		p.x = -1 + ((radius * cos (2*M_PI / n * i) + WINDOWSIZE / 2)*2/500);
		p.y = -1 + ((radius * sin (2*M_PI / n * i) + WINDOWSIZE / 2)*2/500);
		points.push_back(p);
	}
}


//initializes the points in a x shape
void initializePointsX(int n) {
	for(int i = 0; i < n; ++i)
	{
		Point2D newPoint;
		newPoint.x = -1 + (2 * (double)rand() / (double)RAND_MAX);
		newPoint.y = newPoint.x;
		points.push_back(newPoint);
	}

	for(int i = 0; i < n; ++i)
	{
		Point2D newPoint;
		newPoint.x = -1 + (2 * (double)rand() / (double)RAND_MAX);
		newPoint.y = -1 * newPoint.x;
		points.push_back(newPoint);
	}
	return;
}

//Initializes pointsi n a grid. Best at an n of 200. Many numbers don't work well
//with the test case function, so best to try at 200.
void initialize_points_grid(int currN) {
  
  // clear the vector
   points.clear();

   double window  = (double) WINDOWSIZE;
   double padding = window / 8;
   double width   = window - 2 * padding;
   int    side    = sqrt(currN);
   double spacing = width / (double) side;
   Point2D newpoint;
   for (int row = 0; row < side; row++) {
          for (int col = 0; col < side; col++) {
                 // col * spacing + padding
                 newpoint.x = -1 + ((fma(col, spacing, padding))/500*2);
                 // row * spacing + padding
                 newpoint.y = -1 + ((fma(row, spacing, padding))/500*2);
                                                                 
                 points.push_back(newpoint);
           }
   }
}
// Bo Bleckel & Henry Daniels Koch
// Initialize the points in a downward sloping diagonal
// Works best with n <= 100
//Altered Considerably by duncan and dustin to work on grid.
void initialize_points_diag() {
    points.clear();

    for(int i = 0; i < n; ++i)
        {
                Point2D newPoint;
                newPoint.x = -1 + (2 * (double)rand() / (double)RAND_MAX);
                newPoint.y = newPoint.x;
                points.push_back(newPoint);
        }
}


//funciton to print points for debugging purposes 
void printPoints(vector<Point2D> points){
	for(unsigned int i = 0; i < points.size(); i++)
	{
		cout << points[i].x << " " <<  points[i].y << endl;
	}
	return;	
}

//function to draw the colored squares for the Mondrian visual 
void draw_segments() {
  //set polygons style: filled or contour 
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glLineWidth(1);
for (unsigned int i = 0; i < squares.size(); i++)
  {
	//vary color of squares
	if (i % 4 == 0) {
		glColor3fv(blue);
	}
	if (i % 4 == 1) {
                glColor3fv(yellow);
        }
	if (i % 4 == 2) {
                glColor3fv(red);
        }
	if (i % 4 == 3) {
                glColor3fv(white);
        }
	
	glBegin(GL_POLYGON);
  	glVertex2f(squares[i].a.x, squares[i].a.y);
  	glVertex2f(squares[i].a.x, squares[i].b.y);
	glVertex2f(squares[i].b.x, squares[i].b.y);
    glVertex2f(squares[i].b.x, squares[i].a.y);
  	glEnd();
  }
  glLineWidth(3);
  for (unsigned int i = 0; i < segs.size(); i++) {
	glColor3fv(black);
	glBegin(GL_LINES);
	glVertex2f(segs[i].a.x, segs[i].a.y);
	glVertex2f(segs[i].b.x, segs[i].b.y);
	glEnd();
  }
}


void display(){
  //clear the screen
  glClear(GL_COLOR_BUFFER_BIT); 
 //clear all transformations 
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();

  /* the default GL window is [-1,1]x[-1,1] with the origin in the
     center  */

  draw_segments(); 

  
  /* execute the drawing commands */
  glFlush();


}


//takes a kd tree and fills a vector with the lines to be drawn for the Mondrian visual 
//additionally, fills the vector with the coordinates needed to draw the colored squares
void treetoLines(TreeNode* node, double boundUp, double boundDown, double boundLeft, double boundRight)
{	
	if (node == NULL) {
		return;
	}
	if (node->left == NULL && node->right == NULL) {
		return;
	}
	Point2D start, end, start2, end2, start3, end3;
	if (!node->type)
	{	
		start2.x = boundLeft;
                start2.y = node->p.y;
                end2.x = boundRight;
                end2.y = boundUp;
		start.x = boundLeft;
		start.y = node->p.y;
		end.x = boundRight;
		end.y = boundDown;
		start3.x = boundLeft;
                start3.y = node->p.y;
                end3.x = boundRight;
                end3.y = node->p.y;
		MondrianSeg newseg(start, end);
		MondrianSeg line(start3, end3);
		MondrianSeg newseg2(start2, end2);
		squares.push_back(newseg2);
		squares.push_back(newseg);
		segs.push_back(line);
		treetoLines(node->left, node->p.y, boundDown, boundLeft, boundRight);
		treetoLines(node->right, boundUp, node->p.y, boundLeft, boundRight);
	}
	else
	{
		start2.x = node->p.x;
                start2.y = boundUp;
                end2.x = boundLeft;
                end2.y = boundDown;
		start.x = boundRight;
		start.y = boundUp;
		end.x = node->p.x;
		end.y = boundDown;
		start3.x = node->p.x;
                start3.y = boundUp;
                end3.x = node->p.x;
                end3.y = boundDown;
		MondrianSeg line(start3, end3);
		MondrianSeg newseg(start, end);
                MondrianSeg newseg2(start2, end2);
		segs.push_back(line);
                squares.push_back(newseg2);
                squares.push_back(newseg);
		treetoLines(node->left, boundUp, boundDown, boundLeft, node->p.x);	
		treetoLines(node->right, boundUp, boundDown, node->p.x, boundRight); 
	}
}
	
void keypress(unsigned char key, int x, int y)
{
        switch(key){
        case 'q':
                exit(0);
                break;
        case '1':
	{
		squares.clear();
		segs.clear();	
		points.clear();
                initializePointsX(n);
                Kdtree kid (points);
                treetoLines(kid.root, 1, -1, -1, 1);
		glutPostRedisplay();
		break;
	}
	case '2':
	{
                squares.clear();
                segs.clear();  
                points.clear();
                initiallize_points_circle();
                Kdtree kid (points);
                treetoLines(kid.root, 1, -1, -1, 1);
                glutPostRedisplay();
                break;
	}
	case '3':
        {       
		int momentaryN= 200;
                squares.clear();
                segs.clear();  
                points.clear();
		initialize_points_grid(momentaryN);
                Kdtree kid (points);
                treetoLines(kid.root, 1, -1, -1, 1);
                glutPostRedisplay();
                break;
        }
	case '4':
        {      
                squares.clear();
                segs.clear();
                points.clear();
                initialize_points_diag();
                Kdtree kid (points);
                treetoLines(kid.root, 1, -1, -1, 1);
                glutPostRedisplay();
                break;
        }
        }
}		

int main(int argc, char** argv){
	if (argc != 2)
	{
		cout << "enter a number pretty please" << endl;
		return 0;
	}
	n = atoi(argv[1]);
	assert(n>0);
	initializePointsRandom(n);
	//printPoints(points);
	Kdtree kid (points);
	treetoLines(kid.root, 1, -1, -1, 1);
 	
	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  	glutInitWindowSize(WINDOWSIZE, WINDOWSIZE);
  	glutInitWindowPosition(100,100);
	glutCreateWindow(argv[0]);
	
	//glut framework code used from the glut practice exercises
  	/* register callback functions */
  	glutDisplayFunc(display); 
  	glutKeyboardFunc(keypress);
  
  	/* OpenGL init */
  	/* set background color black*/
  	glClearColor(0, 0, 0, 0);   
  	/* here we can enable depth testing and double buffering and so on */

  	/* give control to the event handler */
  	
	glutMainLoop();
  	
	return 0;
}







