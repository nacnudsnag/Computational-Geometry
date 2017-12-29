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
    vector<point2D> ray;   
    int hasRay;
    int p1Vis;
} lineSegment2D;


typedef struct _rect2D  {
    point2D origin;
    float width, height;
} rect2D;

int checkTwoPoints(point2D a, point2D b);
vector <point2D> sortVisibleRadially (vector <point2D> points, point2D guard);
bool compareByAngle(const point2D &a, const point2D &b);
vector<point2D> sortPoints(vector <point2D> p);
vector<Triangle> compute_vp(vector<point2D> points, point2D guard);
int collinear(point2D p, point2D q, point2D r);
int signed_area2D(point2D a, point2D b, point2D c);
int left (point2D a, point2D b, point2D c);
#endif

