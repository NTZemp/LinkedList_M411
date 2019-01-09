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


/* 
    Autor: Lino Meyer
    Gibt einen zufälligen Grossbuchstaben zurück
*/
char randomName() {
    return rand() % 26 + 'A';
}

/*
    Autor: Lino Meyer
    Gibt ein zufälliges Jahr zwischen 1900 und 2018 zurück
*/
int randomYear() {
    return 1900 + (rand() % 119);
}

/*
    Autor: Lino Meyer
    Erstellt eine doppelt verkettete Liste mit einer bestimmten Anzahl Elementen
*/
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

/*
    Autor: Lino Meyer
    Löscht die Ganze Liste
*/
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

/*
    Autor: Lino Meyer
    Löscht alle Personen mit dem angegebenen Vor- und Nachnamen
*/
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

/*
    Autor: Noah Zemp
*/
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

/*
    Autor: Noah Zemp
*/
struPerson* GetElementAt(int index, struPerson* pStart) {
    struPerson* pCurrent = pStart;
    int counter = 0;
    while (counter != index) {
        counter++;
        pCurrent = pCurrent->pNext;
    }
    return pCurrent;
}

/*
    Autor: Noah Zemp
*/
void SetElementToStart(struPerson* pStart, struPerson* pElementToStart) {
    pElementToStart->pPrev = NULL;
    pElementToStart->pNext = pStart;
    pStart->pPrev = pElementToStart;
}

/*
    Autor: Noah Zemp
*/
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

/*
    Autor: Lino Meyer
    Tauscht die Position eines Elements mit dem nächsten
*/
struPerson* swapWithNextElement(struPerson* pStart, struPerson* pCurrent) {

    struPerson* pBefore = pCurrent->pPrev;
    struPerson* pAfter = pCurrent->pNext;
    struPerson* pAfterAfter = pAfter->pNext;

    if (pCurrent == pStart) {
        pStart = pAfter;
    }

    // vorherigen Node neu verknüpfen
    if (pBefore != NULL) {
        pBefore->pNext = pAfter;
    }
    // jetzigen Node neu verknüpfen
    pCurrent->pNext = pAfter->pNext;
    pCurrent->pPrev = pAfter;
    // nächsten Node neu verknüpfen
    pAfter->pNext = pCurrent;
    pAfter->pPrev = pBefore;
    // übernächsten Node neu verknüpfen
    if (pAfterAfter != NULL) pAfterAfter->pPrev = pCurrent;

    return pStart;
}

/*
    Autor: Lino Meyer
    Sortiert die Liste nach Bubblesort vorgehen.
*/
struPerson* bubbleSort(struPerson* pStart) {
    bool isSorting;
    struPerson* pCurrent;
    do
    {
        isSorting = false;
        pCurrent = pStart;
        while (pCurrent != NULL && pCurrent->pNext != NULL) {
            struPerson* pNext = pCurrent->pNext;
            if (strcmp(pCurrent->lastname, pNext->lastname) > 0) {
                pStart = swapWithNextElement(pStart, pCurrent);
                /* da pCurrent jetzt den an dem Ort ist an dem pNext zuvor war, 
                   wird pCurrent auf diesen Wert gesetzt damit kein Element übersprungen wird. */
                pCurrent = pNext;
                isSorting = true;
                isSorting = true;
            }
            // AM FREITAG IM UNTERRICHT FRAGEN?
            // nach Vornamen sortieren funktioniert mysteriöserweise nicht
            else if (strcmp(pCurrent->lastname, pNext->lastname) == 0
                && strcmp(pCurrent->firstname, pNext->firstname) > 0) {
                    pStart = swapWithNextElement(pStart, pCurrent);
                    pCurrent = pNext;
                    isSorting = true;
            }
            pCurrent = pCurrent->pNext;
        }
    } while (isSorting);
    return pStart;
}

/*
    Autor: Lino Meyer
    Gibt die Ganze Liste in der Konsole aus
*/
void printList(struPerson* pStart) {
    for (struPerson* pOutput = pStart; pOutput != NULL; pOutput = pOutput->pNext) {
        printf("Vorname: %c\nNachname: %c\nJahrgang: %d\n", pOutput->firstname[0], pOutput->lastname[0], pOutput->year);
    }
}

/*
    Autor: Noah Zemp
*/
void PrintElement(struPerson* pElement) {
    printf("Vorname: %c\nNachname: %c\nJahrgang: %d\n", pElement->firstname[0], pElement->lastname[0], pElement->year);
}

/*
    Autor: Noah Zemp
*/
void main() {
    srand((unsigned)time(NULL));
    struPerson* pStart = create(150);
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