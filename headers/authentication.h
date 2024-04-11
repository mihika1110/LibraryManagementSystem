#include "./data-types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int login=0;

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

    char fileName[50];
    sprintf(fileName, "credentials/%s.bin", email);

    file = fopen(fileName, "r");

    if(file==NULL)
    {
        struct Credentials temp={"null","null"};
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

        strcpy(credential.email, email);
        strcpy(credential.password, pass);

        registerCredentials(credential);
    }
    else
    {
        printf("Already Registered\n");
    }
}

struct Student loginUser()
{
    struct Student student;
    char email[50],pass[50];
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

    if(strcmp(credential.password,pass)==0)
    {
        login=1;
        
        student=fetchData(credential.email);
    }
    else
    {
        login=0;
    }

    return student;
}
