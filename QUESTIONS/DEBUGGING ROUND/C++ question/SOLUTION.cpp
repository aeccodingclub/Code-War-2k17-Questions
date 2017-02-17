#include <iostream>
#include<vector>
#include<string>

using namespace std;
/// Q. NAMESPACE specifier missing

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
{   ///Q. LOGICAL ERROR of OPERATOR precedence being messed up
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

int verify(string infixexp) // verifies character length be greater than operator length by 1
{
    int countAlpha=0,countOpp=0;
    for(int i=0;i<=infixexp.length();i++)
    {
        if(isalpha(infixexp[i]))
            countAlpha++;
        else if(isOpperator(infixexp[i]))
            countOpp++;
    }

    return ((countAlpha-countOpp)==1);
    ///Q. LOGICAL ERROR OF COMPARING WRONG VALUES SHOULD BE 1 NOT 0
}

template<class S> void print(char ch,S st,string postexp) // a template class for printing the output
{   ///Q.TEMPLATE ARGUEMENT IS REMOVED FOR ILLUSION OF SELF RESOLUTION
    cout<<ch<<" ";
    cout<<"[";
    for(typename S::iterator it=st.begin();it!=st.end();it++)
    {   ///Q. no typename used
        cout<<*it;
    }
    cout<<"] "<<postexp;
    cout<<"\n";
}

string infixToPost(string infixexp) //main conversion routine
{
    string postfix="";
    std::vector<char> STACK;
    ///Q. removed vector data type arguement
    if(!verify(infixexp))
        return postfix; // checks for extra operators
    int countRP=0; //count of right parenthesis
    for(int i=0;i<infixexp.length();i++)
    {
        print(infixexp[i],STACK,postfix);
        if(STACK.empty() && (!postfix.length())) // if stack is empty and also postexpression is empty
        {
            if(isParent(infixexp[i])==1) //If encounter the right parent when stack and post exp is empty
            {
                postfix="";
                return postfix;
            }
            else if(isOpperator(infixexp[i]))//if encounter operatr even before expression begins
            {
                postfix="";
                return postfix;
            }
            else if(isParent(infixexp[i])==-1) // on left parent append
            {
                STACK.push_back(infixexp[i]);
                countRP++;
            }
            else// on anything else append
            {
                postfix.push_back(infixexp[i]); //
            }
        }
        else
        {
            if(isalpha(infixexp[i]))// if variable
            {
                postfix.push_back(infixexp[i]);

            }
            else if(isParent(infixexp[i])) // if parenthesis
            {
                if(infixexp[i]=='(')
                {
                    countRP++;
                    STACK.push_back(infixexp[i]);
                }
                else if(infixexp[i]==')')
                {
                    if(countRP==0)
                    {
                        postfix="";
                        return postfix;
                    }
                    else
                    {
                      while(STACK.back()!='(') // empty based on parenthesis match
                      { ///Q.LOGICAL error of not emptying the stack when met with right parenthesis
                          postfix.push_back(STACK.back());
                          STACK.pop_back();
                      }
                      STACK.pop_back();
                      countRP--;
                    }
                }

            }
            else if(isOpperator(infixexp[i])) //if operator
            {
                if(!STACK.empty()) //checks for stack being not empty
                {
                     if(isParent(STACK.back())) //checks last element as parenthesis
                     {
                         STACK.push_back(infixexp[i]);
                     } /// Q push_back being made into push-back
                     else if(isOpperator(STACK.back())) // checks for it being operator
                     {
                         if(OppPrecedence(infixexp[i],STACK.back())>=0)
                         {
                            STACK.push_back(infixexp[i]);
                         }
                         else
                         {
                           postfix.push_back(STACK.back());
                           STACK.pop_back();
                           STACK.push_back(infixexp[i]);
                         }
                     }
                }
                 else
                 {
                    STACK.push_back(infixexp[i]);       //  push if nothing special

                 }
            }
        }
    }

    if(countRP!=0) // chceks for count of the right = left parenthesis
        {postfix=""; return postfix;}
    while(!STACK.empty()) // empties the stack if anything remains
    {
        postfix.push_back(STACK.back());
        ///Q. No data is pushed from Stack.back
        STACK.pop_back();
    }
    return postfix;
    ///Q. LOGICAL infix expression being returned

}



int main()
{


    string infixexp="A*(B+C)/(C+D)";
    string postexp=infixToPost(infixexp);
    if(postexp.length())
    {///Q. postexp.length() being written as postexp.length
        cout<<postexp;
    }
    else
    {
        cout<<"\nEHHHH the expression is wrong DOC !!";
    }

}
