#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_DESC 256

typedef struct {
    int id;
    char description[MAX_DESC];
    int completed;
} Task;

void addTask(Task tasks[], int *taskCount) {
    if (*taskCount >= MAX_TASKS) {
        printf("Task limit reached!\n");
        return;
    }

    printf("Enter task description: ");
    getchar(); // Consume leftover newline character
    fgets(tasks[*taskCount].description, MAX_DESC, stdin);
    tasks[*taskCount].description[strcspn(tasks[*taskCount].description, "\n")] = '\0';

    tasks[*taskCount].id = *taskCount + 1;
    tasks[*taskCount].completed = 0;
    (*taskCount)++;

    printf("Task added successfully!\n");
}

void viewTasks(Task tasks[], int taskCount) {
    printf("\n--- Task List ---\n");
    for (int i = 0; i < taskCount; i++) {
        printf("[%d] %s - %s\n", tasks[i].id, tasks[i].description, tasks[i].completed ? "Completed" : "Pending");
    }
}

void markTaskComplete(Task tasks[], int taskCount) {
    int id;
    printf("Enter task ID to mark as complete: ");
    scanf("%d", &id);

    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            tasks[i].completed = 1;
            printf("Task marked as complete!\n");
            return;
        }
    }
    printf("Task ID not found.\n");
}

void removeTask(Task tasks[], int *taskCount) {
    int id, found = 0;
    printf("Enter task ID to remove: ");
    scanf("%d", &id);

    for (int i = 0; i < *taskCount; i++) {
        if (tasks[i].id == id) {
            found = 1;
            for (int j = i; j < (*taskCount) - 1; j++) {
                tasks[j] = tasks[j + 1];
                tasks[j].id = j + 1;
            }
            (*taskCount)--;
            printf("Task removed successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Task ID not found.\n");
    }
}

void saveTasksToFile(Task tasks[], int taskCount) {
    FILE *file = fopen("tasks.txt", "w");
    if (file == NULL) {
        printf("Error saving tasks.\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%d,%s,%d\n", tasks[i].id, tasks[i].description, tasks[i].completed);
    }
    fclose(file);
    printf("Tasks saved successfully.\n");
}

void loadTasksFromFile(Task tasks[], int *taskCount) {
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL) {
        printf("No previous tasks found.\n");
        return;
    }

    while (fscanf(file, "%d,%255[^,],%d\n", &tasks[*taskCount].id, tasks[*taskCount].description, &tasks[*taskCount].completed) != EOF) {
        (*taskCount)++;
    }
    fclose(file);
    printf("Tasks loaded successfully.\n");
}

int main() {
    Task tasks[MAX_TASKS];
    int taskCount = 0, choice;

    loadTasksFromFile(tasks, &taskCount);

    while (1) {
        printf("\n--- To-Do List ---\n");
        printf("1. Add Task\n2. View Tasks\n3. Mark Task as Complete\n4. Remove Task\n5. Save & Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                viewTasks(tasks, taskCount);
                break;
            case 3:
                markTaskComplete(tasks, taskCount);
                break;
            case 4:
                removeTask(tasks, &taskCount);
                break;
            case 5:
                saveTasksToFile(tasks, taskCount);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
