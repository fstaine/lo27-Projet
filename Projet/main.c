#include <polygon.h>
#include <string.h>

//#define TEST

#define REVERSE printf("\033[7m")
#define NORMAL printf("\033[0m")
#define POS(X,Y) printf("\033[%d;%dH",X,Y)
#define CLEAR() printf("\033[2J\033[0;0H")


#ifdef TEST
int main(int argc, char *argv[])
{
	char *str;
	Polygon poly;
	poly = createPolygon();
	poly = addPoint(poly, createPoint(-1,-1));
	poly = addPoint(poly, createPoint(-1,1));
	str = toString(poly);
	printf("%s\n",str);
	return 0;
}
#else

int main (int argc, char *argv[])
{
	Polygon poly;
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
		puts("Press 'q'to quit");
		scanf("%s",str);
		if(!strcmp(str,"1"))
		{
			printf("\nAdding a new point :\n");
			printf("Enter x,y : ");
			scanf("%f,%f",&x,&y);
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
			isTrue(containsPoint(poly, createPoint(x,y)));
		}
	}
	return 0;
}
#endif

