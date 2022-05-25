#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdint.h>
#include "cachelab.h"

typedef struct csim_opt {
    int s, E, b;
    FILE *tracefile;
} csim_opt_t;

typedef struct csim_rst {
    int hits, misses, evicts;
} csim_rst_t;

typedef enum csim_operation { I=0, L, S, M } csim_operation_e;

typedef struct csim_command {
    csim_operation_e operation;
    uint64_t addr;
    unsigned int size;
} csim_command_t;

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

/* simulate code */

int next_command(csim_command_t *command, FILE *fd);
void process_command(csim_command_t *command, int **cache, csim_rst_t *rst);

void simulate(const csim_opt_t *opts, csim_rst_t *rst) {
    csim_command_t command = {0, };
    int **cache = NULL;

    /* TODO: malloc to cache*/

    while (-1 != next_command(&command, opts->tracefile))
        process_command(&opts, cache, &rst);
}

int next_command(csim_command_t *command, FILE *fd) {
    /* TODO */
    return -1;
}

void process_command(csim_command_t *command, int **cache, csim_rst_t *rst) {
    /* TODO */
   return ; 
}