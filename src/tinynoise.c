/**
* @file tinynoise.c
* @brief TinyNoise library source file
* @author Cesar Pires Severo
* @date 2/17/2025
*/

/* Includes */
#include "tinynoise.h"
//TEST
#include <stdio.h>
//TEST


/* Static Variables */
static distrib_t distrib = DEF_DISTRIB;
static color_t color = DEF_COLOR;
static uint16_t seed[3] = {DEF_SEED1, DEF_SEED2 ,DEF_SEED3};
static uint8_t gama = 0u;
static uint8_t seed_counter = 0u;

/* Static functions */
static uint16_t tn_get_rand()
{
    /* Generating new sample */
    uint32_t accum = (uint32_t)(seed[seed_counter] * seed[seed_counter]);
    uint16_t output = (uint16_t)(accum >> (16 - gama));
    /* Updating gama */
    if(gama == 15u)
    {
        gama = 0u;
    }
    else
    {
        gama++;
    }
    /* Updating seeds */
    if(seed_counter == 2u)
    {
        seed[seed_counter] = output + seed[0u];
        seed_counter = 0u;
    }
    else
    {
        seed[seed_counter] = output + seed[seed_counter + 1u];
        seed_counter++;
    }
    return output;
}

/* Functions */
void tn_set_distrib(distrib_t new_distrib)
{
    distrib = new_distrib;
}

void tn_set_color(color_t new_color)
{
    color = new_color;
}

void tn_set_seed(uint16_t seed1, uint16_t seed2, uint16_t seed3)
{
    seed[0] = seed1;
    seed[1] = seed2;
    seed[2] = seed3;
}

void tn_reset(void)
{
    distrib = DEF_DISTRIB;
    color = DEF_COLOR;
    seed[0] = DEF_SEED1;
    seed[1] = DEF_SEED2;
    seed[2] = DEF_SEED3;
    gama = 0;
    seed_counter = 0;
}

uint16_t tn_run(void)
{
    uint16_t rand_num = tn_get_rand();
    static uint16_t prev_num = 0;
    if(distrib == NORMAL)
    {
        rand_num = prev_num + rand_num;
        prev_num = rand_num;
    }
    

    return rand_num;
}

