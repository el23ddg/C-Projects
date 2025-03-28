#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define FILENAME "bank_data.dat"

typedef struct {
    int account_number;
    char name[50];
    double balance;
    char password[20];  // Will be stored in encrypted form
} Account;

void encryptDecrypt(char *data) {
    char key = 'X';  // Simple XOR key
    while (*data) {
        *data ^= key;
        data++;
    }
}

void createAccount() {
    FILE *file = fopen(FILENAME, "ab");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    Account acc;
    printf("Enter Account Number: ");
    scanf("%d", &acc.account_number);
    printf("Enter Name: ");
    scanf("%s", acc.name);
    printf("Enter Initial Deposit: ");
    scanf("%lf", &acc.balance);
    printf("Create a Password: ");
    scanf("%s", acc.password);

    encryptDecrypt(acc.password);  // Encrypt password

    fwrite(&acc, sizeof(Account), 1, file);
    fclose(file);
    printf("Account created successfully!\n");
}

int login(int acc_num, char *password) {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Error opening file!\n");
        return 0;
    }

    Account acc;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.account_number == acc_num) {
            encryptDecrypt(acc.password);
            if (strcmp(acc.password, password) == 0) {
                fclose(file);
                return 1; // Login success
            }
        }
    }
    fclose(file);
    return 0; // Login failed
}

void deposit(int acc_num, double amount) {
    FILE *file = fopen(FILENAME, "rb+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    Account acc;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.account_number == acc_num) {
            acc.balance += amount;
            fseek(file, -sizeof(Account), SEEK_CUR);
            fwrite(&acc, sizeof(Account), 1, file);
            fclose(file);
            printf("Deposit successful! New Balance: %.2f\n", acc.balance);
            return;
        }
    }
    fclose(file);
    printf("Account not found!\n");
}

void withdraw(int acc_num, double amount) {
    FILE *file = fopen(FILENAME, "rb+");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    Account acc;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.account_number == acc_num) {
            if (acc.balance >= amount) {
                acc.balance -= amount;
                fseek(file, -sizeof(Account), SEEK_CUR);
                fwrite(&acc, sizeof(Account), 1, file);
                fclose(file);
                printf("Withdrawal successful! New Balance: %.2f\n", acc.balance);
                return;
            } else {
                printf("Insufficient balance!\n");
                fclose(file);
                return;
            }
        }
    }
    fclose(file);
    printf("Account not found!\n");
}

void checkBalance(int acc_num) {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    Account acc;
    while (fread(&acc, sizeof(Account), 1, file)) {
        if (acc.account_number == acc_num) {
            printf("Account Number: %d\n", acc.account_number);
            printf("Name: %s\n", acc.name);
            printf("Current Balance: %.2f\n", acc.balance);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("Account not found!\n");
}

int main() {
    int choice, acc_num;
    char password[20];
    double amount;

    while (1) {
        printf("\nBanking System\n");
        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Check Balance\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                printf("Enter Account Number: ");
                scanf("%d", &acc_num);
                printf("Enter Password: ");
                scanf("%s", password);
                if (login(acc_num, password))
                    printf("Login Successful!\n");
                else
                    printf("Invalid Credentials!\n");
                break;
            case 3:
                printf("Enter Account Number: ");
                scanf("%d", &acc_num);
                printf("Enter Amount to Deposit: ");
                scanf("%lf", &amount);
                deposit(acc_num, amount);
                break;
            case 4:
                printf("Enter Account Number: ");
                scanf("%d", &acc_num);
                printf("Enter Amount to Withdraw: ");
                scanf("%lf", &amount);
                withdraw(acc_num, amount);
                break;
            case 5:
                printf("Enter Account Number: ");
                scanf("%d", &acc_num);
                checkBalance(acc_num);
                break;
            case 6:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
