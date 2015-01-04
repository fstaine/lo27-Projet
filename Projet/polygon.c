#include <polygon.h>

Point createPoint(double x, double y)
{
	Point pt;
	pt.x = x;
	pt.y = y;
	return pt;
}

Polygon createPolygon()
{	
	Polygon poly;
	poly.size = 0;
	poly.head = NULL;
	return poly;
}

Polygon addPoint(Polygon poly, Point p)
{/* Insert tail */
	Elt *elem;
	elem = NULL;
	if((elem = (Elt *) malloc(sizeof(Elt))) == NULL)
		return poly;
	poly.size++;
	elem->value.x = p.x;
	elem->value.y = p.y;
	if(poly.head == NULL)
	{
		poly.head = elem->next = elem->prev = elem;
	}
	else
	{
		elem->prev = poly.head->prev;
		elem->next = poly.head;
		poly.head->prev->next = elem;
		poly.head->prev = elem;
	}
	return poly;
}

Polygon removePoint(Polygon poly, int place)/* Problem with removePoint */
{
	if(isEmpty(poly) || place == 0)
	{
		return poly;
	}
	else if(poly.size == 1)
	{
		free(poly.head);
		poly.head = NULL;
		poly.size = 0;
	}
	else
	{
		int i;
		Elt *elem;
		if(place>0)
		{
			place %= poly.size;
			if(place == 1)
			{
				elem = poly.head;
				poly.head = poly.head->next;
			}
			else
			{
			elem = poly.head->prev;
			for(i=0;i<place;i++)
			{
				elem = elem->next;
			}
			}
		}
		else if(place<0)
		{
			place%= place;
			if(place == 0)
			{
				elem = poly.head;
				poly.head = poly.head->next;
			}
			else
			{
			elem = poly.head;
			for(i=0;i>place;i--)
			{
				elem = elem->prev;
			}
			}
		}
		elem->next->prev = elem->prev;
		elem->prev->next = elem->next;
		free(elem);
		poly.size--;
	}
	return poly;
}

Polygon unionPolygons(Polygon poly1, Polygon poly2)
{
	int i;
	Status status;
	Elt *elem1;
	Polygon unionpoly, cpy1, cpy2, intersect, polyswap;

	if(isEmpty(poly1))
	{/* Faire des copies !! */
		return copyPolygon(poly2);
	}
	else if(isEmpty(poly2))
	{
		return copyPolygon(poly1);
	}
	status = containsPolygon(poly1, poly2);
	if(status == OUTSIDE)
	{/* On ne veut pas de poly séparés pour l'instant ! */
		exit(EXIT_FAILURE);
	}
	else if(status == EQUAL)
	{
		return copyPolygon(poly1);
	}
	else if(status == INSIDE)
	{
		return copyPolygon(poly1);
	}
	else if(status == ENCLOSING)
	{
		return copyPolygon(poly2);
	}
	/* Ajout des points d'intersections entre les deux polygones dans les deux polygones*/
	cpy1 = addIntersectionPoints(poly1, poly2);
	cpy2 = addIntersectionPoints(poly2, poly1);
	elem1 = cpy1.head;
	intersect = createPolygon();
	for(i=0;i<cpy1.size;i++)
	{/* Création du polygon avec les intersections */
		if(pointBelongsToPoly(cpy2, elem1->value))
		{
			intersect = addPoint(intersect, elem1->value);
		}
		elem1 = elem1->next;
	}
	elem1 = findSamePoint(cpy1, intersect.head->value);
	/* Commencer sur une intersection */
	unionpoly = createPolygon();
	do
	{
		if(!pointBelongsToPoly(intersect, elem1->value))
		{/* si il n'y a pas d'intersection */
			if(pointBelongsToPoly(unionpoly,  elem1->next->value) && !equalsPoints(unionpoly.head->value, elem1->next->value))
			{
				elem1 = elem1->prev;
			}
			else
			{
				elem1 = elem1->next;
			}
		}
		else
		{
			unionpoly = addPoint(unionpoly, elem1->value);
			/* Retrouver le point dans l'autre poly */
			elem1 = findSamePoint(cpy2, elem1->value);
			polyswap = cpy1;
			cpy1 = cpy2;
			cpy2 = polyswap;
			if(containsPoint(cpy2,elem1->next->value) || pointBelongsToPoly(intersect, elem1->next->value))
			{/* Si le point suiant est dans l'autre poly ou si c'est une intersection */
				elem1 = elem1->prev;
			}
			else
			{
				elem1 = elem1->next;
			}
		}
	}
	while(!equalsPoints(unionpoly.head->value, elem1->value));
	return unionpoly;
}

