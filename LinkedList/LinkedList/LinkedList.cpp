#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

typedef struct Person {
	char vorname[40];
	char nachname[40];
	int jahrgang;
	struct Person* pNext;
} struPerson;

char randomName() {
	return rand() % 26 + 'A';
}

int randomYear() {
	return 1900 + (rand() % 119);
}

struPerson* create(int amount) {
	struPerson* pStart = NULL;
	struPerson* pLast = NULL;

	for (int i = 0; i < amount; i++) {
		struPerson* pNew = (struPerson*)malloc(sizeof(struPerson)); // malloc == new
		pNew->pNext = NULL;
		pNew->vorname[0] = randomName();
		pNew->vorname[1] = '\0';
		pNew->nachname[0] = randomName();
		pNew->nachname[1] = '\0';
		pNew->jahrgang = randomYear();
		if (pStart == NULL) pStart = pNew;
		if (pLast != NULL) pLast->pNext = pNew;
		pLast = pNew;
	}
	return pStart;
}

void printList(struPerson* pStart) {
	for (struPerson* pOutput = pStart; pOutput != NULL; pOutput = pOutput->pNext) {
		printf("Vorname: %c\nNachname: %c\nJahrgang: %d\n", pOutput->vorname[0], pOutput->nachname[0], pOutput->jahrgang);
	}
}

void main() {
	srand((unsigned)time(NULL));
	struPerson* pStart = create(5);
	printList(pStart);
	system("pause");
}