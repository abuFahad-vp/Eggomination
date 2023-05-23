
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <math.h>

// generate random b/w -1 to 1 with precision
float glRandomNormalized(int precision) {
    int offset = pow(10,precision);
    float genN = rand() % (2*offset);
    if(genN > offset) {
        genN -= offset;
        genN *= -1;
    }
    return (genN/offset);
}

// generate number b/w range
int glRandomRange(int lower,int upper) {
    int genN = rand() % upper;
    if(genN < lower) {
        genN += lower;
    }
    return genN;
}
