#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "user.h"
#include "file.h"

#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

void displayMenu() {
    printf("\n==============================\n");
    printf(" Welcome to the Library System\n");
    printf("==============================\n");
    printf("1. Admin login\n");
    printf("2. User login\n");
    printf("3. Exit\n\n");
    printf("Please select an option: ");
}

int main() {
    int choice;
    loadFromCSV();

    while (1) {
        displayMenu();

        if (scanf("%d", &choice) != 1) {
            printf(RED"\nInvalid input. Please enter a number.\n"RESET);
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                userLogin();
                break;
            case 3:
                printf("Exiting the system.\n");
                saveToCSV();
                printf("Goodbye!\n");
                exit(0);
            default:
                printf(RED"\nInvalid choice, please try again.\n"RESET);
        }
    }

    return 0;
}
