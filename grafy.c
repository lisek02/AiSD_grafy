#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i,j;
int n, m;
int *visited, tofind;

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
            if ((((i+j) % 2) == 1) && (i<j))
            {
                adjmatrix[i][j] = 1;         //macierz gornotrojkatna
                m+=1;
            }
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
        for (j=n-1; j>0; j--)
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

void DFS_adjlist(int* adjlist[], int w)
{
    slistEl *tmp;
    visited[w] = 1;
    printf("%d",w);
    tmp = adjlist[w];
    while(tmp)
    {
        if (visited[tmp->value] == 0) DFS_adjlist(adjlist, tmp->value);
        tmp = tmp->next;
    }
}

void BFS_adjlist(int *adjlist[], int w)
{
    BFS_list *newEl, *tmp, *head, *tail;
    slistEl *currEl;

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

        currEl = adjlist[w];
        while(currEl)
        {
            if (visited[currEl->value] == 0)
            {
                newEl = (BFS_list*)malloc(sizeof(BFS_list));
                newEl->next = NULL;
                newEl->value = currEl->value;
                if(!tail) head = newEl;
                else tail->next = newEl;
                tail = newEl;
                visited[currEl->value] = 1;
            }
            currEl = currEl->next;
        }
    }
}

void edgeList_gen(int n, int **edgeTab, int **adjmatrix)
{
    int counter = 0;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            if (adjmatrix[i][j] == 1)
            {
                edgeTab[counter][0] = i;
                edgeTab[counter][1] = j;
                counter+=1;
            }
        }
    }
}

void edgeList_print(int **edgeTab)        //wyswietlanie listy krawedzi
{
    printf("\nLISTA KRAWEDZI: \n");
    for (i=0; i<m; i++)
    {
        printf("%d->%d\n",edgeTab[i][0],edgeTab[i][1]);
    }
}

void DFS_edgelist(int **edgeTab, int w)
{
    visited[edgeTab[w][0]] = 1;
    printf("%d",edgeTab[w][0]);
    tofind = edgeTab[w][1];
    //w = edgeTab[w][1];
    for (i=0; i<m; i++)
    {
        //if ((edgeTab[i][0] == edgeTab[w][1]) && (visited[edgeTab[i][0]] == 0)) DFS_edgelist(edgeTab, edgeTab[i][0]);
        if ((edgeTab[i][0] == tofind) && (visited[tofind] == 0)) DFS_edgelist(edgeTab, i);
    }
    if(visited[tofind] == 0)
    {
        printf("%d",tofind);
        visited[tofind] = 1;
    }
}

void BFS_edgelist(int **edgeTab, int w)
{
    BFS_list *newEl, *head, *tail;

    newEl = (BFS_list*)malloc(sizeof(BFS_list));
    newEl->next = NULL;
    newEl->value = w;
    head = tail = newEl;

    //tofind = edgeTab[w][1];
    //visited[w] = 1;

    while(head)
    {
        w = head->value;
        newEl = head;
        head = head->next;
        if(!head) tail = NULL;
        free(newEl);

        //printf("%d",edgeTab[w][1]);
        //tofind = edgeTab[w][0];
        tofind = w;
        printf("%d",tofind);

        for (i=0; i<m; i++)
        {
            if ((edgeTab[i][0] == tofind) && (visited[edgeTab[i][1]] == 0))
            {
                newEl = (BFS_list*)malloc(sizeof(BFS_list));
                newEl->next = NULL;
                newEl->value = edgeTab[i][1];
                if(!tail) head = newEl;
                else tail->next = newEl;
                tail = newEl;
                visited[edgeTab[i][1]] = 1;
            }
        }
    }
}


int main()
{
    srand(time(NULL));
    printf("Podaj liczbe wierzcholkow: \n");
    scanf("%d",&n);
    visited = (int*)malloc(n*sizeof(int));
    m = 0;

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
    printf("----DFS----\n");
    DFS_adjmatrix(adjmatrix, 0);

    for (i=0; i<n; i++) visited[i] = 0;
    printf("\n----BFS----\n");
    BFS_adjmatrix(adjmatrix, 0);
    printf("\n-----------\n");

    //INICJALIZACJA - lista sasiedztwa
    slistEl ** adjlist;
    slistEl *newEl, *toDel, *currEl;
    adjlist = (slistEl*)malloc(n*sizeof(slistEl));

    //LISTA SASIEDZTWA
    adjList_gen(n, adjlist, adjmatrix);
    adjList_print(n, adjlist);

    for (i=0; i<n; i++) visited[i] = 0;
    printf("----DFS----\n");
    DFS_adjlist(adjlist, 0);

    for (i=0; i<n; i++) visited[i] = 0;
    printf("\n----BFS----\n");
    BFS_adjlist(adjlist, 0);
    printf("\n-----------\n");

    //INICJALIZACJA -lista krawedzi
    int edgeTab[m];
    for (i=0; i<m; i++)
    {
        edgeTab[i] = (int*)malloc(2*sizeof(int));
    }

    //LISTA KRAWEDZI
    edgeList_gen(n, edgeTab, adjmatrix);
    edgeList_print(edgeTab);

    for (i=0; i<n; i++) visited[i] = 0;
    printf("----DFS----\n");
    DFS_edgelist(edgeTab, 0);

    for (i=0; i<n; i++) visited[i] = 0;
    printf("\n----BFS----\n");
    BFS_edgelist(edgeTab, 0);
    printf("\n-----------\n");

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

    /*
    currEE = head;
    sedgeList *tmp;
    while (currEE)
    {
        tmp = currEE->next;
        free(currEE);
        currEE = tmp;
    }*/



}
