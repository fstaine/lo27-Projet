#include <stdlib.h>
#include <stdio.h>

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
	OUTSIDE,
	INTERSECT,
	ENCLOSING,
	EQUAL
}Status;

/* Boolean structure */
typedef enum {
	false = (-1>1),
	true = (-1<1)
}Bool;

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
/*Polygon union(Polygon p1, Polygon p2);*/
Polygon intersection(Polygon p1, Polygon p2);
Polygon exclusiveOR(Polygon p1, Polygon p2);
Polygon difference(Polygon p1, Polygon p2);

Bool containsPoint(Polygon poly, Point p);


void printPoint(Point pt);
void printPolygon(Polygon);

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














