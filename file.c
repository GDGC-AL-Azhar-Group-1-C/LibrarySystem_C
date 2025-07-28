#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include "admin.h"
#include "file.h"

#define MAX_BOOKS 10000

Book library[MAX_BOOKS];
int bookCount = 0;


void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}



// Load book data from a CSV file
void loadFromCSV() {
    FILE *fp = fopen("books.csv", "r");
    if (fp == NULL) {
        printf("No existing data found (books.csv not found). Starting with an empty library.\n");
        return;
    }

    bookCount = 0;
    while (bookCount < MAX_BOOKS &&
           fscanf(fp, "%d,%99[^,],%99[^,],%d,%d\n",
                &library[bookCount].id,
                library[bookCount].title,
                library[bookCount].author,
                &library[bookCount].year,
                &library[bookCount].isAvailable) == 5) {
        bookCount++;
    }

    fclose(fp);

    if (bookCount >= MAX_BOOKS) {
        printf("Warning: Reached the maximum number of books (%d).\n", MAX_BOOKS);
    } else {
        printf("Loaded %d books from books.csv.\n", bookCount);
    }
}

// Save current book data to a CSV file
void saveToCSV() {
    FILE *fp = fopen("books.csv", "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        fprintf(fp, "%d,%s,%s,%d,%d\n",
                library[i].id,
                library[i].title,
                library[i].author,
                library[i].year,
                library[i].isAvailable);
    }

    fclose(fp);
   // printf("Library saved successfully to books.csv.\n");
}
