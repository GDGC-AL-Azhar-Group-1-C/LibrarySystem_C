void viewAvailableBooks()
 {
    Book books[100];
    int count =0;

printf("Available books:\n");
    int found = 0;
    for (int i = 0; i < count; i++) 
    {
    if (books[i].isBorrowed == 0) 
      { 
printf("ID: %d | Title: %s | Author: %s | Year: %d\n",
     books[i].id, books[i].title,
     books[i].author, books[i].year);
 found = 1;      
    }
    }
      if (!found) {
      printf("No available books at the moment.\n");
    }
    } 


void returnBook() {
    Book books[100];
    int count, id, found = 0;  

printf("Please enter the book ID to return:\n");
scanf("%d", &id);

    for (int i = 0; i < count; i++) {
    if (books[i].id == id && books[i].isBorrowed == 1) {
            books[i].isBorrowed = 0;     
    printf("Book returned successfully.\n");
    found = 1;
}   else {
        printf("This book is not currently borrowed.\n");
    found =1;    
}
    break;
} 
}
    if (!found)  {
                  printf("Book with ID %d not found.\n",id);

}
