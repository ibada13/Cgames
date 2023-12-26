#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
typedef struct nodep
{
    char *data;
    struct nodep *next;

} nodep;

typedef struct nodei
{
    int data;
    struct nodei *next;
} nodei;

typedef struct param
{
    struct nodep **phead;
    struct nodei **ihead;

} param;
void spc_print(nodep *phead, nodei *ihead, int *number)
{
    // if(*number = 1 ){
    system("start cmd.exe");

    if (phead != NULL)
    {
        nodei *i = ihead;
        nodep *p = phead;
        while (p != NULL)
        {
            printf("the eqution is : %s , and the solution is : %i \n", p->data, i->data);
            i = i->next;
            p = p->next;
        }
    }
}
void print_equ(nodep *phead)
{
    nodep *p = phead;
    system("cls");
    printf("|");
    while (p != NULL)
    {

        if( p->next ==NULL){
        printf(" %s |\n >>>>>>>  ", p->data);
        }
        else{
        printf(" %s |", p->data);
        }
        p = p->next;
    }
}
void freeall(nodep *phead, nodei *ihead)
{
    nodep *fi = phead;
    nodei *se = ihead;
    while (fi != NULL)
    {
        nodep *p = fi;
        nodei *i = se;
        fi = fi->next;
        se = se->next;
        free(p);
        free(i);
    }
}
void creatist(nodep **phead, nodei **ihead)
{
    char equa[10];
    srand(time(0) + rand() % 100);
    int x = rand() % 10;
    int y = rand() % 10 + 1;
    int op = rand() % 4;
    int res = 0;
    if (op == 0)
    {
        sprintf(equa, "%i %c %i", x, '+', y);
        res = x + y;
    }
    else if (op == 1)
    {
        sprintf(equa, "%i %c %i", x, '*', y);
        res = x * y;
    }
    else if (op == 2)
    {
        sprintf(equa, "%i %c %i", x, '-', y);
        res = x - y;
    }
    else
    {
        sprintf(equa, "%i %c %i", x, '/', y);
        res = x / y;
    }
    nodep *p = (nodep *)malloc(sizeof(nodep));
    nodei *i = (nodei *)malloc(sizeof(nodei));
    p->data = (char *)malloc((strlen(equa) + 1));
    strcpy(p->data, equa);
    i->data = res;
    p->next = *phead;
    i->next = *ihead;
    *phead = p;
    *ihead = i;
}
boolean checkans_sup(nodep **phead, nodei **ihead, int ans)
{
    boolean sup = false;
    if(*phead !=NULL){

    nodep *p = *phead;
    nodei *i = *ihead;
    if (i->data == ans)
    {
        free(i);
        *ihead = (*ihead)->next;
        free(p);
        *phead = (*phead)->next;
        sup = true;
    }
    p = (*phead)->next;

    i = (*ihead)->next;
    nodep *pr = *phead;
    nodei *ir = *ihead;

    while (i != NULL)
    {
        if (i->data == ans)
        {
            ir->next = i->next;
            pr->next = p->next;
            free(i);
            free(p);
            i = ir->next;
            p = pr->next;
            sup = true;
        }
        else
        {
            ir = ir->next;
            pr = pr->next;
            i = i->next;
            p = p->next;
        }
    }

}
    return sup;
    }
DWORD WINAPI CR(LPVOID thead)
{
    param *head = thead;
    nodep **p = head->phead ;
    nodep **i = head->ihead ;

    while (1)
    {
        creatist(p, i);
        print_equ(*p);
        Sleep(2000);
    }

}
DWORD WINAPI RE(LPVOID thead)
{
    param *head = thead;
    nodei **i = head->ihead;
    nodep **p = head->phead;
   
    int ans;
    while (1)
    {
        scanf("\n %i", &ans);
        boolean mark = checkans_sup(p, i, ans);
        if (mark)
        {
            print_equ(*p);
        }
    }
}

int main()
{

    nodei *ihead = NULL;
    nodep *phead = NULL;
    param *pa = (param *)malloc(sizeof(param));
    pa->phead = &phead;
    pa->ihead = &ihead;

    HANDLE theardsHa[2];
    theardsHa[0] = CreateThread(NULL, 0, CR, pa, 0, NULL);
    theardsHa[1] = CreateThread(NULL, 0, RE, pa, 0, NULL);

    if (theardsHa[0] == NULL || theardsHa[1] == NULL)
    {
        fprintf(stderr, "404 err hapend ... \n");
    }
    WaitForMultipleObjects(2, theardsHa, TRUE, INFINITE);
    int k = 0;

    spc_print(phead, ihead, &k);
    freeall(phead, ihead);
}