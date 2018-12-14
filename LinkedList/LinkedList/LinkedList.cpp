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

//cont char* ist als Parameter wie ein String
void deletePerson(struPerson* pStart, const char* firstname, const char* lastname) {
	for (struPerson* pCurrentPerson = pStart; pCurrentPerson != NULL; pCurrentPerson = pCurrentPerson->pNext) {
		
	}
}

void main() {
	srand((unsigned)time(NULL));
	// Liste erstellen
	printf("Geben Sie die Anzahl Elemente die Sie erstellen moechten ein: ");
	int createElements;
	scanf_s("%d", &createElements);
	struPerson* pStart = create(createElements);
	printList(pStart);

	deleteList(pStart);
	// Liste löschen
	//printf("Geben Sie \"j\" ein wenn Sie die Liste loeschen moechten.");
	//char yesOrNo;
	//scanf_s("%c", &yesOrNo);

	//if (yesOrNo == 'j') {
	//	deleteList(pStart);
	//}
	system("pause");
}