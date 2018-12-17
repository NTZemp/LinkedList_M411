#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

typedef struct Person {
	char firstname[40];
	char lastname[40];
	int year;
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
		pNew->firstname[0] = randomName();
		pNew->firstname[1] = '\0';
		pNew->lastname[0] = randomName();
		pNew->lastname[1] = '\0';
		pNew->year = randomYear();
		if (pStart == NULL) pStart = pNew;
		if (pLast != NULL) pLast->pNext = pNew;
		pLast = pNew;
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

void printList(struPerson* pStart) {
	for (struPerson* pOutput = pStart; pOutput != NULL; pOutput = pOutput->pNext) {
		printf("Vorname: %c\nNachname: %c\nJahrgang: %d\n", pOutput->firstname[0], pOutput->lastname[0], pOutput->year);
	}
}

void deletePerson(struPerson* pStart, char firstname, char lastname) {
	struPerson* pPreviousPerson = pStart;
	// Um sicherzustellen das die erste Person keine ist, die gelöscht werden soll
	// FUNKTIONIERT IRGENDWIE NICHT!!!
	//if (pPreviousPerson->firstname[0] == firstname && pPreviousPerson->lastname[0])
	//{
	//	struPerson* pNext = pPreviousPerson->pNext;
	//	free(pPreviousPerson);
	//	pPreviousPerson = pNext;
	//}

	struPerson* pCurrentPerson = pPreviousPerson->pNext;
	while (pCurrentPerson != NULL)
	{
		struPerson* pNext = pCurrentPerson->pNext;
		if (pCurrentPerson->firstname[0] == firstname && pCurrentPerson->lastname[0]) {
			free(pCurrentPerson);
			pPreviousPerson->pNext = pNext;
		}
		else
		{
			pPreviousPerson = pCurrentPerson;
		}
		pCurrentPerson = pNext;
	}
}

void main() {
	srand((unsigned)time(NULL));
	// Liste erstellen
	printf("Geben Sie die Anzahl Elemente die Sie erstellen moechten ein: ");
	int numberOfElements;
	scanf_s("%d", &numberOfElements);
	struPerson* pStart = create(numberOfElements);
	printList(pStart);
	char yesOrNo;
	printf("\n\nMoechten Sie einige Elemente loeschen? [j/n]: ");
	scanf_s(" %c", &yesOrNo);

	char firstname;
	char lastname;
	if (yesOrNo == 'j')
	{
		printf("Geben Sie den Vornamen ein: ");
		scanf_s(" %c", &firstname);
		printf("Geben Sie den Nachnamen ein: ");
		scanf_s(" %c", &lastname);
	}
	deletePerson(pStart, firstname, lastname);

	// Liste löschen
	printf("Möchten Sie die Ganze Liste löschen? [j/n]: ");
	scanf_s(" %c", &yesOrNo);

	if (yesOrNo == 'j') {
		deleteList(pStart);
	}

	printList(pStart);

	system("pause");
	system("pause");
}