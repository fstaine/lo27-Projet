#include <polygon.h>
#include <string.h>
#include <math.h>

//#define TEST

#define REVERSE printf("\033[7m")
#define NORMAL printf("\033[0m")

#ifdef TEST
int main(int argc, char *argv[])
{
	Point p1,p2;
	p1.x = 1;
	p1.y = 2;
	p2.x = 3;
	p2.y = 4;
	p2 = p1;
	printf("%f, %f\n",p2.x,p2.y);
	return 0;
}
#else /* Test undefined */

int main (int argc, char *argv[])
{
	Polygon poly,poly1,poly2;
	float x,y;
	int i;
	char str[50],*str2;
	poly = createPolygon();
	CLEAR();
	puts("##############################################################");
	puts("# Welcome in the main programm to test the polygon.h Library #");
	puts("##############################################################");
	while(strcmp(str,"q"))
	{
		puts("\nSelect an action :");
		puts("1 - Add a new point to the polygon");
		puts("2 - Remove a point");
		puts("3 - print the polygon");
		puts("4 - Test if a point is inside the polygon");
		puts("5 - Print a polygon on the terminal");
		puts("6 - Translate polygon");
		puts("Press 'q'to quit");
		scanf("%s",str);
		getchar();
		if(!strcmp(str,"1"))
		{
			printf("\nAdding a new point :\n");
			printf("Enter x,y : ");
			scanf("%f,%f",&x,&y);
			getchar();
			poly = addPoint(poly, createPoint(x,y));
		}
		else if(!strcmp(str,"2"))
		{
			printf("\nRemoving a point : \n");
			printf("Which point do you want to delete :");
			scanf("%d", &i);
			poly = removePoint(poly, i);
		}
		else if(!strcmp(str,"3"))
		{
			str2 = toString(poly);
			printf("Printing the polygon :\n%s\n",str2);
		}
		else if(!strcmp(str,"4"))
		{

			printf("\nContains point :\n");
			printf("Enter x,y : ");
			scanf("%f,%f",&x,&y);
			getchar();
			isTrue(containsPoint(poly, createPoint(x,y)));
		}
		else if(!strcmp(str,"5"))
		{
			printPolygon(poly);
			CLEAR();
		}
		else if(!strcmp(str,"6"))
		{
			printf("Not yet ready !\n");
		}
		else if(!strcmp(str,"7"))
		{
			Status res;
			poly2 = createPolygon();
			poly2 = addPoint(poly2, createPoint(1.5,1.5));
			poly2 = addPoint(poly2, createPoint(4.5,1.5));
			poly2 = addPoint(poly2, createPoint(4.5,4.5));
			poly2 = addPoint(poly2, createPoint(1.5,4.5));
			
			poly1 = createPolygon();
			poly1 = addPoint(poly1, createPoint(3,1));
			poly1 = addPoint(poly1, createPoint(5,3));
			poly1 = addPoint(poly1, createPoint(3,5));
			poly1 = addPoint(poly1, createPoint(1,3));
			
			res = containsPolygon(poly2, poly1);
			printStatus(res);
		}
	}
	return 0;
}
#endif












