#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <stdlib.h>
#else
#include <unistd.h>
#include <stdio.h>
#endif

struct Credentials
{
    char email[50];
    char password[50];
};


int login=0;

void homePage();
void welcomePage();
void displayASCII(char [50]);
void pause(int);
void clear();
void registerCredentials(struct Credentials);
struct Credentials fetchCredentials(char [50]);
void registerUser();
void loginUser();
void homePage();
void welcomePage();


void displayASCII(char fileName[50])
{
    FILE *file = fopen(fileName, "r");

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);

    printf("\n\n\n");
}

void pause(int seconds)
{
    #ifdef _WIN32
        Sleep(seconds*1000); // Windows: Sleep for 3000 milliseconds (3 seconds)
    #else
        sleep(seconds);    // Unix-like systems: Sleep for 3 seconds
    #endif
}

void clear()
{
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        printf("\033[2J\033[1;1H"); // Unix-like systems (ANSI escape codes)
    #endif
}

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

void registerUser()
{
    char name[50],roll[50],pass[50];
    printf("Enter your name: ");
    scanf("%s",name);
    printf("Enter your roll number: ");
    scanf("%s",roll);

    char email[50];
    sprintf(email, "%s_%s@iitp.ac.in", name,roll);

    struct Credentials credential=fetchCredentials(email);

    if(strcmp(credential.email,"null")==0)
    {
        printf("Enter password: ");
        scanf("%s",pass);

        printf("%s %s",email,pass);

        strcpy(credential.email, email);
        strcpy(credential.password, pass);

        registerCredentials(credential);
    }
    else
    {
        printf("Already Registered\n");
    }
}

void loginUser()
{
    char email[50],pass[50];
    printf("Enter your email: ");
    scanf("%s",email);

    struct Credentials credential=fetchCredentials(email);

    if(strcmp(credential.email,"null")==0)
    {
        printf("Email ID not found\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s",pass);

    if(strcmp(credential.password,pass)==0)
    {
        login=1;
    }
    else
    {        
        login=0;
    }
}

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
        loginUser();
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
    printf("Login: %d",login);
    scanf("");
}

int main()
{
    welcomePage();
}
