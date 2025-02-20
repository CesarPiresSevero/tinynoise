#include <stdio.h>
#include <stdint.h>
#include <tinynoise.h>

int main()
{
    printf("Hello World!\n");
    for(uint16_t i=0; i<10; i++)
    {
        uint16_t val = tn_run();
        printf("%d\n",val);
    }
}

