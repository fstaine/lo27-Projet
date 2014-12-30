#include <polygon.h>

//#define TEST

#define REVERSE printf("\033[7m")
#define NORMAL printf("\033[0m")

#ifdef TEST
int main(int argc, char *argv[])
{
	printf("test :%5d\n", 5);
	return 0;
}
#else /* Test undefined */

int main (int argc, char *argv[])
{
	double x;
	int i;
	char str[50], *str2;
	Bool b;
	Status status;
	Point pt,pt2;
	Polygon *poly,*poly1,*poly2;
	PolyList list;
	list = NULL;
	CLEAR();
	puts("################################################################");
	puts("#  Welcome in the main programm to test the polygon.h Library  #");
	puts("################################################################");
	while(strcmp(str,"q"))
	{
		puts("\nSelect an action :");
		puts("1  - Add a new point to a polygon");
		puts("2  - Remove a point from a polygon");
		puts("3  - Compute the union between two polygons");
		puts("4  - Compute the intersection between two polygons");
		puts("5  - Compute the exclusive OR between two polygons");
		puts("6  - Compute the difference between two polygons");
		puts("7  - Test if a point is inside the polygon");
		puts("8  - Returs the status of two polygons");
		puts("9  - Compute the central symmetry of a polygon");
		puts("10 - Compute the rotation of a polygon");
		puts("11 - Resize a poygon");
		puts("12 - Translate a polygon");
		puts("13 - Compute the convex hull of a polygon");
		puts("14 - Print a polygon on the terminal");
		puts("15 - print the string of the polygon");
		puts("Press 'q'to quit");
		scanf("%s",str);
		getchar();
		if(!strcmp(str,"1"))
		{/* Add a new point to a polygon */
			puts("Select the polygon were you want to add a point :");
			poly = selectPolygon(&list);
			if(poly == NULL)
				continue;
			pt = selectPoint();
			*poly = addPoint(*poly, pt);
			printf("New point [%f,%f] added to the polygon\n", pt.x, pt.y);
		}
		else if(!strcmp(str,"2"))
		{/* Remove a point from a polygon */
			puts("Select the polygon were you want to remove a point :");
			poly = selectPolygon(&list);
			if(poly == NULL)
				continue;
			if(isEmpty(*poly))
			{
				printf("The polygon is aleady empty !\n");
			}
			else
			{
				puts("Enter the index of the point you'd like to remove : ");
				scanf("%d", &i);
				*poly = removePoint(*poly, i);
				printf("%dth point removed from the polygon\n",i);
			}
		}
		else if(!strcmp(str,"3"))
		{/* Compute the union of two polygons */
			puts("Compute the union between two polygons :\nSelect the 1st input polygon");
			poly1 = selectPolygon(&list);
			if(poly1 == NULL)
				continue;
			puts("Select the second input polygon");
			poly2 = selectPolygon(&list);
			if(poly2 == NULL)
				continue;
			puts("Select the destination\nYou should select an empty polygon");
			poly = selectPolygon(&list);
			if(poly == NULL)
				continue;
			*poly = unionPolygons(*poly1, *poly2);
		}
		else if(!strcmp(str,"4"))
		{/* Compute the intersection of two polygons */
			puts("Compute the intersection between two polygons :\nSelect the 1st input polygon");
			poly1 = selectPolygon(&list);
			if(poly1 == NULL)
				continue;
			puts("Select the second input polygon");
			poly2 = selectPolygon(&list);
			if(poly2 == NULL)
				continue;
			puts("Select the destination\nYou should select an empty polyg");
			poly = selectPolygon(&list);
			if(poly == NULL)
				continue;
			*poly = intersectionPolygons(*poly1, *poly2);
		}
		else if(!strcmp(str,"5"))
		{/* Compute the exclusive OR of two polygons */
			puts("Compute the exclusive OR between two polygons :\nSelect the 1st input polygon\n");
			poly1 = selectPolygon(&list);
			if(poly1 == NULL)
				continue;
			puts("Select the second input polygon");
			poly2 = selectPolygon(&list);
			if(poly2 == NULL)
				continue;
			puts("Select the destination\nYou should select an empty polygon\n");
			poly = selectPolygon(&list);
			if(poly == NULL)
				continue;
			*poly = exclusiveORPolygons(*poly1, *poly2);
		}
		else if(!strcmp(str,"6"))
		{/* Compute the difference of two polygons */
			puts("Compute the difference between two polygons :\nSelect the 1st input polygon");
			poly1 = selectPolygon(&list);
			if(poly1 == NULL)
				continue;
			puts("Select the second input polygon");
			poly2 = selectPolygon(&list);
			if(poly2 == NULL)
				continue;
			puts("Select the destination\nYou should select an empty polygon");
			poly = selectPolygon(&list);
			if(poly == NULL)
				continue;
			*poly = differencePolygons(*poly1, *poly2);
		}
		else if(!strcmp(str,"7"))
		{/* Test if a point is inside the polygon */
			puts("Select the polygon");
			poly = selectPolygon(&list);
			if(poly == NULL)
				continue;
			puts("Select the point");
			pt = selectPoint();
			b = containsPoint(*poly, pt);
			if(b)
				printf("The point [%f,%f] is inside the polygon\n",pt.x,pt.y);
			else
				printf("The point [%f,%f] is outside the polygon\n",pt.x,pt.y);
		}
		else if(!strcmp(str,"8"))
		{/* Returs the status of two polygons */
			puts("Select the first polygon");
			poly1 = selectPolygon(&list);
			if(poly1 == NULL)
				continue;
			puts("Select the second polygon");
			poly2 = selectPolygon(&list);
			if(poly2 == NULL)
				continue;
			status = containsPolygon(*poly1, *poly2);
			printStatus(status);
		}
		else if(!strcmp(str,"9"))
		{/* Compute the central symmetry of a polygon */
			puts("Select the polygon you want to compute the central symmetery, he is going to be modified");
			poly = selectPolygon(&list);
			if(poly == NULL)
				continue;
			puts("Select the center of the symmetery");
			pt = selectPoint();
			*poly = centralSymmetry(*poly, pt);
		}
		else if(!strcmp(str,"10"))
		{/* Compute the rotation of a polygon */
			puts("Select the polygon you want to compute the central symmetery, he is going to be modified");
			poly = selectPolygon(&list);
			if(poly == NULL)
				continue;
			puts("Sel!ct the center of the rotation");
			pt = selectPoint();
			puts("Select the angle (in radians) : ");
			scanf("%lf", &x);
			*poly = rotatePolygon(*poly, pt, x);
		}
		else if(!strcmp(str,"11"))
		{/* Resize a poygon */
			puts("Select the polygon you want to resize, he is going to be modified");
			poly = selectPolygon(&list);
			if(poly == NULL)
				continue;
			printf("Select the factor : ");
			scanf("%lf", &x);
			*poly = scalePolygon(*poly, x);
		}
		else if(!strcmp(str,"12"))
		{/* Translate a polygon */
			puts("Select the polygon you want to translate, he is going to be modified");
			poly = selectPolygon(&list);
			if(poly == NULL)
				continue;
			puts("Select the departure");
			pt = selectPoint();
			puts("Select the arrival");
			pt2 = selectPoint();
			*poly = translatePolygon(*poly, pt, pt2);
		}
		else if(!strcmp(str,"13"))
		{/* Compute the convex hull of a polygon */
			puts("Select the polygon you want to compute the conveh hull, he is going to be modified");
			poly = selectPolygon(&list);
			if(poly == NULL)
				continue;
			*poly = convexHullPolygon(*poly);
		}
		else if(!strcmp(str,"14"))
		{/* Print a polygon on the terminal */
			puts("Select the polygon you want to print on the terminal ");
			poly = selectPolygon(&list);
			if(poly == NULL)
				continue;
			printPolygon(*poly);

		}
		else if(!strcmp(str,"15"))
		{/* print the string of the polygon */
			puts("Select the polygon you'd like to extract the string");
			poly = selectPolygon(&list);
			if(poly == NULL)
				continue;
			str2 = toString(*poly);
			printf("Do you want to print it in the terminal ?(y/n) : ");
			scanf("%s",str);
			if(!strcmp(str, "y"))
				puts(str2);
			free(str2);
		}
	}
	return 0;
}
#endif












