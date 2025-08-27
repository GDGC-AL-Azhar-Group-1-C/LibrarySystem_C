#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "admin.h"
#include "file.h"
#include "user.h"

#define MAX_BOOKS 10000
#define MAX_STRING 128
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

extern Book library[MAX_BOOKS];
extern int bookCount;

void adminLogin() {
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;
    int adminId;
    while (attempts < MAX_ATTEMPTS) {
        printf("Enter Admin ID: ");
        if (scanf("%d", &adminId) != 1) {
            printf(RED"\nInvalid input. Please enter a valid number.\n"RESET);
            while (getchar() != '\n');  // clear buffer
            continue;
        }
        while (getchar() != '\n');  // clear buffer after valid input

        printf("Enter Password: ");
        char password[20];
        scanf("%19s", password);
        while (getchar() != '\n');  // clear buffer after reading password

        if (adminId != 1234 || strcmp(password, "admin123") != 0) {
            printf(RED"\nInvalid Admin ID or Password. Please try again.\n"RESET);
            attempts++;
        } else {
            printf(GREEN"\nAdmin login successful!\n"RESET);
            Sleep(1000); // Simulate a short delay
            clearScreen();
            adminMenu();
            return;
        }
    }
   
    printf(RED"\nToo many failed attempts. Exiting...\n"RESET);
    exit(1);    
}

void displayAdminMenu() {
    printf("\n=========================\n");
    printf("        Admin Menu       \n");
    printf("=========================\n");
    printf("1. Add New Book\n");
    printf("2. Remove Book\n");
    printf("3. View All Books\n");
    printf("4. View Borrowed Books\n");
    printf("5. Count Total Books\n");
    printf("6. Search for Book\n");
    printf("7. Logout\n");
    printf("=========================\n");
    printf("Please select an option: ");
}

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf(RED"Cannot add more books. Library is full.\n"RESET);
        return;
    }

    Book newBook;
    int maxId = 0;
    for (int i = 0; i < bookCount; i++) {
        if (library[i].id > maxId)
            maxId = library[i].id;
    }
    newBook.id = maxId + 1;

    while (getchar() != '\n'); 

    // Validate title length
    do {
        printf("Enter book title: ");
        fgets(newBook.title, sizeof(newBook.title), stdin);
        newBook.title[strcspn(newBook.title, "\n")] = '\0';
        if (strlen(newBook.title) < 3) {
            printf(RED"Title too short! Please enter at least 3 characters.\n"RESET);
        }
    
    } while (strlen(newBook.title) < 3);

    // Validate author length
    do {
        printf("Enter author name: ");
        fgets(newBook.author, sizeof(newBook.author), stdin);
        newBook.author[strcspn(newBook.author, "\n")] = '\0';
        if (strlen(newBook.author) < 3) {
            printf(RED"Author name too short! Please enter at least 3 characters.\n"RESET);
        }
    } while (strlen(newBook.author) < 3);

    // Read year with validation
    printf("Enter publication year: ");
    while (scanf("%d", &newBook.year) != 1) {
        printf(RED"Invalid input! Please enter a valid year: "RESET);
        while (getchar() != '\n'); 
    }

    newBook.isAvailable = 1; // Default to available

    library[bookCount++] = newBook;

    printf(GREEN"\nBook added successfully!\n"RESET);
    printf("ID: %d\nTitle: %s\nAuthor: %s\nYear: %d\n\n",
           newBook.id, newBook.title, newBook.author, newBook.year);
}

void removeBook() {
    int id, found = 0;
    printf("Enter the ID of the book to remove: ");
    if (scanf("%d", &id) != 1) {
        printf(RED"Invalid input. Please enter a valid number.\n"RESET);
        while (getchar() != '\n');
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            found = 1;
            for (int j = i; j < bookCount - 1; j++) {
                library[j] = library[j + 1];
            }
            memset(&library[bookCount - 1], 0, sizeof(Book));
            bookCount--;
            printf(GREEN "Book with ID %d removed successfully.\n" RESET, id);
            return;
        }
    }

    if (!found) {
        printf("Book with ID %d not found.\n", id);
    }
    Sleep(1000); 
    clearScreen();

}

void viewAllBooks() {
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\n---------------------- All Books ----------------------\n");
    printf("+------+------------------------+------------------------+------+------------+\n");
    printf("| ID    | Title                     | Author                 | Year | Status     |\n");
    printf("+------+------------------------+------------------------+------+------------+\n");
    for (int i = 0; i < bookCount; i++) {
        printf("| %-5d | %-25s | %-22s | %-4d | %-10s |\n",
            library[i].id,
            library[i].title,
            library[i].author,
            library[i].year,
            library[i].isAvailable ? "Available" : "Borrowed");
    }
    printf("+------+------------------------+------------------------+------+------------+\n");
    printf("/nDo you want keep viewing the books? (Y): ");
    char c;
    scanf(" %c", &c);
    if (c == 'Y' || c == 'y') {
        Sleep(1000);
        clearScreen();
    } else {
        printf("Exiting book view.\n");
    }
}

void viewBorrowedBooks() {
    int found = 0;
    printf("\n---------------------- Borrowed Books ----------------------\n");
    printf("+------+---------------------------+------------------------+------+------------+\n");
    printf("| ID   | Title                     | Author                 | Year | Status     |\n");
    printf("+------+---------------------------+------------------------+------+------------+\n");
    for (int i = 0; i < bookCount; i++) {
        if (!library[i].isAvailable) {
            printf("| %-4d | %-25s | %-22s | %-4d | %-10s |\n",
                library[i].id,
                library[i].title,
                library[i].author,
                library[i].year,
                "Borrowed");
            found = 1;
        }
    }
    if (!found) {
        printf("| No borrowed books found.                                                  |\n");
    }
    printf("+------+---------------------------+------------------------+------+------------+\n");
    printf("\nDo you want to keep viewing the borrowed books? (Y): ");
    char c; 
    scanf(" %c", &c);
    if (c == 'y' || c == 'Y') {
        Sleep(1000);
        clearScreen();
    } else {
        printf("Exiting book view.\n");
    }
}

void countBooks() {
    printf(GREEN"\nTotal number of books in the library: %d\n"RESET, bookCount);
    printf("Press Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
    clearScreen();
}


void adminMenu() {
    int choice;
    while (1) {
        displayAdminMenu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf(RED"\nInvalid input. Please enter a number from 1 to 7.\n"RESET);
            continue;
        }

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                removeBook();
                break;
            case 3:
                viewAllBooks();
                break;
            case 4:
                viewBorrowedBooks();
                break;
            case 5:
                countBooks();
                break;
            case 6:
                searchForBooks();
                break;
            case 7:
                printf(GREEN "Saving data...\n" RESET);
                saveToCSV();
                Sleep(1000);
                printf(GREEN "Data saved successfully! Logging out...\n" RESET);
                Sleep(1000);
                clearScreen();
                return;
            default:
                printf(RED"\nInvalid choice, please try again.\n"RESET);
        }
    }
}
