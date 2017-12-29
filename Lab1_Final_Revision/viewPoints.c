/* view1.c
 
 Laura Toma
 
 What it does:
 
 Draws a set of points in the default 2D projection.
 
 Includes a tentative function for printing and drawing a list of-
 points (assumed to be a convex hull). These functions were not
 debugged so use them at your own risk.
 
 This code is written in C.  You will need to update this code to work
 with your own (presumably C++) data structures. Feel free to change
 this code as much as you need to.
 
 */

#include "geom.h"
#include "rtimer.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


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



/* forward declarations of functions */
void display(void);
void keypress(unsigned char key, int x, int y);
void main_menu(int value);



/* global variables */
const int WINDOWSIZE = 500;

//the array of n points; note: this variable needs to be global
//because it needs to be rendered
point2D*  points = NULL;
int n;

//the convex hull, stored as a list. note: this variable needs to be
//global because it needs to be rendered
pointNode*  hull = NULL;



void initialize_points_circle() {
    
    assert(points);
    
    double  step = 2* M_PI/n;
    int rad = 100;
    
    int i;
    for (i=0; i<n; i++) {
        points[i].x = WINDOWSIZE/2+ rad*cos(i*step);
        points[i].y = WINDOWSIZE/2+ rad*sin(i*step);
    }
    
}
void initialize_points_stairs() {
    assert(points);
    
    int i;
    for (i=0; i<n; i++) {
        points[i].x = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE));
        points[i].y = WINDOWSIZE - points[i].x + random() % ((int)(.05*WINDOWSIZE));
    }
    
}
void initialize_cg(){
    assert(points);
    double step = 2* M_PI/n;
    int rad = 100;
    double PI = acos(-1.0);
    int i;
    //C
    for (i=0; i<n/3; i++) {
        points[i].x = WINDOWSIZE/2+ rad*cos(1.6*i*step+PI/2.0);
        points[i].y = WINDOWSIZE/2+ rad*sin(1.6*i*step+PI/2.0);
    }
    //Curve of G
    for (i=(n/3); i< (2*n/3 ); i++) {
        points[i].x = WINDOWSIZE/2+ 0.5*rad*cos(1.6*i*step-PI/2.0);
        points[i].y = WINDOWSIZE/2+ 0.5*rad*sin(1.6*i*step-PI/2.0);
    }
    //Vertical line of G
    int j;
    for (i=(2*n/3); i< 5*n/6; i++) {
        points[i].x = WINDOWSIZE/2;
        points[i].y = WINDOWSIZE/2 - j*3;
        j++;
    }
    //Horizontal line of G
    int k;
    for (i=5*n/6; i< n; i++) {
        points[i].x = WINDOWSIZE/2 - 0.05*WINDOWSIZE + k*3;
        points[i].y = WINDOWSIZE/2;
        k++;
    }
}
void initialize_points_person() {
    assert(points);
    int headPoints = n / 4;
    int bodyPoints = n / 4;
    int lArmPoints = n / 8;
    int rArmPoints = n / 8;
    int rad = 40;
    double step = 2 * 4 * M_PI/ n;
    int bodyRange = (int) (4 * WINDOWSIZE / 5) - rad - (WINDOWSIZE) / 5;
    
    // easy tracking of start and stop points for each for loop
    int start = 0;
    int stop = headPoints;
    
    /**head**/
    for (int i = start; i < stop; i++) {
        points[i].x = WINDOWSIZE / 2 + rad * cos(i * step);
        points[i].y = 4 * WINDOWSIZE / 5 + rad * sin(i * step);
    }
    
    start += headPoints;
    stop += bodyPoints;
    
    /**body**/
    srand(time(NULL));
    for (int i = start; i < stop; i++) {
        points[i].x =  WINDOWSIZE / 2;
        // 4 * WINDOWSIZE / 5 - rad is the bottom of the circle
        int yPoint = (WINDOWSIZE / 5) + rand() % bodyRange;
        points[i].y = yPoint;
    }
    
    start += bodyPoints;
    stop += lArmPoints;
    
    /**left arm**/
    // bottom of head
    int top = 4 * WINDOWSIZE / 5 - rad;
    int bottom = (top - WINDOWSIZE / 5) / 2;
    // left side of head
    int left = WINDOWSIZE / 2 - 2 * rad;
    for (int i = start; i < stop; i++) {
        int xCoord = left + rand() % (WINDOWSIZE / 2 - left);
        int yCoord = (-0.5 * xCoord) + top;
        points[i].x = xCoord;
        points[i].y = yCoord;
    }
    
    start += lArmPoints;
    stop += rArmPoints;
    
    /**right arm**/
    // right side of head
    int right = WINDOWSIZE / 2 + 2 * rad;
    for (int i = start; i < stop; i++) {
        int xCoord = WINDOWSIZE / 2 + rand() % (right - WINDOWSIZE / 2);
        int yCoord = (0.5 * xCoord) + (4 * WINDOWSIZE / 5 - rad + 10) - 2 * bottom;
        points[i].x = xCoord;
        points[i].y = yCoord;
    }
    
    start += lArmPoints;
    stop += lArmPoints;
    
    /**left leg**/
    for (int i = start; i < stop; i++) {
        int xCoord = left + rand() % (WINDOWSIZE / 2 - left);
        int yCoord = xCoord - 3 * WINDOWSIZE / 10;
        points[i].x = xCoord;
        points[i].y = yCoord;
    }
    
    start += lArmPoints;
    stop += lArmPoints;
    
    /**right leg**/
    for (int i = start; i < stop; i++) {
        int xCoord = WINDOWSIZE / 2 + rand() % (right - WINDOWSIZE / 2);
        int yCoord = -1 * xCoord + 7 * WINDOWSIZE / 10;
        points[i].x = xCoord;
        points[i].y = yCoord;
    }
    
    // add any extra points randomly
    for(int i = stop; i < n; i++) {
        points[i].x = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE));
        points[i].y =  (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE));
    }
}
void initialize_points_horizontal_line() {
    
    assert(points);
    
    int i;
    for (i=0; i<n; i++) {
        points[i].x = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE));
        points[i].y =  WINDOWSIZE/2;
    }
    
}
/*Alligns all points in a vertical line*/
void initialize_points_vertical_line() {
    assert(points);
    
    int i;
    for (i=0; i<n; i++) {
        points[i].x =  WINDOWSIZE/2;
        points[i].y = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE));
    }
}

