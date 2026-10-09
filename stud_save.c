//stud_save.c

#include<stdio.h>

void stud_save(student *head)
{
        FILE *fp = NULL;
        student *temp;
        fp = fopen("/home/v25he11g2/cProject/studentDB","w");

        if(fp == NULL)
        {
                printf("File cannot be opened\n");
                return;
        }

        temp = head;

        while(temp != NULL)
        {
                fprintf(fp, "%d %s %.2f\n",
                temp->rollno,
                temp->student_name,
                temp->percentage);

        temp = temp->link;
        }

        fclose(fp);

        printf("Student records saved successfully\n");
}