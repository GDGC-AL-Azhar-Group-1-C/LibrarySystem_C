#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "admin.h"
#include "file.h"

#define MAX_BOOKS 10000

extern Book library[MAX_BOOKS];
extern int bookCount;

void adminLogin() {
    int attempts = 0;
    const int MAX_ATTEMPTS = 3;
    int adminId;
    while (attempts < MAX_ATTEMPTS) {
        printf("Enter Admin ID: ");
        if (scanf("%d", &adminId) != 1) {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');  // clear buffer
            continue;
        }
        while (getchar() != '\n');  // clear buffer after valid input

        printf("Enter Password: ");
        char password[20];
        scanf("%19s", password);
        while (getchar() != '\n');  // clear buffer after reading password

        if (adminId != 1234 || strcmp(password, "admin123") != 0) {
            printf("Invalid Admin ID or Password. Please try again.\n");
            attempts++;
        } else {
            printf("\nAdmin login successful!\n");
            Sleep(1000); // Simulate a short delay
            adminMenu();
            return;
        }
    }
   
    printf("Too many failed attempts. Exiting...\n");
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
    printf("6. Logout\n");
    printf("=========================\n");
    printf("Please select an option: ");
}

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Cannot add more books. Library is full.\n");
        return;
    }

    Book newBook;
    newBook.id = bookCount + 1;

    getchar(); // Clear input buffer
    printf("Enter book title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0';

    printf("Enter author name: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    printf("Enter publication year: ");
    scanf("%d", &newBook.year);

    newBook.isAvailable = 1; // New book is available by default

    library[bookCount++] = newBook;
    printf("Book added successfully!\n");
}

void removeBook() {
    int id, found = 0;
    printf("Enter the ID of the book to remove: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input. Please enter a valid number.\n");
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
            printf("Book with ID %d removed successfully.\n", id);
            return;
        }
    }

    if (!found) {
        printf("Book with ID %d not found.\n", id);
    }
}

void viewAllBooks() {
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\n--- All Books ---\n");
    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d | Title: %s | Author: %s | Year: %d | Status: %s\n",
            library[i].id,
            library[i].title,
            library[i].author,
            library[i].year,
            library[i].isAvailable ? "Available" : "Borrowed");
    }
}
void viewBorrowedBooks() {
    int found = 0;
    printf("\n--- Borrowed Books ---\n");
    for (int i = 0; i < bookCount; i++) {
        if (!library[i].isAvailable) {
            printf("ID: %d | Title: %s | Author: %s | Year: %d\n",
                library[i].id,
                library[i].title,
                library[i].author,
                library[i].year);
            found = 1;
        }
    }
    if (!found) {
        printf("No borrowed books found.\n");
    }
}

void countBooks() {
    printf("\nTotal number of books in the library: %d\n", bookCount);
}

void adminMenu() {
    char choice;
    while (1) {
        displayAdminMenu();
        if (scanf(" %c", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number from 1 to 6.\n");
            continue;
        }

        switch (choice) {
            case '1':
                addBook();
                break;
            case '2':
                removeBook();
                break;
            case '3':
                viewAllBooks();
                break;
            case '4':
                viewBorrowedBooks();
                break;
            case '5':
                countBooks();
                break;
            case '6':
                printf("Saving data...\n");
                saveToCSV(); 
                printf("Logging out...\n");
                Sleep(1000);
                return;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}
