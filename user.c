void viewAvailableBooks()
 {
    Book books[100];
    int count = 0;
    readBooks(books, &count);

printf("Available books:\n");
    for (int i = 0; i < count; i++) 
    {
    if (books[i].isBorrowed == 0) 
      { 
printf("ID: %d | Title: %s | Author: %s | Year: %d\n",
     books[i].id, books[i].title,
     books[i].author, books[i].year);
       
    }
    }
    } 


void returnBook() {
    Book books[100];
    int count, id, found = 0;
    
    readBooks(books, &count);  

printf("Please enter the book ID to return:\n");
scanf("%d", &id);

    for (int i = 0; i < count; i++) {
    if (books[i].id == id && books[i].isBorrowed == 1) {
            books[i].isBorrowed = 0;  
            found = 1;
            break;
}
}
    if (found) {
        writeBooks(books, count); 
        printf("Book returned successfully.\n");
}   else {
        printf("This book is not currently borrowed.\n");
}
}