// user.h

#ifndef USER_H
#define USER_H

#include "file.h"
#define MAX_STRING 128


void toLowerCase(char* str);

// User functions
void borrowBook();
void userLogin();
void userMenu();
void displayUserMenu();
void viewAvailableBooks();
void returnBook();
void searchForBooks();


#endif
