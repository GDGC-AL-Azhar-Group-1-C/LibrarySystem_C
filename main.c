#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "admin.h"
#include "user.h"
#include "file.h"

void displayMenu(){
    printf("Welcome to the file management system!\n");
    printf("1. Admin login\n");
    printf("2. User login\n");
    printf("3. Exit\n");
    printf("please select an option: ");
}

int main(){
    int choice;
    loadFromCSV();
    while (1){
        displayMenu();
        scanf("%d", &choice);
        switch (choice){
            case 1:
                adminLogin();
                break;
            case 2:
                userLogin();
                break;
            case 3:
                printf("Exiting the system. Goodbye!\n");
                saveToCSV();
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}
