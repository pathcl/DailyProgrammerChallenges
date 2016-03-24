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

static char *numbers[] = {
    "zero", "one", "two", "three", "four",
    "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen",
    "fourteen", "fifteen", "sixteen",
    "seventeen", "eighteen", "nineteen",
};

static char *tens[] = {
    "twenty", "thirty", "forty",
    "fifty", "sixty", "seventy",
    "eighty", "ninety",
};

enum { HUNDRED = 100, THOUSAND = 1000, MILLION = 1000000, MILLIARD = 1000000000, BILLION = 1000000000000 };

static void usage(void);
static void version(void);

static void print_number(int number);

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
            print_number(number);
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

static void print_number(int number){
    if(number < 20){
        printf("%s",numbers[number]);
    }
    else if(number < HUNDRED){
        printf("%s",tens[number / 10 - 2]);
        number %= 10;
        if(number > 0){
            printf("-");
            print_number(number);
        }
    }
    else if(number < THOUSAND){
        printf("%s",numbers[number / HUNDRED]);
        printf("%s"," hundred");
        number %= HUNDRED;
        if(number > 0){
            printf(" and ");
            print_number(number);
        }
    }
    else if(number < MILLION){
        print_number(number / 1000);
        printf("%s"," thousand");
        number %= 1000;
        if(number > 0){
            if(number < HUNDRED)
                printf(" and ");
            else
                printf(", ");
            print_number(number);
        }
    }
    else if(number < MILLIARD){
        print_number(number / MILLION);
        printf("%s"," million");
        number %= MILLION;
        if(number > 0){
            if(number < HUNDRED)
                printf(" and ");
            else
                printf(", ");
            print_number(number);
        }
    }
    else if(number < BILLION){
        print_number(number / MILLIARD);
        printf("%s"," milliard");
        number %= MILLIARD;
        if(number > 0){
            if(number < HUNDRED)
                printf(" and ");
            else
                printf(", ");
            print_number(number);
        }
    }
}

static void usage(void){
    printf("Usage %s [OPTION]... [number...]\n", invoc_name);
    printf("Convert Arabic numberals to English words.\n");
    puts("");
    puts("Options:");
    printf(" -h, --help        print this help and exit.\n");
    printf(" -v, --version     display version information and exit.\n");
}

static void version(void){
    printf("Numbers v%s\n", version_string);
}
