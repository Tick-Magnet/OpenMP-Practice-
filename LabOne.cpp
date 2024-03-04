#include <iostream>
#include <omp.h>

//Compilation Syntax: g++ LabOne.cpp -o lab -fopenmp

using namespace std;

int main(int argc, char* argv[]) {
  
    char *p;
    int tid, threads, i, r;
    
    i = 0;

    //Check for Input Argument 
    if (argc != 2) {
        cout << "Incorrect Input Arguments" << endl;
        return -1;
    }

    threads = strtol(argv[1], &p, 10);

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
        //printf("Thread ID: %d, %d\n", tid, i);
        #pragma omp flush 
    }
    printf("Final i: %d\n", i);
    return 0;
} 



/* 

        i = 0;

        #pragma omp critical 
        {
            #pragma omp master
            {
                int total_threads = omp_get_num_threads();

                cout << "Total Threads: " << total_threads << endl;
                cout << "Master ";
            }

            #pragma omp atomic 
                i++;
            
            
            cout << "Thread ID: " << tid << " int: " << i << endl;
        }
        
*/
