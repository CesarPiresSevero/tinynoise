/**
* @file tinynoise.c
* @brief TinyNoise library source file
* @author Cesar Pires Severo
* @date 2/17/2025
*/

/* Includes */
#include "tinynoise.h"

/* Static Variables */
static distrib_t distrib = DEF_DISTRIB;
static color_t color = DEF_COLOR;
static uint16_t seed[3] = {DEF_SEED1, DEF_SEED2 ,DEF_SEED3};
static uint8_t gama = 0;

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
}

uint16_t tn_run(void)
{
    return seed[0];
}
