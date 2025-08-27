#ifndef FILE_H
#define FILE_H

#define MAX_BOOKS 10000

typedef struct {
    int id;
    char title[100];
    char author[100];
    int year;
    int isAvailable; // 1 = Available, 0 = Borrowed
} Book;

extern Book library[MAX_BOOKS];
extern int bookCount;

void toLowerCase(char* str);
// clear terminal
void clearScreen();

void loadFromCSV();        // Load books from CSV
void saveToCSV();          // Save books to CSV

#endif
