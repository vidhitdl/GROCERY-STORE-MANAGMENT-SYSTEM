#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

#define ANS 15
#define ACS 4


//void gotoxoy(int a, int b);
void password(int pwd , int upwd);
void main_page();
void admin();
void admin_main();
void add();
void del();
void modify();
void display();
void bill();
void add_newitems();
void c_code(char y[]);
int check(char x[ANS]);
void extra();
void file_del();



typedef struct
{
    char name[ANS],code[ACS];
    float rate;
    int quantity;
} rec;
rec item;


int main()
{
    main_page();
    return 0;
}




void password(int pwd , int upwd)
{
    system("cls");
    int x = 10 ;
    while (x != 0)
    {
        if (pwd==upwd)
        {
            printf("LOGIN SUCCESFUL \n");
            x=0;
            admin_main();
        }

        else
        {
            int input;
            printf("wrong password\n");
            printf("do you want to enter password ( YES PRESS 1 , NO PRESS 2 ) \n");
            scanf("%d",&input);
            if(input==1)
            {
                admin();
            }

            else if (input==2);
            {
                x=0;
                main_page();
            }

        }
    }
}

void main_page()
{

    system("cls");
    int opt;

    printf("\n                           GROCERY MANAGMENT SYSTEM                  \n \n\n\n");

    printf("                     Please select the required option :  \n\n ");

    printf("                    SELECT 1 FOR ADMIN LOGIN PAGE \n\n");

    printf("                     SELECT 2 TO EXIT FROM THE APPLICATION\n\n");

    printf("                     INPUT : \t");

    scanf("%d",&opt);
    if (opt==1)
    {
        admin();
    }
    else if (opt==2)
    {
         exit(0);
    }
    else
    {
    printf("wrong input \n\n");
    }

}

void admin()

{
    system("cls");

    int pwd = 1234 ;
    int upwd ;
    int x ;
    printf("\n ADMIN PAGE\n");
    printf("\n PLEASE ENTER THE ADMIN PIN : \t");
    scanf("%d",&upwd);
    password(pwd,upwd);

}

void admin_main()
{

    system("cls");
    int input ;
    printf("    select the required options \n\n");
    printf("    1 - TO ADD ITEMS \n\n");
    printf("    2 - TO DELETE ITEMS \n\n");
    printf("    3 - TO MODIFY ITEMS \n\n");
    printf("    4 - TO DISPLAY ALL ITEMS \n\n");
    printf("    5 - TO GO TO HOME PAGE \n\n");
    printf("    INPUT : \t");
    scanf("%d",&input);
    if (input == 1 )
    {
        add();
    }
    else if (input == 2 )
    {
        del();
    }

    else if (input == 3 )
    {
        modify();
    }

    else if (input == 4)
    {
        display();
    }
    else if (input == 5)
    {
        main_page();
    }
    else
    {
        main_page();
    }


}


void add()
{
    system("cls");
    int input;

    FILE *file;
    char y[ACS],x[12];
    system("cls");
    printf("    Enter New Record(Y/N)? =  \t");
    while(toupper(getche())=='Y')
    {
        system("cls");
        file=fopen("record.txt","ab");
        c_code(y);
        strcpy(item.code,y);

        printf("    Enter Rate Of The Item: \t");
        scanf("%f",&item.rate);
        printf("\n");

        printf("    Enter Quantity Of The Item:\t");
        scanf("%d",&item.quantity);
        printf("\n");

        printf("    Enter Name Of The Item:\t");
        scanf("%s",item.name);
        printf("\n");
        fseek(file,0,SEEK_END);
        fwrite(&item,sizeof(item),1,file);
        fclose(file);

        printf("Enter New Record(Y/N)? = \t\n");
        printf("\n");

    }
    admin_main();
    fclose(file);
}
void c_code(char y[])
{
    int flag;
    FILE *file;
    file=fopen("record.txt","rb");
    while(1)
    {
        system("cls");


        printf("     ADD ARTICLES \n ")  ;
        flag=1;
        rewind(file);
        printf("    Enter New Code Of The Article:\t");
        scanf(" %[^\n]",y);
        printf("\n");
        while(fread(&item,sizeof(item),1,file)==1)
        {
            if (strcmp(y,item.code)==0)
            {
                flag=0;

                printf("    Code Already Exists !!\n");

                printf("    Please Enter Again \n");
                getch();
                break;
            }
        }
        if (flag==1)
            break;
    }
    fclose(file);
}

