#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#include <ctype.h>
#include "user.h"
#include "file.h"

#define MAX_STRING 128

void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}

void userLogin() {
    printf("Welcome to the User Login!\n");

    int userId;
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;

    char password[20]; 
    const int correctUserId = 1234;
    const char correctPassword[] = "user123";

    while (attempts < MAX_ATTEMPTS) {
        printf("Enter User ID: ");
        if (scanf("%d", &userId) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');  // clear buffer
            continue;
        }
        while (getchar() != '\n');  // clear buffer after valid input

        printf("Enter Password: ");
        scanf("%19s", password);
        while (getchar() != '\n');  // clear buffer after reading password

        if (userId != correctUserId || strcmp(password, correctPassword) != 0) {
            printf("\nInvalid User ID or Password. Please try again.\n");
            attempts++;
        } else {
            printf("\nUser login successful!\n");
            Sleep(1000); // Simulate a short delay
            userMenu();
            return;
        }
    }

    printf("Too many failed attempts. Exiting...\n");
    exit(1);
}

void userMenu() {
    char choice;
    while (1) {
        displayUserMenu();
        if (scanf(" %c", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number from 1 to 5.\n");
            continue;
        }

        switch (choice) {
            case '1':
                viewAvailableBooks();
                break;
            case '2':
                borrowBook();
                break;
            case '3':
                returnBook();
                break;
            case '4':
                searchForBooks();
                break;
            case '5':
                saveToCSV(); 
                printf("Logging out...\n");
                Sleep(1000);
                return;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}

void searchForBooks(){
    char choice;

    if (bookCount == 0) {
        printf("No books in the system.\n");
        printf("---------------------------------\n");
        return;
    }

    printf("\n--- Choose Search Option ---\n");
    printf("------------------------------\n");
    printf("1. Search by Title\n");
    printf("2. Search by Author\n");
    printf("3. Filter by Publication Year\n");
    printf("4. Exit Search\n");
    printf("------------------------------\n");
    printf("Please select an option: ");
    scanf(" %c", &choice);
    getchar(); // Clean up newline

    int found = 0;

    if (choice == '1') {
        char tempSearch[MAX_STRING], tempBookTitle[MAX_STRING];
        printf("Enter book title: ");
        fgets(tempSearch, MAX_STRING, stdin);
        tempSearch[strcspn(tempSearch, "\n")] = 0;

        toLowerCase(tempSearch);

        for (int i = 0; i < bookCount; i++) {
            strcpy(tempBookTitle, library[i].title);
            toLowerCase(tempBookTitle);
            if (strstr(tempBookTitle, tempSearch) != NULL) {
                if (!found) {
                    printf("\n--- Search Results ---\n");
                    printf("| %-4s | %-25s | %-22s | %-4s | %-10s |\n", "ID", "Title", "Author", "Year", "Status");
                    printf("-------------------------------------------------------------------------------\n");
                }
                printf("| %-4d | %-25s | %-22s | %-4d | %-10s |\n",
                    library[i].id, library[i].title, library[i].author,
                    library[i].year, library[i].isAvailable ? "Available" : "Borrowed");
                found = 1;
            }
        }

    } else if (choice == '2') {
        char tempSearch[MAX_STRING], tempBookAuthor[MAX_STRING];
        printf("Enter author name: ");
        fgets(tempSearch, MAX_STRING, stdin);
        tempSearch[strcspn(tempSearch, "\n")] = 0;

        toLowerCase(tempSearch);

        for (int i = 0; i < bookCount; i++) {
            strcpy(tempBookAuthor, library[i].author);
            toLowerCase(tempBookAuthor);
            if (strstr(tempBookAuthor, tempSearch) != NULL) {
                if (!found) {
                    printf("\n--- Search Results ---\n");
                    printf("| %-4s | %-25s | %-22s | %-4s | %-10s |\n", "ID", "Title", "Author", "Year", "Status");
                    printf("-------------------------------------------------------------------------------\n");
                }
                printf("| %-4d | %-25s | %-22s | %-4d | %-10s |\n",
                    library[i].id, library[i].title, library[i].author,
                    library[i].year, library[i].isAvailable ? "Available" : "Borrowed");
                found = 1;
            }
        }

    } else if (choice == '3') {
        int year;
        do {
            printf("Enter book publication year: ");
            if (scanf("%d", &year) != 1 || (year <= 0 || year > 2025)) {
                printf("Invalid year. Please enter a correct number (e.g., 1900-2025).\n");
                while (getchar() != '\n');
            } else {
                break;
            }
        } while (1);
        while (getchar() != '\n');

        for (int i = 0; i < bookCount; i++) {
            if (library[i].year == year) {
                if (!found) {
                    printf("\n--- Search Results ---\n");
                    printf("| %-4s | %-25s | %-22s | %-4s | %-10s |\n", "ID", "Title", "Author", "Year", "Status");
                    printf("-------------------------------------------------------------------------------\n");
                }
                printf("| %-4d | %-25s | %-22s | %-4d | %-10s |\n",
                    library[i].id, library[i].title, library[i].author,
                    library[i].year, library[i].isAvailable ? "Available" : "Borrowed");
                found = 1;
            }
        }

    } else if (choice == '4') {
        return;
    } else {
        printf("Invalid option.\n");
        return;
    }

    if (!found) {
        printf("No books found matching your input.\n");
    } else {
        printf("-------------------------------------------------------------------------------\n");
    }
}

void displayUserMenu() {
    printf("\n=========================\n");
    printf("        User Menu        \n");
    printf("=========================\n");
    printf("1. View Available Books\n");
    printf("2. Borrow Book\n");
    printf("3. Return Book\n");
    printf("4. Search for Books\n");
    printf("5. Logout\n");
    printf("=========================\n");
    printf("Please select an option: ");
}
void viewAvailableBooks() {
    int found = 0;
    printf("\n---------------------- Available Books ----------------------\n");
    printf("+------+---------------------------+------------------------+------+------------+\n");
    printf("| ID   | Title                     | Author                 | Year | Status     |\n");
    printf("+------+---------------------------+------------------------+------+------------+\n");
    for (int i = 0; i < bookCount; i++) {
        if (library[i].isAvailable == 1) {
            printf("| %-4d | %-25s | %-22s | %-4d | %-10s |\n",
                   library[i].id,
                   library[i].title,
                   library[i].author,
                   library[i].year,
                   "Available");
            found = 1;
        }
    }
    if (!found) {
        printf("| No available books found.                                                 |\n");
    }
    printf("+------+---------------------------+------------------------+------+------------+\n");
}
void borrowBook() {
    int id, found = 0;
    printf("Enter the book ID to borrow: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a valid book ID.\n");
        while (getchar() != '\n'); // clear buffer
        return;
    }
    while (getchar() != '\n'); // clear buffer after valid input

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            found = 1;
            if (library[i].isAvailable == 1) {
                library[i].isAvailable = 0;
                printf("Book borrowed successfully.\n");
            } else {
                printf("This book is currently borrowed.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Book with ID %d not found.\n", id);
    }
}
void returnBook() {
    int id, found = 0;
    printf("Enter the book ID to return: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            if (library[i].isAvailable == 0) {
                library[i].isAvailable = 1;
                printf("Book returned successfully.\n");
                found = 1;
                break;
            } else {
                printf("This book is not currently borrowed.\n");
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("Book with ID %d not found.\n", id);
    }
}
