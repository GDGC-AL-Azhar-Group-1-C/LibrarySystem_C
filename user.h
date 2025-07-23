void viewAvailableBooks();
void returnBOOK();
void searchForBooks();

#define MAX_STRING 100
#define MAX_BOOKS 1000
#define MAX_MEMBERS 500
#define MAX_USERS 100

Book books[MAX_BOOKS];
Member members[MAX_MEMBERS];
User users[MAX_USERS];

int countBooks = 0;
int countMembers = 0;
int countUsers = 0;