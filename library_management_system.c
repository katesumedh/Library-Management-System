#include <stdio.h>
#include <string.h>
#include <conio.h>
struct Stu
{
    int bkid;
    char name[30], atname[30], isdate[10];  
} S[100], T;
int no, i, cnt, n;
FILE *f1;

// heading code start

   

void headMessage(const char *message)
{
    clrscr();
    printf("\n\t###################################################################");
    printf("\n\t########                                                   ########");
    printf("\n\t########      Library management System Project in C       ########");
    printf("\n\t########                                                   ########");
    printf("\n\t###################################################################");
    printf("\n\t-------------------------------------------------------------------\n");
    printf("\n\t\t%s", message);
    printf("\n\t--------------------------------------------------------------------");
    
          
}
void welcomeMessage()
{
    clrscr();
    printf("\n\n\n");
    printf("\n\t*------------------*\n");
    printf("\n\t      =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t      =                 WELCOME                   =");
    printf("\n\t      =                   TO                      =");
    printf("\n\t      =                 LIBRARY                   =");
    printf("\n\t      =               MANAGEMENT                  =");
    printf("\n\t      =                 SYSTEM                    =");
    printf("\n\t      =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t*------------------*\n");
    printf("\n\n\n\t Enter any key to continue.....");
    getch();
}

// heading code end

int search(int no)
{
    for (i = 0; i < cnt; i++)
    {
        if (S[i].bkid == no)
            return (i);
    }
    return (-1);
}
void add()
{
    int cont;

    do
    {
        clrscr();
        headMessage("ADD NEW BOOKS");

        printf("\nEnter Book ID  ");
        scanf("%d", &no);
        i = search(no);
        if (i == -1)
        {
            S[cnt].bkid = no;
            printf("\nEnter book name- ");
            fflush(stdin);
            gets(S[cnt].name);
            printf("\nEnter book Author name- ");
            fflush(stdin);
            gets(S[cnt].atname);
            printf("\nEnter book issue date in DD/MM/YYYY format only- ");
            fflush(stdin);
            gets(S[cnt].isdate);

            cnt++;
        }
        else
            printf("\nRecord already present");

        printf("\nDo you want to continue?  Press 1:YES    Press 0:NO \nEnter Choice- ");
        scanf("%d", &cont);
    } while (cont == 1);
}
void mod()
{
    int cont;

    do
    {
        clrscr();
        headMessage("MODIFY BOOKS");

        printf("\nEnter Book ID- ");
        scanf("%d", &no);
        i = search(no);
        if (i != -1)
        {
            printf("\nOld data : %d  %s %s %s", S[i].bkid, S[i].name, S[i].atname, S[i].isdate);
            printf("\nEnter new book name- ");
            fflush(stdin);
            gets(S[i].name);
            printf("\nEnter book author name- ");
            fflush(stdin);
            gets(S[i].atname);
            printf("\nEnter book issue date in DD/MM/YYYY format only- ");
            fflush(stdin);
            gets(S[i].isdate);

            printf("\nRecord modified !!!");
        }
        else
            printf("\nRecord not present ");

        printf("\nDo you want to continue?  Press 1:YES    Press 0:NO");
        scanf("%d", &cont);
    } while (cont == 1);
}
void del()
{
    int cont;

    do
    {
        clrscr();
        headMessage("delete BOOKS");

        printf("\nEnter Book ID  ");
        scanf("%d", &no);
        i = search(no);
        if (i != -1)
        {
            S[i].bkid = -1;
            printf("\nRecord deleted");
        }
        else
            printf("\nRecord not present");

        printf("\nDo you want to continue?  Press 1:YES    Press 0:NO");
        scanf("%d", &cont);
    } while (cont == 1);
}
void disp()
{
    clrscr();
    headMessage("DISPLAYING ALL BOOKS");
    printf("Book ID        Book name       Author name        Issue date");
    for (i = 0; i < cnt; i++)
    {
        if (S[i].bkid != -1)
            printf("\n%4d  %-30s  %-30s  %-30s ", S[i].bkid, S[i].name, S[i].atname, S[i].isdate);
    }
}

void myRead()
{
    f1 = fopen("lib.dat", "r");
    if (f1 == NULL)
    {
        f1 = fopen("lib.dat", "w");
        cnt = 0;
    }
    else
    { 
        fseek(f1, 0, SEEK_END);
        cnt = ftell(f1) / sizeof(T);       
        fseek(f1, 0, SEEK_SET);
        fread(S, sizeof(T), cnt, f1);
    }
    fclose(f1);
}
void myWrite()
{
    f1 = fopen("lib.dat", "w");
    fwrite(S, sizeof(T), cnt, f1);
    fclose(f1);
}
void sort()
{
    int i, j;
    for (i = 0; i < cnt - 1; i++)
    {
        for (j = i + 1; j < cnt; j++)
        {
            if (S[i].bkid > S[j].bkid)
            {
                T = S[i];
                S[i] = S[j];
                S[j] = T;
            }
        }
    }
}

void menu()
{
    int ch;
    myRead();
    do
    {
        clrscr();
        headMessage("MENU");
        printf("\n\n\t\tMenu\n\n\t1.Add \n\t2.Mod \n\t3.Delete \n\t4.Disp \n\t5.Exit \n\t\tENTER CHOICE- ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            add();
            break;
        case 2:
            mod();
            break;
        case 3:
            del();
            break;
        case 4:
            disp();
            break;
        case 5:
            printf("\n Coming out!!!");
            break;
        default:
            printf("\n Wrong choice");
        }
        getch();
    } while (ch != 5);
    sort();
    myWrite();

    getch();
}
void login()
{
    int n = 0;
start:
    if (strcmp(getpass("Enter Password  "), "aryan") == 0)
        menu();
    else
    {
        n++;
        printf("\n Enter correct password -- %d Attempts Remaining", 3 - n);
        if (n < 3)
            goto start;
        else
            printf("\n Sorry!!!");
    }
    getch();
}

void main()
{
    welcomeMessage();
    login();
}