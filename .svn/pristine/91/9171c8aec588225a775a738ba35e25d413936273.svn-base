#include "geom.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* **************************************** */
/* returns the signed area of triangle abc. The area is positive if c
 *    is to the left of ab, and negative if c is to the right of ab
 *     */
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
//Partition for quiksort based off of angle
int partition(point2D* array, int p, int q)
{
    double pivot = array[q].angle;
    int i = p;
    int j;
    for (j = p; j < q; j++)
    {
        if (array[j].angle <= pivot)
        {
            point2D temp = array[j];
            array[j] = array[i];
            array[i] = temp;
            i = i + 1;
        }
    }
    point2D temp1 = array[i];
    array[i] = array[q];
    array[q] = temp1;
    return i;
}

//quicksort to sort a point2D array by respect to the structs angle value

void quiksort(point2D* array, int p, int q)
{
    int r;
    
    if (p < q)
    {
        r = partition(array, p, q);
        quiksort(array, p, r-1);
        quiksort(array, r+1, q);
    }
    return;
}


//Partition to deal with points that have the same angle but different distances
int partitionD(point2D* array, int p, int q)
{
    //Partition that factors in distance
    double pivotD = array[q].distance;
    int i = p;
    int j;
    for (j = p; j < q; j++)
    {
        if (array[j].distance > pivotD)
        {
            point2D temp = array[j];
            array[j] = array[i];
            array[i] = temp;
            i = i + 1;
        }
    }
    point2D temp1 = array[i];
    array[i] = array[q];
    array[q] = temp1;
    return i;
}

//quicksort to sort a point2D array by respect to the structs distance value
void quiksortD(point2D* array, int p, int q)
{
    int r;
    
    if (p < q)
    {
        r = partitionD(array, p, q);
        quiksortD(array, p, r-1);
        quiksortD(array, r+1, q);
    }
    return;
}


/* compute the convex hull of the points in p; the points on the CH are returned as a list
 //input: array of point2D structs, size of array
 //purpose: computes the convex hull of these points
 //output: a linked list of each point2D element in the convex hull
 * */
pointNode* graham_scan(point2D* p, int n) {
    
    int i;
    //identify the smallest y value
    double smallY = 100000000;
    point2D smallYpoint;
    for(i = 0; i < n; i++)
    {
        if(p[i].y < smallY)
        {
            smallY = p[i].y;
            smallYpoint = p[i];
        }
    }
    //create the head of the linked list and set the smallY point to it
    pointNode *hull = malloc(sizeof(pointNode));
    hull->p = smallYpoint;
    //calculate the slope and angle between the smallY point and all other points
    for(i = 0; i < n; i++)
    {
        if((p[i].x == smallYpoint.x)&&(p[i].y == smallYpoint.y))
        {
            p[i].slope = 0;
        }
        else
        {
            //slope was kept track of for debugging purposes
            p[i].slope = (p[i].y - smallYpoint.y) / (p[i].x - smallYpoint.x);
            p[i].angle = atan((p[i].x - smallYpoint.x)/ (p[i].y - smallYpoint.y));
            double xDif = p[i].y - smallYpoint.y;
            double yDif = p[i].x - smallYpoint.x;
            p[i].distance = xDif * xDif + yDif * yDif;
        }
    }
    
    //sorts the point2D by angle with respect to the smallY point
    quiksort(p, 0, n-1);
    //sort secondarily by distance to smallYpoint
    int startDup;
    int endDup;
    for(i = 0; i < n; ++i)
    {
        startDup = i;
        endDup = i;
        //Determines section that should be sorted within array
        while(endDup <  n && (p[startDup].angle == p[endDup].angle))
        {
            ++endDup;
        }
        if(endDup - startDup > 1)
        {
            quiksortD(p, startDup, endDup - 1);
        }
    }
    //add the second item of the convex hull to the linked list--the item with the smallest slope
    pointNode *second = malloc(sizeof(pointNode));
    hull->next = second;
    second->p = p[n-1];
    second->prev = hull;
    second->next = NULL;
    pointNode *a = hull; //pointer to keep track of the 2nd most recent node
    pointNode *b = second;  //pointer to keep track of the most recent node
    printf("Hull = %f, %f", hull->p.x, hull->p.y);
    //for loop to calculate the convex hull for the rest of the n-2 points
    for (i = n - 2; i >= 0; --i)
    {
        //If duplicate points, ignore
        if (p[i].distance == p[i-1].distance) {continue;}
        //If Collinear, add.
        else if (collinear(a->p, b->p, p[i]))
        {
            pointNode *tempA = a;
            pointNode *newNode = malloc(sizeof(pointNode));
            newNode->p = p[i];
            b = newNode; //deal with pointers
            a = a->next;
            a->next = b; //update a and b
            b->prev = a;
            b->next = NULL;
            a->prev = tempA;
        }
        //if the next point considered is to the left of the previous two points, add it to the convex hull
        else if (left(a->p, b->p, p[i]))
        {
            pointNode *tempA = a;
            pointNode *newNode = malloc(sizeof(pointNode));
            newNode->p = p[i];
            b = newNode; //deal with pointers
            a = a->next;
            a->next = b; //update a and b
            b->prev = a;
            b->next = NULL;
            a->prev = tempA;
        }
        //if the next point is to the right of a and b
        else
        {
            while(!left(a->p, b->p, p[i]))
                //remove every node while the new node is to the right of a b
            {	
                pointNode *tempPrev = a->prev->prev;
                b = b->prev;
                a = a->prev;
                a->next = b;
                b->next = NULL;
                a->prev = tempPrev;
                b->prev = a;
            }	
            //add the new node
            pointNode *tempA = a;
            pointNode *newNode = malloc(sizeof(pointNode));
            newNode->p = p[i];
            b = newNode; //update a and b
            a = a->next;
            a->next = b;
            b->prev = a;
            b->next = NULL;
            a->prev = tempA;
        }
    }
    
    return hull;
    
}


