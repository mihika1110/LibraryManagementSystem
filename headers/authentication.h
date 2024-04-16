#include "./data-types.h"
// #include "./encryption.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int login=0;
int ADMIN=0;
char Email[50];

void registerCredentials(struct Credentials);
struct Credentials fetchCredentials(char [50]);
void registerUser();
struct Student loginUser();



void registerCredentials(struct Credentials credential)
{
    FILE *file;

    char fileName[50];
    sprintf(fileName, "credentials/%s.bin", credential.email);

    file = fopen(fileName, "w");
    fwrite(&credential, sizeof(struct Credentials), 1, file);
    fclose(file);
    printf("Successfully Registered\n");
}

struct Credentials fetchCredentials(char email[50])
{
    struct Credentials credential;
    FILE *file;
    char t;

    char fileName[50];
    sprintf(fileName, "credentials/%s.bin", email);

    file = fopen(fileName, "r");

    if(file==NULL)
    {
        struct Credentials temp;
        strcpy(temp.email,"null");
        return temp;
    }


    fread(&credential, sizeof(struct Credentials), 1, file);
    fclose(file);
    return credential;
}

void storeData(struct Student student, char email[50])
{
    FILE *file;

    char fileName[50];
    sprintf(fileName, "students-data/%s.bin",email);

    file = fopen(fileName, "w");
    fwrite(&student, sizeof(struct Student), 1, file);
    fclose(file);
}

struct Student fetchData(char email[50])
{
    struct Student student;
    FILE *file;

    char fileName[50];
    sprintf(fileName, "students-data/%s.bin", email);

    file = fopen(fileName, "r");


    fread(&student, sizeof(struct Student), 1, file);
    fclose(file);
    return student;
}

void registerUser()
{
    char name[50],roll[50],pass[50];
    printf("Enter your name: ");
    scanf("%s",name);
    printf("Enter your roll number: ");
    scanf("%s",roll);

    char email[50];
    sprintf(email, "%s_%s@iitp.ac.in", name,roll);//task1

    struct Credentials credential=fetchCredentials(email);

    if(strcmp(credential.email,"null")==0)
    {
        printf("Enter password: ");
        scanf("%s",pass);

        struct Student student;
        strcpy(student.name,name);
        student.nMessages=0;
        student.nBooks=0;
        storeData(student,email);

        int encrypted_password[8];
        EncryptPasssword(pass,encrypted_password);
        
        strcpy(credential.email, email);
        for(int i=0;i<8;i++){
            credential.password[i]=encrypted_password[i];
        }
        
        registerCredentials(credential);

        printf("Registered Successfully!\n");        
    }
    else
    {
        printf("Already Registered\n");
    }
}

int compare_password(int input_password[],int actual_password[])
{
    int equal = 1;
    for(int i=0;i<8;i++){
        if(input_password[i]!=actual_password[i]){
            equal=0;
            break;
        }
    }

    return equal;
}

struct Student loginUser()
{
    struct Student student;
    char email[50],pass[50];
    int Encrypted_password[8];
    printf("Enter your email: ");
    scanf("%s",email);

    struct Credentials credential=fetchCredentials(email);

    if(strcmp(credential.email,"null")==0)
    {
        printf("Email ID not found\n");
        return student;
    }

    printf("Enter password: ");
    scanf("%s",pass);

    EncryptPasssword(pass,Encrypted_password);

    if(compare_password(Encrypted_password,credential.password)==1)
    {
        if(strcmp(credential.email,"admin_admin@iitp.ac.in")==0)
        {
            ADMIN = 1;
        }
        login=1;
        sprintf(Email,credential.email);
        student=fetchData(credential.email);
    }
    else
    {
        login=0;
    }

    return student;
}
