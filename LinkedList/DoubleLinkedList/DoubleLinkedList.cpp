#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

typedef struct Person {
	char firstname[40];
	char lastname[40];
	int year;
	struct Person* pNext;
	struct Person* pPrev;
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
		struPerson* pNew = (struPerson*)malloc(sizeof(struPerson));
		pNew->pNext = NULL;
		pNew->pPrev = NULL;
		pNew->firstname[0] = randomName();
		pNew->firstname[1] = '\0';
		pNew->lastname[0] = randomName();
		pNew->firstname[1] = '\0';
		pNew->year = randomYear();
		if (pStart == NULL) {
			pStart = pNew;
			pStart->pPrev = NULL;
			pLast = pStart;
		}
		else {
			pLast->pNext = pNew;
			pNew->pPrev = pLast;
			pLast = pNew;
		}
	}

	return pStart;
}

void deleteList(struPerson* pStart) {
	struPerson* pCurrentPerson = pStart;
	struPerson* pNextPerson;

	while (pCurrentPerson != NULL) {
		// pNextPerson zeigt auf nächstes Personenelement
		pNextPerson = pCurrentPerson->pNext;
		// momentanes Elements löschen
		free(pCurrentPerson);
		pCurrentPerson = pNextPerson;
	}
}

struPerson* deletePerson(struPerson* pStart, char firstname, char lastname) {
	struPerson* pCurrent = pStart;
	while (pCurrent != NULL) 
	{
		struPerson* pNext = pCurrent->pNext;

		if (firstname == pCurrent->firstname[0] && lastname == pCurrent->lastname[0])
		{
			if (pCurrent->pPrev == NULL)
			{
				pCurrent->pNext->pPrev = NULL;
				pStart = pCurrent->pNext;
				free(pCurrent);
			}
			else if (pCurrent->pNext == NULL)
			{
				pCurrent->pPrev->pNext = NULL;
				free(pCurrent);
			}
			else 
			{
				pCurrent->pPrev->pNext = pCurrent->pNext;
				pCurrent->pNext->pPrev = pCurrent->pPrev;
				free(pCurrent);
			}
		}

		pCurrent = pNext;
	}

	return pStart;
}

struPerson* swapWithNextElement(struPerson* pCurrent) {

	struPerson* pNext = pCurrent->pNext;
	struPerson* pPrevious = pCurrent->pPrev;

	// links for current node
	pCurrent->pNext = pCurrent->pNext->pNext;
	pCurrent->pPrev = pNext;

	// links for next node
	pNext->pNext = pCurrent;
	pNext->pPrev = pPrevious;

	//link for previous node
	if (pPrevious != NULL)
	{
		pPrevious->pNext = pNext;
	}

	return pCurrent;
}

struPerson* bubbleSort(struPerson* pStart) {
	struPerson* pCurrent;
	struPerson* pNext;
	bool isSorting;
	do
	{
		isSorting = false;
		pCurrent = pStart;
		pNext = pStart->pNext;

		while (pNext != NULL)
		{
			if (strcmp(pCurrent->lastname, pNext->lastname) > 0)
			{
				if (pCurrent->pPrev == NULL)
				{
					pStart = pCurrent->pNext;
				}
				pNext = swapWithNextElement(pCurrent);
				isSorting = true;
			}
			else if (strcmp(pCurrent->lastname, pNext->lastname) == 0
				&& strcmp(pCurrent->firstname, pNext->firstname) > 0)
			{
				if (pCurrent->pPrev == NULL)
				{
					pStart = pCurrent->pNext;
				}
				pNext = swapWithNextElement(pCurrent);
				isSorting = true;
			}
		}
	} while (isSorting);

	return pStart;
}


void printList(struPerson* pStart) {
	for (struPerson* pOutput = pStart; pOutput != NULL; pOutput = pOutput->pNext) {
		printf("Vorname: %c\nNachname: %c\nJahrgang: %d\n", pOutput->firstname[0], pOutput->lastname[0], pOutput->year);
	}
}

void main() {
	srand((unsigned)time(NULL));

	printf("Geben Sie die Anzahl Elemente die Sie erstellen moechten ein: ");
	int numberOfElements;
	scanf_s("%d", &numberOfElements);
	struPerson* pStart = create(numberOfElements);

	printList(pStart);

	char yesNo;
	printf("Wollen Sie Personen loeschen? [j/n]: ");
	scanf_s(" %c", &yesNo);

	if (yesNo == 'j')
	{
		char firstname;
		char lastname;
		printf("Vorname: ");
		scanf_s(" %c", &firstname);
		printf("Nachname: ");
		scanf_s(" %c", &lastname);

		pStart = deletePerson(pStart, firstname, lastname);
	}

	pStart = bubbleSort(pStart);
	printList(pStart);

	system("pause");
}