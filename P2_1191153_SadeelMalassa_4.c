#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Sadeel Malassa_1191153_4

typedef struct node* PtrToNode;
typedef struct node* Stack;

//functions
int IsEmpty( Stack S );
void MakeEmpty( Stack S );
void Pop( Stack S );
void Push( char comm[100], Stack S );
char *Top( Stack S );
void DisposeStack( Stack S );
void print(Stack S,Stack C,int n );
void reverse(Stack C,Stack R,int n);
void save(Stack C,Stack R,int n);

//define the struct of a node
struct node
{
    char Element[100];
    PtrToNode Next;
};


//checking if a stack is empty
int IsEmpty( Stack S )
{
    return S->Next == NULL;
}

//create Stack
Stack CreateStack( )
{
    struct node* temp = (struct node*)malloc( sizeof( struct node ) );
    if( temp == NULL )
        printf( "Out of space!" );
    temp->Next = NULL;
    MakeEmpty( temp );
    return temp;
}

//delete the elmenets of a stack and make it empty
void MakeEmpty( Stack S )
{

    if( S == NULL )
        printf( "Out of space!");
    else
        while( !IsEmpty( S ))
            Pop( S );
}

//delete the last node
void Pop( Stack S )
{
    PtrToNode firstCell;
    if( IsEmpty( S ) )
        printf( "Empty stack pop " );
    else
    {
        firstCell = S->Next;
        S->Next = S->Next->Next;
        free( firstCell );
    }
}

//takes all elements in the stack s and move them to stack c using push and pop to reverse the the order of elements
void print( Stack S,Stack C,int n )
{

    if( IsEmpty( S ) )
        printf( "Empty stack print " );
    else
    {
        for(int i=0; i<n; i++)
        {
            Push(Top(S),C);
            Pop(S);
        }
    }

}

//move the elements from c to R to change the order of the entered elements and print them on the same order they were entered on
void reverse(Stack C,Stack R,int n)
{
    if( IsEmpty( C ) )
        printf( "Empty stack r" );
    else
    {
        for (int i=0; i<n; i++)
        {
            Push(Top(C),R);
            Pop(C);
            printf("MyCommand -> %s\n",Top(R));
        }
    }


}
//printing the top of a stack

char *Top( Stack S )
{
    if( !IsEmpty( S ) )
    {
        return S->Next->Element;
    }
    printf( "Empty stack t" );
    return NULL;
}

//adding elements to stack
void Push( char comm[100], Stack S )
{
    PtrToNode temp;
    temp = ( Stack )malloc( sizeof( struct node ) );
    if( temp == NULL)
        printf( "Out of space!" );
    else
    {
        strcpy(temp->Element,comm);
        temp->Next = S->Next;
        S->Next = temp;
    }
}

void DisposeStack( Stack S )
{
    MakeEmpty( S );
    free( S );
}

//remove the last entered element
void undo(Stack S,Stack U)
{
    Push(Top(S),U);
    Pop(S);
}

//save all the edited elements in output.txt file
void save(Stack C,Stack R,int n)
{
    FILE *out;
    out = fopen("output.txt","w");
    if( IsEmpty( C ) )
        printf( "Empty stack r" );
    else
    {
        for (int i=0; i<n; i++)
        {
            Push(Top(C),R);
            Pop(C);
            fprintf(out,"MyCommand -> %s \n", Top(R) );
        }
    }
    fclose(out);
}

int main()
{
    //creating Stacks
    Stack S = CreateStack();
    S->Next=NULL;
    Stack C = CreateStack();
    C->Next=NULL;
    Stack R = CreateStack();
    R->Next=NULL;
    Stack U = CreateStack();
    U->Next=NULL;

    char comm[100];
    int n=0;
    int i=0;

    //while loop to take statements and apply the functions on them
    while(i==0)
    {

        printf("MyCommand -> ");
        gets(comm);
        if (strcmp(strlwr(comm), "print") == 0)
        {
            if(!IsEmpty(S))
            {
                print(S,C,n);
                reverse(C,R,n);
            }
            else
            {
                print(R,C,n);
                reverse(C,S,n);
            }


        }
        else if (strcmp(strlwr(comm), "undo") == 0)
        {
            if(!IsEmpty(S))
            {
                n=n-1;
                undo(S,U);
                print(S,C,n);
                reverse(C,R,n);
            }
            else
            {
                n=n-1;
                undo(R,U);
                print(R,C,n);
                reverse(C,S,n);
            }
        }
        else if (strcmp(strlwr(comm),"redo") == 0)
        {
            if(!IsEmpty(S))
            {
                if( IsEmpty( U ) )
                {
                    printf("nothing to redo ! \n");
                }
                else
                {
                    n++;
                    Push(Top(U),S);
                    Pop(U);
                    print(S,C,n);
                    reverse(C,R,n);
                }
            }
            else
            {
                if( IsEmpty( U ) )
                {
                    printf("nothing to redo ! \n");
                }
                else
                {
                    n++;
                    Push(Top(U),R);
                    Pop(U);
                    print(R,C,n);
                    reverse(C,S,n);
                }
            }

        }
        else if (strcmp(strlwr(comm),"quit") == 0)
        {
            if(!IsEmpty(S))
            {
                print(S,C,n);
                save(C,R,n);
            }
            else
            {
                print(R,C,n);
                save(C,S,n);
            }
            printf("thank you !\n");
            i=1;
        }
        else if (strcmp(strlwr(comm),"save") == 0)
        {

            if(!IsEmpty(S))
            {
                print(S,C,n);
                save(C,R,n);
            }
            else
            {
                print(R,C,n);
                save(C,S,n);
            }
        }
        else
        {
            if(!IsEmpty(S))
            {
                Push(comm,S);
                n=n+1;
            }
            else
            {
                Push(comm,R);
                n=n+1;
            }
        }


    }
    return 0;
}


