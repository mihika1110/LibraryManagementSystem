// #include "./data-types.h"
// #include "./miscellaneous.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// void readLibraryFromFile(struct Book libraryBook[], int size) 
// {
//     FILE *file = fopen("./library-data/libraryBook.bin", "rb");
//     if (file == NULL)
//     {
//         printf("Error opening file for reading.\n");
//         return;
//     }
//     fread(libraryBook, sizeof(struct Book), size, file);
//     fclose(file);
// }

void writeLibraryBookToFile(struct Book libraryBook[], int size)
{
    FILE *file = fopen("./library-data/libraryBook.bin", "wb");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(libraryBook, sizeof(struct Book), size, file);
    fclose(file);
}

void initializeBooks()
{
    struct Book libraryBook[49];
    char *bookNames[] =  {
        "To Kill a Mockingbird",
        "1984",
        "The Great Gatsby",
        "One Hundred Years of Solitude",
        "Moby-Dick",
        "War and Peace",
        "The Catcher in the Rye",
        "Lolita",
        "Middlemarch",
        "The Lord of the Rings",
        "Pride and Prejudice",
        "Crime and Punishment",
        "Wuthering Heights",
        "The Brothers Karamazov",
        "The Odyssey",
        "Anna Karenina",
        "Great Expectations",
        "The Grapes of Wrath",
        "Catch-22",
        "Beloved",
        "In Search of Lost Time",
        "Brave New World",
        "Gone with the Wind",
        "The Sound and the Fury",
        "The Picture of Dorian Gray",
        "Ulysses",
        "Jane Eyre",
        "Don Quixote",
        "The Adventures of Huckleberry Finn",
        "The Count of Monte Cristo",
        "Emma",
        "The Sun Also Rises",
        "The Scarlet Letter",
        "A Tale of Two Cities",
        "The Iliad",
        "The Divine Comedy",
        "Les Misérables",
        "Frankenstein",
        "Alice's Adventures in Wonderland",
        "The Canterbury Tales",
        "The Three Musketeers",
        "The Hobbit",
        "A Clockwork Orange",
        "The Stranger",
        "The Old Man and the Sea",
        "Heart of Darkness",
        "Lord of the Flies",
        "Slaughterhouse-Five",
        "Invisible Man"
    };
    
    char *authorNames[] = {
        "Harper Lee",
        "George Orwell",
        "F. Scott Fitzgerald",
        "Gabriel Garcia Marquez",
        "Herman Melville",
        "Leo Tolstoy",
        "J.D. Salinger",
        "Vladimir Nabokov",
        "George Eliot",
        "J.R.R. Tolkien",
        "Jane Austen",
        "Fyodor Dostoevsky",
        "Emily Bronte",
        "Fyodor Dostoevsky",
        "Homer",
        "Leo Tolstoy",
        "Charles Dickens",
        "John Steinbeck",
        "Joseph Heller",
        "Toni Morrison",
        "Marcel Proust",
        "Aldous Huxley",
        "Margaret Mitchell",
        "William Faulkner",
        "Oscar Wilde",
        "James Joyce",
        "Charlotte Bronte",
        "Miguel de Cervantes",
        "Mark Twain",
        "Alexandre Dumas",
        "Jane Austen",
        "Ernest Hemingway",
        "Nathaniel Hawthorne",
        "Charles Dickens",
        "Homer",
        "Dante Alighieri",
        "Victor Hugo",
        "Mary Shelley",
        "Lewis Carroll",
        "Geoffrey Chaucer",
        "Alexandre Dumas",
        "J.R.R. Tolkien",
        "Anthony Burgess",
        "Albert Camus",
        "Ernest Hemingway",
        "Joseph Conrad",
        "William Golding",
        "Kurt Vonnegut",
        "Ralph Ellison"
    };

    for(int i=0;i<sizeof(libraryBook) / sizeof(libraryBook[0]);i++)
    {
        strcpy(libraryBook[i].name,bookNames[i]);
        strcpy(libraryBook[i].author,authorNames[i]);
        libraryBook[i].issueDate=20240411;
        libraryBook[i].dueDate=20240511;
    }

    writeLibraryBookToFile(libraryBook, sizeof(libraryBook) / sizeof(libraryBook[0]));
    
    printf("\n\nBoks initialised successfully\n");
}

