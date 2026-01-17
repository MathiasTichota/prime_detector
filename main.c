/*
 * Project: Prime Detector
 * Author: Mathias (MathiasSystem)
 * License: GPLv3
 * Description: A command-line tool to check for primality using the 
 * 6k +/- 1 optimization method.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

// Function Prototypes
bool is_prime(unsigned long long);
void print_usage(const char*, FILE*);

int main(int argc, char *argv[]) {
    // ---------------------------------------------------------
    // 1. Argument Handling
    // ---------------------------------------------------------

    // Check for help flags (-h or --help)
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        print_usage(argv[0], stdout);
        return 0;
    }

    // Ensure exactly one argument is provided
    if (argc != 2) {
        fprintf(stderr, "Error: Incorrect number of arguments.\n");
        print_usage(argv[0], stderr);
        return 1;
    }

    // ---------------------------------------------------------
    // 2. Input Parsing & Validation
    // ---------------------------------------------------------
    
    char *endptr;
    errno = 0; // Reset error number before conversion
    
    // strtoull is used over atoi for safety and 64-bit support
    unsigned long long number = strtoull(argv[1], &endptr, 10);

    // Check for overflow (number larger than ULLONG_MAX)
    if (errno == ERANGE) {
        fprintf(stderr, "Error: Number is too large (maximum %llu).\n", ULLONG_MAX);
        return 1;
    }

    // Check for invalid characters (e.g., "123abc" or empty input)
    if (argv[1] == endptr || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid input. Please provide a valid positive integer.\n");
        print_usage(argv[0], stderr);
        return 1;
    }

    // ---------------------------------------------------------
    // 3. Execution & Output
    // ---------------------------------------------------------

    if (is_prime(number)) {
        printf("true\n");
    } else {
        printf("false\n");
    }

    return 0;
}

/**
 * Checks if a number is prime using the 6k +/- 1 optimization.
 * * Theory: All integers can be expressed as (6k + i).
 * Since 2 divides (6k, 6k+2, 6k+4) and 3 divides (6k+3),
 * primes > 3 can only exist at 6k+1 and 6k+5 (aka 6k-1).
 * * @param number The unsigned 64-bit integer to check.
 * @return true if prime, false otherwise.
 */
bool is_prime(unsigned long long number) {
    // Handle small base cases
    if (number <= 1) return false;
    if (number <= 3) return true;

    // Fast check: Eliminate multiples of 2 and 3
    if (number % 2 == 0 || number % 3 == 0) return false;

    // Check divisors starting from 5 (the first 6k - 1 number)
    // We increment by 6 to jump to the next pair of candidates.
    // Loop Condition: i <= number / i is used to prevent integer overflow
    // compared to i * i <= number.
    for (unsigned long long i = 5; i <= number / i; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

/**
 * Prints usage instructions to the specified output stream.
 * * @param program_name The name of the executable (argv[0]).
 * @param stream The file stream to write to (stdout or stderr).
 */
void print_usage(const char *program_name, FILE *stream) {
    fprintf(stream, "Usage: %s <positive integer>\n", program_name);
    fprintf(stream, "Checks if the provided number is a prime number.\n");
}
