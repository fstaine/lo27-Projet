#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/* For printPolygon : */
#include <sys/ioctl.h>
#include <unistd.h>

#define POS(x,y) printf("\033[%d;%dH",(int)x,(int)y);  /* Move to the x,y position 2 positives integers */
#define CLEAR() printf("\033[2J\033[0;0H");            /* Clear the terminal and move to the top-left position */

/* Types */
typedef struct{
	double x;
	double y;
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

typedef struct EltPolyList {
	Polygon poly;
	struct EltPolyList *next;
}EltList;

typedef EltList* PolyList;

/* Status enum, for the containsPolygon function */
typedef enum{
	INSIDE,
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

/**********************\
 * Provided Functions *
 \**********************/

/*
 * Allocate the memory for a Point structure and fill x and y
 * x : double, the coordonate x of the point
 * y : double, the coordonate y of the point
 * return a point with the coordonates (x,y)
 */
Point createPoint(double x, double y);

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

/*
 * 
 * 
 */
Polygon removePoint(Polygon poly, int nb);

/*
 * Compute the union between two specified polygons
 * The two polygons musn't be OUTSIDE and they don't have to create a hole during the process
 * poly1 : (Polygon) the 1st input polygon
 * poly2 : (Polygon) the 2nd input polygon
 * Return : (Polygon) The union polygon of the two inputs ones. 
 */
Polygon unionPolygons(Polygon poly1, Polygon poly2);

/*
 * Compute the intersection between two specified polygons
 * The two inputs polygons must not create a hole during the process. 
 * poly1 : (Polygon) the 1st input polygon
 * poly2 : (Polygon) the 2nd input polygon
 * Return : (Polygon) The intersection polygon of the two inputs ones. 
 */
Polygon intersectionPolygons(Polygon p1, Polygon p2);

PolyList exclusiveORPolygons(Polygon p1, Polygon p2);

PolyList differencePolygons(Polygon p1, Polygon p2);

/* 
 * Find if the polygon poly contains the point p
 * poly : a non trivial polygon (Not reducted to a line)
 * p : the point we want to know if he is inside the polygon
 * Return a boolean value : true if the point is inside the polygon, false otherwise
 */
Bool containsPoint(Polygon poly, Point p);

Status containsPolygon(Polygon ref , Polygon poly);

Polygon centralSymmetry(Polygon poly, Point p);

Polygon rotatePolygon(Polygon poly, Point pt, double angle);

Polygon scalePolygon(Polygon poly, double factor);

Polygon translatePolygon(Polygon poly, Point pt1, Point pt2);

Polygon convexHullPolygon(Polygon poly);

/*
 * Print a point on the terminal
 * P : (Point) the point to print on the terminal
 * Return : nothing
 */
void drawPoint(Point p);

/*
 * Print a polygon with the same shape as the input one, 
 * the polygon must not be trivial (not only aligned points)
 * the polygon is 1st scaled and translated to be visible on the whole terminal
 * poly : (Polygon) : the polygon we want to print
 * Return : Nothing
 */
void drawPolygon(Polygon poly);

/*
 * Transform a polygon into a string that respect a specific template : [[x1,y1],[x2,y2],[...]]
 * poly : (Polygon) the polygon we want transform into a string
 * Return : (char*) A pointer on the string containing the coordonate of the polygon poly
 */
char *toString(Polygon poly);

/* Others functions : */

/*
 * Compute the minimum between two double values
 * a : (double) a double value
 * b : (double) a double value
 * Return : (double) the minimum between a and b
 */
double min(double a, double b);

/*
 * Compute the maximum between two double values
 * a : (double) a double value
 * b : (double) a double value
 * Return : (double) the maximum between a and b
 */
double max(double a, double b);

/*
 * Return a boolean value, describing if two double values are equals or not
 * a : (double) a double value
 * b : (double) a double value
 * Return : (Bool) true if a == b, false otherwise
 */
Bool equals(double a, double b);

/*
 * Return a boolean value, describing if two Points are equals or not
 * a : (PointPoint) a specific point
 * b : (double) a specific point
 * Return : (Bool) true if a == b, false otherwise
 */
Bool equalsPoints(Point a, Point b);

/*
 * Return a Boolean value, describing if an input polygon is empty or not
 * poly : (Polygon) the input polygon we want to know if he is empty or not
 * Return : (Bool) true if poly is empty, false otherwise
 */
Bool isEmpty(Polygon poly);

/*
 * Print true on the terminal if the input Boolean value is true, false otherwise
 * b : (Bool) a boolean that we want to print the value on the terminal
 * Return : Nothing
 */
void isTrue(Bool b);

/*
 * 
 * pt1 : (Point) 
 * pt2 : (Point) 
 * pt3 : (Point) 
 * pt4 : (Point) 
 * 
 */
Point intersectionStraights(Point pt1, Point pt2, Point pt3, Point pt4);

/*
 * Check if the point belongs to the rectangle formed by it's diagonal (formed by the two points)
 * pt1 : (Point) an extremum of the segment
 * pt2 : (Point) the other extremum of the segment
 * pt : (Point) the point belonging to the straights and we want to know if he is in the segment
 * Return : (Bool) true if the point pt is inside the segment, false otherwise
 */
Bool pointBelongsToS(Point pt1, Point pt2, Point pt);

/*
 * Compute the norm between two specified points
 * p1 : (Point) 
 * p2 : (Point) 
 * Result : (double) the value of the norm (>0)
 */
double normPoints(Point p1, Point p2);

Point replacePoints(Point p1, Point p2); /* ????????? */

/*
 * Print the value of a Status value on the terminal
 * stat : (Status) the input status we want to print the value
 * Return : Nothing
 */
void printStatus(Status stat);

/*
 * Fint if the point pt is a vertex of the polygon
 * poly : (Polygon) the input polygon we are going to check
 * pt : (Point) the point we want to know if he is a vertex or not
 * Return a Boolean value, true if the point is a vertex, false otherwise
 */
Bool pointBelongsToPoly(Polygon poly, Point pt);

/*
 * Free each point in a polygon
 * poly : (Polygon) the polygon we want to free
 * return the empty polygon
 */
Polygon freePolygon(Polygon poly);

/*
 * Create a new polygon with the same points as the input one
 * poly : (Polygon) the polygon we want to copy
 * Return : A new polygon with the same points as the input one
 */
Polygon copyPolygon(Polygon poly);

/*
 * Copy the input polygon poly1 and add the intersection points in a new polygon
 * poly1 : (Polygon) the input polygon we are going to copy and add new points
 * poly2 : (Polygon) the polygon we will check to know if there are intersection between its edges and the ones of poly1
 * Return : a new polygon with the new points of poly1 and the intersection between poly1 and poly2
 */
Polygon addIntersectionPoints(Polygon poly1, Polygon poly2);

/*
 * Find the point as p in a polygon, return a pointer on this element if it exists, NULL otherwise
 * poly2 : the input polygon, were we 
 * p : (Point) the point 
 * Return : (Elt*) a pointer on an element
 */
Elt *findSamePoint(Polygon poly2, Point p);

/*
 * Create a new polygon with the same shape as the input one but with a different size and position
 * poly : (Polygon) the polygon we want to transform
 * Return : A new polygon that can easely be printed on the terminal
 */
Polygon adjustPolygon(Polygon poly);

Polygon sortByAngle(Polygon poly);

double anglePoints(Point A, Point B, Point C);

EltList *addPolyList(PolyList *list);

/* Menu functions */

Polygon *selectPolygon(PolyList *list);

Point selectPoint();

int selectRank(Polygon);

Bool pressEnter();

void emptyBuff();





