#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    char title[50];
    char author[50];
    char isbn[20];
    int quantity;
};

void saveBook(struct Book book) {
    FILE *file = fopen("books.txt", "a");
    fprintf(file, "%s,%s,%s,%d\n", book.title, book.author, book.isbn, book.quantity);
    fclose(file);
}

void addBook() {
    struct Book book;
    printf("Enter title: ");
    scanf(" %[^\n]", book.title);
    printf("Enter author: ");
    scanf(" %[^\n]", book.author);
    printf("Enter ISBN: ");
    scanf(" %s", book.isbn);
    printf("Enter quantity: ");
    scanf("%d", &book.quantity);
    saveBook(book);
    printf("Book added successfully!\n");
}

void searchBook() {
    char searchTitle[50];
    struct Book book;
    FILE *file = fopen("books.txt", "r");

    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter title to search: ");
    scanf(" %[^\n]", searchTitle);

    int found = 0;
    while (fscanf(file, "%[^,],%[^,],%[^,],%d\n", book.title, book.author, book.isbn, &book.quantity) != EOF) {
        if (strcmp(book.title, searchTitle) == 0) {
            printf("Found: %s by %s (ISBN: %s) - Quantity: %d\n", book.title, book.author, book.isbn, book.quantity);
            found = 1;
            break;
        }
    }
    fclose(file);
    if (!found) printf("Book not found!\n");
}

int authenticateAdmin() {
    char username[20], password[20];

    printf("Enter Admin Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        return 1;
    }
    printf("Invalid credentials!\n");
    return 0;
}

void removeBook() {
    char isbnToRemove[20];
    struct Book book;
    FILE *file = fopen("books.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (!file || !tempFile) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter ISBN of the book to remove: ");
    scanf(" %s", isbnToRemove);

    int found = 0;
    while (fscanf(file, "%[^,],%[^,],%[^,],%d\n", book.title, book.author, book.isbn, &book.quantity) != EOF) {
        if (strcmp(book.isbn, isbnToRemove) != 0) {
            fprintf(tempFile, "%s,%s,%s,%d\n", book.title, book.author, book.isbn, book.quantity);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        printf("Book removed successfully!\n");
    else
        printf("Book not found!\n");
}

void updateBook() {
    char isbnToUpdate[20];
    struct Book book;
    FILE *file = fopen("books.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (!file || !tempFile) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter ISBN of the book to update: ");
    scanf(" %s", isbnToUpdate);

    int found = 0;
    while (fscanf(file, "%[^,],%[^,],%[^,],%d\n", book.title, book.author, book.isbn, &book.quantity) != EOF) {
        if (strcmp(book.isbn, isbnToUpdate) == 0) {
            printf("Enter new title: ");
            scanf(" %[^\n]", book.title);
            printf("Enter new author: ");
            scanf(" %[^\n]", book.author);
            printf("Enter new quantity: ");
            scanf("%d", &book.quantity);
            found = 1;
        }
        fprintf(tempFile, "%s,%s,%s,%d\n", book.title, book.author, book.isbn, book.quantity);
    }

    fclose(file);
    fclose(tempFile);

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        printf("Book updated successfully!\n");
    else
        printf("Book not found!\n");
}

void menu() {
    int choice;
    if (!authenticateAdmin()) return;

    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Search Book\n");
        printf("3. Remove Book\n");
        printf("4. Update Book\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: searchBook(); break;
            case 3: removeBook(); break;
            case 4: updateBook(); break;
            case 5: printf("Exiting...\n"); return;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}