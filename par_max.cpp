#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <unistd.h> 
#include <omp.h>
#include <vector>


//Compilation Syntax: g++ par_max.cpp -o par_max -fopenmp
using namespace std;

int findMax(int array[], int size) {
    int maxVal = array[0];
    for (int i = 1; i < size; ++i) {
        if (array[i] > maxVal) {
            maxVal = array[i];
        }
    }
    return maxVal;
}

int main(int argc, char* argv[]) {
    int SIZE = 32;
    int MAX_VALUE = 1000;
    int VALUE_LENGTH = 100;
    int MAX_TRIALS = 0;
    int THREAD_COUNT = 1;

    int opt;
    while ((opt = getopt(argc, argv, "s:v:l:r:t:")) != -1) {
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
            case 't':
                THREAD_COUNT = atoi(optarg);
                break;
            default:
                cerr << "Usage: " << argv[0] << " -s [size] -v [max_value] -l [value_length] -t [max_trials] -r [thread_count]" << endl;
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

    // Set number of threads
    omp_set_num_threads(THREAD_COUNT);
    vector<long> elapsedTimes;

    #pragma omp parallel shared(TOTAL_TIME, elapsedTimes) 

    #pragma omp for schedule(static)
    for (int t = 0; t < MAX_TRIALS; t++) {
        gettimeofday(&t0, 0);
        int max = findMax(array, SIZE);
        gettimeofday(&t1, 0);
        long elapsed = (t1.tv_sec - t0.tv_sec) * 1000000 + t1.tv_usec - t0.tv_usec;

        printf("Thread_ID: %d - Run Time: %ld\n", omp_get_thread_num(), elapsed);
        #pragma omp flush 
        
        #pragma omp critical 
        {
            TOTAL_TIME += elapsed;
            elapsedTimes.push_back(elapsed);
        }

    }

    long totalElapsedTime = 0;
    for (long time : elapsedTimes) {
        totalElapsedTime += time;
    }
    double averageTime = totalElapsedTime / static_cast<double>(MAX_TRIALS);

    cout << "Average Time: " << averageTime << " microseconds" << endl;

    cout << "Total Time: " << TOTAL_TIME / 60000000.0 << " minutes" << endl;

    return 0;
}