#include "user.h"

void viewAvailableBooks()
 {
    Book books[100];
    int count = 0;
    readBooks(books, &count);

printf("Available books:\n");
    for (int i = 0; i < count; i++) 
    {
    if (books[i].isBorrowed == 0) 
      { 
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
    int choice;
    printf("\n--- Choose Search Option ---\n");
    printf("------------------------------\n");
    printf("1. Search by Title or Author\n");
    printf("2. Search by Publication Year\n");
    do
    {
        printf("Choice: ");
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2))
        {
            printf("Invalid choice. Please enter 1 or 2: ");
        }
    } while (choice != 1 && choice != 2);
    int found = 0;
    printf("\n--- Search Results ---\n");
    if (choice == 1)
    {
        char search[MAX_STRING];
        printf("Enter book (title or author): ");
        fgets(search, MAX_STRING, stdin);
        search [ strcspn (search, "\n") ] = 0;

        for (int i = 0; i < countBooks; i++)
        {
            if ( strstr ( books[i].title, search) || strstr ( books[i].author, search))
            {
                printf("Book ID: %d  |  Title: %s  |  Author: %s  |  Year: %d\n",books[i].id, books[i].title, books[i].author, books[i].year);
                found = 1;
            }
        }
    } else if (choice == 2)
    {
        int search_year;
        do
        {
            printf("Enter book publication year: ");
            if (scanf("%d", &search_year) != 1 || search_year <= 0 || search_year > 2025)
            {
                printf("Invalid year. Please enter correct number: ");
            }
        } while (search_year <= 0 || search_year > 2025);

        for (int i = 0; i < countBooks; i++)
        {
            if (books[i].year == search_year)
            {
                printf("Book ID: %d | Title: %s | Author: %s | Year: %d\n",
                        books[i].id, books[i].title, books[i].author, books[i].year);
                found = 1;
            }
        }
    }
    if (!found)
    {
        printf("No books found in the system.\n");
    }
    printf("---------------------------------\n");
}