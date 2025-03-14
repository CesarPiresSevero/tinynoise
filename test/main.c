#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <tinynoise.h>

// #define LOOP 1000000000
#define LOOP 100000

int main()
{
    // TEST SPEED
//     int value=0;
//     int16_t val=0;
//     clock_t t;
//     t = clock();
//     for(uint32_t i=0; i<LOOP; i++)
//     {
//         // C lib
//         value = rand();
// 
//         // Tiny noise
//         val = tn_run();
//     }
//     t = clock() - t;
//     double time_taken = ((double)t)/CLOCKS_PER_SEC;
//     value++;
//     val++;
//     printf("Time: %f\n",time_taken);
    // TEST SPEED


    // FILE SAVING
    FILE *fptr;

    fptr = fopen("log.txt", "w");

    for(uint32_t i=0; i<LOOP; i++)
    {
        int16_t val = tn_run();
        fprintf(fptr,"%hx\n", val);
    }
    fclose(fptr);
    // FILE SAVING

    // TEST FIXED POINT 
//     int16_t x = 0x8000; //-1
//     int16_t y = 0x4000; //0.5
//     int16_t z = x+y;
//     printf("x=%hx, y=%hx, z=%hx\n",x,y,z);
//     x = x>>1; //-0.5
//     y = y>>1; //0.25
//     z = x-y;
//     printf("x=%hx, y=%hx, z=%hx\n",x,y,z);
//     int32_t accum = (int32_t) x*y; //-0.5*0.25 = -0.125
//     z = (int16_t)(accum>>15);
//     printf("x=%hx, y=%hx, z=%hx\n",x,y,z);
    // TEST FIXED POINT 
}

