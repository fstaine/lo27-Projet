#include <polygon.h>

#define TEST

#define REVERSE printf("\033[7m")
#define NORMAL printf("\033[0m")
#define POS(X,Y) printf("\033[%d;%dH",X,Y)



#ifdef TEST
int main(int argc, char *argv[])
{
	char *str;
	Polygon poly;
	poly = createPolygon();
	poly = addPoint(poly, createPoint(-1,-1));
	poly = addPoint(poly, createPoint(-1,1));
	poly = addPoint(poly, createPoint(1,1));
	poly = addPoint(poly, createPoint(1,-1));
	str = toString(poly);
	printf("%s\n",str);
	isTrue(containsPoint(poly,createPoint(0.9,0.9)));
	return 0;
}
#else

int main (int argc, char *argv[])
{
	char str[50];
	puts("##############################################################");
	puts("# Welcome in the main programm to test the polygon.h Library #");
	puts("##############################################################");
	return 0;
}
#endif

