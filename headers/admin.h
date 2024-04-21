#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void addBook()
{
    struct Book new_book;

        //geting book data//
    printf("\nname of the book : ");
    scanf("%s",&(new_book.name));
    new_book.issueDate=20240421;
    new_book.dueDate=20240521;
    printf("\nname of the authour : ");
    scanf("%s",&(new_book.author));
    

    FILE *file;
    file = fopen("./library-data/libraryBook.bin", "ab"); //opening file

    fwrite(&new_book,sizeof(struct Book),1,file);//writing data to file
    printf("\nnew book added successfully\n");

    fclose(file);//closing the file 

}


void remove_book(){

    FILE *file,*temp_file;
    struct Book temp_book;
    int found=0,count=0,line=1;

    char fileName[50] = "";
            
    sprintf(fileName, "./library-data/libraryBook.bin");
            

    file=fopen(fileName,"rb");  //opening files
    temp_file=fopen("./book-issue-data/temp.bin","wb");

    if(file!=NULL){//checking if file is there

        int book_number;
            printf("Book number you want to delete: ");
            scanf("%d",&book_number);


        while(1)
        {
            fread(&temp_book,sizeof(temp_book),1,file);

            if(feof(file))//checking for end of the file
            {
                break;
            }
            if(line==book_number)
            {
                found=1;
            }
            else
            {
                fwrite(&temp_book,sizeof(temp_book),1,temp_file);//writing data to the temp file
            }

            line++;
        }
        fclose(file);
        fclose(temp_file);

        if(found==0)
        {
            printf("Sorry No Record Found\n\n");
        }
        else
        {
            file=fopen(fileName,"wb");
            temp_file=fopen("./book-issue-data/temp.bin","rb");

            //rewriting data to original file

            while(1)
            {
                fread(&temp_book,sizeof(temp_book),1,temp_file);

                if(feof(temp_file))
                {
                    break;
                }

                fwrite(&temp_book,sizeof(temp_book),1,file);
            }
        }
        fclose(file);//close the file
        fclose(temp_file);

        printf("\n\nBook has been removed successfully from the library.\n");
    }else{
        printf("no books to remove\n");
    }
}


void print_users()
{

   DIR *directory; //creating a directory pointer
   struct dirent *directory_entry;
   int i=1;
   directory = opendir("./credentials"); //opening the directory
   
   if (directory!=NULL) {
      while ((directory_entry = readdir(directory)) != NULL) {
        if(!(directory_entry->d_type)){
            //printing every entry in the directory

            FILE *file;
            struct Credentials user_data;
            char fileName[50];
            sprintf(fileName,"./credentials/%s",directory_entry->d_name);
            
            file=fopen(fileName,"rb");

            if(file!=NULL){
                fread(&user_data,sizeof(user_data),1,file);
                printf("%d. %s\n",i, user_data.email); //print all directory name
                
                i++;
                fclose(file);
            }
            
        }
      }
      closedir(directory); //close all directory
   }
}

void Modify_book(int book_number){

    FILE *file,*temp_file;
    struct Book temp_book,modifed_book;
    int found=0,count=0,line=1;
    char modify_name[50],modify_author[50];

    //input
    printf("Modifed name of the book : ");
        scanf("%s",modify_name);
    printf("Modifed author of the book : ");
        scanf("%s",modify_author);


    sprintf(modifed_book.name,modify_name);
    sprintf(modifed_book.author,modify_author);

    char fileName[50] = "";
            
            sprintf(fileName, "./library-data/libraryBook.bin");
            

    file=fopen(fileName,"rb");
    temp_file=fopen("./book-issue-data/temp.bin","wb");

    //transfering data to a temp file
    while(1)
    {
        fread(&temp_book,sizeof(temp_book),1,file);

        if(feof(file))
        {
            break;
        }
        if(line==book_number)
        {
            fwrite(&modifed_book,sizeof(struct Book),1,temp_file);
            found=1;
        }
        else
        {
            fwrite(&temp_book,sizeof(temp_book),1,temp_file);
        }

        line++;
    }
    fclose(file);
    fclose(temp_file);

    if(found==0)
    {
        printf("Sorry No Record Found\n\n");
    }
    else
    {
        file=fopen(fileName,"wb");//opening the file
        temp_file=fopen("./book-issue-data/temp.bin","rb");

        //writing data to the original file
        while(1)
        {
            fread(&temp_book,sizeof(temp_book),1,temp_file);

            if(feof(temp_file))
            {
                break;
            }

            fwrite(&temp_book,sizeof(temp_book),1,file);
        }
    }
    fclose(file);
    fclose(temp_file);
}

void delete_user(int user_number){

    DIR *directory;
   struct dirent *en;
    int line=1;

   directory = opendir("./credentials"); //opening the directory

   if (directory!=NULL) {
      while ((en = readdir(directory)) != NULL) {
        if(!(en->d_type)){
            if(line==user_number){
                //printing every entry in the directory

                char fileName[50];
                sprintf(fileName,"./credentials/%s",en->d_name);
                
                if(!strcmp(en->d_name,"admin_admin@iitp.ac.in.bin")){
                    printf("can not delete admin\n");
                }else{
                    if(!remove(fileName)){  //removing the user
                        printf("user deleted successfully\n");
                    }else{
                        printf("%s user not found\n",fileName);
                    }
                }

                break;
            }

            line++;
        }
      }
      closedir(directory); //close all directory
   }

}
