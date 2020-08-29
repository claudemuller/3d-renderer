#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "benchmark.h"

float startTime1 = 0;
float startTime2 = 0;
float endTime = 0;
float bench1 = 0;
float bench2 = 0;
uint32_t bench_c = 0;

void start_bench(int bench) {
	if (bench == 1) {
		startTime1 = (float) clock() / CLOCKS_PER_SEC;
	} else {
		startTime2 = (float) clock() / CLOCKS_PER_SEC;
	}
}

void stop_bench(int bench) {
	endTime = (float) clock() / CLOCKS_PER_SEC;
	if (bench == 1) {
		bench1 += endTime - startTime1;
	} else {
		bench2 += endTime - startTime2;
	}
}

void print_bench(void) {
	printf("Bench val1: %f\n", bench1 / bench_c);
	printf("Bench val2: %f\n", bench2 / bench_c);
}
