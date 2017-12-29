#ifndef __geom_h
#define __geom_h
#include <vector>
using namespace std;
class Point2D {
	public:
		double x, y;
};
class TreeNode {
  public: 
     Point2D p; 
     int type; 
     TreeNode *left, *right;  
     TreeNode(Point2D); 
     TreeNode();
     void printNode();
};
class Kdtree {
  public: 
     TreeNode* buildKdtree(vector<Point2D> sortedbyX, vector<Point2D> sortedbyY, int cuttype); 
     TreeNode* root; 
     Kdtree(vector<Point2D>);
     
};

class MondrianSeg {
  public:
	Point2D  a, b;
  	MondrianSeg(Point2D start, Point2D end) {a = start; b = end;};
};
void recursivePrint(TreeNode *);

#endif

