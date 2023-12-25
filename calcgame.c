#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include<stdbool.h>
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
void spc_print(nodep *phead, nodei* ihead,int* number){
    // if(*number = 1 ){
        system("start cmd.exe");

    if (phead != NULL)
    {
        nodei *i = ihead;
        nodep *p = phead;
        while(p!=NULL){
            printf("the eqution is : %s , and the solution is : %i \n", p->data, i->data);
            i = i->next;
            p = p->next;
        }
    }
}
void freeall(nodep* phead , nodei* ihead ){
    nodep *fi = phead;
    nodei *se = ihead;
    while(fi != NULL){
        nodep *p = fi;
        nodei *i = se;
        fi = fi->next;
        se = se->next;
        free(p);
        free(i);
    }
}
void creatist(nodep **phead  , nodei** ihead)
{
    char equa[10];
    srand(time(0) + rand()%100);
    int x = rand() % 10;
    int y = rand() % 10 +1;
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
DWORD WINAPI CR(LPVOID phead , LPVOID ihead){
    nodep **p = (nodep **)phead ;
    nodep **i = (nodep **)ihead ;

    int turn = 1;
    while(1){
        creatist(p,i);
        spc_print(*p,*i,&turn);
        Sleep(3000);
    }
    Sleep(6000);
    printf("this is fromCR function");
}
DWORD WINAPI RE(LPVOID phead, LPVOID ihead){

    system("start cmd.exe");
    int ans  ;
    while(1){
        scanf("%i", &ans);
        boolean mark = checkans_sup((nodep**)phead , (nodei**)ihead , ans);
    }
}

boolean checkans_sup(nodep** phead,nodei** ihead , int ans){
    boolean sup = false;
    nodep* p  =*phead ;
    nodei* i = *ihead ;
    if(i->data == ans ){
        free(i);
        *ihead = (*ihead)->next ;
        free(p);
        *phead = (*phead)->next ;
        sup = true;
    } 
     p  =(*phead)->next ;
     
     i = (*ihead)->next ;
     nodep* pr  =*phead ;
    nodei* ir = *ihead ;
    
    
    while(i!=NULL ){
        if(i->data == ans){
            ir->next = i->next;
            pr->next = p->next;
            free(i);
            free(p);
            i = ir->next;
            p = pr->next;
            sup = true;
        }
        else{
            i = i->next;
            p = p->next;
        }


    }

    return sup;
}

int main()
{

    // HANDLE theardsHa[2];
    // theardsHa[0] = CreateThread(NULL, 0,CR, NULL, 0, NULL);
    // theardsHa[1] = CreateThread(NULL, 0, RE, NULL, 0, NULL);

    // if (theardsHa[0] == NULL || theardsHa[1] == NULL)
    // {
    //     fprintf(stderr, "404 err hapend ... \n");
    // }
    // WaitForMultipleObjects(2, theardsHa, TRUE, INFINITE);
    int k = 0;
    nodep *phead = NULL;
    nodei *ihead = NULL;
    creatist(&phead, &ihead);
    creatist(&phead, &ihead);
    creatist(&phead, &ihead);


    spc_print(phead , ihead , &k);
    freeall(phead, ihead);
}