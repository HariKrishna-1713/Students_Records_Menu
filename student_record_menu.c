/*** student_record_menu.c ***/

#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>


#include "/home/v25he11g2/cProject/stud_add.c"
#include "/home/v25he11g2/cProject/stud_del.c"
#include "/home/v25he11g2/cProject/stud_mod.c"
#include "/home/v25he11g2/cProject/stud_show.c"
#include "/home/v25he11g2/cProject/stud_sort.c"
#include "/home/v25he11g2/cProject/stud_save.c"
#include "/home/v25he11g2/cProject/stud_load.c"

int main()
{
        student *DB = NULL;
        DB = stud_load();
        char choice;

        while(1)
        {
        system("clear");
        printf("\n");

        printf("**** STUDENT RECORD MENU ****\n");

        printf("\n");

        printf("A/a : Add New Record\n");
        printf("D/d : Delete a Record\n");
        printf("S/s : Show the List\n");
        printf("M/m : Modify a Record\n");
        printf("V/v : Save\n");
        printf("T/t : Sort the List\n");
        printf("E/e : Exit\n");

        printf("\n");

        printf("Enter your choice\n");

        //__fpurge(stdin);
        scanf(" %c", &choice);

        switch(choice)
        {
                case 'a':

                case 'A':
                        DB = stud_add(DB);
                        break;

                case 'd':

                case 'D':
                        DB = stud_del(DB);
                        break;

                case 's':

                case 'S':
                        stud_show(DB);
                        break;

                case 'm':

                case 'M':
                        DB = stud_mod(DB);
                        break;

                case 'v':

                case 'V':
                        stud_save(DB);
                        break;

                case 't':

                case 'T':
                        stud_sort(DB);
                        break;

                case 'e':

                case 'E':
                        exit(0);

                default :
                        printf("Invalid input\n");
                        break;
        }
        printf("\nPress Enter to continue...");
        __fpurge(stdin);
        getchar();
        }
        return 0;
}