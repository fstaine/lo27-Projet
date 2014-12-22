
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



/* De post'it
Polygon unionPolygons (Polygon p1, Polygon p2)
{
	Status Temp;
	int i=0,j=0;
	if (isEmpty(p1) && isEmpty(p2))
    {
        return p1;
    }
    else if (isEmpty(p1))
        {
            return p2;
        }
        else if (isEmpty(p2))
            {
                return p1;
            }
            else
            {
				p=createPolygon();
				Temp=containsPolygon(p1,p2);
				if (Temp==OUTSIDE)
				{
					return p;
				}
				else if (Temp==INSIDE || Temp==EQUAL)
					{
						return p1;
					}
					else if(Temp==ENCLOSING)
						{
							return p2;
						}
						else
						{
							Elt* Pelem1,Pelem2;
							Pelem1=p1.head;
							Pelem2=p2.head;
							while(containsPoint(p2,Pelem1->value))
							{
								Pelem1=Pelem1->next;
							}
							addPoint(p,Pelem1->value);
							while(i!=p1.size)
							{
								i=i+1;
								Pelem1=Pelem1->next;
								while (j!=p2.size)
								{
									j=j+1;
									Pelem2=Pelem2->next;
									if(intersectionStraights(Pelem1->prev,Pelem1,Pelem2->prev,Pelem2)!=NAN
									


*/
Polygon intersectionPolygons(Polygon p1, Polygon p2);

Polygon exclusiveORPolygons(Polygon p1, Polygon p2);

Polygon differencePolygons(Polygon p1, Polygon p2);



Bool containsPoint(const Polygon poly, Point p)
{
	int i;
	float a,b,xIntersect;
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
				if(xIntersect >= min(start->value.x,stop->value.x) && xIntersect < max(start->value.x,stop->value.x) && xIntersect > p.x && !equals(stop->value.x, start->value.x))
				{/* les demi-droite et segments se coisent */
					contains = !contains;
				}
			}
			start = start->next;
		}
		return contains;
	}
}



Status containsPolygon(Polygon ref , Polygon poly);

Polygon centralSymetry(Polygon poly, Point p);

Polygon rotatePolygon(Polygon poly, Point p, float angle);

Polygon scalePolygon(Polygon poly, float factor);

Polygon translatePolygon(Polygon poly, Point start, Point stop);

Polygon convexHullPolygon(Polygon poly);

void printPoint(Point p)
{
	POS(p.x,p.y);
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
	
	/* Finding the number of line - Collums : */
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	line = w.ws_row;
	col = w.ws_col;
	CLEAR();
	for(i=0;i<line;i++)
	{
		for(j=0;j<col;j++)
		{
			if( containsPoint(poly,(p=createPoint(j+0.1,i+0.1))) )
			{
				p2.x = p.y;
				p2.y = p.x;
				printPoint(p2);
			}
		}
	}
	POS(line,0);
	getchar();
	CLEAR();
}

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
			str += sprintf(str,"[%f,%f],",(float)elt->value.x,(float)elt->value.y);/* /!\ double precision */
			elt = elt->next;
		}
		str += sprintf(str, "[%f,%f]]",(float)elt->value.x,(float)elt->value.y) -1;
		return strsave;
	}
}

/* Not asked functions */

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

Point intersectionStraights(Point pt1, Point pt2, Point pt3, Point pt4)
{
	float a,b,c,d;
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
	
	if( equals(a,c) && equals(b,d))//Cas droites confondues et parallèles
	{
		Temp.x=NAN;
		Temp.y=NAN;
	}
	else if (pt1.x==pt2.x) // Cas d'une droite verticale
	{
		if(c!=0)
		{
			Temp.x=pt1.x;
			Temp.y=(pt1.x-d)/c;
		}
		else //Cas d'une droite verticale + horizontale
		{
			Temp.x=pt1.x;
			Temp.y=pt4.y;
		}
	}
	else if (pt3.x==pt4.x)// Cas inverse
	{
		if(a!=0)
		{
			Temp.x=pt3.x;
			Temp.y=(pt3.x-b)/a;
		}
		else
		{
			Temp.x=pt3.x;
			Temp.y=pt2.y;
		}
	}
	else// Cas général
	{
		Temp.x=(d-b)/(a-c);
		Temp.y=a*Temp.x+b;
	}
	return Temp;
}