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
	for(i=0; i<4; i++)
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
	char printAll = 0;
	char printArea = 0;
	char printShapeAndVerticles = 0;
	char printPerimeter = 0;
	for (int i = 0; i < size; i++)
	{
		if (input[i] != 'N' && input[i] != 'L')
		{
			switch (input[i])
			{
			case 'a':
			default:
				break;
			}
		}
	}
}
