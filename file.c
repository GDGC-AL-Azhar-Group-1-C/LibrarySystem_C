#include<stdio.h>
#include<stdlib.h>
#include<string.h>  
#include <windows.h>
#include "admin.h"
#include "file.h"

void loadFromCSV(){
    printf("Loading data from CSV...\n");
    FILE *file = fopen("books.csv","r");
    if (file == NULL){
        printf("Error opening file.\n");
        exit(1);
    }

}

void saveToCSV(){
    printf("Saving data to CSV...\n");
}
