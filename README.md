# C-Projects
Projects that I am learning and building to understand and grasp better concepts in C programming.
## 1. 📚 Library Management System
A simple Library Management System written in C with file handling and admin authentication.
#### ✨ Features
- ✅ Add books
- 🔍 Search books
- ❌ Remove books
- ✏️ Update book details
- 🔑 Admin authentication
- 💾 Persistent storage using files
#### 📜 Usage
- Admin Login: Enter username (admin) and password (password).
- Choose an option:
1) ➝ Add a book 📖
2) ➝ Search for a book 🔍
3) ➝ Remove a book ❌
4) ➝ Update book details ✏️
5) ➝ Exit 🚪
#### 📝 File Handling
Books are stored in books.txt, ensuring data persistence.
#### 🔒 Admin Authentication
- Username: admin
- Password: password
#### Why is temp.txt needed?
##### In Library Management System in C, temp.txt is created as a temporary file to facilitate updating or deleting records in books.txt.
Files in C do not support direct modification (like updating a specific line). To update or remove a book, we need to:
- Read books.txt line by line and copy its content to temp.txt, while applying changes.
- Skip the book to be removed (for delete) or modify the book details (for update).
- Replace the original file (books.txt) with temp.txt, effectively applying the changes.
#### Give a ⭐ if you like this project! 🚀
