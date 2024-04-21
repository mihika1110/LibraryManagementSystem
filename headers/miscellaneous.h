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

void displayASCII(char [50]);
void pause(int);
void clear();
void toLower(char *);

void displayASCII(char fileName[50])
{
    FILE *file = fopen(fileName, "r");

    int ch;
    while ((ch = fgetc(file)) != EOF)
    {
        printf("%c",ch);
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


void toLower(char *str)
{
    int i = 0;
    while(str[i] != '\0')
    {
        if(str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = str[i] + 32;
        }
        i++;
    }
}
