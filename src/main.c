#include <stdio.h>
#include "../headers/RTree.h"
#include <math.h>
#include <string.h>
#include "../headers/testUtils.h"

int main(int argc, char **argv) {
    
    if (argc > 1) {
        char testOption[] = "-test";
        for (int i = 0; i < argc; ++i) {
    
            if (strcmp(argv[i], testOption)) {
                testSuite();
                // fflush(stdout);
                // fflush(stderr);
                printf("All tests completed");
                // return 0;
            }
        }
    } 

    

    printf("Hello world my name is james\n");
}