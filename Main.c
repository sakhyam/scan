#include <stdio.h>
#include <string.h>
#include <ctype.h>

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int passwordStrength(const char *pwd) {
    int len = strlen(pwd);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    for (int i = 0; pwd[i] != '\0'; i++) {
        if (isupper((unsigned char)pwd[i])) hasUpper = 1;
        else if (islower((unsigned char)pwd[i])) hasLower = 1;
        else if (isdigit((unsigned char)pwd[i])) hasDigit = 1;
        else hasSpecial = 1;
    }

    if (len >= 12 && hasUpper && hasLower && hasDigit && hasSpecial) return 3; // Strong
    if (len >= 8 && ((hasUpper + hasLower + hasDigit + hasSpecial) >= 3)) return 2; // Medium
    return 1; // Weak
}

unsigned long simpleHash(const char *text) {
    unsigned long hash = 5381;
    for (int i = 0; text[i] != '\0'; i++) {
        hash = ((hash << 5) + hash) + (unsigned char)text[i]; // djb2
    }
    return hash;
}

int isValidPort(int port) {
    return port >= 1 && port <= 65535;
}

void passwordMenu() {
    char pwd[256];
    printf("\nEnter password to check: ");
    fgets(pwd, sizeof(pwd), stdin);
    pwd[strcspn(pwd, "\n")] = '\0';

    int result = passwordStrength(pwd);
    if (result == 3) printf("Password Strength: Strong\n");
    else if (result == 2) printf("Password Strength: Medium\n");
    else printf("Password Strength: Weak\n");
}

void hashMenu() {
    char text[256];
    printf("\nEnter text to hash: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Hash Value: %lu\n", simpleHash(text));
}

void portMenu() {
    int port;
    printf("\nEnter port number to check: ");
    scanf("%d", &port);
    clearInput();

    if (isValidPort(port))
        printf("Port %d is valid\n", port);
    else
        printf("Invalid port number\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n=== Cyber Security Tools UI ===\n");
        printf("1. Password Strength Checker\n");
        printf("2. Hash Generator\n");
        printf("3. Port Checker\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        clearInput();

        switch (choice) {
            case 1:
                passwordMenu();
                break;
            case 2:
                hashMenu();
                break;
            case 3:
                portMenu();
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
