#define _CRT_SECURE_NO_WARNINGS
#include "ex1_q1.h"
typedef struct
{
	struct Node* head;
	struct Node* tail;
}listOfPoly;

lluint mask = 0x00ff;
struct polygon* CreatePolygon(char kindOfPoly);
void addVerticles(struct polygon* poly);
char extractCordinate(lluint* pBuffer);
fillTheRest(struct polygon* poly);
struct Node* creatNode(struct polygon* poly);
void addToEndOfList(struct polygon* poly, listOfPoly* lst);
void printPolyons(char *input, int size, listOfPoly* lst);
void printChosenOption(char* input, enum WHOM_TO_OUTPUT whomToPrint, listOfPoly* lst);
void printPoly(char* input, struct Node* currentNode);
printVerticles(enum POLY_TYPE poly_type, struct polygon* poly);
int calcNumOfVerticles(enum POLY_TYPE poly_type);
void calculateAndPrintPerimeter(enum POLY_TYPE poly_type, struct polygon* poly);
void calculateAndPrintArea(enum POLY_TYPE poly_type, struct polygon* poly);
void freeList(listOfPoly* lst);



void main()
{
	char hasFinished = 0;
	char input[7];
	struct polygon* poly;
	listOfPoly lst;
	lst.head = lst.tail = NULL;
	int size;
	while (1)
	{
		scanf("%s", &input);
		size = strlen(input);
		if (input[0] == 'N')
		{
			poly = CreatePolygon(input[1]);
			addToEndOfList(poly, &lst);
		}
		else if (input[0] == 'L')
		{
			hasFinished = 1;
		}

		printPolyons(input, size, &lst);

		if (hasFinished)
		{
			break;
		}
	}

	freeList(&lst);
}


struct polygon* CreatePolygon(char kindOfPoly)
{
	struct polygon* poly;
	poly = (struct polygon*)malloc(sizeof(struct polygon));
	switch (kindOfPoly)
	{
	case 'Q':
		poly->poly_type = QUADRI;
		break;
	case 'H':
		poly->poly_type = HEXAGON;
		break;
	case 'O':
		poly->poly_type = OCTAGON;
		break;
	}

	addVerticles(poly);

	return poly;
}

void addVerticles(struct polygon* poly)
{
	char i,x,y;
	lluint buffer;
	scanf("%llx", &buffer);
	for(i = 0; i < 4; i++)
	{
	x = extractCordinate(&buffer);
	y = extractCordinate(&buffer);
	poly->vertices[i].x = (int) x;
	poly->vertices[i].y = (int) y;;
	}

	if (poly->poly_type != QUADRI)
	{
		fillTheRest(poly);
	}
}

char extractCordinate(lluint* pBuffer)
{
	char x;
	x = mask & *pBuffer;
	*pBuffer=*pBuffer >> 8;
	return x;
}

fillTheRest(struct polygon* poly)
{
	char i, x, y;
	int numOfVerticels = 8;
	lluint buffer;
	scanf("%llx", &buffer);
	if (poly->poly_type == HEXAGON)
	{
		numOfVerticels = 6;
	}
	for(i=4; i < numOfVerticels; i++)
	{
		x = extractCordinate(&buffer);
		y = extractCordinate(&buffer);
		poly->vertices[i].x =(int) x;
		poly->vertices[i].y = (int)y;;
	}
}

struct Node* creatNode(struct polygon* poly)
{
	struct Node* node;
	node = (struct Node*)malloc(sizeof(struct Node));
	node->poly = poly;
	node->next = NULL;
	return node;
}

void addToEndOfList(struct polygon* poly, listOfPoly* lst)
{
	struct Node* node = creatNode(poly);
	if (lst->head == NULL)
	{
		lst->head = lst->tail = node;
	}
	else 
	{		
		lst->tail->next = node;
		lst->tail = node;
	}
}


