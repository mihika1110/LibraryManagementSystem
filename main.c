#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/encryption.h"
#include "./headers/authentication.h"
#include "./headers/miscellaneous.h"
#include "./headers/librarySystem.h"
#include "./headers/admin.h"


struct Student student;

void welcomePage();
void homePage();

void return_back()//this makes the execution wait until the user enters "1"
{
    char temp[50];

    printf("\nPress 1 to go back : ");
    while(strcmp(temp,"1")!=0)
    {
        scanf("%s",temp);
    }
    
    printf("\n\nGoing Back:)\n");

    pause(2);
    clear();

    homePage();
}

void welcomePage()
{
    int choice;

    displayASCII("ascii-arts/header.txt");//displays "IIT Patna Library"
    displayASCII("ascii-arts/welcome.txt");//displays welcome screen

    scanf("%d",&choice);

    if(choice==1)
    {
        registerUser();//redirects user to the register page
        
        printf("\n\nRedirecting to welcomepage\n");

        pause(2);//pauses the code execution for 2seconds
        clear();//clears the console

        welcomePage();
    }
    else if(choice==2)
    {
        student=loginUser();
        if(login)
        {
            printf("\n\nLogined Successfully\nRedirecting to Homepage\n");

            pause(2);
            clear();

            homePage();
        }
        else
        {
            printf("\n\nIncorrect credentials!\nRedirecting to Welcomepage\n");
            
            pause(2);
            clear();

            welcomePage();
        }
    }
}

void homePage()
{

    if(ADMIN==0)
    {
        int choice;

        displayASCII("./ascii-arts/header.txt");//displays "IIT Patna Library"
        displayASCII("./ascii-arts/home.txt");//displays homepage features-user

        scanf("%d",&choice);

        if(choice==1)
        {
            if(student.nBooks<6)
            {
                printf("The lists of book that you can issue are:-\n");

                printBooks();

                int issuebook=0;
                printf("Enter the book you want to be issued : ");

                scanf("%d",&issuebook);
                addToIssuedBook(issuebook);
                
                printf("\n\nBook issued succesfull\n");
            }
            else
            {
                printf("You can't issue more than 5 books at a time.\nReturn a book before issuing another\n\n");
            }        

            printf("Redirecting to Homepage\n");

            pause(2);
            clear();

            homePage();
        }
        else if(choice==2)
        {
            printIssuedBooks(Email);//prints all issued books of the corresponding email id  
            
            return_back();//awaits till user's response with "1"
        }
        else if(choice==3)
        {
            printIssuedBooks(Email);

            return_book();//calls method to return the book

            return_back();
        }
        else if(choice==4)
        {
            printMessage(Email);//prints the messages that the user received from the admin

            return_back();
        }
        else
        {
            printf("Invalid Choice!\n");

            return_back();
        }
    }


    if(ADMIN==1)
    {
        int choice;
        
        displayASCII("./ascii-arts/header.txt");//displays "IIT Patna Library"
        displayASCII("./ascii-arts/admin-features.txt");//displays homepage features

        scanf("%d",&choice);

        if(choice==1)
        {
            addBook();//calls method to add book to the library stock
            
            return_back();
        }
        else if(choice==2)
        {            
            sendMail();//sends mails to the library customers

            return_back();      
        }
        else if(choice==3)
        {
            printBooks();//prints all the lists of books available

            int book_number;
            printf("Book number you want to delete: ");
            scanf("%d",&book_number);

            remove_book(book_number);//removes the book from the library stock of the given book number

            return_back();
        }
        else if(choice==4)
        {
            print_users();//lists all the registered users

            return_back();
        }
        else if(choice==5)
        {
            printBooks();

            int book_number;
            printf("Book number you want to modify: ");
            scanf("%d",&book_number);
            Modify_book(book_number);

            return_back();
        }
        else if(choice==6)
        {
            print_users();
            int user_number;

            printf("User number you want to delete: ");
            scanf("%d",&user_number);

            delete_user(user_number);//delete the user accossiated with the user number 

            return_back();
        }
        else if(choice==7)
        {
            initializeBooks();//initalizes the book stock to the default book stocks

            return_back();
        }
        else
        {
            printf("\n\nInvalid choice!\n");

            return_back();
        }
    }
}


int main()
{
    welcomePage();
}
