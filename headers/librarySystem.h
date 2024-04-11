// #include "./data-types.h"
// #include "./miscellaneous.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readLibraryFromFile(struct Book libraryBook[], int size) 
{
    FILE *file = fopen("./library-data/libraryBook.bin", "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    fread(libraryBook, sizeof(struct Book), size, file);
    fclose(file);
}

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
    struct Book libraryBook[50];
    char *bookNames[] = {"The Catcher in the Rye", "To Kill a Mockingbird", "1984", "The Great Gatsby", "Pride and Prejudice", "The Lord of the Rings", "The Hobbit", "Harry Potter and the Philosopher's Stone", "The Hunger Games", "The Da Vinci Code"};
    char *authorNames[] = {"J.D. Salinger", "Harper Lee", "George Orwell", "F. Scott Fitzgerald", "Jane Austen", "J.R.R. Tolkien", "J.K. Rowling", "Suzanne Collins", "Dan Brown"};
    
    for(int i=0;i<10;i++)
    {
        strcpy(libraryBook[i].name,bookNames[i]);
        strcpy(libraryBook[i].author,authorNames[i]);
        libraryBook[i].issueDate=20240411;
        libraryBook[i].dueDate=20240511;
    }

    writeLibraryBookToFile(libraryBook, sizeof(libraryBook) / sizeof(libraryBook[0]));
}

void printBooks(struct Book books[],int len)
{
    for(int i=0;i<len;i++)
    {
        printf("Book:-%s Author:-%s Issued Date:-%s Due Date:-%s",books[i].name,books[i].author,formatDate(books[i].issueDate),formatDate(books[i].dueDate));
        printf("\n\n");
    }
}