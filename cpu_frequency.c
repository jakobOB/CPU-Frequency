#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#ifndef NUM_MEASUREMENTS
#define NUM_MEASUREMENTS 3
#endif

#ifndef MEASUREMENT_US
#define MEASUREMENT_US 100000
#endif

int main()
{
    printf("Starting CPU frequency measurement\n");

    uint64_t average_cycles = 0;
    double freq_ghz = 0;
    uint64_t before, after;

    for(int i = 0; i < NUM_MEASUREMENTS; ++i)
    {
      // Read CPU cycle counter using the rdtscp instruction via inline assembly
      uint32_t a, d;

      asm volatile ("rdtscp" : "=a"(a), "=d"(d)::"%rcx");
      before = ((uint64_t)d << 32) | a;

      // Sleep for a few microseconds
      usleep(MEASUREMENT_US);

      // Read CPU cycle counter again, calculate the cycle
      // difference and sum it up in average_cycles
      asm volatile ("rdtscp" : "=a"(a), "=d"(d)::"%rcx");
      after = ((uint64_t)d << 32) | a;

      average_cycles += (after - before);

    }

    average_cycles /= NUM_MEASUREMENTS;
    
    // Calculate CPU cycle frequency in GHz based on
    // the measured number of cycles per time period
    freq_ghz = average_cycles * 0.001 / MEASUREMENT_US;

    printf("CPU frequency: %f GHz\n", freq_ghz);
}
