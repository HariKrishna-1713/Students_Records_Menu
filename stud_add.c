// stud_add.c

#include<stdio.h>
#include<stdlib.h>

int cnt = 1;

typedef struct student
{
    int rollno;
    char student_name[50];
    float percentage;

    struct student *link;
} student;

student *stud_add(student *head)
{
    student *newnode, *temp;
    int max_rollno = 0;

    newnode = malloc(sizeof(student));

    if(newnode == NULL)
    {
        printf("Memory is not allocated\n");
        return head;
    }

    /* Find the highest existing Roll Number */
    temp = head;

    while(temp != NULL)
    {
        if(temp->rollno > max_rollno)
        {
            max_rollno = temp->rollno;
        }

        temp = temp->link;
    }

    /* Assign next Roll Number */
    newnode->rollno = max_rollno + 1;

    printf("Enter Student_name\n");
    scanf("%49s", newnode->student_name);

    printf("Enter percentage\n");
    scanf("%f", &newnode->percentage);

    newnode->link = NULL;

    if(head == NULL)
    {
        head = newnode;
    }
    else
    {
        temp = head;

        while(temp->link != NULL)
        {
            temp = temp->link;
        }

        temp->link = newnode;
    }

    return head;
}