/* ****************************** */
/* initialize  the array of points stored in global variable points[] with random points */
void initialize_points_random() {
    //points must be allocated
    assert(points);
    
    int i;
    for (i=0; i<n; i++) {
        points[i].x = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE));
        points[i].y =  (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE));
    }
}


/* ****************************** */
/* initialize the array of points stored in global variable points[]
 with random points shaped like a star */
void initialize_points_star() {
    
    //points must be allocated
    assert(points);
    
    int i;
    for (i=0; i<n; i++) {
        if (i%2 == 0) {
            
            points[i].x = (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE));
            points[i].y =  random() % ((int)(.7*WINDOWSIZE))  / 5;
            points[i].y += (int)((1-.7/5)*WINDOWSIZE/2);
        };
        if (i%2 == 1)  {
            
            points[i].x = random() % ((int)(.7*WINDOWSIZE)) / 5;
            points[i].x +=  (int)((1-.7/5)*WINDOWSIZE/2);
            points[i].y =  (int)(.3*WINDOWSIZE)/2 + random() % ((int)(.7*WINDOWSIZE));
        }
        
    }//for i
    
}

/* ****************************** */
/* print the array of points stored in global variable points[]*/
void print_points() {
    assert(points);
    int i;
    printf("points: ");
    for (i=0; i<n; i++) {
        printf("[%3d,%3d] ", points[i].x, points[i].y);
    }
    printf("\n");
    fflush(stdout);  //flush stdout, weird sync happens when using gl thread
}

