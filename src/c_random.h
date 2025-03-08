#ifndef C_RANDOM_H
#define C_RANDOM_H

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>

/* DEFINES */
#define srand(x) {srand(x); isUsedSrand = true; }

/* STATIC VARIABLES */
static bool isUsedSrand = false;

/* FUNCTIONS */
int64_t	generateRandom(int64_t min, int64_t max);

#endif
