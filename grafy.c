#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i,j;

struct list
{
    int value;
    struct list *next;
};
typedef struct list slistEl;

void adjmatrix_gen(int n, int *adjmatrix[])     //generowanie macierzy sasiedztwa
{
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            if ((((i+j) % 2) == 1) && (i<j)) adjmatrix[i][j] = 1;         //macierz gornotrojkatna
            else adjmatrix[i][j] = 0;
        }
    }
}

void adjmatrix_print(int n, int *adjmatrix[])      //wyswietlanie macierzy sasiedztwa
{
    printf("\nMACIERZ SASIEDZTWA: \n");
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            printf("%d\t",adjmatrix[i][j]);
        }
        printf("\n");
    }
}

void adjlist_gen(int n, int* adjlist, int** adjmatrix)
{
    slistEl *newEl;
    for (i=0; i<n; i++)
    {
        adjlist[i] = NULL;
    }

    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            if (adjmatrix[i][j] == 1)
            {
                newEl = (slistEl*)malloc(sizeof(slistEl));
                newEl->value = j;
                newEl->next = adjlist[i];
                adjlist[i] = newEl;
            }
        }
    }
}

void adjlist_print(int n, int* adjlist)
{
    slistEl *currEl;
    printf("\nLISTA SASIEDZTWA: \n");
    for (i=0; i<n; i++)
    {
        printf("%d | ",i);
        currEl = adjlist[i];
        while(currEl)
        {
            printf("%d ",currEl->value);
            currEl = currEl->next;
        }
        printf("\n");
    }
}
int main()
{
    srand(time(NULL));
    int n;
    printf("Podaj liczbe wierzcholkow: \n");
    scanf("%d",&n);

    //INICJALIZACJA TABLICY n x n - macierz sasiedztwa
    int **adjmatrix;
    adjmatrix = (int**)malloc(n*sizeof(int*));
    for (i=0; i<n; i++)
    {
        adjmatrix[i] = (int*)malloc(n*sizeof(int));
    }

    //MACIERZ SASIEDZTWA
    adjmatrix_gen(n, adjmatrix);
    adjmatrix_print(n, adjmatrix);

    //INICJALIZACJA - lista sasiedztwa
    slistEl ** adjlist;
    slistEl *newEl, *toDel, *currEl;
    adjlist = (slistEl*)malloc(n*sizeof(slistEl));

    //LISTA SASIEDZTWA
    adjlist_gen(n, adjlist, adjmatrix);
    adjlist_print(n, adjlist);

    //ZWALNIANIE PAMIECI
    for (i=0; i<n; i++) free(adjmatrix[i]);
    free(adjmatrix);

    for (i=0; i<n; i++)
    {
        currEl = adjlist[i];
        while(currEl)
        {
            toDel = currEl;
            currEl = currEl->next;
            free(toDel);
        }
    }

}