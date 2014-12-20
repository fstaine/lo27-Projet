
#include <polygon.h>

Point createPoint(float x, float y) /* Must change to double precision */
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
{
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

Polygon removePoint(Polygon poly, int place)
{
	int i;
	Elt *toFree = NULL;
	if(place == 0 || poly.size == 0)
	{
		return poly;
	}
	else if (poly.size == 1)
	{
		poly.head = NULL;
		poly.size = 0;
		free(poly.head);
	}
	else
	{
		toFree = poly.head;
		if(place>0)
		{
			place %= poly.size;
			if(place != 0)
				for(i=1;i<place;i++)
				{
					toFree = toFree->next;
				}
		}
		else
		{
			place %= poly.size;
			if(place == 0)
			{
				toFree = toFree->prev;
			}
			else
			{
				for(i=0;i<-place;i++)
				{
					toFree = toFree->prev;
				}
			}
		}
	}
	toFree->next->prev = toFree->prev;
	toFree->prev->next = toFree->next;
	free(toFree);
	return poly;
}
/*
Bool containsPolygon(const Polygon poly, Point p)
{
	Elt *start, *end;
	Point p1, p2;
	start = poly.head;
	end = poly.head->next;
	do
	{
		p1 = start->value;
		p2 = end->value;
		// Calucul du vecteur normal DANS LA BONNE DIRECTION (vers le centre)
		// Regarder si le point est du mauvais coté vecteur normal
		// 	Arrèt du process
		// Sinon
		// 	Continue le process
	}
	while(start != poly.head);
}
*/


Bool containsPoint(const Polygon poly, Point p)
{
	int i;
	float a,b,xIntersect;
	/*Vector v;*/
	Elt *start,*stop;
	Bool contains;
	
	contains = false;
	
	start = poly.head;
	for(i=0;i<poly.size;i++)
	{
		stop = start->next;
		a = (stop->value.y - start->value.y) / (stop->value.x - start->value.x);
		b = stop->value.y - a*start->value.x;
		xIntersect = (p.x - b)/a;
		printf("xIntersect = %f\n",xIntersect);
		if(xIntersect > min(start->value.x,stop->value.x) && xIntersect < max(start->value.x,stop->value.x)/* && xIntersect > p.x && !equals(stop->value.x, start->value.x)*/)
		{/* les demi-droite et segments se coisent */
			printf("Test : contains\n");
			contains = !contains;
		}
		start = start->next;
	}
	return contains;
}

/*
Polygon convexhull(Polygon poly)
{
	
}*/

char *toString(Polygon poly)
{
	int i;
	char *str,*strsave;
	Elt *elt;
	if((str = (char *) malloc(sizeof(char)*(20*poly.size) + 2)) == NULL) /* Mem pour la chaine */
	{
		return str;
	}
	else
	{
		strsave = str;
		str += sprintf(str,"[");
		elt = poly.head;
		if(isEmpty(poly))
		{
			sprintf(str,"[]");
			return str;
		}
		for(i=0;i<poly.size-1;i++)
		{
			str += sprintf(str,"[%f,%f],",(float)elt->value.x,(float)elt->value.y) -1;/* /!\ double precision */
			elt = elt->next;
		}
		str += sprintf(str, "[%f,%f]]",(float)elt->value.x,(float)elt->value.y) -1;
		return strsave;
	}
}

/* Not asked functions */

/*
Bool isConvexPoints(Polygon poly, Elt *elem)
{
	if(elem == NULL || elem.prev == elem.next)
		return true;
	else
	{
		
		* Si le milieu entre prev et next est du coté opposé à la normale
		 * Alors le polygone n'est pas convexe en ce point => return TRUE
		 * Sinon, il est convexe => return FALSE
		 
	}
}

*/



float min(float a, float b)
{
	if(a<b)
		return a;
	else
		return b;
}


float max(float a, float b)
{
	if(a>b)
		return a;
	else
		return b;
}



Bool  equals(float a, float b)
{
	float eps;
	eps = 0.001;
	if( a-eps < b && b < a+eps)
		return true;
	else
		return false;
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