Polygon intersectionPolygons(Polygon poly1, Polygon poly2)
{
	int i;
	Status status;
	Elt *elem1;
	Polygon intersectionpoly, cpy1, cpy2, intersect, polyswap;

	if(isEmpty(poly1))
	{
		return copyPolygon(poly1);
	}
	else if(isEmpty(poly2))
	{
		return copyPolygon(poly2);
	}
	status = containsPolygon(poly1, poly2);
	if(status == OUTSIDE)
	{
		return createPolygon();
	}
	else if(status == EQUAL)
	{
		return copyPolygon(poly1);
	}
	else if(status == INSIDE)
	{
		return copyPolygon(poly2);
	}
	else if(status == ENCLOSING)
	{
		return copyPolygon(poly1);
	}
	cpy1 = addIntersectionPoints(poly1, poly2);
	cpy2 = addIntersectionPoints(poly2, poly1);
	elem1 = cpy1.head;
	intersect = createPolygon();
	for(i=0;i<cpy1.size;i++)
	{/* Création du polygon avec les intersections */

		if(pointBelongsToPoly(cpy2, elem1->value))
		{
			intersect = addPoint(intersect, elem1->value);
		}
		elem1 = elem1->next;
	}
	elem1 = findSamePoint(cpy1, intersect.head->value);
	printf("%f, %f\n",elem1->value.x, elem1->value.y);
	intersectionpoly = createPolygon();
	do
	{
		if(!pointBelongsToPoly(intersect, elem1->value))
		{/* si il n'y a pas d'intersection */
			intersectionpoly = addPoint(intersectionpoly, elem1->value);
			if(pointBelongsToPoly(intersectionpoly,  elem1->next->value))
			{
				elem1 = elem1->prev;
			}
			else
			{
				elem1 = elem1->next;
			}
		}
		else
		{
			intersectionpoly = addPoint(intersectionpoly, elem1->value);
			/* Retrouver le point dans l'autre poly */
			elem1 = findSamePoint(cpy2, elem1->value);
			polyswap = cpy1;
			cpy1 = cpy2;
			cpy2 = polyswap;
			if(containsPoint(cpy1,elem1->next->value))
			{/* Si le suivant est dehors */
				elem1 = elem1->prev;
			}
			else
			{
				elem1 = elem1->next;
			}
		}
		getchar();
	}
	while(!equalsPoints(intersectionpoly.head->value, elem1->value));
	return intersectionpoly;
}

PolyList exclusiveORPolygons(Polygon p1, Polygon p2)
{
	PolyList list, end;
	end = list = NULL;
	list = differencePolygons(p1,p2);
	end = list;
	if(end != NULL)
	{
		while(end->next != NULL)
		{
			end = end->next;
		}
	}
	end->next = differencePolygons(p2,p1);
	return list;
}

