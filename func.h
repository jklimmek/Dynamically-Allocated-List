#pragma once
#include "global.h"

typedef struct tagListItem
{
	LISTINFO* pInfo;		//wsk do str w global.h
	tagListItem* pNext;
} ListItem;

ListItem* createList();
ListItem* front(ListItem* pList);
ListItem* find(ListItem* pList, const void* searchingFor, ListItem** pPrev, int(__cdecl* compare)(const void* p, const void* q));
void insertAfter(ListItem* pAfter, LISTINFO* pInfo);
void insertFront(ListItem* pList, LISTINFO* pInfo);
void remove(ListItem* pAfter);
void removeFront(ListItem* pList);
void freeList(ListItem* pList);
void sortList(ListItem* pList, int(__cdecl* compare)(const void* p, const void* q));
int isEmpty(ListItem* pList);


