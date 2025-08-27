# 📚 Library Management System (C Language)

## 🎯 Objective
A console-based application written in **C** that simulates a simple **Library Management System**.  
It provides two modes: **Admin** and **User**, with different privileges.  

---

## 👥 Modes

### 🔐 Admin Mode
Admins have full control over the library and can perform:

1. ➕ **Add New Book**  
2. ❌ **Remove Book**  
3. 📚 **View All Books**  
4. 📕 **View Borrowed Books**  
5. 🔢 **Count Total Books**  
6. 🔍 **Search for Book**  
7. 🔓 **Logout**

---

### 👤 User Mode
Users can interact with the library and perform:

1. 📖 **View Available Books**  
2. 📥 **Borrow a Book**  
3. 📤 **Return a Book**  
4. 🔍 **Search for Books**  
   - By **Title**  
   - By **Author**  
   - By **Publication Year**  
5. 🔓 **Logout**

---

## 🛠 Features
- Book management: add, remove, borrow, return.  
- Search functionality: by title, author, year.  
- Data persistence using **CSV files**.  
- Login system with limited attempts.  
- Interactive text menus with **clear console UI**.  

---

## 🚀 How to Compile & Run

1. Navigate to the project folder:
   ```bash
   cd LibrarySystem_C
