
struct Credentials
{
    char email[50];
    int password[8];
};

struct Book
{
    char name[50];
    char author[50];
    int issueDate;
    int dueDate;
    char preview[500];
};

struct Student
{
    int nBooks;
};
