#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

static char *invoc_name = NULL;
static char *version_string = "1.0";

static struct option longopts[] = {
    { "version", no_argument, NULL, 'v' },
    { "help", no_argument, NULL, 'h' },
    { NULL, 0, NULL, 0 },
};

static char *unit_words[] = {
    "zero", "one", "two", "three", "four",
    "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen",
    "fourteen", "fifteen", "sixteen",
    "seventeen", "eighteen", "nineteen",
};

static char *tens_words[] = {
    "twenty", "thirty", "forty",
    "fifty", "sixty", "seventy",
    "eighty", "ninety",
};

static char *multiplier_words[] = {
    "hundred",
    "thousand",
    "million",
    "milliard",
    "billion",
};

static void usage(void);
static void version(void);

static void print_number_in_words(int number);

int main(int argc, char **argv){
    int c;
    invoc_name = argv[0];

    while ( ( c = getopt_long(argc, argv, "hv", longopts, NULL) ) != -1 ) {
        switch (c) {
            case 'h':
                usage();
                exit(EXIT_SUCCESS);
            case 'v':
                version();
                exit(EXIT_SUCCESS);
            default:
                fprintf(stderr, "Try %s --help for more information.\n", invoc_name);
                exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        int number;
        if (sscanf(argv[optind], "%d", &number)) {
            print_number_in_words(number);
            puts("");
        }
        else {
            fprintf(stderr, "Invalid number: %s\n", argv[optind]);
            exit(EXIT_FAILURE);
        }
    }
    else {
        ; /* print it for each line of input */
    }

    return 0;
}

static void print_number_in_words(int number){
    if ( number >= 100 ) {
        int hundreds = (number / 100);
    }
    else if ( number >= 20 ) {
        int tens = (number / 10) % 10 - 2;
        int units = number % 10;
        printf("%s", tens_words[tens]);
        if ( units ) {
            printf("-");
            print_number_in_words(units);
        }
    }
    else
        printf("%s", unit_words[number]);
}

static void usage(void){
    printf("Usage:\n");
}

static void version(void){
    printf("Numbers v%s\n", version_string);
}
