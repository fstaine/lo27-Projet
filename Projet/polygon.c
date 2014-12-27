
#include <polygon.h>

Point createPoint(double x, double y) /* Must change to double precision */
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
		elem = poly.head;
		if(place == 1)
		{
			poly.head = poly.head->next;
		}
		else if(place>0)
		{
			for(i=1;i<place;i++)
			{
				elem = elem->next;
			}
		}
		else if(place<0)
		{
			elem = elem->prev;
			for(i=1;i<-place;i++)
			{
				elem = elem->prev;
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
	{/* On ne veut pas de poly séparés pour l'instant !*/
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
	printf("Intersect :\n%s\n\n",toString(intersect));
	elem1 = findSamePoint(cpy1, intersect.head->value);
	/* Commencer sur une intersection */
	unionpoly = createPolygon();
	do
	{
		printf("\nDébut de la boucle\n");
		if(!pointBelongsToPoly(intersect, elem1->value))
		{/* si il n'y a pas d'intersection */
			printf("Pas d'intersection\n");
			unionpoly = addPoint(unionpoly, elem1->value);
			printf("unionpoly : %s\n",toString(unionpoly));
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
			printf("Intersection en vue !\n");
			unionpoly = addPoint(unionpoly, elem1->value);
			printf("unionpoly : %s\n",toString(unionpoly));
			/* Retrouver le point dans l'autre poly */
			elem1 = findSamePoint(cpy2, elem1->value);
			polyswap = cpy1;
			cpy1 = cpy2;
			cpy2 = polyswap;
			if(containsPoint(cpy2,elem1->next->value) || pointBelongsToPoly(intersect, elem1->next->value))
			{/* Si le point suiant est dans l'autre poly ou si c'est une intersection */
				printf("Prendre le précédent\n");
				elem1 = elem1->prev;
			}
			else
			{
				printf("Prendre le suivant\n");
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
	{/* Faire des copies !! */
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
	//printf("cpy1 : \n%s\n\n", toString(cpy1));

	cpy2 = addIntersectionPoints(poly2, poly1);
	//printf("cpy2 : \n%s\n\n", toString(cpy2));

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
	//printf("Intersect :\n%s\n\n",toString(intersect));
	elem1 = findSamePoint(cpy1, intersect.head->value);
	printf("%f, %f\n",elem1->value.x, elem1->value.y);
	intersectionpoly = createPolygon();
	do
	{
		printf("\nDébut de la boucle\n");
		if(!pointBelongsToPoly(intersect, elem1->value))
		{/* si il n'y a pas d'intersection */
			printf("Pas d'intersection\n");
			intersectionpoly = addPoint(intersectionpoly, elem1->value);
			printf("intersectionpoly : %s\n",toString(intersectionpoly));
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
			printf("Intersection en vue !\n");
			intersectionpoly = addPoint(intersectionpoly, elem1->value);
			printf("intersectionpoly : %s\n",toString(intersectionpoly));
			/* Retrouver le point dans l'autre poly */
			elem1 = findSamePoint(cpy2, elem1->value);
			polyswap = cpy1;
			cpy1 = cpy2;
			cpy2 = polyswap;
			printf("poly.size = %d\n", cpy1.size);
			if(containsPoint(cpy1,elem1->next->value))
			{/* Si le suivant est dehors */
				printf("Prendre le précédent\n");
				elem1 = elem1->prev;
			}
			else
			{
				printf("Prendre le suivant\n");
				elem1 = elem1->next;
			}
		}
		printf("NextPoint.x = %f, NextPoint.y = %f\n", elem1->value.x, elem1->value.y);
		getchar();
	}
	while(!equalsPoints(intersectionpoly.head->value, elem1->value));
	return intersectionpoly;
}

Polygon intersectionPolygons(Polygon p1, Polygon p2);

Polygon exclusiveORPolygons(Polygon p1, Polygon p2);

Polygon differencePolygons(Polygon p1, Polygon p2);



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
			enclosing = false; /* enclosing ?*/
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
			for(j=0;j<poly2.size;j++)
			{
				el2 = poly2.head;
				intersect = intersectionStraights(el1->value, el1->next->value, el2->value,el2->next->value);/* intersection semgent */
				if(pointBelongsToS(el1->value, el1->next->value, intersect) && pointBelongsToS(el2->value, el2->next->value, intersect))
				{/* Si il y a un point d'intersection dans les segments */
					outside = false;
				}
				else
				{
					el2 = el2->next;
				}
			}
			el1 = el1->next;
		}
	}
	if(equals)
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
		}}
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
		angle = -angle;
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
	return poly;	
}

Polygon convexHullPolygon(Polygon poly)/* marche pas si on a un polygone croisée ou un vraiment tordu :'( */
{
	int i;
	Point mid;
	Elt *elem;
	elem = poly.head;
	Polygon convex;
	convex = createPolygon();
	Bool ok;
	elem = poly.head;
	for(i=0;i<poly.size;i++)
	{
		convex = addPoint(convex, elem->value);
		elem = elem->next;
	}
	do
	{
		ok = true;
		elem = convex.head;
		for(i=0;i<convex.size;i++)
		{
			mid.x = (elem->value.x + elem->next->next->value.x)/2;
			mid.y = (elem->value.y + elem->next->next->value.y)/2;

			if(!containsPoint(convex, mid))
			{
				convex = removePoint(convex, i+2);
				ok = false;
			}
			elem = elem->next;
		}
	}
	while(ok == false);
	return convex;
}

void printPoint(Point p)
{
	POS(p.x,p.y*2);
	printf("*");
}

/*
 * Print a polygon with the same shape as poly on the terminal
 * poly : The input polygon we want to print
 */
void printPolygon(Polygon poly)
{
	int line, col,i,j;
	Point p,p2;
	Polygon newpoly;
	if(isEmpty(poly))
	{
		return;
	}
	newpoly = ajustPolygon(poly);
	/* Finding the number of line - Collums : */
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	line = w.ws_row;
	col = w.ws_col;
	CLEAR();
	for(i=0;i<line;i++)
	{
		for(j=0;j<2*col;j++)
		{
			if(containsPoint(newpoly,(p=createPoint(j+0.1,i+0.1))))
			{
				p2.x = p.y;
				p2.y = p.x;
				printPoint(p2);
			}
		}
	}
	POS(line,0);
	printf("Press <enter> to quit");
	getchar();
	CLEAR();
	newpoly = freePolygon(newpoly);
}

char *toString(Polygon poly)
{
	int i;
	char *str,*strsave;
	Elt *elt;
	if((str = (char *) malloc(sizeof(char)*(20*poly.size) + 2)) == NULL) /* Mem pour la chaine */
	{
		fprintf(stderr, "Allocation error, not enough space in memory !\n");
		return str;
	}
	else
	{
		if(isEmpty(poly))
		{
			sprintf(str, "[]");
			return str;
		}
		else
		{
			strsave = str;
			str += sprintf(str,"[");
			elt = poly.head;
			for(i=0;i<poly.size-1;i++)
			{
				str += sprintf(str,"[%f,%f],",elt->value.x,elt->value.y);
				elt = elt->next;
			}
			str += sprintf(str, "[%f,%f]]",elt->value.x,elt->value.y) -1;
			return strsave;
		}
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
	eps = 0.001;
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
	if(b==true)
		printf("True\n");
	else
		printf("False\n");
}

Point intersectionStraights(Point pt1, Point pt2, Point pt3, Point pt4)
{
	double a,b,c,d;
	Point Temp;
	/*creation of the straights in function of the points*/
	if (pt1.x!=pt2.x)
	{
		a=(pt1.y-pt2.y)/(pt1.x-pt2.x);
		b=pt1.y-a*pt1.x;
	}
	if (pt3.x!=pt4.x)
	{
		c=(pt3.y-pt4.y)/(pt3.x-pt4.x);
		d=pt3.y-c*pt3.x;
	}

	if(equals(a,c) && equals(b,d))//Cas droites confondues
	{
		Temp.x=NAN;
		Temp.y=NAN;
	}
	else if(equals(a,c))// Cas droites parallèles uniquement
	{
		Temp.x=INFINITY;
		Temp.y=INFINITY;
	}
	else if (equals(pt1.x, pt2.x)) // Cas d'une droite verticale
	{
		if(c!=0)
		{
			Temp.x=pt1.x;
			Temp.y=(pt1.x-pt3.x)*c+pt3.y;
		}
		else //Cas d'une droite verticale + horizontale
		{
			Temp.x=pt1.x;
			Temp.y=pt4.y;
		}
	}
	else if (equals(pt3.x, pt4.x))// Cas inverse
	{
		if(a!=0)
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
	else // Cas général
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

Polygon copyPolygon(Polygon poly)
{
	int i;
	Elt *elem;
	Polygon newpoly;
	newpoly = createPolygon();
	elem = poly.head;
	for(i=0;i<poly.size;i++)
	{
		newpoly = addPoint(newpoly, elem->value);
		elem = elem->next;
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

					nbintersect ++; //nb intersect = nombre d'interesections pas encores rentrées
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
	Elt *elem;
	elem = poly2.head;
	while(!equalsPoints(elem->value, p))
	{
		elem = elem->next;
	}
	return elem;
}

Polygon ajustPolygon(Polygon poly)
{
	int i, col, line;
	Point minp, maxp, size, scale;
	Elt *elem;
	Polygon newpoly;
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
	return newpoly;
}



