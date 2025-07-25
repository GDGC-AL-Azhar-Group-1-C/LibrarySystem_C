#ifndef ADMIN_H
#define ADMIN_H

typedef struct {
    int id;
    char title[100];
    char author[100];
    int year;
    int isAvailable; 
} Book;


void loadBooksFromCSV();
void saveBooksToCSV();
void viewAllBooks();

// Admin functions
void addBook();
void removeBook();
void viewBorrowedBooks();
void countBooks();

// User functions
void viewAvailableBooks();
void borrowBook();
void returnBook();
void searchForBooks();
