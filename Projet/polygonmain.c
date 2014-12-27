#include <polygon.h>

//#define TEST

#define REVERSE printf("\033[7m")
#define NORMAL printf("\033[0m")

#ifdef TEST
int main(int argc, char *argv[])
{
	
	return 0;
}
#else /* Test undefined */

int main (int argc, char *argv[])
{
	float x,y;
	int i;
	char str[50],*str2;
	Point pt;
	Polygon polytab[10];
	for(i=0;i<10;i++)
	{
		polytab = createPolygon();
	}
	CLEAR();
	puts("##############################################################");
	puts("#                                                            #");
	puts("# Welcome in the main programm to test the polygon.h Library #");
	puts("#                                                            #");
	puts("##############################################################");
	while(strcmp(str,"q"))
	{
		puts("\nSelect an action :");
		puts("1\t- Add a new point to the polygon");
		puts("2\t- Remove a point from a polygon");
		puts("5\t- Compute the union of two polygons");
		puts("6\t- Compute the intersection of two polygons");
		puts("7\t- Compute the exclusive OR of two polygons");
		puts("8\t- Compute the difference of two polygons");
		puts("9\t- Test if a point is inside the polygon");
		puts("10\t- Returs the status of two polygons");
		puts("11\t- Compute the central symmetry of a polygon");
		puts("12\t- Compute the rotation of a polygon");
		puts("13\t- Resize a poygon");
		puts("14\t- Translate a polygon");
		puts("15\t- Compute the convex hull of a polygon");
		puts("16\t- Print a polygon on the terminal");
		puts("17\t- print the string of the polygon");
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
		{/* Ecrire dans un fichier ou sur le terminal */

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
			;
		}
	}
	return 0;
}
#endif












