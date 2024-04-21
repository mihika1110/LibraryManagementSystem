#include "./authentication.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

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

    char *preview[]={
        "A poignant tale of racial injustice and moral growth in the American South.",
        "An ominous portrayal of a dystopian society ruled by totalitarianism and surveillance.",
        "A vivid depiction of the Jazz Age's excesses and disillusionment with the American Dream.",
        "A multigenerational narrative blending magical realism and family saga in a Latin American village.",
        "An epic adventure of obsession, revenge, and the awe-inspiring power of nature.",
        "A sweeping panorama of Russian society during the Napoleonic Wars, exploring love, war, and fate.",
        "A coming-of-age novel capturing the angst and alienation of adolescence in post-war America.",
        "A controversial exploration of obsession, desire, and the corruption of innocence.",
        "A rich tapestry of provincial life and human struggles, focusing on marriage, ambition, and societal expectations.",
        "An epic fantasy journey through a world of myth, magic, and heroism.",
        "A sparkling comedy of manners exploring love, marriage, and social class in Georgian England.",
        "A psychological exploration of guilt, punishment, and redemption in 19th-century Russia.",
        "A Gothic masterpiece of passion, revenge, and the destructive power of love on the Yorkshire moors.",
        "A profound examination of faith, morality, and the nature of evil in 19th-century Russia.",
        "An epic poem chronicling the trials and tribulations of Odysseus as he journeys home from the Trojan War.",
        "A tragic tale of love, betrayal, and societal constraints in imperial Russia.",
        "A classic bildungsroman portraying the struggles of a young orphan striving for social acceptance.",
        "A powerful depiction of the Great Depression's impact on a displaced Oklahoma family.",
        "A satirical masterpiece exposing the absurdity and brutality of war and bureaucracy.",
        "A haunting exploration of slavery, trauma, and the enduring legacy of America's past.",
        "A monumental exploration of memory, time, and identity in a world transformed by technology.",
        "A dystopian vision of a future society dominated by consumerism, conformity, and surveillance.",
        "A sweeping saga of love and loss amidst the turbulence of the American Civil War.",
        "A modernist masterpiece of stream-of-consciousness narrative, exploring time, memory, and identity.",
        "A dark and atmospheric tale of vanity, decadence, and the price of artistic ambition.",
        "An experimental novel that pushes the boundaries of narrative form and language.",
        "A timeless romance exploring themes of class, morality, and social convention.",
        "A rollicking adventure following the exploits of a chivalrous knight and his loyal squire.",
        "A satirical coming-of-age story set against the backdrop of pre-Civil War America.",
        "A thrilling tale of adventure, revenge, and redemption set in early 19th-century France.",
        "A witty comedy of manners exploring the complexities of matchmaking and romance.",
        "A poignant exploration of the Lost Generation's disillusionment and search for meaning.",
        "A haunting tale of sin, guilt, and redemption in Puritan New England.",
        "A sweeping historical novel set against the backdrop of the French Revolution.",
        "An epic poem recounting the trials and tribulations of the Trojan War heroes.",
        "A medieval allegory detailing the author's journey through Hell, Purgatory, and Paradise.",
        "A sprawling epic of love, sacrifice, and redemption set in 19th-century France.",
        "A seminal work of Gothic literature exploring themes of science, ambition, and morality.",
        "A whimsical journey through a world of imagination and wordplay.",
        "A collection of stories that offer a vivid snapshot of medieval English society.",
        "A swashbuckling adventure following the escapades of a young swordsman and his friends.",
        "An enchanting tale of adventure, friendship, and heroism in Middle-earth.",
        "A chilling exploration of free will, morality, and the nature of evil in a dystopian future.",
        "An existentialist masterpiece exploring the absurdity and alienation of modern life.",
        "A gripping tale of endurance, resilience, and the struggle against nature's indifference.",
        "A haunting journey into the heart of darkness both within and without.",
        "A disturbing allegory of civilization's collapse and the descent into savagery.",
        "A satirical indictment of war and the dehumanizing effects of bureaucracy and technology.",
        "A searing exploration of race, identity, and invisibility in America."
    };

    for(int i=0;i<sizeof(libraryBook) / sizeof(libraryBook[0]);i++)
    {
        strcpy(libraryBook[i].name,bookNames[i]);
        strcpy(libraryBook[i].author,authorNames[i]);
        strcpy(libraryBook[i].preview,preview[i]);
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

    if(file!=NULL){
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
    }else{
        printf("library is empty\n");
    }

}

void printBooksPreview(int bookNumber)
{
    FILE *file;
    file = fopen("./library-data/libraryBook.bin", "rb");
    struct Book temp;
    int i=1;

    if(file!=NULL){

        printf("\n\n\n");
        displayASCII("./ascii-arts/preview.txt");

        while(1)
        {
            fread(&temp,sizeof(temp),1,file);
            if(feof(file))
            {
                break;
            }
        
            if(i==bookNumber)
            {
                printf("%s \n%s",temp.name,temp.preview);
                printf("\n\n");
            }
            i++;
        }
        fclose(file);
    }
}

void addToIssuedBook()
{
    FILE *readfile,*writefile;
    struct Book temp;

    char fileName[50] = "";
    int line =1;
    
    sprintf(fileName, "./book-issue-data/%s.bin", Email);
    writefile = fopen(fileName, "ab");
    readfile = fopen("./library-data/libraryBook.bin","rb");

    if(readfile!=NULL){

        printf("The lists of book that you can issue are:-\n");

        printBooks(); 

        int book_number=0;
        printf("Enter the book number you want to issue: ");
        scanf("%d",&book_number);

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

        student.nBooks++;
    }else{
        printf("library is empty\n");
    }
}

void printIssuedBooks(char mail[50])
{    
    FILE *file;
    char fileName[50] = "";
    
    sprintf(fileName, "./book-issue-data/%s.bin", Email);
    file = fopen(fileName, "rb");
    
    struct Book temp;
    int i=1;

    if(file!=NULL){
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
    }else{
        printf("No books were issued to you\n");
    }
}

void return_book()
{

    FILE *file1;
    char fileName[50] = "";
    
    sprintf(fileName, "./book-issue-data/%s.bin", Email);
    file1 = fopen(fileName, "rb");
    
    struct Book temp;
    int i=1,is_empty=0;

    if(file1!=NULL){
        while(1)
        {
            fread(&temp,sizeof(temp),1,file1);
            if(feof(file1))
            {
                if(i==1)
                {
                    printf("No books were issued to you\n");
                    is_empty=1;
                }
                break;
            }        
        
            printf("Book %d:-%s Author:-%s",i,temp.name,temp.author);
            printf("\n\n");
            
            i++;
        }
        fclose(file1);
    }else{
        printf("No books were issued to you\n");
        is_empty=1;
    }



    if(!is_empty){

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

        student.nBooks--;

    }
}

