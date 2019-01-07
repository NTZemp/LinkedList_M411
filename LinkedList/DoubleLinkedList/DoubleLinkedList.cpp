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


int GetNumberOfElements(struPerson* pStart) {
    struPerson* pCurrent = pStart;
    int counter = 1;
    while (pCurrent->pNext != NULL)
    {
        counter++;
        pCurrent = pCurrent->pNext;
    }
    free(pCurrent);
    free(pStart);
    return counter;
}

struPerson* GetElementAt(int index, struPerson* pStart) {
    struPerson* pCurrent = pStart;
    int counter = 0;
    while (counter != index) {
        counter++;
        pCurrent = pCurrent->pNext;
    }
    return pCurrent;
}

void SetElementToStart(struPerson* pStart, struPerson* pElementToStart) {
    pElementToStart->pPrev = NULL;
    pElementToStart->pNext = pStart;
    pStart->pPrev = pElementToStart;
}

void swapElements(struPerson* pElement1, struPerson* pElement2) {
    struPerson* pTemp = (struPerson*)malloc(sizeof(struPerson));
    //Copy Element1 into Temp
    pTemp->pNext = pElement1->pNext;
    pTemp->pPrev = pElement1->pPrev;
    //Put Element1 to the same Position as Element2
    pElement1->pNext = pElement2->pNext;
    pElement1->pPrev = pElement2->pPrev;
    //Put Element2 to the Position were Element1 was
    pElement2->pNext = pTemp->pNext;
    pElement2->pPrev = pTemp->pPrev;
}


/*Dä esch scheisse
struPerson* selectionSort(struPerson* pStart) {
    struPerson* pCurrent = pStart;
    int i, j, min_index, n;
    n = GetNumberOfElements(pStart);
    for (i = 0; i <= n-1; i++) {
        min_index = i;
        for (j = i+1; j <= n-1; j++) {
            pCurrent = GetElementAt(j, pStart);
            if (pCurrent->lastname < GetElementAt(min_index, pStart)->lastname) {
                swapElements(pStart, pCurrent);
                min_index = j;
                pStart = pCurrent;
            }

        }

    }
    return NULL;
}*/



//struPerson* bubbleSort(struPerson* pStart) {
//	struPerson* pCurrent;
//	struPerson* pNext;
//	bool isSorting;
//	do
//	{
//		isSorting = false;
//		pCurrent = pStart;
//		pNext = pStart->pNext;
//
//		while (pNext != NULL)
//		{
//			//if pNext -> Lastname is less than pCurrent -> Lastname, then swap those elements
//			if (strcmp(pCurrent->lastname, pNext->lastname) > 0)
//			{
//				//Swap Elements
//				pCurrent = swapWithNextElement(pCurrent);
//				isSorting = true;
//			}
//			else if (strcmp(pCurrent->lastname, pNext->lastname) == 0
//				&& strcmp(pCurrent->firstname, pNext->firstname) > 0)
//			{
//				pCurrent = swapWithNextElement(pCurrent);
//				isSorting = true;
//            }
//            if (pCurrent->pPrev == NULL)
//            {
//                pStart = pCurrent;
//            }
//            pCurrent = pNext;
//            pNext = pNext->pNext;
//		}
//	} while (isSorting);
//
//	return pStart;
//}

struPerson* swapWithNextElement(struPerson* pCurrent) {

    struPerson* pNext = pCurrent->pNext;
    struPerson* pPrevious = pCurrent->pPrev;

    // links for current node
    pCurrent->pNext = pNext->pNext;
    pCurrent->pPrev = pNext;

    // links for next node
    pNext->pNext = pCurrent;
    pNext->pPrev = pPrevious;

    // link for previous node
    if (pPrevious != NULL)
    {
        pPrevious->pNext = pNext;
    }

    //link for next next node
    if (pNext->pNext != NULL) {
        pNext->pNext->pPrev = pCurrent;
    }
    return pCurrent;
}

struPerson* bubbleSort(struPerson* pStart) {
    bool isSorting;
    bool isPStart;
    struPerson* pCurrent;
    do
    {
        isSorting = false;
        isPStart = false;
        pCurrent = pStart;
        while (pCurrent->pNext != NULL) {
            if (strcmp(pCurrent->lastname, pCurrent->pNext->lastname) > 0) {
                isSorting = true;
                struPerson* pBefore = pCurrent->pPrev;
                struPerson* pAfter = pCurrent->pNext;
                // vorherigen Node neu verknüpfen
                if (pBefore != NULL) {
                    pBefore->pNext = pAfter;
                }
                else {
                    isPStart = true;
                }
                // jetzigen Node neu verknüpfen
                pCurrent->pNext = pAfter->pNext;
                pCurrent->pPrev = pAfter;
                // nächsten Node neu verknüpfen
                pAfter->pNext = pCurrent;
                pAfter->pPrev = pBefore;
            }
            else {
                pCurrent = pCurrent->pNext;
            }

            if (isPStart == true) {
                pStart = pCurrent;
                isPStart = false;
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


void PrintElement(struPerson* pElement) {
    printf("Vorname: %c\nNachname: %c\nJahrgang: %d\n", pElement->firstname[0], pElement->lastname[0], pElement->year);
}

void main() {
    srand((unsigned)time(NULL));
    struPerson* pStart = create(5);
    printList(pStart);
    pStart = bubbleSort(pStart);
    printf("\n\n");
    printList(pStart);
    printf_s("\n\nNumber of Elements: %i\n", GetNumberOfElements(pStart));
    system("pause");
}
/*void main() {
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
}*/