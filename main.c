#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

bool is_prime(unsigned long long);
void print_usage(const char*, FILE*);

int main(int argc, char *argv[]) {
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        print_usage(argv[0], stdout);
        return 0;
    }

    if (argc != 2) {
        fprintf(stderr, "Error: Incorrect number of arguments.\n");
        print_usage(argv[0], stderr);
        return 1;
    }

    char *endptr;
    errno = 0;
    unsigned long long number = strtoull(argv[1], &endptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Error: Number is too large (maximum %llu).\n", ULLONG_MAX);
        return 1;
    }

    if (argv[1] == endptr || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid input. Please provide a valid positive integer.\n");
        print_usage(argv[0], stderr); // Reusing the function
        return 1;
    }

    if (is_prime(number)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}

bool is_prime(unsigned long long number) {
    if (number <= 1) return false;
    if (number <= 3) return true;
    if (number % 2 == 0 || number % 3 == 0) return false;

    // FIX: Use division to prevent overflow of i*i
    for (unsigned long long i = 5; i <= number / i; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

void print_usage(const char *program_name, FILE *stream) {
    fprintf(stream, "Usage: %s <positive integer>\n", program_name);
    fprintf(stream, "Checks if the provided number is a prime number.\n");
}
