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
 
typedef struct robot  {
	point2D a, b, c, d;
	int prevIndex;
	int prevX;
	int fits;
	int prevY;
	int prevAngle;
	bool operator< (const robot &other) const { return score < other.score; }
	double score;
	double cost;
	int theta;
	int distX, distY;
} robot;


void updatePoints(robot * robit);
int checkSegInsidePolygon(vector <lineSegment2D> polygon, point2D a, point2D b);
double dist(point2D a, point2D b);
void updatePoints(robot* robit);
int isVisible(point2D line1, point2D line2, point2D guard, point2D a); 
int checkTwoPoints(point2D a, point2D b);
int checkEqual(point2D a, point2D b, point2D c);
vector <point2D> sortVisibleRadially (vector <point2D> points, point2D guard);
int collinear(point2D p, point2D q, point2D r);
int signed_area2D(point2D a, point2D b, point2D c);
int left (point2D a, point2D b, point2D c);
#endif

