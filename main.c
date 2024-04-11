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
            system("cls");

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
    }
    else if(choice==2)
    {
        for(int i=0;i<=student.nBooks;i++)
        {
            printf("Book:-%s Author:-%s Issued Date:-%s Due Date:-%s",student.bookIssued[i].name,student.bookIssued[i].author,formatDate(student.bookIssued[i].issueDate),formatDate(student.bookIssued[i].dueDate));
        }
    }
    else if(choice==3)
    {
        printf("Enter the book number to return:-\n");
        for(int i=0;i<=student.nBooks;i++)
        {
            printf("%d. Book:-%s Author:-%s Issued Date:-%s Due Date:-%s",i+1,student.bookIssued[i].name,student.bookIssued[i].author,formatDate(student.bookIssued[i].issueDate),formatDate(student.bookIssued[i].dueDate));
        }
    }
    else if(choice==4)
    {
        for(int i=0;i<=student.nMessages;i++)
        {
            printf("Message%d",i+1);
            printf("%s",student.messages[i]);
            strcpy(student.messages[i],NULL);
        }
    }
    else
    {
        printf("Invalid Choice!\n");

        pause(2);
        clear();

        homePage();
    }
}

int main()
{
    // welcomePage();

    // initializeBooks();

    struct Book bookIssued[10];
    readLibraryFromFile(bookIssued,sizeof(bookIssued) / sizeof(bookIssued[0]));

    printBooks(bookIssued,sizeof(bookIssued) / sizeof(bookIssued[0]));
}
