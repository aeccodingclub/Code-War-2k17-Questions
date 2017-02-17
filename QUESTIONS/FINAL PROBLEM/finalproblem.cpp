#include<iostream>

/*
Q1. The following iterative sequence is defined for the set of positive integers:

n ? n/2 (n is even)
n ? 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13 ? 40 ? 20 ? 10 ? 5 ? 16 ? 8 ? 4 ? 2 ? 1

It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.
Create a general purpose function to create a list and store the collatz sequence length for each positive integer. Given argument n with list ranging from 1-N.

Q2.By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

              3
             7 4
            2 4 6
           8 5 9 3

That is, 3 + 7 + 4 + 9 = 23.

Find the maximum total from top to bottom in triangle.(also the maximum sum path)
But the triangle(tree) you will have to generate on your own.
So use the above Colatz series list to populate such a tree as above.
Once generated you have the tree or input to operate on based on N steps of the trees the input will be given to test the execution.

*/

using namespace std;

int algo(int n)
{
    if(n%2==0)
        return n/2;
    else
        return 3*n+1;
}

//generate collatz steps
int collatz(int steps,int **ar)
{
    int total=steps*(steps+1)/2;
    int *li=new int[total+1];
    int t;int count=0;
    li[1]=1;
    for(int i=2;i<(total+1);i++)
    {   count=0;
        t=i;

        while(t!=1)
        {
            if(t<i)
            {
                count+=li[t];
                count--;
                break;

            }
            t=algo(t);
            count++;
        }
        count++;
        li[i]=count;
    }


    int k=1;
    for(int i=0;i<steps;i++)
    {
        for(int j=0;j<=i;j++)
        {
            ar[i][j]=li[k];k++;
            cout<<ar[i][j]<<" ";

        }
        cout<<"\n";
    }

}


//run the dynamic algortithm
int maxpathsum(int steps,int **ar)
{   unsigned long long int max=0;
    for(int i=steps-1;i>=0;i--)
    {
        for(int k=0;k<=i-1;k++)
        {
            max=ar[i][k]>ar[i][k+1]?ar[i][k]:ar[i][k+1];
            ar[i-1][k]+=max;
        }
    }
    cout<<endl<<ar[0][0];
}

int main()
{
    int steps=10;
    int **ar=new int*[steps];
    for(int i=0;i<steps;i++)
        ar[i]=new int[i];
    collatz(steps,ar);
    maxpathsum(steps,ar);




}
