#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

typedef struct {
    int id;
    char name[50];
    float grade;
} Student;

void addStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Database full!\n");
        return;
    }
    printf("Enter Student ID: ");
    scanf("%d", &students[*count].id);
    printf("Enter Name: ");
    scanf(" %[^\n]", students[*count].name);
    printf("Enter Grade: ");
    scanf("%f", &students[*count].grade);
    
    (*count)++;
    printf("Student added successfully!\n");
}

void displayStudents(Student students[], int count) {
    if (count == 0) {
        printf("No students available!\n");
        return;
    }
    printf("\n%-5s %-20s %-5s\n", "ID", "Name", "Grade");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-5.2f\n", students[i].id, students[i].name, students[i].grade);
    }
}

void updateStudent(Student students[], int count) {
    int id, found = 0;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);
    
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", students[i].name);
            printf("Enter New Grade: ");
            scanf("%f", &students[i].grade);
            printf("Student record updated!\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Student not found!\n");
}

void deleteStudent(Student students[], int *count) {
    int id, found = 0;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);
    
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1]; // Shift records
            }
            (*count)--;
            printf("Student deleted successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Student not found!\n");
}

void sortStudentsByGrade(Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].grade < students[j + 1].grade) { // Descending order
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("Students sorted by grade!\n");
}

void saveToFile(Student students[], int count) {
    FILE *file = fopen("students.dat", "wb");
    if (!file) {
        printf("Error saving data!\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), count, file);
    fclose(file);
    printf("Data saved successfully!\n");
}

void loadFromFile(Student students[], int *count) {
    FILE *file = fopen("students.dat", "rb");
    if (!file) {
        printf("No existing data found!\n");
        return;
    }
    fread(count, sizeof(int), 1, file);
    fread(students, sizeof(Student), *count, file);
    fclose(file);
    printf("Data loaded successfully!\n");
}

int main() {
    Student students[MAX_STUDENTS];
    int count = 0, choice;

    loadFromFile(students, &count);

    do {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n2. Display Students\n3. Update Student\n4. Delete Student\n5. Sort by Grade\n6. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(students, &count); break;
            case 2: displayStudents(students, count); break;
            case 3: updateStudent(students, count); break;
            case 4: deleteStudent(students, &count); break;
            case 5: sortStudentsByGrade(students, count); displayStudents(students, count); break;
            case 6: saveToFile(students, count); printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}
