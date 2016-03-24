#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define _(String) (String)

int print_number(int);
void print_help();
void print_version();

char* version = "1.0";
char* programme_name;

char* numbers[20] = {"zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
char* tens[8] = {"twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};

int main(int argc, char **argv){
    static const struct option longopts[] = 
    {
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {0,0,0,0}
    };


    programme_name = argv[0];

    while((option=getopt_long(argc,argv,"hv",\
                    longopts,NULL)) != -1){
        switch(option) {
            case 'h':
                print_help();
                exit(EXIT_SUCCESS);
            case 'v':
                print_version();
                exit(EXIT_SUCCESS);
            case '?':
                printf("Try `%s --help' for more information.\n", programme_name);
                exit(EXIT_FAILURE);
        }
    }

    if(optind < argc){
        while(optind < argc){
            print_number(atoi(argv[optind++]));
            puts("");
        }
    }else{
        //default to stdin
        while(){
            //read lines until no more
            print_number(atoi("123"));
            puts("");
        }
    }

    return 0;
}

int print_number(int number){
    if(number < 0){
        number *= -1;
        printf(_("minus "));
    }
    if(number < 20){
        printf("%s",numbers[number]);
    }
    else if(number < 100){
        printf("%s",tens[number/10 - 2]);
        number %= 10;
        if(number > 0){
            printf("-");
            print_number(number);
        }
    }else if(number < 1000){
        printf("%s",numbers[number/100]);
        printf("%s"," hundred");
        number %= 100;
        if(number > 0){
            printf(_(" and "));
            print_number(number);
        }
    }else if(number < 1000000){
        print_number(number / 1000);
        printf("%s"," thousand");
        number %= 1000;
        if(number > 0){
            if(number < 100)
                printf(" and ");
            else
                printf(", ");
            print_number(number);
        }
    }else{
        print_number(number / 1000000);
        printf("%s"," million");
        number %= 1000000;
        if(number > 0){
            if(number < 100)
                printf(" and ");
            else
                printf(", ");
            print_number(number);
        }
    }
    return 0;
}

void print_help(){
    printf("Number %s\n",version);
    puts("");
    printf("Usage %s [OPTION]... [number...]\n", programme_name);
    printf("Convert Arabic numberals to English words.\n");
    puts("");
    puts("Options:");
    printf(" -h, --help        print this help and exit.\n");
    printf(" -v, --version     display version information and exit.\n");
    puts("");
    printf(" -a, --american    print incorrect English.\n");

}

void print_version(){
    printf("Version\n");
}
