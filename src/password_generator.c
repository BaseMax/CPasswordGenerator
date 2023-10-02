/*
*
*    @Name: C Password Manager
*    @License: GPL-3.0
*    @Date:     01/10/2023
*    @Repository: https://github.com/BaseMax/CPasswordGenerator
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <fcntl.h>
#include <unistd.h>
#endif

// Function to generate a random password
void generatePassword(int length, int useSymbols, int useUpperCase) {
    const char charsetLower[] = "abcdefghijklmnopqrstuvwxyz";
    const char charsetUpper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char symbols[] = "!@#$%^&*()_+=-{}[]|:;<>,.?";

    char charset[128]; // Max possible characters

    strcpy(charset, charsetLower);

    if (useUpperCase) {
        strcat(charset, charsetUpper);
    }

    if (useSymbols) {
        strcat(charset, symbols);
    }

    int charsetLength = strlen(charset);

    char password[length + 1];

#ifdef _WIN32
    HCRYPTPROV hCryptProv;
    if (CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        CryptGenRandom(hCryptProv, length, (BYTE *)password);
        CryptReleaseContext(hCryptProv, 0);
    } else {
        perror("Error generating random password");
        exit(1);
    }
#else
    int urandom_fd = open("/dev/urandom", O_RDONLY);
    if (urandom_fd == -1) {
        perror("Unable to open /dev/urandom");
        exit(1);
    }

    for (int i = 0; i < length; ++i) {
        unsigned char randomByte;
        ssize_t bytes_read = read(urandom_fd, &randomByte, sizeof(randomByte));
        if (bytes_read != sizeof(randomByte)) {
            perror("Error reading from /dev/urandom");
            exit(1);
        }
        password[i] = charset[randomByte % charsetLength];
    }
    close(urandom_fd);
#endif

    password[length] = '\0';

    printf("Generated Password: %s\n", password);
}

int main() {
    int length;
    int useSymbols, useUpperCase;

    printf("Enter the length of the password: ");
    scanf("%d", &length);

    printf("Should the password contain symbols? (0/1): ");
    scanf("%d", &useSymbols);

    printf("Should the password contain uppercase letters? (0/1): ");
    scanf("%d", &useUpperCase);

    generatePassword(length, useSymbols, useUpperCase);

    return 0;
}
