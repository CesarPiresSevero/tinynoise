#include <stdio.h>
#include <stdint.h>
#include <tinynoise.h>

int main()
{

    FILE *fptr;

    fptr = fopen("log.txt", "w");

    for(uint16_t i=0; i<10; i++)
    {
        uint16_t val = tn_run();
        fprintf(fptr,"%x\n",val);
    }
    fclose(fptr); 
}