void printBooks()
{
    FILE *file;
    file = fopen("./library-data/libraryBook.bin", "rb");
    struct Book temp;
    int i=1;

    while(1)
    {
        fread(&temp,sizeof(temp),1,file);
        if(feof(file))
        {
            break;
        }
    
        printf("Book %d:-%s Author:-%s",i,temp.name,temp.author);
        printf("\n\n");
        
        i++;
    }
    fclose(file);
}

void addToIssuedBook(int book_number)
{
    FILE *readfile,*writefile;
    struct Book temp;

    char fileName[50] = "";
    int line =1;
    
    sprintf(fileName, "./book-issue-data/%s.bin", Email);
    writefile = fopen(fileName, "ab");
    readfile = fopen("./library-data/libraryBook.bin","rb");

    while(1)
    {
        fread(&temp,sizeof(temp),1,readfile);
        if(line==book_number)
        {
            fwrite(&temp,sizeof(temp),1,writefile);
            break;
        }
        else
        {
            line++;
        }

        if(line>book_number)
        {
            break;
        }
    }

    fclose(writefile);
    fclose(readfile);
}

void printIssuedBooks(char mail[50])
{    
    FILE *file;
    char fileName[50] = "";
    
    sprintf(fileName, "./book-issue-data/%s.bin", Email);
    file = fopen(fileName, "rb");
    
    struct Book temp;
    int i=1;

    while(1)
    {
        fread(&temp,sizeof(temp),1,file);
        if(feof(file))
        {
            if(i==1)
            {
                printf("No books were issued to you\n");
            }
            break;
        }        
    
        printf("Book %d:-%s Author:-%s",i,temp.name,temp.author);
        printf("\n\n");
        
        i++;
    }
    fclose(file);
}

void return_book()
{
    int book_number;
    printf("\nEnter the book number to return:-\n");
    scanf("%d",&book_number);

    FILE *fp,*fp1;
    struct Book t,t1;
    int found=0,count=0,line=1;

    char fileName[50] = "";
            
    sprintf(fileName, "./book-issue-data/%s.bin", Email);

    fp=fopen(fileName,"rb");
    fp1=fopen("./book-issue-data/temp.bin","wb");

    while(1)
    {
        fread(&t,sizeof(t),1,fp);

        if(feof(fp))
        {
            break;
        }
        if(line==book_number)
        {
            found=1;
        }
        else
        {
            fwrite(&t,sizeof(t),1,fp1);
        }

        line++;
    }
    fclose(fp);
    fclose(fp1);

    if(found==0)
    {
        printf("Sorry No Record Found\n\n");
    }
    else
    {
        fp=fopen(fileName,"wb");
        fp1=fopen("./book-issue-data/temp.bin","rb");

        while(1)
        {
            fread(&t,sizeof(t),1,fp1);

        if(feof(fp1))
        {
            break;
        }
            fwrite(&t,sizeof(t),1,fp);
        }

        printf("\nBook has been returned sucessefully\n");

    }
    fclose(fp);
    fclose(fp1);
}

//need to review
void printMessage(char mail[])
{
    FILE *file;
    char fileName[50] = "";
    
    sprintf(fileName, "./message/%s.bin", Email);
    file = fopen(fileName, "rb");

    if(file==NULL)
    {
        printf("you have no mails to display");
    }
    else
    {            
        char temp[50];
        int i=1;
        printf("\nMAILS\n");

        while(1){
            fread(&temp,sizeof(temp),1,file);
            if(feof(file))
            {
                if(i==1)
                {
                    printf("you have no mails to display");
                }
                break;
            }
            
            printf("%d. %s",i,temp);
            printf("\n");
            
            i++;
        }

        fclose(file);
    }
}
