#include "geom.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

bool compareByX(const Point2D &a, const Point2D &b)
{
	return a.x < b.x;
}

bool compareByY(const Point2D &a, const Point2D &b)
{
        return a.y < b.y;
}

//function to print a tree node, useful for debugging
void recursivePrint(TreeNode * node) {
	if (node != NULL) {
		cout << node->p.x << ", " << node->p.y << endl;
		recursivePrint(node->left);
		recursivePrint(node->right);
	}
}

//constructor for treenode
TreeNode::TreeNode(Point2D point) {
	p = point;
	left = NULL;
	right = NULL;
}

//constructor for kdtree
Kdtree::Kdtree(vector<Point2D> p) {
	vector<Point2D>  pointsByX, pointsByY;
	sort(p.begin(), p.end(), compareByX);
	pointsByX = p;
	sort(p.begin(), p.end(), compareByY); 
	pointsByY = p;
	root = buildKdtree(pointsByX, pointsByY, 0);
}

//recursive helper function for kdtree constructor that recursively builds the tree
TreeNode*  Kdtree::buildKdtree(vector<Point2D> sortedbyX, vector<Point2D> sortedbyY, int cutType) {
	int cuttype = cutType;
	if(sortedbyX.size() == 0) {return NULL;}
	if(sortedbyX.size() == 1)
	{	
		TreeNode* node = new TreeNode(sortedbyX[0]);
		node->left = NULL;
		node->right = NULL;
		node->type = cuttype;
		return node; 
	}
	TreeNode* node;		

	int median = (sortedbyX.size() / 2)-1;//both are same size
	if(cuttype)
	{
		node = new TreeNode(sortedbyX[median]);
		node->type = 1;
		vector<Point2D> leftbyx, leftbyy, rightbyx, rightbyy;
		for(int i = 0; i <= median; ++i)
		{
			leftbyx.push_back(sortedbyX[i]);
		}
		for(int i = median + 1; i < sortedbyY.size(); ++i)
		{
			rightbyx.push_back(sortedbyX[i]);
		}
		for(int i = 0; i < sortedbyY.size(); ++i)
		{
			if(sortedbyY[i].x <= sortedbyX[median].x)
			{
				leftbyy.push_back(sortedbyY[i]);
			}
			else
			{
				rightbyy.push_back(sortedbyY[i]);
			}
		}
	node->left = buildKdtree(leftbyx, leftbyy, 0);
	node->right = buildKdtree(rightbyx, rightbyy, 0);
	}
	else
	{	
		node = new TreeNode(sortedbyY[median]);
		node->type = 0;
		vector<Point2D> upbyx, downbyx, upbyy, downbyy;
		for(int i = 0; i <= median; i++)
		{
			downbyy.push_back(sortedbyY[i]);
		}
		for(int i = median + 1; i < sortedbyY.size(); ++i)
		{
			upbyy.push_back(sortedbyY[i]);
		}
		for (int i = 0; i < sortedbyY.size(); ++i)
		{
			if(sortedbyX[i].y <= sortedbyY[median].y)
			{
				downbyx.push_back(sortedbyX[i]);
			}
			else
			{
				upbyx.push_back(sortedbyX[i]);
			}
		}
	node->left = buildKdtree(downbyx, downbyy, 1);
	node->right = buildKdtree(upbyx, upbyy, 1); 
	}
	return node; 							
}


	
