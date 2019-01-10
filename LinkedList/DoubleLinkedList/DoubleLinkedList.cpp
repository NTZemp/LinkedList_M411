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
        pNew->lastname[1] = '\0';
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
struPerson* deletePerson(struPerson* pStart, const char* firstname, const char* lastname) {
    struPerson* pCurrent = pStart;
    while (pCurrent != NULL)
    {
        struPerson* pNext = pCurrent->pNext;

        if (strcmp(firstname, pCurrent->firstname) == 0 && strcmp(lastname, pCurrent->lastname) == 0)
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
struPerson* bubbleSort(struPerson* pStart, const char* sortingCriteria) {
    bool isSorting;
    struPerson* pCurrent;
    do
    {
        isSorting = false;
        pCurrent = pStart;
        while (pCurrent != NULL && pCurrent->pNext != NULL) {
            struPerson* pNext = pCurrent->pNext;
            if (sortingCriteria[0] == 'l') {
                //Nach Nachnamen sortieren
                if (strcmp(pCurrent->lastname, pNext->lastname) > 0) {
                    pStart = swapWithNextElement(pStart, pCurrent);
                    /* da pCurrent jetzt den an dem Ort ist an dem pNext zuvor war, 
                       wird pCurrent auf diesen Wert gesetzt damit kein Element übersprungen wird. */
                    pCurrent = pNext;
                    isSorting = true;
                }
                if (sortingCriteria[1] == 'f')
                {
                    // Nach Vor- und Nachnamen sortieren
                    if (strcmp(pCurrent->lastname, pNext->lastname) == 0
                        && strcmp(pCurrent->firstname, pNext->firstname) > 0) {
                        pStart = swapWithNextElement(pStart, pCurrent);
                        pCurrent = pNext;
                        isSorting = true;
                    }
                    if (sortingCriteria[2] == 'y')
                    {
                        // Nach Vor- Nachnamen und Jahr sortieren
                        if (strcmp(pCurrent->lastname, pNext->lastname) == 0 &&
                            strcmp(pCurrent->firstname, pNext->firstname) == 0 && 
                            pCurrent->year > pNext->year) {
                            pStart = swapWithNextElement(pStart, pCurrent);
                            pCurrent = pNext;
                            isSorting = true;
                        }
                    }
                }
                else if (sortingCriteria[1] == 'y')
                {
                    // Nach Nachnamen und Jahr sortieren
                    if (strcmp(pCurrent->lastname, pNext->lastname) == 0 && pCurrent->year > pNext->year) {
                        pStart = swapWithNextElement(pStart, pCurrent);
                        pCurrent = pNext;
                        isSorting = true;
                    }
                }
            }
            else if (sortingCriteria[0] == 'f')
            {
                // Nach Vornamen sortieren
                if (strcmp(pCurrent->firstname, pNext->firstname) > 0) {
                    pStart = swapWithNextElement(pStart, pCurrent);
                    pCurrent = pNext;
                    isSorting = true;
                }
                if (sortingCriteria[1] == 'y') {
                    // Nach Vornamen und Jahr sortieren
                    if (strcmp(pCurrent->firstname, pNext->firstname) == 0 && pCurrent->year > pNext->year) {
                        pStart = swapWithNextElement(pStart, pCurrent);
                        pCurrent = pNext;
                        isSorting = true;
                    }
                }
            }
            else if (sortingCriteria[0] == 'y') {
                // Nach Jahr sortieren
                if (pCurrent->year > pNext->year) {
                    pStart = swapWithNextElement(pStart, pCurrent);
                    pCurrent = pNext;
                    isSorting = true;
                }
            }
            pCurrent = pCurrent->pNext;
        }
    } while (isSorting);
    return pStart;
}

/*
    Autor: Noah Zemp
*/
void PrintElement(struPerson* pElement) {
    printf("Vorname: %s\nNachname: %s\nJahrgang: %d\n", pElement->firstname, pElement->lastname, pElement->year);
}

/*
    Autor: Lino Meyer
    Gibt die Ganze Liste in der Konsole aus
*/
void printList(struPerson* pStart) {
    for (struPerson* pOutput = pStart; pOutput != NULL; pOutput = pOutput->pNext) {
        PrintElement(pOutput);
    }
}


void printElements(struPerson* pStart, int numberOfElements) {
    struPerson* pCurrent = pStart;
    if (numberOfElements == 0) {
        printList(pStart);
    }
    while (numberOfElements > 0) {
        PrintElement(pCurrent);
        numberOfElements--;
        pCurrent = pCurrent->pNext;
    }
}


void main() {
    srand((unsigned)time(NULL));
    printf("******************\nVerkettete Liste\n******************\n\n");
    printf("Wie viele Personen soll die Liste haben? ");
    int numberOfElements = 0;
    scanf_s("%i", &numberOfElements);
    struPerson* pStart = create(numberOfElements);
    char input[40];

    while (true) {
        // diese Zeile wird zu oft ausgegeben
        printf("Wie viele Elemente wollen Sie ausgeben? [0 = alle]: ");
        scanf_s("%i", &numberOfElements);
        printElements(pStart, numberOfElements);

        printf("\nWas wollen Sie tun?\n\n");
        printf("Liste löschen [\"dl\"]\n");
        printf("Personen löschen [\"dp\"]\n");
        printf("Liste mit BubbleSort sortieren [\"bs\"]\n");
        printf("Programm beenden [\"quit\"]\n");
        printf("Eingabe:");
        getchar();
        gets_s(input);
        // Linien 326-328 werden hier ausgegeben!!! IM UNTERRICHT FRAGEN

        // Liste löschen
        if (strcmp(input, "dl") == 0) {
            deleteList(pStart);
            return;
        } 
        // Person löschen
        else if (strcmp(input, "dp") == 0){
            printf("\nWie heisst die Person die Sie löschen wollen?");
            printf("\nVorname: ");
            char firstname[40];
            gets_s(firstname);
            printf("Nachname: ");
            char lastname[40];
            gets_s(lastname);
            pStart = deletePerson(pStart, firstname, lastname);
        }
        else if (strcmp(input, "bs") == 0) {
            /*Die Priorität beim sortieren ist festgelegt, zuerst Nachname dann Vorname, dann Jahr
              Es kann also nicht nach Jahr und dann nach Nachname sortiert werden, umgekehrt aber schon.
              Ansonsten kann nach einzelnen Variablen oder auch nach mehreren sortiert werden.*/
            printf("\nNach welchen Variablen möchten Sie sortieren? [l = Nachname, f = Vorname, y = Jahr] z.B. \"lf\": ");
            char sortingCriteria[4];
            gets_s(sortingCriteria);
            pStart = bubbleSort(pStart, sortingCriteria);
        }
        else if (strcmp(input, "quit") == 0) {
            return;
        }
        else {
            printf("\nFalsche Eingabe\n");
;        }

    }
    system("pause");
}