void del()
{
    system("cls");

    int flag;
    char x[ANS];
    FILE *file,*file1;

    system("cls");

    printf("    DELETE ARTICLES");

    printf("    Enter Item Code: \t");
    scanf("%s",x);
    printf("\n");
    flag=check(x);
    if(flag==0)
    {
        file1=fopen("record1.txt","ab");
        file=fopen("record.txt","rb");
        rewind(file);
        while (fread(&item,sizeof (item),1,file))
        {
            if(strcmp(item.code,x)!=0)
                fwrite(&item,sizeof(item),1,file1);
        }

        printf("    ---Item Deleted---");
        getch();

    }
    if (flag==1)
    {

        printf("    ---Item Does Not Exist---");

        printf("    TRY AGAIN");
        getch();
        admin_main();
    }

    fclose(file1);
    fclose(file);


    file_del();
    admin_main();
}



void file_del()
{
    int x = remove("record.txt");
    int y = rename("record1.txt","record.txt");
}

int check(char x[ANS])
{
    FILE *file;
    int flag=1;
    file=fopen("record.txt","rb");
    rewind(file);
    while (fread(&item,sizeof (item),1,file))
    {
        if(strcmp(item.code,x)==0)
        {
            flag=0;
            break;
        }
    }
    fclose(file);
    return flag;
}




void modify()
{
    int flag=0,choice;
    char x[ACS],y[ACS];
    FILE *file;
    int size;
    system("cls");


    printf("    EDIT RECORDS \n\n");
    ;

    printf("    Enter Item Code: \t");
    scanf("%s",x);
    printf("\n");
    flag=check(x);
    if(flag==0)
    {
        file=fopen("record.txt","r+b");
        rewind(file);
        while (fread(&item,sizeof (item),1,file))
        {
            if(strcmp(item.code,x)==0)
            {

                printf("    name       = %s \n",item.name);

                printf("    code       = %s\n",item.code);

                printf("    rate       = %g\n",item.rate);

                printf("    quantity   = %d\n",item.quantity);

                printf("\nDo You Want To Edit This Record?(y/n)  :   \t");
                fflush(file);
                if(toupper(getche())=='Y')
                {

                    printf("\n\n    1- Edit Name \n");

                    printf("    2- Edit Code \n");

                    printf("    3- Edit Rate \n");

                    printf("    4- Edit Quantity \n");
                    ;
                    printf("\n Enter Your Choice(1, 2, 3, 4) =  \t");
                    scanf("%d",&choice);
                    printf("\n\n");
                    switch(choice)
                    {
                    case 1:
                        system("cls");


                        printf("EDIT RECORDS\n");

                        printf(" Enter New Name: \t");
                        scanf("%s",item.name);
                        printf("\n");
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 2:
                        system("cls");

                        printf("EDIT RECORDS\n");

                        c_code(y);
                        strcpy(item.code,y);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 3:
                        system("cls");

                        printf("EDIT RECORDS");

                        printf(" Enter New Rate: \t");
                        scanf("%f",&item.rate);
                        printf("\n");
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 4:
                        system("cls");

                        printf("EDIT RECORDS\n");

                        printf(" Enter New Quantity: \t");
                        scanf("%d",&item.quantity);
                        printf("\n");
                        size=sizeof(item);
                        fseek(file,-size,1);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    }

                    printf("--- Item Edited---\n");
                    break;
                }
            }
        }
    }
    if (flag==1)
    {

        printf("Item Does Not Exist.\n");

        printf("TRY AGAIN\n");
        modify();
    }
    getch();
    fclose(file);
    admin_main();
}






void display()
{
    system("cls");
    FILE *file;
    file=fopen("record.txt","rb");

    if (file == NULL){
      printf("No data \n");
    }
    else {
        int size;
        fseek (file, 0, SEEK_END);
        size = ftell(file);
	rewind(file);
        if (size == 0){
            printf("No data\n");
        }
        else{
            printf("\n code \t\t name \t\t price \t\t quantity \t \n");
            while(fread(&item , sizeof(item),1,file)==1)
            {

                printf("\n %s \t\t %s \t\t %f \t\t %d \t\t \n", item.code, item.name, item.rate, item.quantity);
            }
        }
    }
    fclose(file);

    printf("press any key to go to main page \n");
    getch();
    admin_main();
}