/* ****************************** */
//print the list of points in global variable  hull;
void print_hull () {
    
    printf("convex hull: ");
    int i=0;
    pointNode* crt = hull;
    while (crt) {
        i++;
        printf("[%3d,%3d] ", crt->p.x, crt->p.y);
        crt = crt->next;
    }
    printf(" total %d points\n", i);
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
    
    //allocate global arrays of n points
    points = (point2D*)malloc(n*sizeof(point2D));
    assert(points);
    //initialize_points_random();
    initialize_points_star();
    
    //print_points();
    
    Rtimer rt1;
    rt_start(rt1);
    hull = graham_scan(points, n);
    rt_stop(rt1);
    //print the hull
    print_hull();
    //print the timing
    char buf [1024];
    rt_sprint(buf,rt1);
    printf("finding convex hull with graham scan:  %s\n\n", buf);
    fflush(stdout);
    
    
    
    
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
    /* here we can enable depth testing and double buffering and so
     on */
    
    
    /* give control to event handler */
    glutMainLoop();
    return 0;
}


/* ****************************** */
/* draw the array of points stored in global variable points[]
 each point is drawn as a small square
 
 */
void draw_points(){
    
    const int R= 1;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //set color
    glColor3fv(yellow);
    
    assert(points);
    int i;
    for (i=0; i<n; i++) {
        //draw a small square centered at (points[i].x, points[i].y)
        glBegin(GL_POLYGON);
        glVertex2f(points[i].x -R,points[i].y-R);
        glVertex2f(points[i].x +R,points[i].y-R);
        glVertex2f(points[i].x +R,points[i].y+R);
        glVertex2f(points[i].x -R,points[i].y+R);
        glEnd();
    }
    
}





/* ****************************** */
/* draw the list of points stored in global variable hull; the points
 are expected to be in order (ccw or cw) and consecutive points are
 connected by a line
 */
void draw_hull(){
    
    //set color
    glColor3fv(red);
    while (hull != NULL)
    {
        pointNode* curr = hull;
        hull = hull->next;
        free(curr);
    }
    hull = graham_scan(points, n);
    if (hull) {
        pointNode* prev = hull;
        pointNode* crt = prev->next;
        
        while (crt) {
            //draw a line from prev to crt
            glBegin(GL_LINES);
            glVertex2f(prev->p.x, prev->p.y);
            glVertex2f(crt->p.x, crt->p.y);
            glEnd();
            prev=crt;
            crt=crt->next;
        }
        
        //draw a line from the last point to the first point
        glBegin(GL_LINES);
        glVertex2f(prev->p.x, prev->p.y);
        glVertex2f(hull->p.x, hull->p.y);
        glEnd();
        prev=crt;
        crt=crt->next;
        
    }//if (hull)
}


/* ****************************** */
void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //clear the matrix
    
    
    /* the default GL window is [-1,1]x[-1,1] with the origin in the
     center the points are in the range (0,0) to (WINSIZE,WINSIZE), so
     they need to be mapped to [-1,1]x [-1,1] */
    glScalef(2.0/WINDOWSIZE, 2.0/WINDOWSIZE, 1.0);
    glTranslatef(-WINDOWSIZE/2, -WINDOWSIZE/2, 0);
    draw_points();
    draw_hull();
    
    /* execute the drawing commands */
    glFlush();
}



int INITIALIZER =0;
int CASES = 8;

/* Here we have the different test cases. NOTE. We only did those that were in c and not c++, the cg function they created doesn't create a CG, and doesn't appear to work. */
void keypress(unsigned char key, int x, int y) {
    switch(key) {
        case 'q':
            exit(0);
            break;
            
        case 'i':
            INITIALIZER = (INITIALIZER+1)% CASES;
            if (INITIALIZER == 0) {
                initialize_points_circle();
            } else if (INITIALIZER ==1) {
                initialize_points_random();
                
            } else if  (INITIALIZER ==2) {
                initialize_points_star();
            } else if  (INITIALIZER ==3) {
                initialize_points_horizontal_line();
            } else if  (INITIALIZER ==4) {
                initialize_points_stairs();
            } else if  (INITIALIZER ==5) {
                initialize_points_vertical_line();
            } else if  (INITIALIZER ==6) {
                initialize_points_person();
            }  else if  (INITIALIZER ==7) {
                // The initialize function doesn't work.
                initialize_cg();
            }
            
            
            
            
            
            
            glutPostRedisplay();
            break;
    }
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