PolyList  differencePolygons(Polygon poly1, Polygon poly2)
{
	int i;
	Status status;
	Elt *elem1;
	Polygon cpy1, cpy2, intersect;
	EltList *elemlist;
	PolyList list;
	list = NULL;
	if(isEmpty(poly1) || isEmpty(poly2))
	{/* CREATE LINKED LIST OF THESE POLYGONS */
		elemlist = addPolyList(&list);
		elemlist->poly = copyPolygon(poly1);
		return elemlist;
	}
	status = containsPolygon(poly1, poly2);
	if(status == OUTSIDE)
	{
		elemlist = addPolyList(&list);
		elemlist->poly = copyPolygon(poly1);
		return elemlist;
	}
	else if(status == EQUAL)
	{
		elemlist = addPolyList(&list);
		elemlist->poly = createPolygon();
		return elemlist;
	}
	else if(status == INSIDE)
	{/* It should create a hole, but we return the initial polygon */
		elemlist = addPolyList(&list);
		elemlist->poly = copyPolygon(poly1);
		return elemlist;
	}
	else if(status == ENCLOSING)
	{
		elemlist = addPolyList(&list);
		elemlist->poly = createPolygon();
		return elemlist;
	}
	cpy1 = addIntersectionPoints(poly1, poly2);
	cpy2 = addIntersectionPoints(poly2, poly1);
	elem1 = cpy1.head;
	intersect = createPolygon();
	for(i=0;i<cpy1.size;i++)
	{/* Création du polygon avec les intersections */
		if(pointBelongsToPoly(cpy2, elem1->value))
		{
			intersect = addPoint(intersect, elem1->value);
		}
		elem1 = elem1->next;
	}
	elem1 = cpy1.head;
	elem1 = findSamePoint(cpy2, intersect.head->value);
	/* La liste est vide */
	for(i=0;i<intersect.size/2;i++)
	{
		/* Ajouter un elem à la liste */
		elemlist = addPolyList(&list);
		elemlist->poly = addPoint(elemlist->poly, elem1->value);
		if(!containsPoint(poly1, createPoint(elem1->value.x+0.1*(elem1->next->value.x-elem1->value.x), elem1->value.y+0.1*(elem1->next->value.y-elem1->value.y))))
		{
			elem1 = elem1->prev;
			while(!pointBelongsToPoly(intersect, elem1->value))
			{
				elemlist->poly = addPoint(elemlist->poly, elem1->value);
				elem1 = elem1->prev;
			}
		}
		else
		{
			elem1 = elem1->next;
			while(!pointBelongsToPoly(intersect, elem1->value))
			{
				elemlist->poly = addPoint(elemlist->poly, elem1->value);
				elem1 = elem1->next;
			}
		}
		{/* Marche surement */
			elem1 = findSamePoint(cpy1, elem1->value);
			while(!equalsPoints(elem1->value, elemlist->poly.head->value))
			{
				elemlist->poly = addPoint(elemlist->poly, elem1->value);
				elem1 = elem1->next;
			}
		}
		elem1 = findSamePoint(cpy2, findSamePoint(intersect, elem1->value)->next->next->value);
	}
	return list;
}


/* Add a new polygon to the list and return a pointer on the new element */
EltList *addPolyList(PolyList *list)
{
	EltList *elem;
	elem = (EltList *) malloc(sizeof(EltList));
	if(elem != NULL)
	{/* Inerst head */
		elem->poly = createPolygon();
		elem->next = *list;
		*list = elem;
		return elem;
	}
	else
	{
		fprintf(stderr, "Allocation error");
		exit(EXIT_FAILURE);
	}
}

Bool containsPoint(const Polygon poly, Point p)
{
	int i;
	double a,b,xIntersect;
	Elt *start,*stop;
	Bool contains;
	if(isEmpty(poly))
	{
		return false;
	}
	else
	{
		contains = false;
		start = poly.head;
		for(i=0;i<poly.size;i++)
		{/* For each segment in the polygon : */
			stop = start->next;
			if(equals(p.x,start->value.x) && equals(p.y, start->value.y))
			{/* If the point p equals a point of the polygon, return true */
				return true;
			}
			else if(equals(start->value.x,stop->value.x))
			{/* if the segment is vertical  */
				if(!equals(start->value.y,stop->value.y) && p.x<start->value.x && p.y<max(start->value.y, stop->value.y) && p.y>min(start->value.y,stop->value.y))
				{/*if the point p is on the left of the segment, and the intersection between the horizontal line passing by p and the line passing py the segment is inside the segment ... */
					contains = !contains;
				}
			}
			else
			{
				a = (stop->value.y - start->value.y) / (stop->value.x - start->value.x);
				b = start->value.y - a*start->value.x; 
				xIntersect = (p.y - b)/a;
				if((xIntersect > min(start->value.x,stop->value.x) && xIntersect < max(start->value.x,stop->value.x) && xIntersect > p.x && !equals(stop->value.x, start->value.x) && !equals(xIntersect, min(start->value.x, stop->value.x)) && !equals(xIntersect, max(start->value.x, stop->value.x))) || (xIntersect > p.x && equals(xIntersect, start->value.x)))
				{/* les demi-droite et segments se coisent */
					contains = !contains;
				}
			}
			start = start->next;
		}
		return contains;
	}
}



