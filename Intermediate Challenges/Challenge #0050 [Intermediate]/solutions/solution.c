#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

static char *invoc_name = NULL;
static char *version_string = "1.0";

static struct option longopts[] = {
    { "path", required_argument, NULL, 'p' },
    { "depth", required_argument, NULL, 'd' },
    { "help", no_argument, NULL, 'h' },
    { "version", no_argument, NULL, 'v' },
    { NULL, 0, NULL, 0 },
};

static char *path = NULL;
static int depth = 0;

static void usage(void);
static void version(void);

int main(int argc, char **argv){
    int c;
    invoc_name = argv[0];
    while ( ( c = getopt_long(argc, argv, "p:d:hv", longopts, NULL) ) != -1 ) {
        switch (c) {
            case 'p':
                path = optarg;
                break;
            case 'd':
                c = sscanf(optarg, "%d", &depth);
                if ( c != 1 ) {
                    fprintf(stderr, "Invalid depth: %s\n", optarg);
                    fprintf(stderr, "Try %s --help for more information.\n", invoc_name);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h':
                usage();
                exit(EXIT_SUCCESS);
            case 'v':
                version();
                exit(EXIT_SUCCESS);
            case '?':
                fprintf(stderr, "Try %s --help for more information.\n", invoc_name);
                exit(EXIT_FAILURE);
            default:
                break;
        }
    }



    return 0;
}

static void usage(void){
    printf("Usage\n");
}

static void version(void){
    printf("Directory Tree v%s\n", version_string);
}
