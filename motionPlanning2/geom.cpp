/* File for the more basic geometric fuctions used in the implementattion
 * of A* and rrt.  
*/

#include "geom.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
				
//Takes two points and returns the distance between them	 
double dist(point2D a, point2D b)
{       
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

//function to check the intersection of two lines
//returns a points with an x and y value of -1 if there is no intersection
point2D pIntersect(point2D a, point2D b, point2D c, point2D d)
{
	point2D p;
	double s, t; 
	double num, denom;
	denom = a.x * (double)(d.y - c.y) +
		b.x * (double)(c.y - d.y) +
		d.x * (double)(b.y - a.y) +
		c.x * (double)(a.y - b.y);

	if (denom == 0)
	{
		point2D null;
		null.x = -1;
		null.y = -1;
	}
	num =   a.x * (d.y - c.y) +
		c.x * (a.y - d.y) +
		d.x * (c.y - a.y);
	s = num/denom;
	num = -(a.x * (c.y - b.y) + 
		b.x * (a.y - c.y) +
		c.x * (b.y - a.y));
	t = num / denom;
	p.x = a.x + s * (b.x - a.x);
	p.y = a.y + s * (b.y - a.y);
	if ((0.0 <= s) && (s<= 1.0) && (0.0 <= t) && (t <= 1.0))
	{
		return p;
	}
	else 
	{
		point2D null;
		null.x = -1; 
		null.y = -1; 
		return null;
	}
}


//Update points when given a robot, based off of the dist x, dist y
//the theta value, and the x and y coordinates of the point 

//Updates the points for a robot after a rotation
//This function is for a rectangular robot
void updatePoints(robot * robit)
{
	double thetaRadians = ((double)robit->theta/180) * (M_PI);
	int distX = robit->distX;
	int distY = robit->distY;
	robit->b.x = robit->a.x + (distX * cos(thetaRadians));
	robit->b.y = robit->a.y + (distX * sin(thetaRadians));
	robit->c.x = robit->b.x - (distY * sin(thetaRadians));
	robit->c.y = robit->b.y + (distY * cos(thetaRadians));
	robit->d.x = robit->a.x - (distY * sin(thetaRadians));
	robit->d.y = robit->a.y + (distY * cos(thetaRadians));
} 


//function that checks if two points are equal 
int checkTwoPoints(point2D a, point2D b)
{
	int equal = 0;
	if (a.x == b.x && a.y == b.y)
	{	
		equal = 1;
	}
	return equal;
}



int checkEqual(point2D a, point2D b, point2D c)
//Checks if three points are equal
{
	if ((a.x == b.x && a.y == b.y)||(a.x == c.x && a.y == c.y)||(b.x == c.x && b.y == c.y))
	{
		return 1;
	}
	return 0;
}



