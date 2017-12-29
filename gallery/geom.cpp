#include "geom.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <map>

double dist(point2D a, point2D b)
{       
	//Computes distance between Points
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int signed_area2D(point2D a, point2D b, point2D c) {
    //return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x));
    return ((a.x-c.x)*(b.y-c.y) - (b.x-c.x) * (a.y-c.y));
}

/* **************************************** */
/* return 1 if p,q,r collinear, and 0 otherwise */
int collinear(point2D p, point2D q, point2D r) {
    if (signed_area2D(p, q, r) ==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



/* **************************************** */
/* return 1 if c is  strictly left of ab; 0 otherwise */
int left (point2D a, point2D b, point2D c) {
    if (signed_area2D(a, b, c) > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//function that checks whether a segment blocks visibility to a point
int isVisible(point2D line1, point2D line2, point2D guard, point2D a)
{
	if ((line1.x == a.x && line1.y == a.y) || (line2.x == a.x && line2.y == a.y))
	{
		return 1;
	}
	else if (left(line1, line2, guard) != (left(line1, line2, a)))
	{
		if (!left(guard, line1, a) && left(guard, line2, a))
		{
			return 0;
		}
		if (!left(guard, line2,a) && left(guard, line1, a))
		{
			return 0;
		}
	}
	return 1;
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

//function to check if the polygon is simple by checking if any of the segments intersect with any of the other segments
int isSimplePoly(vector<lineSegment2D> segs)
{
	int intBool = 1;
	for (int i = 0; i < segs.size(); ++i)
	{
		for (int j = 0; j < segs.size(); ++j)
		{
			if(i == j)
			{
				continue;
			}
			else
			{
				point2D intersection = pIntersect(segs[i].p1, segs[i].p2, segs[j].p1, segs[j].p2);
				if (intersection.x != -1) //there is an interseciton)
				{
					if(!checkTwoPoints(intersection, segs[i].p1) && !checkTwoPoints(intersection, segs[i].p2) &&
					   !checkTwoPoints(intersection, segs[j].p1) && !checkTwoPoints(intersection, segs[j].p2))
					{
						intBool = 0;
					}
				}
			}
		}
	}
	
	return intBool;
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

//function to check if the guard is inside the polygon
//returns an boonean int that indicates whether a point is inside a polygon
int inside(point2D check, vector<lineSegment2D> segs)
{
	int counter = 0;
	point2D outer;
	outer.x = check.x + 50000;
	outer.y = check.y;
	point2D inter;
	for (int i = 0; i < segs.size(); i++)
	{
		//Iterates through all the segments and checks for intersections
		inter = pIntersect(segs[i].p1, segs[i].p2, check, outer);
		if (segs[i].p1.y == outer.y)
		{
			//If the point shares the same y val
			if (segs[i].p1.x == check.x)
			{
			//if same point, return outside
				return 0;
			}
			if (((segs[i].p1.y > segs[i].p2.y) && (segs[i].p1.y < segs[i - 1].p1.y)) ||
			    ((segs[i].p1.y < segs[i].p2.y) && (segs[i].p1.y > segs[i - 1].p1.y) ))
			{
			//If the point signifies a line that goes on either side of the point, add to counter
				counter += .5;
			}
			
		}
		else if (inter.x != -1)
		{
		//If intersection with seg is not -1, -1 (i.e. exists), add to counter
			counter += 1;
		}
	}
	//Depending on counter return inside or outside
	if (counter % 2 == 0)
	{
		return 0;
	}
	return 1;
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

//Returns intersect of a ray and a set of segments for projections
point2D intersect(point2D a, point2D guard, vector<lineSegment2D> segs)
{	
	point2D helper;
	vector<point2D> rayed;
	point2D ray;
	helper.x = a.x - (50000 * (guard.x - a.x));
	helper.y = a.y - (50000 * (guard.y - a.y)); 
	for (int i = 0; i < segs.size(); i++)
	{

		if (left(guard, a, segs[i].p1) != left(guard, a, segs[i].p2))
                {
			//If the projection falls upon a segment that doesn't include the vertices
			if (!checkEqual(a, segs[i].p1, segs[i].p2))
                        {
				//Add it to the array
				ray = pIntersect(guard, helper, segs[i].p1, segs[i].p2);
				rayed.push_back(ray);
			}
                }
	}
	int distsml = INT_MAX;
	for (int i = 0; i < rayed.size(); i++)
	{
		if (dist(guard, rayed[i]) < distsml)
		{
			distsml = dist(guard, rayed[i]);
			helper = rayed[i];
		}
	}
	//Return closest ray projection point
	return helper;
}
//fucntion to compute the visible polygon from a point
//returns a vector of triangles that triangulate the visible polygon
vector<Triangle> compute_vp(vector<point2D> points, point2D guard) {
	
	vector<lineSegment2D> segs;
	lineSegment2D seg;
	vector<Triangle> returnMe;
	vector<point2D> finalPoints;
	point2D ray;
	for (int i = 1; i < points.size(); i ++)
        {       
                seg.p1 = points[i - 1];
                seg.p2 = points[i];
		seg.p1Vis = 0;
		seg.hasRay = 0;
                segs.push_back(seg);
        }
	seg.p1 = points[points.size() - 1];
        seg.p2 = points[0];
	seg.hasRay = 0;
	seg.p1Vis = 0;
        segs.push_back(seg);
	
	Triangle tri;
        tri.a = guard;
        tri.b = guard;
        tri.c = guard;
	
	int isSimple = isSimplePoly(segs); //check if the polygon is simple
	if (!isSimple)
	{
		cout << "draw a simple polygon please" << endl;
		returnMe.push_back(tri);
		return returnMe;
	}


        if (!inside(guard, segs))
        {
		//Checks to make sure guards are inside
                returnMe.push_back(tri);
                cout << "place the guard in the polygon please" << endl;
                return returnMe;
        }

	int visible = 1;
	for (int i = 0; i < segs.size(); i++)
	{
		//Iterate through all vertices
		visible = 1;	
		for (int j = 0; j < segs.size(); j++) 
		{
			//If segment blocks visibility, set visible = 0
			if (!isVisible(segs[j].p1, segs[j].p2, guard, segs[i].p1))
			{
				visible = 0;
			}		
			
		}
		if (visible)
		{	
			//If visible, project a ray
			segs[i].p1Vis = 1;
			ray = intersect(segs[i].p1, guard, segs);
			if (ray.x > 1)
			{
				if (i != segs.size() - 1)
				{
				//Makes sure that point doesn't fall behind a set of lines connected by a vertex
					if (left(guard, segs[i].p1, segs[i + 1].p1) == left(guard, segs[i].p1, segs[i - 1].p1)) 
					{
						for (int k = 0; k < segs.size(); k++)
						//Iterates through segs, pushing back all the possible rays
						{
							if (collinear(segs[k].p1, segs[k].p2, ray))
							{
								segs[k].ray.push_back(ray);
								segs[k].hasRay = 1;
							}
						}
					}
				}
				else
				{
				//Do something slightly different if on lest element in segs
					if (left(guard, segs[i].p1, segs[0].p1) == left(guard, segs[i].p1, segs[i - 1].p1)) 
                        	        {
						for (int k = 0; k < segs.size(); k++)
                                                {       
                                                        if (collinear(segs[k].p1, segs[k].p2, ray))
                                                        {
                                                                segs[k].ray.push_back(ray);
                                                                segs[k].hasRay = 1;
                                                        }
                                                }
                        	        }
				}
			}
			
		}
	}
	for(int i = 0; i < segs.size(); ++i)
        {
		//If the point on segs is visible, push it on to FinalPoints
		if (segs[i].p1Vis)
		{
			finalPoints.push_back(segs[i].p1);
		}	
		if (segs[i].hasRay)
		{
			//If it has a ray, push all rays in order of their addition to the seg
			if (segs[i].ray.size() > 1)
			{
				if (dist(segs[i].p1, segs[i].ray[1]) < dist(segs[i].p1, segs[i].ray[0]))
				{
					finalPoints.push_back(segs[i].ray[1]);
					finalPoints.push_back(segs[i].ray[0]);
				}
				else
				{
					finalPoints.push_back(segs[i].ray[0]);
                                        finalPoints.push_back(segs[i].ray[1]);
				}
			}
			else
			{
				finalPoints.push_back(segs[i].ray[0]);
			}
		}
        }
	
	for (int i = 1; i < finalPoints.size(); ++i) 
        {
		//Convert finalPoints to triangles to return	
		tri.a = guard;
		tri.b = finalPoints[i - 1];
		tri.c = finalPoints[i];
		returnMe.push_back(tri);
		
	}
	
	tri.a = guard;
	tri.b = finalPoints[finalPoints.size() - 1];
	tri.c = finalPoints[0];
	returnMe.push_back(tri);
	
	return returnMe;
}
