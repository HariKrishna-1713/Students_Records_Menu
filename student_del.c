//stud_del.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

student *stud_del(student *head)
{
    char choice;

    if(head == NULL)
    {
        printf("Student DB is empty\n");
        return head;
    }

    printf("\n");
    printf("R/r : Delete using Roll Number\n");
    printf("N/n : Delete using Name\n");

    printf("\n");
    printf("Enter your choice: ");
    scanf(" %c", &choice);

    switch(choice)
    {

        case 'r':
        case 'R':
        {
            int rollno;
            student *temp;
            student *prev;

            printf("Enter the Student Rollno you want to delete: ");
            scanf("%d", &rollno);

            temp = head;
            prev = NULL;

            while(temp != NULL)
            {
                if(temp->rollno == rollno)
                {
                    if(prev == NULL)
                    {
                        head = temp->link;
                    }
                    else
                    {
                        prev->link = temp->link;
                    }

                    free(temp);

                    printf("Record deleted successfully\n");
                    return head;
                }

                prev = temp;
                temp = temp->link;
            }

            printf("Student Rollno not found in DB\n");
            break;
        }


        case 'n':
        case 'N':
        {
            char name[50];
            int rollno;
            int found = 0;

            student *temp;
            student *prev;

            printf("Enter the Student_Name: ");
            scanf("%49s", name);

            temp = head;

            printf("\n");
            printf("+---------+------------------------------------------------+------------+\n");
            printf("| Roll No |                   Student Name                 | Percentage |\n");
            printf("+---------+------------------------------------------------+------------+\n");

            while(temp != NULL)
            {
                if(strcmp(temp->student_name, name) == 0)
                {
                    printf("| %-7d | %-46s | %-10.2f |\n",
                           temp->rollno,
                           temp->student_name,
                           temp->percentage);

                    found = 1;
                }

                temp = temp->link;
            }

            printf("+---------+------------------------------------------------+------------+\n");

            if(found == 0)
            {
                printf("Student Name not found\n");
                break;
            }

            printf("\n");
            printf("Enter the Roll Number of the record you want to delete: ");
            scanf("%d", &rollno);

            temp = head;
            prev = NULL;

            while(temp != NULL)
            {
                if(temp->rollno == rollno &&
                   strcmp(temp->student_name, name) == 0)
                {
                    if(prev == NULL)
                    {
                        head = temp->link;
                    }
                    else
                    {
                        prev->link = temp->link;
                    }

                    free(temp);

                    printf("Record deleted successfully\n");
                    return head;
                }

                prev = temp;
                temp = temp->link;
            }

            printf("Record with the given Name and Roll Number not found\n");
            break;
        }


        default:
            printf("Invalid input\n");
            break;
    }

    return head;
}