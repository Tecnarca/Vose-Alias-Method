# Non-Uniform-Distribution-Extractor
This program implements an efficent algorithm to extract numbers w.r.t. a 
non-uniform probability distribution, when normally (at least in C) the
random number generator extracts from a uniform distribution.

The objective of this particular implementation is to reduce as much as possible the execution time needed to extract some numbers, along with the time complexity. The explanation on how this was achived can be found below.

## How this works
The algorithm used to do this is named `Vose's Alias Method`, and it is
explained how it works very well [here](http://www.keithschwarz.com/darts-dice-coins).

### Computational Complexity
We divide the complexity of this type of algorithms in three categories: 
* The space complexity (i.e. how much RAM it requires)
* The initialization time complexity (i.e. how much time it takes to generate
the vectors we need to make any extractions)
* The generation time complexity (i.e. how much time it takes to extract a number w.r.t. the distribution), given we generated the needed arrays

This table shows some algorithms that share the same Objective along with their complexity.

![Plotted data](complexity_table.png?raw=true "Computational Complexity of some algorithms with the same objective")

As shown above, a great advantage this algorithm has over its competitors is that 
the complexity to extract a number (once we have computed the arrays we
need to make this extraction) is O(1), meaning that no cycles are needed.

## Usage
You can download the 'extractor.c' file and compiling it with
```
gcc extractor.c -o extractor.exe
```
To execute it, you need to create a `TXT` file with this structure:
```
DISTRIBUTION_LENGTH NUMBER_OF_EXTRACTIONS
PROB_1 PROB_2 PROB_3 ... PROB_N
```
And must be true that `PROB_1+...+PROB_N=1`
For example, this file is correct:
```
5 10
0.2 0.32 0.14 0.06 0.28
```
To execute the program, use the command:
```
./extractor.exe [PATH_TO_TXT]
```
I have provided the `input.txt` file that can be used to test the program.

### Using it as a function
You can implement this on your program freely,
you just need to call the `vose()` function.
The things you need are:
* An integer pointer `extracted`, where the results will be stored as an array of length `n`
* An integer `n`, that represents the numbers of extractions to make
* An integer `length` that represents the length of the probability array
* A double array `probabibilities`, that contains the probabilities of their indexes being extracted, they must sum up to 1

You then call the function as follows:
`extracted = vose(probabilities, length, n);`

If you use every time the same distribution, you may want to implement the
generation and the extraction in two different steps, 
this way you can execute code between different extractions, avoiding the O(N) complexity
of regenerating the needed arrays.

## More info and applications
The explanaton of the algorithm can be found in the page linked above.

This algorithm can be used in pretty much every genetic algorithm as an
improvement to extract the random numbers to choose who must reproduce
in the most efficent way possible, as discussed [here](https://github.com/gr3yc4t/Travelling-Salesman-Genetic).

Also, everything that has to do with simulations may use this to implement a generation given a desired probability distribution.