Status containsPolygon(Polygon poly1, Polygon poly2)
{
	int i,j;
	Elt *el1, *el2;
	Bool inside, outside, enclosing, equals;
	Point intersect;

	if(isEmpty(poly1) && isEmpty(poly2))/* Particular cases */
	{
		return EQUAL;
	}
	else if(isEmpty(poly1))
	{
		return ENCLOSING;
	}
	else if(isEmpty(poly2))
	{
		return INSIDE;
	}
	inside = outside = enclosing = equals = true;
	el1 = poly1.head;
	el2 = poly2.head;
	for(i=0;i<poly1.size;i++)
	{
		if(containsPoint(poly1, el2->value))
		{/* Si le point el2 € ploy1 */
			outside = false;

		}
		else
		{/* Si le point el2 !€ ploy1 */
			inside = false;
			equals = false;
		}
		el2 = el2->next;
	}
	for(i=0;i<poly2.size;i++)
	{
		if(!containsPoint(poly2, el1->value))
		{/* Si le point el1 !€ ploy2 */
			enclosing = false;
			equals = false;
		}
		el1 = el1->next;
	}
	if(outside)
	{/* Test si vraiment outside */
		el1 = poly1.head;
		el2 = poly2.head;
		for(i=0;i<poly1.size;i++)
		{
			el2 = poly2.head;
			for(j=0;j<poly2.size;j++)
			{

				intersect = intersectionStraights(el1->value, el1->next->value, el2->value,el2->next->value);
				if(pointBelongsToS(el1->value, el1->next->value, intersect) && pointBelongsToS(el2->value, el2->next->value, intersect))
				{/* Si il y a un point d'intersection dans les segments */
					outside = false;
					goto end;/* We can imediately stop the process */
				}
				else
				{
					el2 = el2->next;
				}
			}
			el1 = el1->next;
		}
	}
	end:if(equals)
	{/* test si vraiment equals */
		if(poly1.size != poly2.size)
		{
			equals = false;
		}
		else
		{
			el2 = poly2.head;
			for(i=0;i<poly1.size;i++)
			{/* Cherche un point de concordace */
				if(!equalsPoints(poly1.head->value, el2->value))
				{
					el2 = el2->next;	
				}
			}
			if(equalsPoints(el2->value, poly1.head->value))
			{/* Si il y a bien un point de concordance */
				if(equalsPoints(el2->next->value, poly1.head->next->value))
				{/* Si les deux tournent dans le même sens */
					el2 = el2->next;
					el1 = poly1.head->next;
					i=0;
					while(i<poly1.size-1 && equals)
					{
						if(equalsPoints(el2->value, el1->value))
						{
							i++;
							el1 = el1->next;
							el2 = el2->next;
						}
						else
						{
							equals = false;
						}
					}
				}
				else if (equalsPoints(el2->prev->value, poly1.head->next->value))
				{/* Si les deux tournent dans un sens différent */
					el2 = el2->prev;
					el1 = poly1.head->next;
					i=0;
					while(i<poly1.size-1 && equals)
					{
						if(equalsPoints(el2->value, el1->value))
						{
							i++;
							el1 = el1->next;
							el2 = el2->prev;
						}
						else
						{
							equals = false;
						}
					}
				}
				else
				{
					equals = false;
				}
			}
			else
			{
				equals = false;
			}
		}
	}
	/* valeur de retour */
	if(equals)
	{
		return EQUAL;
	}
	else if(enclosing)
	{
		return ENCLOSING;
	}
	else if(inside)
	{
		return INSIDE;
	}
	else if(outside)
	{
		return OUTSIDE;
	}
	else
	{
		return INTERSECT;
	}
}

Polygon centralSymmetry(Polygon poly, Point pt)/*****************/
{
	int i;
	Elt *elem;
	if(!isEmpty(poly))
	{
		elem = poly.head;
		for(i=0;i<poly.size;i++)
		{
			elem->value.x = 2*pt.x - elem->value.x;
			elem->value.y = 2*pt.y - elem->value.y;
			elem = elem->next;
		}
	}
	return poly;
}

