#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include<stdbool.h>
typedef struct nodep
{
    char *data;
    struct nodei *next;

} nodep;

typedef struct nodei
{
    int data;
    struct nodep *next;
} nodei;
void spc_print(nodep *head ,int* number){
    if(*number = 1 ){
        system("start cmd.exe");
        *number++;
    }
    if (head != NULL)
    {

        nodep *p = head;
        nodei *i = head->next;

        while (p != NULL)
        {
            printf("\nTHE WORD IS : %s", p->data);
            printf("\nthe int is : %i", i->data);

            p = i->next;
            if (p == NULL)
            {
                break;
            }
            i = p->next;
        }
    }

}
void freeall(nodep* head ){
    nodep *fi = head;
    nodei *se = head->next;
    while(fi != NULL){
        nodep *p = fi;
        fi = (fi->next)->next;
        free(p);
    }
while(se->next != NULL){
        nodep *p = se;
        se = (se->next)->next;
        free(p);
    }
    free(se);
}
void creatist(nodep **head)
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
    p->next = i;
    i->next = *head;
    *head = p;
}
DWORD WINAPI CR(LPVOID head){
    nodep **p = (nodep **)head ;
    int turn = 1;
    while(1){
        creatist(p);
        spc_print(*p,&turn);
        Sleep(3000);
    }
    Sleep(6000);
    printf("this is fromCR function");
}
DWORD WINAPI RE(){
    system("start cmd.exe");
    int ans  ;
    while(1){
        scanf("%i", &ans);

    }
}

boolean checkans_sup(nodep** head , int ans){
    nodep* p  =*head ;
    nodei* i = (*head)->next ; 
    while(){
        
    } 



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

     nodep *head = NULL;
     creatist(&head);

    //  spc_print(head);
     freeall(head);
}