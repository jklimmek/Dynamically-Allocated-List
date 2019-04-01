#include "func.h"
#include "global.h"
#include <memory.h>
#include <stdlib.h>


ListItem* createList() {
	ListItem* item = (ListItem*)calloc(1, sizeof(ListItem));
	LISTINFO* info = (LISTINFO*)calloc(1, sizeof(ListItem));
	info->nKey = NULL;
	item->pNext = NULL;
	item->pInfo = info;
	return item;
}

void insertAfter(ListItem* pAfter, LISTINFO* pInfo) {
	ListItem* newItem = (ListItem*)calloc(1, sizeof(ListItem));
	if (!newItem) {
		perror("nie udalo sie zaalokowac pamieci\n");
		return;
	}
	newItem->pInfo = pInfo;		
	newItem->pNext = pAfter->pNext;		//nowy el wskazuje na to na co wskazywal pAfter
	pAfter->pNext = newItem;		//pAfter wskazuje na nowy el
}

void insertFront(ListItem* pList, LISTINFO* pInfo) {
	insertAfter(pList, pInfo);
}

void remove(ListItem* pAfter) {
	if (isEmpty(pAfter)) {
		perror("lista jest pusta\n");
		return;
	}
	ListItem* pointer = pAfter->pNext;
	pAfter->pNext = pointer->pNext;
	free(pointer);
}

void removeFront(ListItem* pList) {
	remove(pList);
}

int isEmpty(ListItem* pList) {
	return !(pList->pNext);
}

ListItem* front(ListItem* pList) {
	if (isEmpty(pList)) {
		perror("lista jest pusta\n");
		return NULL;
	}
	return pList->pNext;
}

void freeList(ListItem* pList) {
	while (isEmpty(pList) == 0)
		removeFront(pList);
}

ListItem* find(ListItem* pList, const void* searchingFor, ListItem** pPrev, int(__cdecl* compare)(const void* p, const void* q)) {

	ListItem* pointer = pList->pNext;
	*pPrev = pList;
	while (pointer != NULL) {
		if (!compare(pointer->pInfo, searchingFor))
			return pointer;
		*pPrev = pointer;
		pointer = pointer->pNext;
	}
	//*pPrev ;
	return *pPrev = NULL;
}

void sortList(ListItem* pList, int(__cdecl* compare)(const void* p, const void* q)) {
	
	ListItem* beginning = pList;	//poczatek listy
	while (beginning->pNext != NULL) { 

		ListItem* min = beginning;	// pierwszy el jest najmniejszy
		ListItem* pointer = beginning->pNext;

		while (pointer->pNext != NULL) {
			if (compare(pointer->pNext->pInfo, min->pNext->pInfo) == -1)	//porownanie wartosci 
				min = pointer;
			pointer = pointer->pNext;
		}
		if (min != beginning) {	//przemieszczenie najmniejszego el na poczatek
			ListItem* temp = min->pNext->pNext;
			min->pNext->pNext = beginning->pNext;
			beginning->pNext = min->pNext;
			min->pNext = temp;	
		}
		beginning = beginning->pNext;	//sortowanie od nastepnego el
	}
}