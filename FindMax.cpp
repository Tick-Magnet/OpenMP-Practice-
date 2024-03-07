#include <iostream>
#include <omp.h>
#include <cstdlib>
//Compilation Syntax: g++ LabOne.cpp -o lab -fopenmp

using namespace std;

int main(int argc, char* argv[]) {
  
    char *p;
    int MAC_VALUE, SIZE, currentMax;
    bool parallel;

    parallel = false;
    SIZE = 32;
    MAC_VALUE = 100;
    currentMax = -1;
    int list[SIZE] = {};
    srand(time(NULL));

    for(int i=0;i<SIZE;i++) {
        int random = rand() % MAC_VALUE;  
        list[i] = random;
        printf("i: %d - %d\n", i, random);
    }


    for(int j = 0; j < SIZE; j++)
        {
            if (currentMax < list[j])
            {
                currentMax = list[j];
            }
        }

        printf("Linear Max: %d \n", currentMax);
        currentMax = -1;
        
    //Linear Search
    if(parallel){
        
        

    } else {
        
        int threads = 4;

        omp_set_num_threads(threads);
        #pragma omp parallel shared(currentMax)
        {
            int tid = omp_get_thread_num(); 

            int buffer = (SIZE / threads);
            int localMax = -1;  

            for(int j = (tid * buffer); j < ((tid + 1) * buffer); j++)
            {
                if (localMax < list[j])
                {
                    localMax = list[j];
                }
            }

            #pragma omp critical 
            {
                if(currentMax < localMax)
                {
                    currentMax = localMax;
                } 
            }
        }
    }

    printf("Parallel Max: %d \n", currentMax);

}



    /*
    omp_set_num_threads(threads);  

    #pragma omp parallel private(tid) shared(i)
    {
        int tid = omp_get_thread_num();

        if(tid % 2 == 0) {
            #pragma omp atomic 
                i--;
        } else {
            #pragma omp atomic 
                i++;
        }

        

        printf("i: %d\n", i);
        #pragma omp flush 
    }
    */