Polygon rotatePolygon(Polygon poly, Point pt, double angle)/***********/
{
	double x;
	int i;
	Elt*Temp;
	if(!isEmpty(poly))
	{
		Temp=poly.head;
		angle = -angle;/* counterclockwise */
		for(i=1;i<=poly.size;i++)
		{
			x=cos(angle)*(Temp->value.x-pt.x)-sin(angle)*(Temp->value.y-pt.y)+pt.x;
			Temp->value.y=sin(angle)*(Temp->value.x-pt.x)+cos(angle)*(Temp->value.y-pt.y)+pt.y;
			Temp->value.x=x;
			Temp=Temp->next;
		}
	}
	return poly;
}

Polygon scalePolygon(Polygon poly, double factor)
{
	int i;
	Elt*Temp;
	if(!isEmpty(poly))
	{
		Temp=poly.head;
		for(i=1;i<=poly.size;i++)
		{
			Temp->value.x=Temp->value.x*factor;
			Temp->value.y=Temp->value.y*factor;
			Temp=Temp->next;
		}
	}
	return poly;
}

Polygon translatePolygon (Polygon poly, Point pt1, Point pt2)
{
	if(!isEmpty(poly))
	{
		double x,y;
		int i;

		x=pt2.x-pt1.x;
		y=pt2.y-pt1.y;
		Elt*Temp;
		Temp=poly.head;
		for(i=1;i<=poly.size;i++)
		{
			Temp->value.x=Temp->value.x+x;
			Temp->value.y=Temp->value.y+y;
			Temp=Temp->next;
		}
	}
	return poly;
}

Polygon convexHullPolygon(Polygon poly)
{
	int i;
	double res;
	Polygon newpoly;
	Elt *elem;
	if(poly.size <= 3)/* already convex */
	{
		return copyPolygon(poly);
	}
	else
	{
		i = 1;
		newpoly = sortByAngle(poly); /* Create the new polygon with the good order */
		elem = newpoly.head;
		do
		{
			i++;
			res = (elem->next->value.x - elem->value.x)*(elem->next->next->value.y - elem->value.y) - (elem->next->value.y - elem->value.y)*(elem->next->next->value.x - elem->value.x);
			if(res <= 0)
			{
				newpoly = removePoint(newpoly, i);
			}
			elem = elem->next;
		}
		while(elem != newpoly.head);
	}
	return newpoly;
}


/********************************/
void printPoint(Point p)
{
	printf("[%f,%f]",p.x,p.y);
}

void printPolygon(Polygon poly)
{
	char *str;
	str = toString(poly);
	puts(str);
	free(str);
}


void drawPoint(Point p)
{
	POS(p.x,p.y*2);
	printf("*");
}

/*
 * Print a polygon with the same shape as poly on the terminal
 * poly : The input polygon we want to print
 */
void drawPolygon(Polygon poly)
{
	int line, col,i,j;
	Point p,p2;
	struct winsize w;
	if(isEmpty(poly))
	{
		return;
	}
	/* Finding the number of line - Collums : */
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	line = w.ws_row;
	col = w.ws_col;
	CLEAR();
	for(i=0;i<line;i++)
	{
		for(j=0;j<2*col;j++)
		{
			if(containsPoint(poly,(p=createPoint(j+0.1,i+0.1))))
			{
				p2.x = p.y;
				p2.y = p.x;
				drawPoint(p2);
			}
		}
	}
	POS(line,0);
	printf("Press <enter> to quit");
	getchar();
	CLEAR();
}

char *toString(Polygon poly)
{
	int i;
	char *str,*strsave;
	Elt *elt;
	if(isEmpty(poly))
	{
		str = (char *) malloc(sizeof(char)*3);
		sprintf(str, "[]");
		return str;
	}
	if((str = (char *) malloc(sizeof(char)*(30*poly.size) + 2)) == NULL) /* Memory for the string, 30char : be sure we have enough */
	{
		fprintf(stderr, "Allocation error, not enough space in memory !\n");
		return str;
	}
	else
	{
		strsave = str;
		str += sprintf(str,"[");
		elt = poly.head;
		for(i=0;i<poly.size-1;i++)
		{
			str += sprintf(str,"[%g,%g],",elt->value.x,elt->value.y);
			elt = elt->next;
		}
		str += sprintf(str, "[%g,%g]]",elt->value.x,elt->value.y) -1;
		return strsave;
	}
}

