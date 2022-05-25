#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "cachelab.h"

typedef struct csim_opt {
    int s, E, b;
    FILE *tracefile;
} csim_opt_t;

typedef struct csim_rst {
    int hits, misses, evicts;
} csim_rst_t;

void csim_getopt(int argc, char *argv[], csim_opt_t *dest);
void simulate(const csim_opt_t *opts, csim_rst_t *rst);

int main(int argc, char *argv[]){
    csim_opt_t opt = {0, };
    csim_rst_t rst = {0, };

    csim_getopt(argc, argv, &opt);
    simulate(&opt, &rst);
    printSummary(rst.hits, rst.misses, rst.evicts);
    return 0;
}

void csim_getopt(int argc, char *argv[], csim_opt_t *dest){
    int opt = -1;
    while (-1 != (opt = getopt(argc, argv, "s:E:b:t"))) {
        switch (opt) {
            case 's':
                dest->s = atoi(optarg);
                break;
            case 'E':
                dest->E = atoi(optarg);
                break;
            case 'b':
                dest->b = atoi(optarg);
                break;
            case 't':
                dest->tracefile = fopen(optarg, "r");
                break;
            default:
                break;
        }
    }
}

void simulate(const csim_opt_t *opts, csim_rst_t *rst) {
    rst->hits = 1;
    rst->misses = 2;
    rst->evicts = 3;
    /* TODO */
}
