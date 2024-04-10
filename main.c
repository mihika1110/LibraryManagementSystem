#include <stdio.h>
#include <string.h>

struct Credentials
{
    char email[50];
    char password[50];
};
int login=0;

void registerCredentials(struct Credentials credential)
{
    FILE *file;

    char fileName[50];
    sprintf(fileName, "credentials/%s.txt", credential.email);

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
    sprintf(fileName, "credentials/%s.txt", email);

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
    // sprintf(email, "%s_%s@iitp.ac.in", tolower(name),tolower(roll));
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
}

void welcomePage()
{
    int choice;
    printf("Enter the options: \n1. Register\n2. Login\n");
    scanf("%d",&choice);

    if(choice==1)
    {
        registerUser();
        welcomePage();
    }
    else if(choice==2)
    {
        loginUser();
        homePage();
    }
}

void homePage()
{

}

int main()
{
    welcomePage();
}
