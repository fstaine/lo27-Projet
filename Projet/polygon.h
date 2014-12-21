#include <stdlib.h>
#include <stdio.h>

/* For printPolygon : *\
#include <sys/ioctl.h>
#include <unistd.h>
\**********************/

#define POS(x,y) printf("\033[%d;%dH",(int)x,(int)y);  // Move to the x,y position
#define CLEAR() printf("\033[2J\033[0;0H");

/* Types */
typedef struct{
	float x;
	float y;
}Point;

typedef Point Vector;

typedef struct elt{
	Point value;
	struct elt *prev;
	struct elt *next;
}Elt;

typedef struct{
	int size;
	Elt *head;
}Polygon;

/* Status enum, for the containsPolygon function */
typedef enum{
	INSIDE,
	OUTSIDE,
	INTERSECT,
	ENCLOSING,
	EQUAL,
	ELSE
}Status;

/* Boolean structure */
typedef enum {
	false = (-1>1),
	true = (-1<1)
}Bool;

/**********************\
 * Provided Functions *
\**********************/

/*
 * Allocate the memory for a Point structure and fill x and y
 * x : double, the coordonate x of the point
 * y : double, the coordonate y of the point
 * return a point with the coordonates (x,y)
 */
Point createPoint(float x, float y);

/*
 * Create an empty Polygon
 * Return the empty Polygon
 */
Polygon createPolygon();

/*
 * Add a point in the polygon poly
 * poly : the input polygon
 * pt : a pointer on the point to add in poly
 * return the new version of the Polygon poly
 */
Polygon addPoint(Polygon poly, Point pt);

Polygon removePoint(Polygon poly, int nb);

Polygon unionPolygons(Polygon p1, Polygon p2);
Polygon intersectionPolygons(Polygon p1, Polygon p2);
Polygon exclusiveORPolygons(Polygon p1, Polygon p2);
Polygon differencePolygons(Polygon p1, Polygon p2);

/* 
 * Find if the polygon poly contains the point p
 * poly : a non trivial polygon (Not reducted to a line)
 * p : the point we want to know if he is inside the polygon
 * Return a boolean value : true if the point is inside the polygon, false otherwise
 */
Bool containsPoint(Polygon poly, Point p);

Status containsPolygon(Polygon ref , Polygon poly);

Polygon centralSymetry(Polygon poly, Point p);

Polygon rotatePolygon(Polygon poly, Point p, float angle);

Polygon scalePolygon(Polygon poly, float factor);

Polygon translatePolygon(Polygon poly, Point start, Point stop);

Polygon convexHullPolygon(Polygon poly);

void printPoint(Point p);

void printPolygon(Polygon poly);

/*
 *
 *
 * Return a pointer on the string containing the coordonate of the polygon poly
 */
char *toString(Polygon poly);
/* */

/* Others functions : */

float min(float a, float b);
float max(float a, float b);
Bool equals(float a, float b);

Bool isEmpty(Polygon poly);

void isTrue(Bool b);













