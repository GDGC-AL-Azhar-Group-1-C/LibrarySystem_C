#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#include <ctype.h>
#include "user.h"
#include "file.h"

#define MAX_STRING 128
#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"
 
void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}

void userLogin() {
    printf("\nWelcome to the User Login!\n");

    int userId;
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;

    char password[20]; 
    const int correctUserId = 1234;
    const char correctPassword[] = "user123";

    while (attempts < MAX_ATTEMPTS  ) {
        printf("Enter User ID: ");
        if (scanf("%d", &userId) != 1) {
            printf(RED "\nInvalid input. Please enter a valid number.\n"RESET);
            while (getchar() != '\n');  // clear buffer
            continue;
        }
        while (getchar() != '\n');  // clear buffer after valid input

        printf("Enter Password: ");
        scanf("%19s", password);
        while (getchar() != '\n');  // clear buffer after reading password

        if (userId != correctUserId || strcmp(password, correctPassword) != 0) {
            printf(RED"\nInvalid User ID or Password. Please try again.\n"RESET);
            attempts++;
        } else {
            printf(GREEN"\nUser login successful!\n"RESET);
            Sleep(1000); // Simulate a short delay
            clearScreen();
            userMenu();
            return;
        }
    }

    printf(RED"Too many failed attempts. Exiting...\n"RESET);
    exit(1);
}

void userMenu() {
    char choice;
    clearScreen();
    while (1) {
        displayUserMenu();
        if (scanf(" %c", &choice) != 1) {
            while (getchar() != '\n');
            printf(RED"Invalid input. Please enter a number from 1 to 5.\n"RESET);
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
                printf(GREEN "Saving data...\n" RESET);
                Sleep(1000);
                clearScreen();
                return;
            default:
                printf(RED "\nInvalid choice, please try again.\n"RESET);
        }
    }
}

void searchForBooks(){
    char choice;
    clearScreen();
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
                printf(RED"\nInvalid year. Please enter a correct number (e.g., 1900-2025).\n"RESET);
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
        printf(RED"\nInvalid option.\n"RESET);
        searchForBooks();
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
    printf("\nDo you want to keep viewing the available books? (y/n): ");
    char c; 
    scanf(" %c", &c);
    if (c == 'n' || c == 'N') {
        Sleep(1000);
        clearScreen();
    } else {
        printf("Exiting book view.\n");
    }
}
void borrowBook() {
    int id, found = 0;
    printf("Enter the book ID to borrow: ");
    if (scanf("%d", &id) != 1) {
        printf(RED "\nInvalid input. Please enter a valid book ID.\n" RESET);
        while (getchar() != '\n'); // clear buffer
        return;
    }
    while (getchar() != '\n'); // clear buffer after valid input

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            found = 1;
            if (library[i].isAvailable == 1) {
                library[i].isAvailable = 0;
                printf(GREEN"\nBook borrowed successfully.\n"RESET);
            } else {
                printf("This book is currently borrowed.\n");
                
            }
            break;
        }
    }

    if (!found) {
        printf("Book with ID %d not found.\n", id);
    }
    Sleep(1000); // Simulate a short delay
    clearScreen();
}
void returnBook() {
    int id, found = 0;
    printf("Enter the book ID to return: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            if (library[i].isAvailable == 0) {
                library[i].isAvailable = 1;
                printf(GREEN"\nBook returned successfully.\n"RESET);
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
    Sleep(1000); 
    clearScreen();
}
