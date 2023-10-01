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

// Define the password length
#define PASSWORD_LENGTH 12

#ifdef _WIN32
#include <windows.h>

// Function to generate a random byte on Windows
unsigned char generateRandomByte() {
    unsigned char randomByte;
    if (!CryptGenRandom(GetCurrentProcess(), sizeof(randomByte), &randomByte)) {
        fprintf(stderr, "Error generating random byte\n");
        exit(1);
    }
    return randomByte;
}

#else
#include <fcntl.h>
#include <unistd.h>

// Function to generate a random byte on Linux
unsigned char generateRandomByte() {
    int urandom_fd = open("/dev/urandom", O_RDONLY);
    if (urandom_fd == -1) {
        perror("Error opening /dev/urandom");
        exit(1);
    }

    unsigned char randomByte;
    ssize_t bytes_read = read(urandom_fd, &randomByte, sizeof(randomByte));
    if (bytes_read == -1) {
        perror("Error reading from /dev/urandom");
        close(urandom_fd);
        exit(1);
    }

    close(urandom_fd);
    return randomByte;
}

#endif

int main() {
    int password_length;
    char allow_symbols, allow_uppercase;
    const char* valid_chars_lowercase = "abcdefghijklmnopqrstuvwxyz0123456789";
    const char* valid_chars_symbols = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    printf("Enter password length: ");
    scanf("%d", &password_length);

    printf("Allow symbols (yes/no): ");
    scanf(" %c", &allow_symbols);

    printf("Allow uppercase letters (yes/no): ");
    scanf(" %c", &allow_uppercase);

    const char* valid_chars = valid_chars_lowercase;
    if (allow_symbols == 'y' || allow_symbols == 'Y') {
        valid_chars = valid_chars_symbols;
    }

    char password[password_length + 1]; // +1 for null terminator
    memset(password, 0, sizeof(password));

    size_t num_valid_chars = strlen(valid_chars);

    for (int i = 0; i < password_length; i++) {
        unsigned char random_byte = generateRandomByte();
        password[i] = valid_chars[random_byte % num_valid_chars];

        if (allow_uppercase == 'y' || allow_uppercase == 'Y') {
            // Replace some characters with uppercase letters
            if (i % 3 == 0) {
                password[i] = 'A' + (random_byte % 26);
            }
        }
    }

    printf("Generated Password: %s\n", password);

    return 0;
}
