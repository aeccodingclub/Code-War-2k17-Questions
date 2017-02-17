
#include<stdio.h>
#include<string.h>

struct{
    char *st;
    ///Q.Removed pointer *st
    int size;
}Stack={NULL,0};

void push(char ch)
{
    if(Stack.st==NULL)
    {
        Stack.st=(char *)malloc(sizeof(char)*(++Stack.size));

        Stack.st[0]=ch;
    }
    else
    {
        Stack.st=(char *)realloc(Stack.st,sizeof(char)*(++Stack.size));
        Stack.st[Stack.size-1]=ch;
    }
}

char pop()
{   char t;
    if(Stack.size==1)
    {
       t=Stack.st[Stack.size-1];
       free(Stack.st);
       Stack.st=NULL;
       Stack.size=0;
       return t;
    }
    else
    {
        t=Stack.st[Stack.size-1];
        ///Q.LOGICAL ERROR of POPPING THE actual element[size] not size-1
        Stack.st=(char *)realloc(Stack.st,sizeof(char)*(--Stack.size));
        return t;
    }
}
char stacktop()
{
    if(Stack.size==0)
    {
        return '\0';
    }
    else
    {
        return Stack.st[Stack.size-1];
    }
}
///////////////////////////////////////////////////////////////////////////



//////////STANDARD FUNCTIONS REQUIRED FOR OPERATION////////////////////////
int isParent(char ch) //for detecting paranethesis
{
    if(ch=='(')
        return -1;
    else if(ch==')')
        return 1;
    else
        return 0;
}

int isOpperator(char ch)//checks for character is operator or not
{
    return (ch=='+'||ch=='-'||ch=='*'||ch=='/');
}

int OppPrecedence(char op1,char op2) // checks the precedence of the operators
{///Q.LOGICAL ERROR etire precedence system messed up
    switch(op1)
    {
        case '+':{
                    if(op2=='-')
                    {
                        return 0;
                    }
                    else return -1;
                 }
        case '-':{
                    if(op2=='+')
                    {
                        return 0;
                    }
                    else return -1;
                 }
        case '*':{
                    if(op2=='/')
                    {
                        return 0;
                    }
                    else return 1;
                 }
        case '/':{
                    if(op2=='*')
                    {
                        return 0;
                    }
                    else return 1;
                 }
    }
}
///////////////STANDARD OPERATION END////////////////////////

/////print routine/////
int print(char ch, char *postfix)
{
    printf("\n%c ",ch);
    int i=0;
    printf("[");
    if(stacktop()!='\0')
    {
        for(;i<Stack.size;i++)
        {
            printf("%c",Stack.st[i]);
        }
    }
    printf("]");
    printf("    %s",postfix);
}

//Size of the any strng including the null character///
int size(char *infix)
{ ///Q.Removed the pointer notaton of arguement
    int size=0;
    while(infix[size]!='\0'){size++;}
    ///Q.MAJOR LOGICAL ERROR should be '\0' also syntax error
    return size+1;
}

///////////POSTFIX EXPRESSION PUSH BACK////////////////
int push_back(char *postfix,char ch)
{
        printf("%c",ch);
        int s=size(postfix);
        postfix[s-1]=ch;
        ///Q. Removed the square brackets
        postfix[s]='\0';
}
////////////////////EXPRESSION VALIDITY////////////////
int validity(char *infix)// validates count of varable be geater than operators
{
    int i=0,countVar=0,countOpp=0;
    while(infix[i]!='\0')
    {
        if(isalpha(infix[i]))
            countVar++;
        else if(isOpperator(infix[i]))
            countOpp++;
        i++;
    }
    return ((countVar-countOpp)==1);
    ///Q.LOGICAL ERROR OF ==1 to ==0
}

//The actual conversion routine
char *infixToPost(char *infix)
{
    int sizeOfInfix=size(infix);
    char *postfix=(char *)malloc(sizeof(char)*sizeOfInfix);
    postfix[0]='\0';
    if(!validity(infix))
        return postfix;
    int countRP=0;
    int i=0;
    for(;i<sizeOfInfix-1;i++)
    {
        print(infix[i],postfix);

        if( !Stack.size && postfix[0]=='\0')//when stack is empty and also postfix expression is empty
        {
            if(isParent(infix[i])==1) //checks if parenthesis
            {///Q.ADDED a ';' after teh if statement
               postfix[0]='\0';
               return postfix;
            }
            else if(isParent(infix[i])==-1) //checks if parethesis
            {
                push(infix[i]);
                countRP++;
            }
            else if(isOpperator(infix[i])) //checks if operator
            {
               postfix[0]='\0';
               return postfix;
            }
            else
            {
                push_back(postfix,infix[i]);
            }
        }
        else
        {
            if(isalpha(infix[i]))// checks for variable
            {
                push_back(postfix,infix[i]);
                ///Q.Changed to push-back
            }
            else if(isParent(infix[i]))
            {
                if(infix[i]=='(')
                {
                    countRP++;
                    push(infix[i]);
                }
                else if(infix[i]==')')
                {
                    if(countRP==0)
                    {
                        postfix[0]='\0';
                        return postfix;
                    }
                    else
                    {   if(stacktop()!='\0')
                        {
                           while(stacktop()!='(')
                           {
                                push_back(postfix,pop());
                           }
                           pop();
                           countRP--;
                        }
                    }
                }
            }
            else if(isOpperator(infix[i]))
            {
                if(isParent(stacktop()))
                {
                    push(infix[i]);
                }
                else if(OppPrecedence(infix[i],stacktop())>=0)
                {
                    push(infix[i]);
                }
                else if(OppPrecedence(infix[i],stacktop())<0)
                {
                    push_back(postfix,pop());
                    push(infix[i]);
                }
                else
                {
                    push(infix[i]);
                }
            }

        }

    }

    if( countRP!=0)
        {postfix[0]='\0';return postfix;}

    while(stacktop()!='\0') //empties the stack
    {
        push_back(postfix,pop());
        ///Q.Argument of pop missing
    }

    return postfix;

}

int main()
{
    char infix[]="(A+B)*C/D";
    char *postfix=infixToPost(infix);
    if(postfix[0]!='\0')
    {
        printf("\n%s",postfix);
    }
    else
    {
        printf("\nEhhHH DOC the exepression is wrong ??");
    }
}
