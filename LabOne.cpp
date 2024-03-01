#include <iostream>
#include <omp.h>


using namespace std;

int main(int argc, char* argv[]) {
  
    char *p;
    int tid, threads;
    
    //Check for Input Argument 
    if (argc != 2) {
        cout << "Incorrect Input Arguments" << endl;
        return -1;
    }

    threads = strtol(argv[1], &p, 10);

    omp_set_num_threads(threads);  

    #pragma omp parallel private(tid)
    {
        int tid = omp_get_thread_num();
        #pragma omp critical 
        {
            #pragma omp master
            {
                int total_threads = omp_get_num_threads();

                cout << "Total Threads: " << total_threads << endl;
                cout << "Master ";
            }
            cout << "Thread ID: " << tid << endl;
        }
    }
    
    return 0;
} 