#include<stdio.h>
#include<stdlib.h>

student *stud_load()
{
    FILE *fp;
    student *head = NULL;
    student *newnode;
    student *temp;

    fp = fopen("student.dat", "r");

    if(fp == NULL)
    {
        printf("No previous student records found\n");
        return NULL;
    }

    while(1)
    {
        newnode = malloc(sizeof(student));

        if(newnode == NULL)
        {
            printf("Memory is not allocated\n");
            fclose(fp);
            return head;
        }

        if(fscanf(fp, "%d %49s %f",
                  &newnode->rollno,
                  newnode->student_name,
                  &newnode->percentage) != 3)
        {
            free(newnode);
            break;
        }

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

        cnt = newnode->rollno + 1;
    }

    fclose(fp);

    return head;
}