#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
    HANDLE ghMutex; 

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
    int score;

} param;
param *pa;
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
void print_equ(nodep *phead , int score)
{
    nodep *p = phead;
    system("cls");
    printf("|");
    while (p != NULL)
    {

        if( p->next ==NULL){
        printf(" %s |\n", p->data);
        printf("[+] your score : [%i] \n>>>>>>> ", score);

        }
        else{
        printf(" %s |", p->data);

        }
        p = p->next;
    }
}
void freeall(nodep *phead, nodei *ihead)
{
    WaitForSingleObject(ghMutex, INFINITE);
    nodep *fi = phead;
    nodei *se = ihead;
    while (fi != NULL)
    {
        nodep *p = fi;
        nodei *i = se;
        fi = fi->next;
        se = se->next;
        free(p->data);
        free(p);
        free(i);
    }
    ReleaseMutex(ghMutex);
}
void creatist(nodep** phead, nodei** ihead)
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
            nodei *i ;
            nodep *p ;
        while(*ihead!=NULL&& (*ihead)->data == ans ){
            i = *ihead;
            p = *phead;
            *ihead = (*ihead)->next;
            *phead = (*phead)->next;
            free(i);
            free(p->data);
            free(p);
            sup = true;
        }

    // if (i->data == ans)
    // {
    //     printf("hii5 \n");

    //     free(i);
    //     *ihead = (*ihead)->next;
    //         free(p->data);

    //     free(p);
    //     *phead = (*phead)->next;
    //     sup = true;
    // }
    if(*phead !=NULL ){

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
            free(p->data);
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
}
    return sup;
    }
DWORD WINAPI CR(LPVOID thead)
{
    param *head = pa;
    nodep **p = (nodep**)head->phead ;
    nodei **i = (nodei**)head->ihead ;

    while (1)
    {
    // WaitForSingleObject(ghMutex, INFINITE);

        creatist(p, i);
        print_equ(*p,pa->score);
        // ReleaseMutex(ghMutex)
        
        Sleep(3000-(pa->score/10) );
        printf("\n%i,%i", 3000 - (pa->score / 10),pa->score);
    }

}
DWORD WINAPI RE(LPVOID thead)
{
    param *head = pa;
    nodei **i = head->ihead;
    nodep **p = head->phead;
   
    int ans;
    while (1)
    {
        scanf("\n %i", &ans);
    // WaitForSingleObject(ghMutex, INFINITE);

        boolean mark = checkans_sup(p, i, ans);
        // ReleaseMutex(ghMutex);
        if (mark)
        {
        
        pa->score = pa->score+ 200;
        // WaitForSingleObject(ghMutex, INFINITE);
        print_equ(*p,pa->score);
        // ReleaseMutex(ghMutex);

        }
    }
}

int main()
{
    nodei *ihead = NULL;
    nodep *phead = NULL;
    pa = (param *)malloc(sizeof(param));
    pa->phead = &phead;
    pa->ihead = &ihead;
   
    pa->score = 0; 

    HANDLE theardsHa[2];
      ghMutex = CreateMutex( 
        NULL,            
        FALSE,           
        NULL);            

  if (ghMutex == NULL) 
    {
        printf("CreateMutex error: %d\n", GetLastError());
        return 1;
    }
    theardsHa[0] = CreateThread(NULL, 0, CR, NULL, 0, NULL);
    theardsHa[1] = CreateThread(NULL, 0, RE, NULL, 0, NULL);

    if (theardsHa[0] == NULL || theardsHa[1] == NULL)
    {
        fprintf(stderr, "404 err hapend ... \n");
    }
    WaitForMultipleObjects(2, theardsHa, TRUE, INFINITE);
    int k = 0;

    spc_print(phead, ihead, &k);
    freeall(phead, ihead);
}