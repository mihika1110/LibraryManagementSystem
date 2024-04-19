#include "./headers/authentication.h"
#include "./headers/miscellaneous.h"
#include "./headers/librarySystem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student student;

void welcomePage();
void homePage();

void welcomePage()
{
    int choice;

    displayASCII("ascii-arts/header.txt");

    displayASCII("ascii-arts/welcome.txt");
    scanf("%d",&choice);

    if(choice==1)
    {
        registerUser();
        
        printf("\n\nRegistered Successfully!\nRedirecting to welcomepage\n");

        pause(2);//pauses the code execution for 2seconds
        system("cls");//clears the console

        welcomePage();
    }
    else if(choice==2)
    {
        student=loginUser();
        if(login)
        {
            printf("\n\nLogined Successfully\nRedirecting to Homepage\n");

            pause(2);
            system("cls");

            homePage();
        }
        else
        {
            printf("\n\nIncorrect password!\nRedirecting to Welcomepage\n");
            
            pause(2);
            

            welcomePage();
        }
    }
}

void homePage()
{
    int choice;
    displayASCII("./ascii-arts/header.txt");
    displayASCII("./ascii-arts/home.txt");
    scanf("%d",&choice);

    if(choice==1)
    {
        if(student.nBooks<6)
        {
            printf("The lists of book that you can issue are:-\n");
        }
        else
        {
            printf("You can't issue more than 5 books at a time.\nReturn a book before issuing another\n");
        }
        
        initializeBooks();

        struct Book bookIssued[10];
        readLibraryFromFile(bookIssued,sizeof(bookIssued) / sizeof(bookIssued[0]));

        printBooks(bookIssued,sizeof(bookIssued) / sizeof(bookIssued[0]));

        int issuebook =0;
        printf("enter the book you want to be issued : ");

        scanf("%d",&issuebook);
        addToIssuedBook(bookIssued[issuebook-1],Email);
        
        printf("\nbook issued succesfull\nRedirecting to Homepage\n");
        pause(2);
        system("cls");
        homePage();

    }
    else if(choice==2)
    {   int temp;
        printIssuedBooks(Email);
        printf("\npress 1 to go back : ");
        scanf("%d",&temp);
        if(temp==1){
            system("cls");
            homePage();
        }
    }
    else if(choice==3)
    {   int temp;
        printIssuedBooks(Email);
        printf("\nEnter the book number to return:-\n");
        int book_number;
        scanf("%d",&book_number);

        return_book(book_number);
        
    }
    else if(choice==4)
    {   int temp;
        printMessage(Email);

        printf("\npress 1 to go back : ");
        scanf("%d",&temp);
        if(temp==1){
             system("cls");
            homePage();
        }
    }
    else
    {
        printf("Invalid Choice!\n");

        
        clear();
       
        
    }
}

int main()
{
    welcomePage();

    
}
//aa_aa@iitp.ac.in
