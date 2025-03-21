/**
* @file tinynoise.h
* @brief TinyNoise library header file
* @author Cesar Pires Severo
* @date 2/17/2025
*/

#ifndef TINYNOISE_H
#define TINYNOISE_H

/* C++ wrap */
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/** @brief Default noise color*/
#define DEF_COLOR WHITE
/** @brief Default first seed*/
#define DEF_SEED1 65321u
/** @brief Default second seed*/
#define DEF_SEED2 12043u
/** @brief Default third seed*/
#define DEF_SEED3 2769u

/**
 * @brief Noise color type
 */
typedef enum
{
    WHITE,
    BROWN,
    PINK
}color_t;

/**
* @brief Noise color set function
* @param new_color Noise color to be used (WHITE, BROWN or PINK)
*/
void tn_set_color(color_t new_color);

/**
* @brief Starter seeds set function
* @param seed1 First start seed (unsigned integer 16bits)
* @param seed2 Second start seed (unsigned integer 16bits)
* @param seed3 Third start seed (unsigned integer 16bits)
*/
void tn_set_seed(uint16_t seed1, uint16_t seed2, uint16_t seed3);

/**
* @brief Resets all library parameters to default
*/
void tn_reset(void);

/**
* @brief Noise generation function  
* @return uint16_t New noise data point
*/
int16_t tn_run(void);

/* C++ wrap */
#ifdef __cplusplus
}
#endif

/* TINYNOISE_H */
#endif

