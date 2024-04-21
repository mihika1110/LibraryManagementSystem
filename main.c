#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/encryption.h"
// #include "./headers/authentication.h"
#include "./headers/librarySystem.h"
#include "./headers/admin.h"


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

    pause(1);
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

            char fileName[50];
            sprintf(fileName, "students-data/%s.bin",Email);

            student=fetchData(fileName);
            admin=fetchData("students-data/admin_admin@iitp.ac.in.bin");
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
            if(student.nBooks<5)
            {
                               

                addToIssuedBook();
                
                printf("\n\nBook issued succesfully\n");
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
            
            printf("Total books issued :- %d\n",student.nBooks);//---->debug

            return_back();//awaits till user's response with "1"
        }
        else if(choice==3)
        {
            

            return_book();//calls method to return the book

            return_back();
        }
        else if(choice==4)
        {
            int previewBook=0;
            printf("Enter the book you want to preview: ");
            scanf("%d",&previewBook);
            
            printBooksPreview(previewBook);//prints the book preview

            return_back();
        }
        else if(choice==5)
        {
            ADMIN=0;
            login=0;

            displayASCII("./ascii-arts/logout.txt");

            pause(2);
            clear();

            char fileName[50];
            sprintf(fileName, "students-data/%s.bin",Email);
            storeData(student,fileName);
            storeData(admin,"students-data/admin_admin@iitp.ac.in.bin");

            welcomePage();
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
            printBooks();//prints all the lists of books available

            
            remove_book();//removes the book from the library stock of the given book number

            return_back();
        }
        else if(choice==3)
        {
            print_users();//lists all the registered users

            return_back();
        }
        else if(choice==4)
        {
            printBooks();

            int book_number;
            printf("Book number you want to modify: ");
            scanf("%d",&book_number);
            Modify_book(book_number);

            return_back();
        }
        else if(choice==5)
        {
            print_users();
            int user_number;

            printf("User number you want to delete: ");
            scanf("%d",&user_number);

            delete_user(user_number);//delete the user accossiated with the user number 

            return_back();
        }
        else if(choice==6)
        {
            initializeBooks();//initalizes the book stock to the default book stocks

            return_back();
        }
        else if(choice==7)
        {
            ADMIN=0;
            login=0;

            displayASCII("./ascii-arts/logout.txt");

            pause(2);
            clear();

            storeData(admin,"students-data/admin_admin@iitp.ac.in.bin");

            welcomePage();
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
