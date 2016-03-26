#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

char *invoc_name = NULL;
char *version_number = "1.0";

struct option longopts[] = {
    { "date", required_argument, NULL, 'd' },
    { "bonus", required_argument, NULL, 'b' },
    { "version", no_argument, NULL, 'v' },
    { "help", no_argument, NULL, 'h' },
    { NULL, 0, NULL, 0 },
};

char *weekdays[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday",
};

void usage(void);
void version(void);

int get_doomsday(unsigned int year);
void print_weekday(unsigned int day, unsigned int month, unsigned int year);
int leapyear(unsigned int year);

int main(int argc, char **argv){
    int c;
    int bonus = 0;
    invoc_name = argv[0];

    while ( ( c = getopt_long(argc, argv, "d:b:hv", longopts, NULL) ) != -1 ) {
        switch (c) {
            case 'd':
                break;
            case 'b':
                bonus = 1;
                break;
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

    if ( bonus == 0 && optind == argc) {
        //printf("Oh, dear.\n");
    }

    print_weekday(15,10,1985);

    return 0;
}

void usage(void){
    printf("Usage: \n");
}

void version(void){
    printf("Weekday v%s\n", version_number);
}

void print_weekday(unsigned int day, unsigned int month, unsigned int year){
    /*
     * Basic implementation of the Doomsday algorithm
     * see http://ruby.ca/doomsday.html for an explanation
     */
    int doomsday = get_doomsday(year);

    /* In leapyears Jan = 4 and Feb = 29, this is dealt with below*/
    int months_doomsday[] = {
         3, 28,  0,
         4,  9,  6,
        11,  8,  5,
        10,  7, 12,
    };

    int weekday = (day - months_doomsday[month - 1] + doomsday);

    if ( weekday < 0 )
        weekday += 7;
    
    /* 
     * In leap years, Jan and March Doomsday is 4th and 29th
     * This is a correction for the value in the above
     * months_doomsday array
     */
    if ( leapyear(year) && ( month == 3 || month == 1) )
        weekday++;

    weekday %= 7;

    printf("%s\n", weekdays[weekday]);
}

int get_doomsday(unsigned int year) {
    /* need to calculate doomsday for arbitrary year */
    int doomsday = 3 /* DD 1900 = WED */
    int two_digit_year = year % 100;

    /* Calculate Doomsday for this year */
    doomsday += two_digit_year / 12;
    doomsday += two_digit_year % 12;
    doomsday += (two_digit_year % 12) / 4;
    doomsday %= 7;

    return doomsday;
}

int leapyear(unsigned int year){
    /*
     *  Rule for leap years isn't as simple as divisible by four => leap
     * If the year is divisible by 100 then it's not a leap year unless
     * it is also divisible by 400.
     */

    if ( year % 4 != 0 )
        return 0;

    if ( year % 100 != 0 )
        return 1;

    if ( year % 400 != 0 )
        return 0;

    return 1;
}
