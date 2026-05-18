#ifndef RANDOM_H
#define RANDOM_H

void init_rand_without_seed();
void init_rand_with_seed(unsigned int seed);
int randint(int min, int max);

static inline void init_rand() {
#ifdef DEBUG
    init_rand_with_seed(42);
#else
    init_rand_without_seed();
#endif
}

#endif
