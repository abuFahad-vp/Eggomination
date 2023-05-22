
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <time.h>

void glRandom(int precision,int count, float* values) {
	srand(time(0));
    int offset = pow(10,precision);
    for(int i=0;i<count;i++) {
        float genN = rand() % (2*offset);
        if(genN > 100) {
            genN -= 100;
            genN *= -1;
        }
        values[i] = genN/offset;
    }
}

