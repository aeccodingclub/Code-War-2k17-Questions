#include<stdio.h>
/*  implementing the stack using struture containg
    Contaning st pointer for theactual stack array
    and top for denoting the index. Doesnt keeps count.
    Count is top+1.

*/
struct
{
    char *st;
    int top;
}Stack={NULL,0};
 //Standard push function, pushes charcetr in this regard
void push(char ch)
{
    if(Stack.st==NULL)
    {
        Stack.st=(char *)malloc(sizeof(char)*(Stack.top+1));
        Stack.st[Stack.top]=ch;
    }
    else
    {
        Stack.st=(char *)realloc(Stack.st,sizeof(char)*(++Stack.top+1));
        Stack.st[Stack.top]=ch;
    }
}
//Standard pop function pops out charcters
char pop()
{   char ch;
    if(Stack.top==0)
    {
        ch=Stack.st[Stack.top];
        free(Stack.st);
        Stack.st=NULL;
    }
    else
    {
        ch=Stack.st[Stack.top];
        Stack.st=(char*)realloc(Stack.st,sizeof(char)*(--Stack.top+1));
    }
    return ch;

}
//Just shows the charcter doesnt deletes the character
char stackTop()
{
    if(Stack.top==NULL)
        return '\0';
    else
        return (char)Stack.st[Stack.top];
}
/////////////END OF STACK IMPLEMENTATION //////////////

/*  Operation on the characters
    1.isopertor
    2.checkprecedence
    3.isparent
*/
int isoperator(char ch)
{

    return (ch=='+'|| ch=='-'||ch=='*'||ch=='/'||ch=='^');
}

int isparent(char ch)
{
    if(ch=='(')
        return 1;
    else if(ch== ')')
        return -1;
    else
        return 0;
}
/*  returns 1 for op1 > op2
    returns 0 for op1 == op2
    return -1 for op1 < op2

*/
int checkPrc(char op1,char op2) // check preceddence of operators
{   if(op2=='\0')
        return 1;
    switch(op1)
    {
        case '^':{ return 1;}
        case '/':{
                    if(op2=='*')
                        return 0;
                    else if(op2=='^')
                        return -1;
                    else
                        return 1;
                 }
        case '*':{
                    if(op2=='/')
                        return 0;
                    else if(op2=='^')
                        return -1;
                    else
                        return 1;
                 }
        case '-':{
                    if(op2=='+')
                        return 0;
                    else
                        return -1;
                 }
        case '+':{
                    if(op2=='-')
                        return 0;
                    else
                        return -1;
                 }
    }
}

//THE ACTUAL POST FIX CONVERSION ROUTINE ///

char *postfix(char *exp,int size)
{
    char *postfixExp=(char *)malloc(size*sizeof(char)); // fe block of memory wasted
    int i=0, pexi=0; //pexi = post expression i
    int isp,countparent=0; // isp for isparent() ??
    if(isoperator(exp[0]))
    {
        printf("Not a vald expression. when does mathematical exression starts with opertors !!!!");
        return '\0';
    }
    for(;exp[i]!='\0';i++)
    {       isp=isparent(exp[i]);

            if(isoperator(exp[i])) //operator operation
            {   printf("%c|%c:%d",exp[i],stackTop(),checkPrc(exp[i],stackTop()));
                switch(checkPrc(exp[i],stackTop()))
                {
                    case 1 : {
                                push(exp[i]);
                             }break;
                    case -1:{   printf("%c : %c \n",exp[i],stackTop());
                                postfixExp[pexi]=Stack.st[Stack.top];
                                Stack.st[Stack.top]= exp[i];
                                pexi++;

                            }break;
                    case 0:{
                                push(exp[i]);
                           }break;

                }
            }
            else if(isp!=0) // for brackets
            {
                if(isp>0)
                {
                    push(exp[i]);
                    countparent++;
                }
                else
                {
                    if(countparent==0)
                    {
                        printf("NOT A VALID EXPRESSION match your number of ( and )");
                        return '\0';
                    }
                    else
                    {
                        while(Stack.st[Stack.top]!='(') // stacktop is not working here for unknown reasons
                        {
                            postfixExp[pexi]=pop();
                            pexi++;
                        }
                        pop();
                        countparent--;
                    }
                }

            }
            else // for characters
            {
                postfixExp[pexi]=exp[i];
                pexi++;
            }
    }
    if(countparent!=0)
    {
        printf("Balnace out the the damn ( and ) !!!");
        return '\0';
    }
    //trunking out the entire stack at once
    while(Stack.st!=NULL)
    {
        postfixExp[pexi]=pop();
        pexi++;
    }
    // truncating the entire stack at once
    postfixExp[pexi]='\0';
    return postfixExp;
}

int main()
{
    char ar[]="(A+B)*D-C";
    printf("%s",postfix(ar,sizeof(ar)));
}
