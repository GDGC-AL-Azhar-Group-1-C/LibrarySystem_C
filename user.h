
typedef struct {
    int id;
    char title[100];
    char author[100];
    int year;
    bool isAvailable; 
} Book;

void viewAvailableBooks();
void returnBOOK();