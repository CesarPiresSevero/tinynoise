#include <stdio.h>
#include <stdint.h>
#include <tinynoise.h>

int main()
{
    printf("Hello World!\n");
    uint16_t val = tn_run();
    printf("%d",val);
}

