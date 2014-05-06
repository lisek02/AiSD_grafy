#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i,j;
int n;
int *visited;

struct list
{
    int value;
    struct list *next;
};
typedef struct list slistEl;

struct list2
{
    int v1;
    int v2;
    struct list2 *next;
};
typedef struct list2 sedgeList;

struct BFSl
{
    struct BFSl *next;
    int value;
};
typedef struct BFSl BFS_list;

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

void adjmatrix_read(int *adjmatrix[])
{
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            adjmatrix[i][j] = 0;
        }
    }
    int x,y;
    /*
    for (i=0; i<=n; i++)
    {
        scanf("%d",&x);
        scanf("%d",&y);
        adjmatrix[x][y] = 1;
    }*/
    adjmatrix[0][1] = 1;
    adjmatrix[0][2] = 1;
    adjmatrix[1][3] = 1;
    adjmatrix[1][4] = 1;
    adjmatrix[2][3] = 1;
    adjmatrix[2][4] = 1;
    adjmatrix[3][4] = 1;
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

void DFS_adjmatrix(int* adjmatrix[], int w)
{
    visited[w] = 1;
    printf("%d",w);
    for (i=0; i<n; i++)
    {
        if ((adjmatrix[w][i] == 1) && (visited[i] == 0)) DFS_adjmatrix(adjmatrix, i);
    }
}

void BFS_adjmatrix(int *adjmatrix[], int w)
{
    BFS_list *newEl, *head, *tail;

    newEl = (BFS_list*)malloc(sizeof(BFS_list));
    newEl->next = NULL;
    newEl->value = w;
    head = tail = newEl;

    visited[w] = 1;

    while(head)
    {
        w = head->value;
        newEl = head;
        head = head->next;
        if(!head) tail = NULL;
        free(newEl);

        printf("%d",w);

        for (i=0; i<n; i++)
        {
            if ((adjmatrix[w][i] == 1) && (visited[i] == 0))
            {
                newEl = (BFS_list*)malloc(sizeof(BFS_list));
                newEl->next = NULL;
                newEl->value = i;
                if(!tail) head = newEl;
                else tail->next = newEl;
                tail = newEl;
                visited[i] = 1;
            }
        }
    }
}

void adjList_gen(int n, int* adjlist, int** adjmatrix)      //tworzenie listy sasiedztwa
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

void adjList_print(int n, int* adjlist)         //wyswietlanie listy sasiedztwa
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

void BFS_adjlist(int *adjlist, int w)
{
    BFS_list *newEl, *tmp, *head, *tail;

    newEl = (BFS_list*)malloc(sizeof(BFS_list));
    newEl->next = NULL;
    newEl->value = w;
    head = tail = newEl;

    visited[w] = 1;

    while(head)
    {
        w = head->value;
        newEl = head;
        head = head->next;
        if(!head) tail = NULL;
        free(newEl);

        printf("%d",w);

        //for (tmp = adjlist[w]; tmp; tmp = tmp->next)
        tmp = adjlist[w];
        while(tmp)
        {
            if (visited[tmp->value] == 0)
            {
                newEl = (BFS_list*)malloc(sizeof(BFS_list));
                newEl->next = NULL;
                newEl->value = tmp->value;
                if(!tail) head = newEl;
                else tail->next = newEl;
                tail = newEl;
                visited[tmp->value] = 1;
            }
            tmp = tmp->next;
        }
    }
}


void edgeList_gen(int n, sedgeList **head, int **adjmatrix)         //tworzenie listy krawedzi
{
    sedgeList *newEE;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            if (adjmatrix[i][j] == 1)
            {
                newEE = (sedgeList*)malloc(sizeof(sedgeList));
                newEE->v1 = i;
                newEE->v2 = j;
                newEE->next = *head;
                *head = newEE;
            }
        }
    }
}

void edgeList_print(sedgeList *head)        //wyswietlanie listy krawedzi
{
    sedgeList *currEE;
    currEE = head;
    printf("\nLISTA KRAWEDZI: \n");
    while (currEE)
    {
        printf("%d->%d\n",currEE->v1,currEE->v2);
        currEE = currEE->next;
    }
}

int main()
{
    srand(time(NULL));
    printf("Podaj liczbe wierzcholkow: \n");
    scanf("%d",&n);
    visited = (int*)malloc(n*sizeof(int));

    //INICJALIZACJA TABLICY n x n - macierz sasiedztwa
    int **adjmatrix;
    adjmatrix = (int**)malloc(n*sizeof(int*));
    for (i=0; i<n; i++)
    {
        adjmatrix[i] = (int*)malloc(n*sizeof(int));
    }

    //MACIERZ SASIEDZTWA
    //adjmatrix_read(adjmatrix);
    adjmatrix_gen(n, adjmatrix);
    adjmatrix_print(n, adjmatrix);

    for (i=0; i<n; i++) visited[i] = 0;
    printf("----------\n");
    DFS_adjmatrix(adjmatrix, 0);
    printf("\n----------");

    for (i=0; i<n; i++) visited[i] = 0;
    printf("----------\n");
    BFS_adjmatrix(adjmatrix, 0);
    printf("\n----------");

    //INICJALIZACJA - lista sasiedztwa
    slistEl ** adjlist;
    slistEl *newEl, *toDel, *currEl;
    adjlist = (slistEl*)malloc(n*sizeof(slistEl));

    //LISTA SASIEDZTWA
    adjList_gen(n, adjlist, adjmatrix);
    adjList_print(n, adjlist);

    for (i=0; i<n; i++) visited[i] = 0;
    printf("----------\n");
    BFS_adjlist(adjlist, 0);
    printf("\n----------");

    //INICJALIZACJA -lista krawedzi
    sedgeList *head, *newEE, *currEE;
    head = NULL;

    //LISTA KRAWEDZI
    edgeList_gen(n, &head, adjmatrix);
    edgeList_print(head);

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

    currEE = head;
    sedgeList *tmp;
    while (currEE)
    {
        tmp = currEE->next;
        free(currEE);
        currEE = tmp;
    }



}
