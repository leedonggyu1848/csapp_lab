#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "cachelab.h"

#define MBIT 64
typedef int64_t m_addr;

long long g_timer = 0;

typedef struct csim_opt {
    int s, E, b, t;
    FILE *tracefile;
    m_addr tag_mask;
    m_addr index_mask;
    m_addr offset_mask;
} csim_opt_t;

typedef struct csim_rst {
    int hits, misses, evicts;
} csim_rst_t;

typedef struct csim_command {
    int num_access;
    m_addr tag;
    m_addr index;
    m_addr offset;
    unsigned int size;
} csim_command_t;

typedef struct csim_line {
    int valid;
    m_addr tag;
    long long counter;
} csim_line_t;

void csim_getopt(int argc, char *argv[], csim_opt_t *dest);
void simulate(const csim_opt_t *opts, csim_rst_t *rst);
void update_mask_in_opt(csim_opt_t *opt);
m_addr make_mask(int size, int offset);
m_addr extract_bit(m_addr addr, m_addr mask, int offset);

int main(int argc, char *argv[]){
    csim_opt_t opt = {0, };
    csim_rst_t rst = {0, };

    csim_getopt(argc, argv, &opt);
    update_mask_in_opt(&opt);
    simulate(&opt, &rst);
    printSummary(rst.hits, rst.misses, rst.evicts);

    fclose(opt.tracefile);
    return 0;
}

void csim_getopt(int argc, char *argv[], csim_opt_t *dest){
    int opt = -1;
    while (-1 != (opt = getopt(argc, argv, "s:E:b:t:"))) {
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

    dest->t = MBIT - (dest->s + dest->b);
}

void update_mask_in_opt(csim_opt_t *opt){
    opt->tag_mask = make_mask(opt->t, opt->s + opt->b);
    opt->index_mask = make_mask(opt->s, opt->b);
    opt->offset_mask = make_mask(opt->b, 0);
}

m_addr make_mask(int size, int offset) {
    m_addr ret = 0;
    ret = ((1 << size) - 1) << offset;
    return ret;
}

m_addr extract_bit(m_addr addr, m_addr mask, int offset) {
    m_addr ret = (addr & mask) >> offset;
    return ret;
}

/* simulate code */

int next_command(csim_command_t *command, const csim_opt_t *opt);
void process_command(csim_command_t *command, csim_line_t **cache, csim_rst_t *rst, const csim_opt_t *opt);

void simulate(const csim_opt_t *opt, csim_rst_t *rst) {
    csim_command_t command = {0, };
    csim_line_t **cache = NULL;
    int S = (1 << opt->s);
    g_timer = 0;

    cache = (csim_line_t**)malloc(sizeof(csim_line_t*) * S);
    for(int i = 0; i < S; ++i){
        cache[i] = (csim_line_t*)malloc(sizeof(csim_line_t) * opt->E);
        memset(cache[i], 0, sizeof(csim_line_t) * opt->E);
    }

    while (next_command(&command, opt) >= 0) {
        while (command.num_access--) {
            process_command(&command, cache, rst, opt);
            g_timer++;
        }
    }
    
    for(int i = 0; i < S; ++i)
        free(cache[i]);
    free(cache);
}

int next_command(csim_command_t *command, const csim_opt_t *opt) {
    char instruction = 0;
    m_addr addr = 0;

    if (fscanf(opt->tracefile, " %c %lx,%d\n", &instruction, &addr, &command->size) != 3)
        return -1;
    if (instruction == 'L' || instruction == 'S')
        command->num_access = 1;
    else if (instruction == 'M')
        command->num_access = 2;
    else if(instruction == 'I')
        command->num_access = 0;
    else
        return -1;
    command->tag = extract_bit(addr, opt->tag_mask, opt->s + opt->b);
    command->index = extract_bit(addr, opt->index_mask, opt->b);
    command->offset = extract_bit(addr, opt->offset_mask, 0);
    return 0;
}

void process_command(csim_command_t *command, csim_line_t **cache, csim_rst_t *rst, const csim_opt_t *opt) {
    csim_line_t* lines = cache[command->index];
    int lru_index = -1;
    int lru_value = -1;
    int empty_index = -1;

    for(int i = 0; i < opt->E; ++i){
        if (lines[i].valid){
            if (lines[i].tag == command->tag){
                rst->hits++;
                lines[i].counter = g_timer;
                return ;
            }
            if (lru_value < g_timer - lines[i].counter){
                lru_index = i;
                lru_value = g_timer - lines[i].counter;
            }
        } else {
            empty_index = i; 
        }
    }

    if (empty_index != -1) {
        lines[empty_index].tag = command->tag;
        lines[empty_index].valid = 1;
        lines[empty_index].counter = g_timer;
    } else {
        lines[lru_index].tag = command->tag;
        lines[lru_index].counter = g_timer;
        rst->evicts++;
    }
    rst->misses++;
}