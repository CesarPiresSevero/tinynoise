# TinyNoise

TinyNoise is an efficient fixed-point stochastic noise generator written in C, based on pseudo random numbers, with a very small footprint.

**Are ready to hear the noise? It is so tiny...**

## Donations

I believe in **free and open source software**! Help the OSS community by donating below:

[<img src="img/paypal_button.png" width="400" height="228">](https://www.paypal.com/donate/?hosted_button_id=AMFZ83MA4Z3RA)

## Overview

### Features

* Computationally and memory efficient algorithm 
* No math library used
* White, brown and pink noise options
* Unit-tested using Cmocka

### Pseudo Random Number Generator Algorithm

The algorithm described below was designed by me. It was an effort to create a fix point, low footprint stochastic noise generator for integration on a low power DSP chip. This signal was used, after filtering, for tinnitus treatment.

#### Implementation

Random number generation with 16 bit variable
* Using 3 seeds
* Just 2 counters
* Only one multiplication, two additions and one shift operation
* Only 10 bytes need for RAM

1. Take a seed using the counter to select it. The counter is increased by 1 every loop. Here is an example of 3 seeds:

```
seeds = [65321,12043,2769]

val = seeds[seed_counter] = 65321 = 1111111100101001
```

2. Square the current value to get twice the size (in this example, from 16 bit to 32 bit).

```
val = val * val = 11111110010100101011010010010001
```

3. Crop the current sample based on the gama factor. Gama, same as seed counter, gets updated by 1 every loop, being that the maximum is the number of bits, this case 16 bits (0 to 15).

```
11111110010100101011010010010001
|     gama=0    |
 |     gama=1    |
  |     gama=2    |
            ...
               |     gama=15    |
```

For *gama = 0*, the output value will be *1111111001010010* or *65106*.

4. Next step is to update the seeds. Update the seed by adding the current value to the next seed. Hence, the output will be even more likely to imitate random behaviour. 

```
seeds[seed_counter] = val + seeds[seed_counter + 1]
```

For *seed_counter = 0*:

```
seeds[0]= 65106 + 12043 = 11613 = 0010110101011101
```

Note that the value above overflew and there is no problem with it for this algorithm.

5. The final step is to add the previous sample to the output.

```
output = val + prev_val
prev_val = val
```

Update the previous sample value too. For the first loop, *prev_val* is initialized to zero.

#### Results

The algorithm above has a uniform distribution with flat spectral composition. The plot below shows the output of it for 100k samples:

![TinyNoiseUniform](img/TinyNoiseUniform.png)

For comparison, here is the output of Python's Numpy random uniform implementation:

![NumpyRandomUniform](img/NumpyRandomUniform.png)

## Getting started

This section will go into detail about the pseudo random number implementation of the algorithm above to generate noise. The generated noise is intended to be used in audio applications.

### Usage

TinyNoise library can be included in your project by:

* Including the source files in your build
* Linking the library file on your Makefile

It is advised to always link the library rather than including source code. It makes the SW architecture cleaner and modular. Also, it can avoid issues with licenses and intellectual properly. 
To link the TinyNoise library on your project just follow the example of the Makefile which is contained in this repo:

```
# Include flags
IFLAGS = -I$(SRCDIR)

# Library name
LIBNAME = tinynoise

# Library linking flags
LDFLAGS= -L$(BINDIR) -l$(LIBNAME)

$(BINDIR)/$(MYEXE): $(LIBDIR)/$(MYSRC).o
        @$(CC) $(LIBDIR)/$(MYSRC).o $(LDFLAGS) -o $(BINDIR)/$(MYEXE)  

$(LIBDIR)/$(MYSRC).o: $(MYDIR)/$(MYSRC).c 
        @$(CC) -c $^ -o $@ $(CFLAGS) $(IFLAGS) 
```
 
The example above shows the linking of the library follow this repo folder structure. Feel free to change it to your needs.

### APIs Refence

TinyNoise library follows the KISS approach (Keep It Stupid Simple). Therefore, there are just 4 APIs available. They are focused on the user and the different implementations that might be done using the library.

#### void tn_set_color(color_t new_color);

Selecting the noise color (white, brown or pink) will change the frequency components of the signal. The colors are defined as:

```
typedef enum
{
    WHITE,
    BROWN,
    PINK
}color_t;
```

The default color is **white**. To change it just follow the example below:

```
tn_set_color(PINK);
``` 

Here is the expected PSD of the signal based on the different colors:

![TinyNoiseColors](img/TinyNoiseColors.png)


#### int16_t tn_run(void);

TinyNoise has as output a **signed 16 bit in fixed-point Q15 format** value. To get a noise sample call the function:

```
int16_t new_sample = tn_run();
```  
