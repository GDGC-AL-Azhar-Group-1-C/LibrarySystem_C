#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "user.h"
#include "file.h"
#include "admin.h"

void userLogin(){
    printf("Welcome to the User Login!\n");
    int userId;
    int count = 1;
    char password[20];
    const int correctUserId = 1234;
    const char correctPassword[] = "user123";   
    while(1){
        printf("Enter User ID:");
        scanf("%d", &userId);
        printf("Enter Password: "); 
        scanf("%s", password);
        if (userId != correctUserId || strcmp(password,correctPassword) != 0){
            printf("Invalid User ID or Password. Please try again.\n");
            count++;
            if (count > 3){
                printf("Too many failed attempts. Exiting...\n");
                exit(1);
            }
        } else {
            printf("User login successful!\n");
            break;
        }

    }
}

void viewAvailableBooks(){
    Book books[100];
    int count = 0;
    readBooks(books, &count);

printf("Available books:\n");
for (int i = 0; i < count; i++) 
{

    if (books[i].isBorrowed == 0) { 
        printf("ID: %d | Title: %s | Author: %s | Year: %d\n",
        books[i].id, books[i].title,
        books[i].author, books[i].year);
    }
} 
} 


void returnBook() {
    Book books[100];
    int count, id, found = 0;
    readBooks(books, &count);  
    printf("Please enter the book ID to return:\n");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
    if (books[i].id == id && books[i].isBorrowed == 1) {
            books[i].isBorrowed = 0;  
            found = 1;
            break;
    }
}
    if (found) {
        writeBooks(books, count); 
        printf("Book returned successfully.\n");
}   else {
        printf("This book is not currently borrowed.\n");
}
}

void searchForBooks()
{
    Book books[100];
    readBooks(books, &countBooks);
    int choice;
    printf("\n--- Choose Search Option ---\n");
    printf("------------------------------\n");
    printf("1. Search by Title \n");
    printf("2. Search by Author \n");
    printf("3. Filter by Publication Year \n");
    printf("4. Exit Search \n");
    printf("------------------------------\n");
    printf("Please select an option: ");    

    do {
        printf("Choice: ");
        if (scanf("%d", &choice) != 1 || (choice < 1 || choice > 4)) 
        {
            printf("Invalid choice. Please enter 1, 2, 3 or 4 :\n");
            while(getchar() != '\n');
        }
    } while (choice < 1 || choice > 4);

    int found = 0;

    printf("\n--- Search Results ---\n");
    if (choice == 1)
    {
        char search[MAX_STRING];
        printf("Enter book title: ");
		getchar();
        fgets(search, MAX_STRING, stdin);
        search [ strcspn (search, "\n") ] = 0;

        for (int i = 0; i < countBooks; i++)
        {
            if ( strstr ( books[i].title, search))
            {
                printf("Book ID: %d  |  Title: %s  |  Author: %s  |  Year: %d\n",
                    books[i].id, books[i].title, books[i].author, books[i].year);
                found = 1;
            }
        }
    } else if (choice == 2)
    {
        char search[MAX_STRING];
        printf("Enter book author: ");
		getchar();
        fgets(search, MAX_STRING, stdin);
        search[strcspn(search, "\n")] = 0;

        for (int i = 0; i < countBooks; i++)
        {
            if (strstr(books[i].author, search))
            {
                printf("Book ID: %d  |  Title: %s  |  Author: %s  |  Year: %d\n",
                    books[i].id, books[i].title, books[i].author, books[i].year);
                found = 1;
            }
        }
    }else if (choice == 3)
    {
        int year;
        do
        {
            printf("Enter book publication year: ");
            if (scanf("%d", &year) != 1 || year <= 0 || year > 2025)
            {
                printf("Invalid year. Please enter correct number: ");
            }
        } while (year <= 0 || year > 2025);

        for (int i = 0; i < countBooks; i++)
        {
            if (books[i].year == year)
            {
                printf("Book ID: %d | Title: %s | Author: %s | Year: %d\n",
                    books[i].id, books[i].title, books[i].author, books[i].year);
                found = 1;
            }
        }
    }else if (choice == 4)
    {
        return;
	}
    if (!found)
    {
        printf("No books found in the system.\n");
    }
    printf("---------------------------------\n");
}