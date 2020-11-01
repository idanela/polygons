#define _CRT_SECURE_NO_WARNINGS
#include "ex1_q1.h"

typedef struct
{
	struct Node* head;
	struct Node* tail;
}listOfPoly;

char mask = 0xff;
void addToEndOfList(struct polygon*, listOfPoly lst);

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
	int i,x,y;
	lluint buffer;
	scanf("%llx", &buffer);
	for(i=0; i < 4; i++)
	{
	x = extractCordinate(&buffer);
	y = extractCordinate(&buffer);
	poly->vertices[i].x = x;
	poly->vertices[i].y = y;;
	}

	if (poly->poly_type != QUADRI)
	{
		fillTheRest(poly);
	}
}

int extractCordinate(lluint* pBuffer)
{
	int x;
	x = mask & *pBuffer;
	*pBuffer = *pBuffer << 8;
	return x;
}

fillTheRest(struct polygon* poly)
{
	int i, x, y;
	int numOfVerticels = 8;
	lluint buffer;
	scanf("%llu", buffer);
	if (poly->poly_type = HEXAGON)
	{
		numOfVerticels = 6;
	}
	for(i=4; i < numOfVerticels; i++)
	{
		x = extractCordinate(&buffer);
		y = extractCordinate(&buffer);
		poly->vertices[i].x = x;
		poly->vertices[i].y = y;;
	}
}

struct Node* creatNode(struct polygon* poly)
{
	struct Node* node;
	node = (struct Node*)malloc(sizeof(struct Node));
	node->next = NULL;
	return node;
}

void addToEndOfList(struct polygon* poly, listOfPoly* lst)
{
	struct Node* node = creatNode(poly);
	if (lst->head = NULL)
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
	char input[10];
	int j = 0;
	enum WHOM_TO_OUTPUT whomToPrint =  NONE;
	for (int i = 0; i < size; i++)
	{
		if (input[i] != 'N' && input[i] != 'L')
		{
			switch (input[i])
			{
			case 'A':
				whomToPrint = ALL_POLY;
				break;
			case 'C':
				whomToPrint = CURRENT;
			default:
				input[j++] = input[i];
				break;
			}
		}
	}
	input[j] = NULL;
	printAccordingToFlags(input, whomToPrint,lst);
}

void printAccordingToFlags(char* input, enum WHOM_TO_OUTPUT whomToPrint, listOfPoly* lst)
{
	if (whomToPrint != NONE)
	{
		if (whomToPrint == CURRENT)
		{
			printpoly(input, lst->tail);
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
	while (input[i]!=NULL)
	{
		switch (input[i])
		{
		case 'd':
			print_polygon_name(currentNode->poly->poly_type, nameOfPoly);
			printVerticles(currentNode->poly->poly_type, currentNode->poly);
				break;
		case 'p':
			calculateAndPrintPerimeter(currentNode->poly->poly_type,currentNode->poly);
			break;
		case 'a':
			calculateArea(currentNode->poly->poly_type, currentNode->poly);
		default:
			break;
		}
	}
}

printVerticles(enum POLY_TYPE poly_type,struct polygon* poly)
{
	int numOfVert = calcNumOfVerticles(poly_type);
	
	for (int i = 0; i < numOfVert; i++)
	{
		print_point(poly->vertices[i]);
	}
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
	prinf("perimeter = %lf\n", perimeter);
}