void printPolyons(char *input,int size, listOfPoly* lst)
{
	char commands[10];
	int j = 0;
	enum WHOM_TO_OUTPUT whomToPrint =  NONE;
	for (int i = 0; i < size; i++)
	{
		if (input[i] != 'N' && input[i] != 'L' &&input[i] != 'O' && input[i] != 'H' && input[i] != 'Q')
		{
			switch (input[i])
			{
			case 'A':
				whomToPrint = ALL_POLY;
				break;
			case 'C':
				whomToPrint = CURRENT;
			default:
				commands[j++] = input[i];
				break;
			}
		}
	}

	commands[j] ='\0';
	printChosenOption(commands, whomToPrint,lst);
}

void printChosenOption(char* input, enum WHOM_TO_OUTPUT whomToPrint, listOfPoly* lst)
{
	if (whomToPrint != NONE)
	{
		if (whomToPrint == CURRENT)
		{
			printPoly(input, lst->tail);
		}
		else 
		{
			struct Node* tmp = lst->head;

			while (tmp != NULL)
			{
				printPoly( input, tmp);
				tmp = tmp->next;
			}
		}
	}
}

void printPoly(char* input , struct Node* currentNode)
{
	char* nameOfPoly;
	int i = 0;
	while (input[i]!='\0')
	{
		switch (input[i])
		{
		case 'd':
			nameOfPoly = (char*)malloc(15);
			print_polygon_name(currentNode->poly->poly_type, nameOfPoly);
			printf("%s ", nameOfPoly);
			free(nameOfPoly);
			printVerticles(currentNode->poly->poly_type, currentNode->poly);
				break;
		case 'p':
			calculateAndPrintPerimeter(currentNode->poly->poly_type,currentNode->poly);
			break;
		case 'a':
			calculateAndPrintArea(currentNode->poly->poly_type, currentNode->poly);
		default:
			break;
		}
		
		i++;
	}
}

printVerticles(enum POLY_TYPE poly_type,struct polygon* poly)
{
	int numOfVert = calcNumOfVerticles(poly_type);
	
	for (int i = 0; i < numOfVert; i++)
	{
		print_point(poly->vertices[i]);
	}

	printf("\n");
}

int calcNumOfVerticles(enum POLY_TYPE poly_type)
{
	int numOfVert;
	switch (poly_type)
	{
	case OCTAGON:
		numOfVert = 8;
		break;
	case HEXAGON:
		numOfVert = 6;
		break;
	default:
		numOfVert = 4;
	}
	return numOfVert;
}

void calculateAndPrintPerimeter(enum POLY_TYPE poly_type, struct polygon* poly)
{
	int numOfVert = calcNumOfVerticles(poly_type);
	double perimeter = 0;
	for (int i = 0; i < numOfVert; i++)
	{
		if (i != numOfVert - 1)
		{
			perimeter+=calc_side(poly->vertices[i], poly->vertices[i + 1]);
		}
		else
		{
			perimeter += calc_side(poly->vertices[i], poly->vertices[0]);
		}
	}
	printf("perimeter = %.1lf\n", perimeter);
}

void calculateAndPrintArea(enum POLY_TYPE poly_type, struct polygon* poly)
{
	double area = calc_triangle_area(poly->vertices[0], poly->vertices[1], poly->vertices[2]);
	area += calc_triangle_area(poly->vertices[0], poly->vertices[2], poly->vertices[3]);

	if (poly_type != QUADRI)
	{
		area += calc_triangle_area(poly->vertices[0], poly->vertices[3], poly->vertices[4]);
		area += calc_triangle_area(poly->vertices[0], poly->vertices[4], poly->vertices[5]);
	}
	if (poly_type == OCTAGON)
	{
		area += calc_triangle_area(poly->vertices[0], poly->vertices[5], poly->vertices[6]);
		area += calc_triangle_area(poly->vertices[0], poly->vertices[6], poly->vertices[7]);
	}

	printf("area = %.1lf\n", area);
}

void freeList(listOfPoly* lst)
{
	struct Node* tmp = lst->head;
	struct Node* next;
	while (tmp != NULL)
	{
		free(tmp->poly);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}