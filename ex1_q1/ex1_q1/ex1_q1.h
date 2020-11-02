//#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>

// *****   declarations of types and constants   *****

#define lluint long long unsigned int

#define MAX_VERT    8 // maximum number of vertices (6 is for hexagon)

enum POLY_TYPE {
	QUADRI = 4, PENTAGON, HEXAGON = 6,
	OCTAGON = 8, BAD_POLY
};
enum WHOM_TO_OUTPUT { CURRENT, ALL_POLY, NONE };

struct point {
	int x, y;
};

struct polygon {
	enum POLY_TYPE poly_type;
	struct point vertices[MAX_VERT];
};

struct Node {
	struct polygon* poly;
	struct Node* next;
};


// *****   declarations of function prototypes   *****
void my_exception(int line, const char* function, char* msg);
double calc_side(struct point pt1, struct point pt2);
double calc_triangle_area(struct point p1, struct point p2, struct point p3);
void print_point(struct point pt);
void print_polygon_name(enum POLY_TYPE poly, char* poly_name);

//-----------------------------------------------
void my_exception(int line, const char* function, char* msg)
{
	fprintf(stderr, "ERROR (line %d function: %s) !!!%s\n", line, function, msg);
	exit(1);
}

//-----------------------------------------------
double calc_side(struct point pt1, struct point pt2)
{
	double x = pt1.x - pt2.x;
	double y = pt1.y - pt2.y;
	return sqrt(x*x + y * y);
}

//-----------------------------------------------
double calc_triangle_area(struct point p1, struct point p2, struct point p3)
{
	double area,
		x1 = p1.x,
		x2 = p2.x,
		x3 = p3.x,
		y1 = p1.y,
		y2 = p2.y,
		y3 = p3.y;
	area = 0.5*(x1*y2 + x2 * y3 + x3 * y1 - x2 * y1 - x3 * y2 - x1 * y3);
	area = (area > 0) ? area : -area;
	return area;
}

//-----------------------------------------------
void print_point(struct point pt)
{
	printf("{%d, %d} ", pt.x, pt.y);
}

//-----------------------------------------------
void print_polygon_name(enum POLY_TYPE poly, char* poly_name)
{
	switch (poly)
	{
	case QUADRI:  sprintf(poly_name, "quadrilateral"); break;
	case HEXAGON: sprintf(poly_name, "hexagon"); break;
	case OCTAGON: sprintf(poly_name, "octagon"); break;
	default: my_exception(__LINE__, __func__, "bad-polygon_type");
	}
}