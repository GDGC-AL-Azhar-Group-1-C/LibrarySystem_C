#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<admin.h>
#include<user.h>
#include<file.h>

void display_menu(){
    printf("Welcome to the file management system!\n");
    printf("1. Admin login\n");
    printf("2. User login\n");
    printf("3. Exit\n");
    printf("please select an option: ");
}

int main(){
    int choice;
    loadFromCSV();
    while (true){
        display_menu();
        scanf("%d", &choice);
        switch (choice){
            case 1:
                admin_login();
                break;
            case 2:
                user_login();
                break;
            case 3:
                saveToCSV();
                printf("Exiting the system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}
