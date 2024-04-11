
struct Credentials
{
    char email[50];
    char password[50];
};

struct Book
{
    char name[50];
    char author[50];
    int issueDate;
    int dueDate;
};

struct Student
{
    char name[50];
    struct Book bookIssued[5];
    char messages[5][50];
    int nMessages;
    int nBooks;
};
