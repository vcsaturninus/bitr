#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "bitr.h"


int num_run  = 0;
int num_passed = 0;
bool passed = 0;

/* test runner */
#define run(f, ...) \
    ++num_run;  \
    passed = f(__VA_ARGS__); \
    if (passed) ++num_passed; \
    printf("[ ] test %i %s\n", num_run, (passed) ? "Passed" : "FAILED !!");

enum{FAILED, PASSED};


static bool test_test_bit(uint32_t n, int state){
    assert(state == 1 || state == 0);

    struct bitr *new = Bitr_new(n);
    assert(new);

    bool res = PASSED;
    
    /* set bit manually */
    int idx = n-1;

    // set bit n-1
    if (state == 1){
        new->bits[idx/8] |= (0x80u >> (idx % 8) );
    }

    // printf("test returned %i\n", Bitr_test(new, n));
    if (Bitr_test(new, n) != state) res = FAILED;
    // printf("bits[%i]=0x%02x\n", n/8, new->bits[idx/8]);

    free(new);
    return res;
}

static bool test_set_bit(uint32_t n){
    struct bitr *new = Bitr_new(n);
    assert(new);

    bool res = PASSED;

    if (Bitr_set(new, n) == -1) res = FAILED;
    if (Bitr_test(new, n) != 1) res = FAILED;

    free(new);
    return res;
}

static bool test_clear_bit(uint32_t n){
    struct bitr *new = Bitr_new(n);
    assert(new);

    bool res = PASSED;

    if (Bitr_clear(new, n) == -1) res = FAILED;
    if (Bitr_test(new, n) != 0) res = FAILED;

    free(new);
    return res;
}

static bool test_toggle_bit(uint32_t n, int state){
    struct bitr *new = Bitr_new(n);
    assert(new);

    assert(state == 1 || state == 0);

    bool res = PASSED;
    
    if (state == 1){
        if (Bitr_set(new, n) == -1) res = FAILED;
    }
    
    if (Bitr_toggle(new, n) == -1) res = FAILED;

    if (Bitr_test(new, n) != !state) res = FAILED;

    free(new);
    return res;
}

int main(int argc, char **argv){

    printf("\n%s\n", "===== Validating bit testing ========= ");
    run(test_test_bit, 7, 1);
    run(test_test_bit, 7, 0);
    run(test_test_bit, 1, 0);
    run(test_test_bit, 111, 1);
    run(test_test_bit, 2000, 1);
    run(test_test_bit, 13, 0);
    run(test_test_bit, 77, 1);

    printf("\n%s\n", "===== Testing bit setting ========= ");
    run(test_set_bit, 1);
    run(test_set_bit, 1);
    run(test_set_bit, 7314);
    run(test_set_bit, 7315);
    run(test_set_bit, 313);
    run(test_set_bit, 71);
    run(test_set_bit, 8);

    printf("\n%s\n", "===== Testing bit clearing ========= ");
    run(test_clear_bit, 1);
    run(test_clear_bit, 1);
    run(test_clear_bit, 7314);
    run(test_clear_bit, 7315);
    run(test_clear_bit, 313);
    run(test_clear_bit, 71);
    run(test_clear_bit, 8);

    printf("\n%s\n", "===== Testing bit toggling ========= ");
    run(test_toggle_bit, 1, 0);
    run(test_toggle_bit, 1, 1);
    run(test_toggle_bit, 7314, 1);
    run(test_toggle_bit, 7315, 0);
    run(test_toggle_bit, 313, 1);
    run(test_toggle_bit, 71, 1);
    run(test_toggle_bit, 8, 0);

printf("\n Passed: %i / %i\n", num_passed, num_run);
if (num_passed != num_run) exit(1);

}



