#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct struElement {
	char vorname[40];
	char nachname[40];
	int jahrgang;
	struElement* pNext;
} struElement;

struElement* create(int amount) {
	struElement* pStart = NULL;
	struElement* pLast = NULL;

	for (int i = 0; i < amount; i++) {
		struElement* pNew = (struElement*)malloc(sizeof(struElement)); // malloc == new
		pNew->pNext = NULL;
		strcpy_s(pNew->vorname, "A");
		strcpy_s(pNew->nachname, "B");
		pNew->jahrgang = 1925;
		if (pStart == NULL) pStart = pNew;
		if (pLast != NULL) pLast->pNext = pNew;
		pLast = pNew;
	}

	return pStart;
}



void main() {
	struElement* pStart = create(5);
	system("pause");
}