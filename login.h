
#include <stdbool.h>
#include <string.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 20
#define PASSWORD_LENGTH 20
#define DATA_FILE "users.txt"

void User_Data_File();
void loginOrRegister();

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User users[MAX_USERS];
int userCount = 0;

void registerUser(const char *username, const char *password) {
    if (userCount >= MAX_USERS) {
        printf("Cannot register more users. Maximum limit reached.\n");
        loginOrRegister();
        return;
    }

    // Check if the username is already taken
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username '%s' is already taken. Please choose a different username.\n", username);
            return;
        }
    }
    User newUser;    // Creating a new user
    strncpy(newUser.username, username, USERNAME_LENGTH);
    strncpy(newUser.password, password, PASSWORD_LENGTH);

    // Adding the new user to the user array
    users[userCount] = newUser;
    userCount++;

    printf("User '%s' registered successfully.\n", username);
loginOrRegister();
    // Save user data to file
    FILE *file = fopen(DATA_FILE, "a");
    if (file != NULL) {
        fprintf(file, "%s %s\n", username, password);
        fclose(file);
    } else {
        printf("Unable to open data file for writing.\n");
    }
}

bool loginUser(const char *username, const char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Welcome, %s!\n", username);
            sleep(7);
            system("cls");
            shop_menu();
            return true;
        }
    }

    printf("Invalid username or password.\n");
    return false;
}

void User_Data_File() {
    FILE *file = fopen(DATA_FILE, "r");
    if (file != NULL) {
        char username[USERNAME_LENGTH];
        char password[PASSWORD_LENGTH];

        while (fscanf(file, "%s %s", username, password) == 2) {
            // Create a new user
            User newUser;
            strncpy(newUser.username, username, USERNAME_LENGTH);
            strncpy(newUser.password, password, PASSWORD_LENGTH);

            // Add the new user to the user array
            users[userCount] = newUser;
            userCount++;
        }

        fclose(file);
    } else {
        printf("Unable to open data file for reading.\n");
    }
}

void loginOrRegister() {
    int choice;
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];

    printf("1. Login\n");
    printf("2. Register\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);


    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    switch (choice) {
        case 1:
            loginUser(username, password);
            break;
        case 2:
            registerUser(username, password);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}
