#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void addBook()
{
    struct Book new_book;

    printf("\nname of the book : ");
    scanf("%s",&(new_book.name));
    printf("\nname of the authour : ");
    scanf("%s",&(new_book.author));
    new_book.issueDate=20240411;
    new_book.dueDate=20240511;

    FILE *file;
    file = fopen("./library-data/libraryBook.bin", "ab");

    fwrite(&new_book,sizeof(struct Book),1,file);
    printf("\nnew book added successfully");

    fclose(file);

}


// void sendMail()
// {
//     char temp_mail[50],subject[50];
//     printf("send message to email : ");
//     scanf("%s",temp_mail);
//     printf("subject of the mail : ");
//     scanf("%s",subject);

//     FILE *file;
//     char fileName[50] ;
//     sprintf(fileName,"./message/%s.bin",temp_mail);
//     file=fopen(fileName,"ab");
//     fwrite(subject,sizeof(subject),1,file);

//     fclose(file);

    
//     printf("\n\nEmail sent sucessfully\n");
// }


void remove_book(){

    FILE *fp,*fp1;
    struct Book t,t1;
    int found=0,count=0,line=1;

    char fileName[50] = "";
            
    sprintf(fileName, "./library-data/libraryBook.bin");
            

    fp=fopen(fileName,"rb");
    fp1=fopen("./book-issue-data/temp.bin","wb");

    if(fp!=NULL){

        int book_number;
            printf("Book number you want to delete: ");
            scanf("%d",&book_number);


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
        }
        fclose(fp);
        fclose(fp1);

        printf("\n\nBook has been removed successfully from the library.\n");
    }else{
        printf("no book to remove\n");
    }
}


void print_users()
{

    DIR *dr;
   struct dirent *en;
   int i=1;
   dr = opendir("./credentials"); //open all or present directory
   if (dr!=NULL) {
      while ((en = readdir(dr)) != NULL) {
        if(!(en->d_type)){
            FILE *file;
            struct Credentials user_data;
            char fileName[50];
            sprintf(fileName,"./credentials/%s",en->d_name);
            
            file=fopen(fileName,"rb");
            fread(&user_data,sizeof(user_data),1,file);


            printf("%d. %s\n",i, user_data.email); //print all directory name
            i++;
            fclose(file);
        }
      }
      closedir(dr); //close all directory
   }
}

void Modify_book(int book_number){
    char modify_name[50],modify_author[50];

    printf("Modifed name of the book : ");
        scanf("%s",modify_name);
    printf("Modifed author of the book : ");
        scanf("%s",modify_author);

    FILE *fp,*fp1;
    struct Book t,t1,temp_book;
    int found=0,count=0,line=1;

    sprintf(temp_book.name,modify_name);
    sprintf(temp_book.author,modify_author);

    char fileName[50] = "";
            
            sprintf(fileName, "./library-data/libraryBook.bin");
            

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
            fwrite(&temp_book,sizeof(struct Book),1,fp1);
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
    }
    fclose(fp);
    fclose(fp1);
}

void delete_user(int user_number){

    DIR *dr;
   struct dirent *en;
    int line=1;

   dr = opendir("./credentials"); //open all or present directory

   if (dr!=NULL) {
      while ((en = readdir(dr)) != NULL) {
        if(!(en->d_type)){
            if(line==user_number){
                
                char fileName[50];
                sprintf(fileName,"./credentials/%s",en->d_name);
                
                if(!strcmp(en->d_name,"admin_admin@iitp.ac.in.bin")){
                    printf("can not delete admin\n");
                }else{
                    if(remove(fileName)){
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
      closedir(dr); //close all directory
   }

}
