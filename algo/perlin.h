#ifndef PERLIN_H_INCLUDED
#define PERLIN_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <time.h>

double perlin(float x, float y);
double octavePerlin(float x, float y);

double* tperlin(int w, int oct);

double* testHMap(int w, int oct);

#endif // PERLIN_H_INCLUDED
