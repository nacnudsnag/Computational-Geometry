#ifndef __geom_h
#define __geom_h


typedef struct _point2d {
  double x,y;
  double slope, angle, distance; //slope and angle are used to keep track of values for graham scan
} point2D;




//a list of points 
typedef struct _pointNode pointNode; 
struct _pointNode  {
  point2D p;
  pointNode* prev;
  pointNode* next;
}; 
/* returns 2 times the signed area of triangle abc. The area is positive if c      is to the left of ab, and negative if c is to the right of ab */
int signed_area2D(point2D a, point2D b, point2D c); 


/* return 1 if p,q,r collinear, and 0 otherwise */ 
int collinear(point2D p, point2D q, point2D r);

/* return 1 if c is  strictly left of ab; 0 otherwise */
int left (point2D a, point2D b, point2D c);

/* compute the convex hull of the points in p; the points on the CH
       are returned as a list.
           */
pointNode* graham_scan(point2D* p, int n);


 #endif
