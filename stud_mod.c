//stud_mod.c

#include <stdio.h>
#include <string.h>

student *stud_mod(student *head)
{
    char search_choice;
    char modify_choice;

    if(head == NULL)
    {
        printf("Student DB is empty\n");
        return head;
    }

    printf("\n");
    printf("R/r : Roll Number\n");
    printf("N/n : Name\n");
    printf("P/p : Percentage\n");

    printf("\n");
    printf("Enter Your Choice: ");
    scanf(" %c", &search_choice);

    student *temp;
    student *selected = NULL;

    switch(search_choice)
    {
        /* SEARCH USING ROLL NUMBER */
        case 'r':
        case 'R':
        {
            int rollno;

            printf("Enter Roll Number: ");
            if(scanf("%d", &rollno) != 1)
            {
                printf("Invalid Roll Number\n");
                return head;
            }

            temp = head;

            while(temp != NULL)
            {
                if(temp->rollno == rollno)
                {
                    selected = temp;
                    break;
                }

                temp = temp->link;
            }

            if(selected == NULL)
            {
                printf("Student Roll Number not found\n");
                return head;
            }

            break;
        }


        /* SEARCH USING NAME */
        case 'n':
        case 'N':
        {
            char name[50];
            int rollno;
            int found = 0;

            printf("Enter Student Name: ");
            scanf("%49s", name);

            temp = head;
            int flag = 1;
            while(temp != NULL)
            {
                if(strcmp(temp->student_name, name) == 0)
                {
                    if(flag)
                    {
                        printf("\n");
                        printf("+---------+------------------------------------------------+------------+\n");
                        printf("| Roll No |                   Student Name                 | Percentage |\n");
                        printf("+---------+------------------------------------------------+------------+\n");

                        flag = 0;
                    }
                    printf("| %-7d | %-46s | %-10.2f |\n",
                           temp->rollno,
                           temp->student_name,
                           temp->percentage);

                    found = 1;
                }

                temp = temp->link;
            }
            if(found)
                printf("+---------+------------------------------------------------+------------+\n");

            else if(found == 0)
            {
                printf("Student Name not found\n");
                return head;
            }

            printf("\n");
            printf("Enter Roll Number of the record to modify: ");
            if(scanf("%d", &rollno) != 1)
            {
                printf("Invalid Roll Number\n");
                return head;
            }

            temp = head;

            while(temp != NULL)
            {
                if(temp->rollno == rollno &&
                   strcmp(temp->student_name, name) == 0)
                {
                    selected = temp;
                    break;
                }

                temp = temp->link;
            }

            if(selected == NULL)
            {
                printf("Record with given Name and Roll Number not found\n");
                return head;
            }

            break;
        }


        /* SEARCH USING PERCENTAGE */
        case 'p':
        case 'P':
        {
            float percentage;
            int rollno;
            int found = 0;

            printf("Enter Percentage: ");
            if(scanf("%f", &percentage) != 1)
            {
                printf("Invalid Percentage\n");
                 return head;
            }
            printf("\n");
            printf("+---------+------------------------------------------------+------------+\n");
            printf("| Roll No |                   Student Name                 | Percentage |\n");
            printf("+---------+------------------------------------------------+------------+\n");

            temp = head;

            while(temp != NULL)
            {
                if(temp->percentage == percentage)
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
                printf("Percentage not found\n");
                return head;
            }

            printf("\n");
            printf("Enter Roll Number of the record to modify: ");
            scanf("%d", &rollno);

            temp = head;

            while(temp != NULL)
            {
                if(temp->rollno == rollno &&
                   temp->percentage == percentage)
                {
                    selected = temp;
                    break;
                }

                temp = temp->link;
            }

            if(selected == NULL)
            {
                printf("Record with given Percentage and Roll Number not found\n");
                return head;
            }

            break;
        }


        default:
            printf("Invalid input\n");
            return head;
    }


    /* STEP 2 : MODIFY FIELD */

    printf("\n");
    printf("N/n : Name\n");
    printf("P/p : Percentage\n");

    printf("\n");
    printf("Enter Your Choice: ");
    scanf(" %c", &modify_choice);

    switch(modify_choice)
    {
        case 'n':
        case 'N':
            printf("Enter New Student Name: ");
            scanf("%49s", selected->student_name);

            printf("Student Name modified successfully\n");
            break;


        case 'p':
        case 'P':
            printf("Enter New Percentage: ");
            scanf("%f", &selected->percentage);

            printf("Student Percentage modified successfully\n");
            break;


        default:
            printf("Invalid input\n");
            break;
    }

    return head;
}