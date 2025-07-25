#include<stdio.h>
#include<stdlib.h>
#include<string.h>  
#include<windows.h>
#include "admin.h"
#include "file.h"

Book library[1000];
int bookCount = 0;
int dataChanged = 0;

void loadFromCSV() {
    FILE *fp = fopen("books.csv", "r");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    bookCount = 0;
    while (fscanf(fp, "%d,%99[^,],%99[^,],%d,%d\n",
                  &library[bookCount].id,
                  library[bookCount].title,
                  library[bookCount].author,
                  &library[bookCount].year,
                  &library[bookCount].isBorrowed) == 5) {
        bookCount++;
    }
    fclose(fp);
}

void saveToCSV() {
    printf("Saving data to CSV...\n");

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
            library[i].isBorrowed);
    }

    fclose(fp);
    printf("Data saved successfully.\n");
}
