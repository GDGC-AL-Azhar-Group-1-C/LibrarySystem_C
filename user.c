#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "user.h"


void userLogin(){
    printf("Welcome to the User Login!\n");
    int userId;
    int count = 1;
    char password[20];
    const int correctUserId = 5678;
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


void viewAvailableBooks()
{
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