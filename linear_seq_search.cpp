#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <unistd.h> 

//Compilation Syntax: g++ linear_seq_search.cpp -o linear_seq_search
using namespace std;

void linearSearch(int *array, int size, int *values, int value_length) {
    for (int v = 0; v < value_length; v++) {
        int vi = values[v];
        for (int s = 0; s < size; s++) {
            int si = array[s];
            if (si == vi) {
                // Value Found;
                break;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int SIZE = 32;
    int MAX_VALUE = 1000;
    int VALUE_LENGTH = 100;
    int MAX_TRIALS = 0;

    int opt;
    while ((opt = getopt(argc, argv, "s:v:l:r:")) != -1) {
        switch (opt) {
            case 's':
                SIZE = atoi(optarg);
                break;
            case 'v':
                MAX_VALUE = atoi(optarg);
                break;
            case 'l':
                VALUE_LENGTH = atoi(optarg);
                break;
            case 'r':
                MAX_TRIALS = atoi(optarg);
                break;
            default:
                cerr << "Usage: " << argv[0] << " -s [size] -v [max_value] -l [value_length] -t [max_trials]" << endl;
                return 1;
        }
    }

    int array[SIZE];
    int values[VALUE_LENGTH];

    // Initialize array and values
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % MAX_VALUE;
    }
    for (int r = 0; r < VALUE_LENGTH; r++) {
        values[r] = rand() % MAX_VALUE;
    }

    long TOTAL_TIME = 0;
    struct timeval t0, t1;
    for (int t = 0; t < MAX_TRIALS; t++) {
        gettimeofday(&t0, 0);
        linearSearch(array, SIZE, values, VALUE_LENGTH);
        gettimeofday(&t1, 0);
        long elapsed = (t1.tv_sec - t0.tv_sec) * 1000000 + t1.tv_usec - t0.tv_usec;
        cout << "Run Time: " << elapsed << " microseconds" << endl;
        TOTAL_TIME += elapsed;
    }

    cout << "Total Time: " << TOTAL_TIME / 60000000.0 << " minutes" << endl;

    return 0;
}