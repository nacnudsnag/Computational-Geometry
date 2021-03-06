#ifndef __geom_h
#define __geom_h
#include <vector>
using namespace std;
class point2D {
	public:
		double x, y, angle, distance;
		int ray;
};
class Triangle {
	public: point2D a, b, c;
};

typedef struct _lineSegment2D {
    point2D p1, p2;
} lineSegment2D;
 
typedef struct graphNode  {
    int operator<(const graphNode& rhs) const //comparitor for creating a heap 
    {
	return currDist < rhs.currDist;
    }
    point2D point;
    int iPrev, jPrev; //keep track of indicides of previous point
    vector <graphNode* > neighbors;
    int currDist;
    int poly;
    int myI, myJ;
    vector<int> iInd;
    vector<int> jInd;
    int completed;
} graphNode;


typedef struct _graph  {
    graphNode begin, end;
} graph;


int checkSegInsidePolygon(vector <lineSegment2D> polygon, point2D a, point2D b);
double dist(point2D a, point2D b);
int isVisible(point2D line1, point2D line2, point2D guard, point2D a); 
int checkTwoPoints(point2D a, point2D b);
//vector<vector<graphNode> > createGraph(vector<vector<graphNode> > polygons, vector<vector<lineSegment2D> > polysegs, int iIndex, int jIndex);
int checkEqual(point2D a, point2D b, point2D c);
vector <point2D> sortVisibleRadially (vector <point2D> points, point2D guard);
bool compareByAngle(const point2D &a, const point2D &b);
vector<point2D> sortPoints(vector <point2D> p);
int collinear(point2D p, point2D q, point2D r);
vector<lineSegment2D> findSegments(vector<vector<point2D> > polygons, point2D start, point2D end);
int signed_area2D(point2D a, point2D b, point2D c);
int left (point2D a, point2D b, point2D c);
#endif

