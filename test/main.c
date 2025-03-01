#include <stdio.h>
#include <stdint.h>
#include <tinynoise.h>

int main()
{

    FILE *fptr;

    fptr = fopen("log.txt", "w");

    for(uint32_t i=0; i<100000; i++)
    {
        int16_t val = tn_run();
        fprintf(fptr,"%hx\n", val);
    }
    fclose(fptr);

    //TEST
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
    //TEST
}

