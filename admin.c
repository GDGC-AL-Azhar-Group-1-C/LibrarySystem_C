#include<stdio.h>
#include<stdlib.h>  
#include<string.h>  
#include <windows.h>
#include "file.h"
#include "admin.h"


void adminLogin(){
    int count = 1;
    printf("Welcome to the Admin Login!\n");
    int adminId;
    char password[20];  
    const int correctAdminId = 1234; 
    const char correctPassword[] = "admin123"; 
    while (1){
        printf("Enter Admin ID: ");
        scanf("%d", &adminId);
        printf("Enter Password: ");
        scanf("%10s", password);
        if (adminId != correctAdminId || strcmp(password, correctPassword) != 0){
            printf("Invalid Admin ID or Password. Please try again.\n");
            count++;
            if (count > 3){
                printf("Too many failed attempts. Exiting...\n");
                exit(1);
            }
            
        }else{
            printf("Admin login successful!\n");
            break;
        }
    }
}

// 1 - Add new books
// 2- Remove books
// 3 - View all books
// 4 - Search for books
// 5 - View borrowed books
// 6 - Count total books
// 7 - Logout
void displayAdminMenu() {
    printf("\n=========================\n");
    printf("        Admin Menu       \n");
    printf("=========================\n");
    printf("1. Add New Book\n");
    printf("2. Remove Book\n");
    printf("3. View All Books\n");
	printf("4. Search For Books\n");
    printf("5. View Borrowed Books\n");
    printf("6. Count Total Books\n");
    printf("7. Logout\n");
    printf("=========================\n");
    printf("Please select an option: ");
}


void adminMenu(){
    char choice;
    DisplayAdminMenu();
    while (1){
        if (scanf(" %c", &choice) != 1) {
            while (getchar() != '\n'); 
            printf("Invalid input. Please enter a number from 1 to 6.\n");
            continue;
        }
        switch (choice){
            case '1:
                // Function to add new book
                break;
            case '2':
                // Function to remove book
                break;
            case '3':
                // Function to view all books
                break;
			case '4':
                // Function to search for books
				searchForBooks();
				break;
            case '5':
                // Function to view borrowed books
                break;      
            case '6':
                // Function to count total books
                break;
            case '7':
                printf("Logging out...\n");
                Sleep(1000); 
                return ; 
            default:
                printf("Invalid choice, please try again.\n");  
        }
    }
}