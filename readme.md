# TinyNoise

TinyNoise is an efficient stochastic noise generator, based on pseudo random numbers, with a very small footprint.

**Are ready to hear the noise? It is so tiny...**

## Donations

I believe in **free and open source software**! Help the OSS community by donating below:

[<img src="img/paypal_button.png" width="400" height="228">](https://www.paypal.com/donate/?hosted_button_id=AMFZ83MA4Z3RA)

## Overview

Random number generation with 16 bit variable
* Using 3 seeds
* Just 2 counters
* Only one squared, one addition operation and one shift
* Only 10 bytes need for RAM

### The algorithm

1. Take the seed using counter to select between the 3. The counter is increased by 1 every loop. Here is an example of 3 seeds.

```
seeds = [65321,12043,2769]

val = seeds[seed_counter] = 65321 = 1111111100101001
```

2. Square the current "val"  value to get twice the size (32 bit now)

```
val = val * val = 11111110010100101011010010010001
```

3. Select the output based on the gama factor. Gama, same as seed counter, gets updated every loop, being that the maximum is the number of bits precision, this case 16 (0 to 15)

```
11111110010100101011010010010001
|     gama=0    |
 |     gama=1    |
  |     gama=2    |
            ...
               |     gama=15    |
```

For gama=0, the output value will be 1111111001010010 or 65106

4. Next step is to update the seeds. Using the output value, add this value to the next seed. Hence the values will be even more likely to imitate random behaviour. 

```
seeds[seed_counter] = val + seeds[seed_counter + 1]
```

For seed_counter = 0

```
seeds[0]= 65106 + 12043 = 11613 = 0010110101011101
```

* Note that the value above overflew and there is no problem with overflow

### Features

* Computationally and memory efficient algorithm 
* No math library needed
* Gaussian and non-Gaussian noise options
* White, brown or pink noise available
* Unit-tested using Cmocka