/* Not asked functions */

double min(double a, double b)
{
	if(a<b)
		return a;
	else
		return b;
}


double max(double a, double b)
{
	if(a>b)
		return a;
	else
		return b;
}


Bool  equals(double a, double b)
{
	double eps;
	eps = 0.0001;
	if( a-eps < b && b < a+eps)
		return true;
	else
		return false;
}

Bool equalsPoints(Point a, Point b)
{
	if(equals(a.x,b.x) && equals(a.y,b.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}


Bool isEmpty(Polygon poly)
{
	if(poly.size == 0)
		return true;
	else
		return false;
}

void isTrue(Bool b)
{
	if(b)
		printf("True\n");
	else
		printf("False\n");
}

Point intersectionStraights(Point pt1, Point pt2, Point pt3, Point pt4)
{
	double a,b,c,d;
	Point Temp;
	/*creation of the straights in function of the points*/
	if (!equals(pt1.x, pt2.x))
	{
		a=(pt1.y-pt2.y)/(pt1.x-pt2.x);
		b=pt1.y-a*pt1.x;
	}
	else
	{
		a = INFINITY;
		b = NAN;
	}
	if (!equals(pt3.x, pt4.x))
	{
		c=(pt3.y-pt4.y)/(pt3.x-pt4.x);
		d=pt3.y-c*pt3.x;
	}
	else
	{
		c = INFINITY;
		d = NAN;
	}
	if(equals(a,c) && equals(b,d))/* Cas droites confondues */
	{
		Temp.x=NAN;
		Temp.y=NAN;
	}

	else if (equals(pt1.x, pt2.x)) /* Cas d'une droite verticale */
	{
		if(!equals(c, 0))
		{
			Temp.x=pt1.x;
			Temp.y=(pt1.x-pt3.x)*c+pt3.y;
		}
		else /* Cas d'une droite verticale + horizontale */
		{
			Temp.x=pt1.x;
			Temp.y=pt4.y;
		}
	}
	else if (equals(pt3.x, pt4.x))/* Cas inverse */
	{
		if(!equals(a, 0))
		{
			Temp.x=pt3.x;
			Temp.y=(pt3.x-pt1.x)*a+pt1.y;
		}
		else
		{
			Temp.x=pt3.x;
			Temp.y=pt2.y;
		}
	}
	else if(equals(a,c))/* Cas droites parallèles uniquement */
	{
		Temp.x=INFINITY;
		Temp.y=INFINITY;
	}
	else /* Cas général */
	{
		Temp.x=(d-b)/(a-c);
		Temp.y=a*Temp.x+b;
	}
	return Temp;
}

double normPoints(Point p1, Point p2)
{
	return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}

Bool pointBelongsToS(Point pt1, Point pt2, Point pt)
{
	if (pt.x <= max(pt1.x,pt2.x) && pt.x >= min(pt1.x,pt2.x) && pt.y <= max(pt1.y,pt2.y) && pt.y >= min(pt1.y,pt2.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void printStatus(Status stat)
{
	switch(stat)
	{
		case INSIDE : printf("Inside\n");break;
		case OUTSIDE : printf("Outside\n");break;
		case INTERSECT : printf("Intersect\n");break;
		case ENCLOSING : printf("Enclosing\n");break;
		default : printf("Equals\n");
	}
}

Bool pointBelongsToPoly(Polygon poly, Point pt)
{
	int i;
	Elt *elem;
	if(isEmpty(poly))
	{
		return false;
	}
	else
	{
		elem = poly.head;
		for(i=0;i<poly.size;i++)
		{
			if(equalsPoints(elem->value, pt))
			{
				return true;
			}
			elem = elem->next;
		}
		return false;
	}
}

Polygon copyPolygon(Polygon poly)
{
	int i;
	Elt *elem;
	Polygon newpoly;
	newpoly = createPolygon();
	if(!isEmpty(poly))
	{
		elem = poly.head;
		for(i=0;i<poly.size;i++)
		{
			newpoly = addPoint(newpoly, elem->value);
			elem = elem->next;
		}
	}
	return newpoly;
}

Polygon freePolygon(Polygon poly)
{
	while(!isEmpty(poly))
	{
		poly = removePoint(poly, 1);
	}
	return poly;
}

Polygon addIntersectionPoints(Polygon poly1, Polygon poly2)
{
	int i,j,nbintersect;
	double norm, newnorm;
	Elt *elem1, *elem2;
	Polygon res;
	Point closer, intersect;
	if(isEmpty(poly1) && isEmpty(poly2))
	{
		return poly1;
	}
	elem1 = poly1.head;
	res = createPolygon();
	res = addPoint(res, createPoint(elem1->value.x, elem1->value.y));
	for(i=0;i<poly1.size;i++)
	{
		do
		{
			nbintersect = 0;
			norm = -1;
			closer.x = NAN;
			elem2 = poly2.head;
			for(j=0;j<poly2.size;j++)
			{
				intersect = intersectionStraights(elem1->value, elem1->next->value, elem2->value, elem2->next->value);
				newnorm = normPoints(elem1->value, intersect);
				if(pointBelongsToS(elem1->value, elem1->next->value, intersect) && pointBelongsToS(elem2->value, elem2->next->value, intersect) && (norm < 0 || newnorm < norm) && !pointBelongsToPoly(res, intersect))
				{
					nbintersect ++; /* nb intersect = nombre d'interesections pas encores rentrées */
					if(!pointBelongsToPoly(res, intersect))
					{
						norm = newnorm;
						closer = intersect;
					}

				}
				elem2 = elem2->next;
			}
			if(norm == -1)
			{/* si pas d'intersection */
				elem1 = elem1->next;
				res = addPoint(res, elem1->value);
			}
			else
			{
				res = addPoint(res, closer);
			}
		}
		while(nbintersect > 0);
	}
	res = removePoint(res, -1);
	return res;
}


Elt *findSamePoint(Polygon poly2, Point p)
{
	int i;
	Elt *elem;
	if(isEmpty(poly2))
	{
		return NULL;
	}
	else
	{
		elem = poly2.head;
		for(i=0;i<poly2.size;i++)
		{
			if(equalsPoints(elem->value, p))
				return elem;
			else
				elem = elem->next;
		}
		return NULL;
	}
}

Polygon adjustPolygon(Polygon poly)
{
	int i, col, line;
	Point minp, maxp, size, scale;
	Elt *elem;
	Polygon newpoly;
	if(!isEmpty(poly))
	{
		elem = poly.head;
		minp.x = maxp.x = minp.y = maxp.y = elem->value.x;
		for(i=0;i<poly.size;i++)
		{/* Trouve les min et max */
			elem = elem->next;
			minp.x = min(minp.x, elem->value.x);
			maxp.x = max(maxp.x, elem->value.x);
			minp.y = min(minp.y, elem->value.x);
			maxp.y = max(maxp.y, elem->value.x);
		}
		size.x = maxp.x - minp.x;
		size.y = maxp.y - minp.y;
		/* Find the size of the terminal */
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		line = w.ws_row-2;
		col = (w.ws_col-2)/2;
		scale.x = col/size.x;
		scale.y = line/size.y;
		newpoly = copyPolygon(poly);
		newpoly = scalePolygon(newpoly, min(scale.x, scale.y));
		newpoly = translatePolygon(newpoly,  createPoint(min(scale.x,scale.y)*minp.x, min(scale.x,scale.y)*minp.y), createPoint(1,1));
	}
	return newpoly;
}

Polygon sortByAngle(Polygon poly)
{
	int i,j;
	double angle,prevangle, minangle;
	Point P, P2;
	Elt *elem, *start, *nextelem;
	Polygon newpoly;
	/* Find the point with the lower y */
	start = poly.head;
	elem = poly.head->next;
	for(i=1;i<poly.size;i++)
	{
		if(elem->value.y < start->value.y || (equals(elem->value.y, start->value.y) && elem->value.x < start->value.x))
			start = elem;
		elem = elem->next;
	}
	/* start is now on the point with the lower x between them with the lower y */
	/* Sort by angle */
	P = start->value;
	P2 = createPoint(P.x+1, P.y);
	prevangle = -1;
	newpoly = createPolygon();
	newpoly = addPoint(newpoly, P);
	for(i=1;i<poly.size;i++)
	{/* Tant qu'il reste encore des points à trouver */
		elem = start->next;
		minangle = 4;
		for(j=1;j<poly.size;j++)
		{/* Trouver celui qui a l'angle minimum */
			angle = anglePoints(elem->value, P, P2);
			if(angle < minangle && angle > prevangle )
			{
				minangle = angle;
				nextelem = elem;
			}
			elem =elem->next;
		}
		prevangle = minangle;
		newpoly = addPoint(newpoly, nextelem->value);
	}
	return newpoly;
}

/*
 * Compute the angle ABC, the value returned is between [0, PI]
 * A : (Point) The starting Point
 * B : (Point) The middle Point
 * C : (Point) The ending Point
 * Result (Double) The angle between ABC between 0 an PI
 */
double anglePoints(Point A, Point B, Point C)
{
	double a, b, c;
	a = normPoints(C,B);
	b = normPoints(A,B);
	c = normPoints(A,C);
	return acos((a*a + b*b - c*c) / (2*a*b));
}





/* Menu functions */

Polygon *selectPolygon(PolyList *list)
{
	char str[50],*error;
	int i,select;
	EltList *elem;
	elem = *list;
	i = 0;
	printf("0 - Create a new polygon\n");
	while(elem != NULL)
	{
		i++;
		if(elem->poly.size == 0)
			printf("%d - poly%d\tsize = 0\t[]\n",i,i);
		else if(elem->poly.size == 1)
			printf("%d - poly%d\tsize = 1\t[[%f,%f]]\n",i,i,elem->poly.head->value.x,elem->poly.head->value.y);
		else if(elem->poly.size == 2)
			printf("%d - poly%d\tsize = 2\t[[%f,%f],[%f,%f]]\n",i,i,elem->poly.head->value.x,elem->poly.head->value.y,elem->poly.head->next->value.x,elem->poly.head->next->value.y);
		else if(elem->poly.size == 3)
			printf("%d - poly%d\tsize = 3\t[[%f,%f],[%f,%f],[%f,%f]]\n",i,i,elem->poly.head->value.x,elem->poly.head->value.y,elem->poly.head->next->value.x,elem->poly.head->next->value.y,elem->poly.head->prev->value.x,elem->poly.head->prev->value.y);
		else
			printf("%d - poly%d\tsize = %d\t[[%f,%f],[%f,%f],[...],[%f,%f]]\n",i,i,elem->poly.size,elem->poly.head->value.x,elem->poly.head->value.y,elem->poly.head->next->value.x,elem->poly.head->next->value.y,elem->poly.head->prev->value.x,elem->poly.head->prev->value.y);
		elem=elem->next;
	}
	printf("Press 'q' to quit\n");
	scanf("%s",str);
	getchar();
	if(!strcmp(str,"q"))
	{
		return NULL;
	}
	select = strtol(str, &error, 10);
	if(*error != '\0')
	{
		puts("Error in the input, select another polygon");
		return selectPolygon(list);
	}
	else if(!select)
	{
		elem = (EltList *) malloc(sizeof(EltList));
		if(elem != NULL)
		{/* Inerst head */
			elem->poly = createPolygon();
			elem->next = *list;
			*list = elem;
			puts("Now this is the poly1");
			return &elem->poly;
		}
		else
		{
			fprintf(stderr, "Allocation error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		elem = *list;
		if(select > i || select < 0)
		{
			puts("This polygon isn't valid, select another one :");
			return selectPolygon(list);
		}
		for(i=1;i<select;i++)
		{
			elem = elem->next;
		}
		return &elem->poly;
	}
}

Point selectPoint()
{
	Point pt;
	do
	{
		puts("\nEnter your point :");
		printf("Enter the X coordinate : ");
		scanf("%lf",&(pt.x));
		emptyBuff();
		printf("Enter the Y coordinate : ");
		scanf("%lf",&pt.y);
		emptyBuff();
		printf("New point : [%f,%f]\n",pt.x,pt.y);
		printf("Press <enter> to continue, anything else to enter a new value\n");
	}
	while(!pressEnter());
	return pt;
}

Bool pressEnter()
{
	if(getchar() == '\n')
		return true;
	else
		emptyBuff();
	return false;
}

void emptyBuff()
{
	while(getchar() != '\n')
		;
}





