#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#include<time.h>
typedef struct elm
{
    char data;
    struct elm *next;
} elm;

void creatgame(elm **head, char t[])
{
    int n = strlen(t);
    if (n > 0)
    {

        *head = (elm *)malloc(sizeof(elm));
        (*head)->data = t[0];
        elm *helper = *head;
        for (int i = 1; i < n; i++)
        {
            elm *p = (elm *)malloc(sizeof(elm));
            p->data = t[i];
            helper->next = p;
            helper = p;
        }
        helper->next = NULL;
    }
}
void spc_print(elm *head, elm *end)
{

    if (head != NULL && head != end)
    {
        if (head->next == end)
        {
            printf("%c\n", head->data);
        }
        else
        {

            printf("%c", head->data);
            spc_print(head->next, end);
        }
    }
}
void readchar(elm *head, elm **start)
{
    while (*start != NULL)
    {
        char c = getch();
        if ((*start)->data == c)
        {
            system("cls");
            spc_print(head, NULL);
            spc_print(head, (*start)->next);
            *start = (*start)->next;
            if(*start == NULL){
                printf("\n\033[0;32mcongrats\n");
                printf("\033[0m"); 
            }
        }
    }
}
    int calc_words(char t[] ){
        int n = strlen(t);
        int k = 0;
        for (int i = 0; i < n-1;i++){
            if(t[i] == ' '&& t[i+1]!= ' '){
                k++;
            }
        }
        return k + 1;
    } 
    void printres(float res , char *color){
            printf("%syou achived %.2f wpm !!!\n",color,res );
            printf("\033[0m");  

    }
int main()
{
    char x[200] = "lllllllllllllllllllll";
    elm *head = NULL;
    // char k = getch();
    // printf("%c", k);
    creatgame(&head, x);
    elm *p = head;
    printf("enter any charcter to start :\n");
    getch();
    spc_print(head, NULL);
    time_t startgame = time(NULL);
    readchar(head, &p);
    time_t endgame = time(NULL);
    int timer = endgame - startgame;
    int l = calc_words(x);

    float ts = (float)timer / 60;

     ts = (float)l /ts ;
    
    if(ts>=100){

        printres(ts, "\033[0;36m");
    }
    else if(ts>=40){
        printres(ts, "\033[0;35m");
    }
    else{
        printres(ts, "\033[0;31m");

    }
}
