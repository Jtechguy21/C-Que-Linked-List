#include <stdio.h>
#include <stdlib.h>

/*
Linked list Que Implementation
Author: John Toledo
Written in: C

*/

typedef struct node
{

    int val;
    struct node* next;

}node;


//typedef so i dont have to keep typing pointer* to my struct
typedef node* boxptr;

//Displays the number that will be pushed onto the list
//Que implementation of linked list
//pushes a value onto a newly created Node
void push(boxptr* head,int val)
{
    printf("Pushing.. %d \n",val);

    //Allocating space for new node, and inserting values into it.
    boxptr newnode=(node*)malloc(sizeof(node));

    //inserts values
    newnode->val=val;

    //if there is nothing on the list, we make the head point to the new node
    //and the new node now takes the attributes of head, which means new node now points to null
    if((*head) == NULL)
    {
    newnode->next=(*head);
    (*head)=newnode;
    }


    boxptr walker=(*head);

    while(walker->next!=NULL)
    {

        walker=walker->next;
    }

    walker->next=newnode;
    newnode->next=NULL;

}

//Displays everything in my linked list

void display(boxptr head)
{

    boxptr walker=(head);

    //empty list
    if(walker==NULL)
    {
        printf("There are no nodes currently in the linked list\n");
        return;
    }


    //print out all the value in my list until we hit null
    //walker!=NULL allwos out to access and print out the last nodes value also
    while(walker!=NULL)
    {
        printf("[%d]  ",walker->val);
        walker=walker->next;
    }
    //exit

    printf("\n\n");
    return;

}


//This function delete the very 1st node in the list, and readjust the head(since in a que, the head always points to the 1st node that got pushed
void popfirst(boxptr* head)
{

    boxptr walker=(*head);

    //empty list
    if((*head)==NULL)
    {
        printf("Nothing to pop. Empty List!!\n");
        return;
    }

    //if we reach this we don't have an empty list, and free the 1st node, and readjust the head to point to the next node
    boxptr temp;
    temp=walker;
    walker=walker->next;
    free(temp);
    (*head)=walker;
    printf("Pop Successful!\n");
    return;

}


void pop(boxptr* head, int val)
{
   // printf("Value coming in! %d",val);

//CASE 1, we have an empty-list, get the f out of here.
    if((*head)==NULL)
        {
        printf("Empty List!!\n");
        return;
        }

    boxptr walker=(*head);
    boxptr temp;
    boxptr prev;

    //CASE2
    //if the current node we are at(1st node) holds the value we want
    //delete node, and readjust the head
    //the 1st node that heads points to, that node holds the current value you want. so we don't even have to traverse,
    //and delete it and readjust the head.

    if((walker->val)==val)
        {
        printf("Found target value in the 1st node,popping %d\n\n",val);
        temp=walker;
        (walker)=walker->next;
        (*head)=walker;
        free(temp);
        return;
        }

    //CASE 3    the node is not the 1st node, and we don't have an empty list, so lets traverse and look for it.
    while(walker!=NULL)
    {
        //if we find the value, we break out of our traversal
        if(walker->val==val)
        {
            printf("We found %d in one of the nodes...\n",val);
            break;
        }

        prev=walker;
        walker=walker->next;
    }

    //this means we searched through the whole list and didn't find the value
    if(walker==NULL)
        {
        printf("We did not find any nodes with corresponding value! \n");
        printf("No popping was performed \n\n");
        return;
        }

    //this means we found the value through our traversal, and now we are making readjustments
    else

    temp=walker;
    walker=walker->next;
    free(temp);
    prev->next=walker;
    printf("Pop was successful! \n\n");
    return;



}

void poplast(boxptr* head)
{

    //setting up my traversal variable
    boxptr walker=(*head);


    //will be used to free the node
    boxptr temp;

    //will be used to store the address/location of the previos node(1-before) current node we are
    boxptr prev;

    //case 1-we  have an empty list, we don't want to segfault so we exit
    if((*head)==NULL)
   {
    printf("Empty List, nothing to pop\n");
    return;
   }

   //case 2- we only have one node in the linked list whom points to NULL
   //So we delete that node, and now the head points to NULL
    if(walker->next==NULL)
       {
        temp=walker;
        free(temp);
        (*head)=NULL;
        return;
       }

    //case 3- traversal to pop the last node in the linked list, since we don't have an empty list, and we have more than 1 node in the list

    while(walker->next!=NULL)
    {
    prev=walker;
    walker=walker->next;
    }

    //if we reach this point its time to delete the last node.
    //temp=walker(walker is currently the address of the last node)
    temp=walker;
    //deletes last node
    free(temp);
    //prev node now is the last node, so now points to NULL
    prev->next=NULL;
    printf("Success!\n");


}

void displaymenu()
{
        printf("___________________________________\n");
        printf("  Linked list operations menu:\n");
        printf("___________________________________\n");
        printf("p - for push + int value\n");
        printf("d - for display the values in the linked list\n");
        printf("f - for popping the the 1st item in the list\n");
        printf("l - for popping the last item in the linked list\n");
        printf("o - for pop + int value. Will search to see if value is anywhere in the list and delete it, it found\n");
        printf("e - to exit program\n");
        printf("Please Enter command now:\n\n");
        return;
}

int main()
{

    //dummy node
    boxptr head=NULL;


    //controls menu
    char dc;

    //value to search for if applicable
    int vpush;


    //Menu for linked list operations
        displaymenu();

//bool variable so we can exit the loop for our linked list operations
int done=0;

while(done==0)
{
        scanf("%c",&dc);


        //if we are pushing or popping we also ask for a value which is vpush
        //if we are not pushing/popping a certain value, we dont even ask for vpush(which is an int)skips over the scanf
        if(dc=='p'||dc=='o')
           scanf("%d",&vpush);


        switch(dc)
        {
        case 'p':
        printf("Pushing selected!\n\n");
        push(&head,vpush);
        displaymenu();
        break;

        case 'd':
        printf("Display values selected!\n\n");
        display(head);
        displaymenu();
        break;

        case 'f':
        printf("Popping 1st node selected!\n\n");
        popfirst(&head);
        displaymenu();
        break;

        case 'l':
        printf("Popping last Node selected!\n\n");
        poplast(&head);
        displaymenu();
        break;

        case 'e':
        printf("Exiting Program.. . . .. . . . .\n");
        done=1;
        break;

        case 'o':
        printf("Searching for %d and popping that node if found Selected!\n\n",vpush);
        pop(&head,vpush);
        displaymenu();



        }

}


    return 0;
}
