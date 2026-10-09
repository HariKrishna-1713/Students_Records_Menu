//stud_sort.c

#include<stdio.h>
#include<string.h>

void stud_sort(student *head)
{
        char choice;
        student *i, *j;

        if(head == NULL)
        {
                printf("Student DB is empty\n");
                return;
        }

        printf("\n");
        printf("N/n : Sort by Name \n");
        printf("P/p : Sort by Percentage \n");
        printf("A/a : Sort by Ascending rollno\n");
        printf("D/d : Sort by Descending roolno\n");

        printf("\n");
        printf("Enter your choice\n");
        scanf(" %c", &choice);
        switch(choice)
        {

           case 'n':
           case 'N':
                    for(i = head; i != NULL; i = i->link)
                    {
                        for(j = i->link; j != NULL; j = j->link)
                        {
                                   if(strcmp(i->student_name, j->student_name)>0)
                                   {
                                         int temp_rollno;
                                         char temp_name[50];
                                         float temp_percentage;

                                         temp_rollno = i->rollno;
                                         i->rollno = j->rollno;
                                         j->rollno = temp_rollno;

                                         strcpy(temp_name, i->student_name);
                                         strcpy(i->student_name, j->student_name);
                                         strcpy(j->student_name, temp_name);

                                         temp_percentage = i->percentage;
                                         i->percentage = j->percentage;
                                         j->percentage = temp_percentage;
                                   }
                        }
                    }

                    printf("Record sorted by Name!\n");
                    break;


                case 'p':
                case 'P':
                         for(i = head; i != NULL; i = i->link)
                         {
                                for(j = i->link; j != NULL; j = j->link)
                                {
                                   if(i->percentage < j->percentage)
                                   {
                                         int temp_rollno;
                                         char temp_name[50];
                                         float temp_percentage;

                                         temp_rollno = i->rollno;
                                         i->rollno = j->rollno;
                                         j->rollno = temp_rollno;

                                         strcpy(temp_name, i->student_name);
                                         strcpy(i->student_name, j->student_name);
                                         strcpy(j->student_name, temp_name);

                                         temp_percentage = i->percentage;
                                         i->percentage = j->percentage;
                                         j->percentage = temp_percentage;
                                   }
                                }
                        }

                        printf("Record sorted by Percentage!\n");
                        break;

                case 'a':
                case 'A':
                         for(i = head; i != NULL; i = i->link)
                         {
                                for(j = i->link; j != NULL; j = j->link)
                                {
                                   if(i->rollno > j->rollno)
                                   {
                                         int temp_rollno;
                                         char temp_name[50];
                                         float temp_percentage;

                                         temp_rollno = i->rollno;
                                         i->rollno = j->rollno;
                                         j->rollno = temp_rollno;

                                         strcpy(temp_name, i->student_name);
                                         strcpy(i->student_name, j->student_name);
                                         strcpy(j->student_name, temp_name);

                                         temp_percentage = i->percentage;
                                         i->percentage = j->percentage;
                                         j->percentage = temp_percentage;
                                   }
                                }
                        }

                        printf("Record sorted by Ascending Rollno!\n");
                        break;

                case 'd':
                case 'D':
                         for(i = head; i != NULL; i = i->link)
                         {
                                for(j = i->link; j != NULL; j = j->link)
                                {
                                   if(i->rollno < j->rollno)
                                   {
                                         int temp_rollno;
                                         char temp_name[50];
                                         float temp_percentage;

                                         temp_rollno = i->rollno;
                                         i->rollno = j->rollno;
                                         j->rollno = temp_rollno;

                                         strcpy(temp_name, i->student_name);
                                         strcpy(i->student_name, j->student_name);
                                         strcpy(j->student_name, temp_name);

                                         temp_percentage = i->percentage;
                                         i->percentage = j->percentage;
                                         j->percentage = temp_percentage;
                                   }
                                }
                        }

                        printf("Record sorted by Descending Rollno!\n");
                        break;
                }
 }