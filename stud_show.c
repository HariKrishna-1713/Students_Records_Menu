//stud_show.c

#include <stdio.h>
#define CYAN    "\033[38;5;51m"
#define GREEN   "\033[38;5;46m"
#define YELLOW  "\033[38;5;226m"
#define RED     "\033[38;5;196m"
#define RESET   "\033[0m"

void stud_show(student *head)
{
    student *temp = head;

    if(temp == NULL)
    {
        printf("Student Record is empty\n");
        return;
    }

    printf("\n");

    /* Table Top Border */
    printf("+---------+------------------------------------------------+------------+\n");

    /* Table Heading */
     printf("| " CYAN "%-7s" RESET
           " | " CYAN "%-46s" RESET
           " | " CYAN "%-10s" RESET " |\n",
           "Roll No", "Student Name", "Percentage");

    /* Table Header Separator */
    printf("+---------+------------------------------------------------+------------+\n");

    while(temp != NULL)
    {
        if(temp->percentage >= 90)
        {
                printf("| %-7d | %-46s | " GREEN "%-10.2f" RESET " |\n",
                temp->rollno,
                temp->student_name,
                temp->percentage);
        }

        else if(temp->percentage >= 60)
        {
                printf("| %-7d | %-46s | " YELLOW "%-10.2f" RESET " |\n",
                temp->rollno,
                temp->student_name,
                temp->percentage);
        }

        else
        {
                printf("| %-7d | %-46s | " RED "%-10.2f" RESET " |\n",
                temp->rollno,
                temp->student_name,
                temp->percentage);
        }

        temp = temp->link;
    }

    printf("+---------+------------------------------------------------+------------+\n");
}