#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>
#include "user.h"
#include "file.h"

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
            printf("Invalid User ID or Password. Please try again.\n");
            attempts++;
        } else {
            printf("User login successful!\n");
            Sleep(1000); // Simulate a short delay
            userMenu();
            return;
        }
    }

    printf("Too many failed attempts. Exiting...\n");
    exit(1);
}

void viewAvailableBooks() {
    int found = 0;
    printf("Available books:\n");

    for (int i = 0; i < bookCount; i++) {
        if (library[i].isAvailable == 1) {
            printf("ID: %d | Title: %s | Author: %s | Year: %d\n",
                   library[i].id, library[i].title, library[i].author, library[i].year);
            found = 1;
        }
    }

    if (!found) {
        printf("No available books at the moment.\n");
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

void searchForBooks() {
    char choice;
    char buffer[128];

    while (1) {
        printf("\n--- Choose Search Option ---\n");
        printf("1. Search by Title or Author\n");
        printf("2. Filter by Publication Year\n");
        printf("3. Exit Search\n");
        printf("Choice: ");
        scanf(" %c", &choice); // add space before %c to skip any newline

        if (choice == '1') {
            char search[100];
            int found = 0;
            printf("Enter keyword (title or author): ");
            getchar(); // flush newline left in buffer
            fgets(search, sizeof(search), stdin);
            search[strcspn(search, "\n")] = 0;

            printf("\n--- Search Results ---\n");
            for (int i = 0; i < bookCount; i++) {
                if (strstr(library[i].title, search) || strstr(library[i].author, search)) {
                    printf("Book ID: %d | Title: %s | Author: %s | Year: %d\n",
                           library[i].id, library[i].title, library[i].author, library[i].year);
                    found = 1;
                }
            }
            if (!found) {
                printf("No books found with this keyword.\n");
            }

        } else if (choice == '2') {
            int year, found = 0;
            printf("Enter publication year: ");
            scanf("%d", &year);

            printf("\n--- Books Published in %d ---\n", year);
            for (int i = 0; i < bookCount; i++) {
                if (library[i].year == year) {
                    printf("Book ID: %d | Title: %s | Author: %s | Year: %d\n",
                           library[i].id, library[i].title, library[i].author, library[i].year);
                    found = 1;
                }
            }
            if (!found) {
                printf("No books found for this year.\n");
            }

        } else if (choice == '3') {
            printf("Exiting search...\n");
            break;
        } else {
            printf("Invalid option. Please choose 1, 2, or 3.\n");
        }
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
