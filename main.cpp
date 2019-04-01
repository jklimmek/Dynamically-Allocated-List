// Listy dynamiczne.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "func.h"
#include "global.h"
#include <time.h>
#include <memory.h>
#include <stdlib.h>

#define CNTRL	//wydruki kontrolne

void showList(ListItem* pList);
int compare(const void* p, const void* q);

int main()
{
	srand((unsigned int)time(NULL));

	ListItem* myList = createList();
	if (!myList) {
		perror("nie udalo sie stworzyc listy\n");
		return 1;
	}

	//insert front
	for (int i = 0; i < 3; i++) {
		LISTINFO* info = (LISTINFO*)calloc(1, sizeof(LISTINFO));
		if (!info) {
			perror("nie mozna zaalokowac pamieci\n");
			return 1;
		}
		info->nKey = rand() % 10;
		insertFront(myList, info);
	}

#ifdef CNTRL
	showList(myList);
	printf("\n\n");
#endif // CNTRL

	//insert after
	ListItem* insertObj = myList->pNext;
	LISTINFO* insertInfo = (LISTINFO*)calloc(1, sizeof(LISTINFO));
	insertInfo->nKey = 12;
	insertAfter(insertObj, insertInfo);

#ifdef CNTRL
	showList(myList);
	printf("\n\n");
#endif // CNTRL

	//head
	printf("poczatek listy: %d\n\n", front(myList)->pInfo->nKey);

	//remove 
	remove(myList->pNext->pNext);	//usuwanie trzeciego el listy
#ifdef CNTRL
	showList(myList);
	printf("\n\n");
#endif // CNTRL


	freeList(myList);
	myList = NULL;
    return 0;
}

int compare(const void* p, const void* q) { //dowolny typ
	if (((LISTINFO*)p)->nKey > ((LISTINFO*)q)->nKey)
		return 0;
	if (((LISTINFO*)p)->nKey < ((LISTINFO*)q)->nKey)
		return -1;
	return 1;
}

void showList(ListItem* pList) {
	if (isEmpty(pList)) {
		printf("lista jest pusta\n");
		return;
	}
	ListItem* pointer = pList->pNext; //pierwszy el pusty
	int iterator = 1;
	while (pointer != NULL) {
		printf("pozycja: %d, wartosc: %d\n", iterator, pointer->pInfo->nKey);
		iterator++;
		pointer = pointer->pNext;
	}
}
