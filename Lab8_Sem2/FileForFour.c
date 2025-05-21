#include <stdio.h>
#include <unistd.h> // sleep
#include <pthread.h>

#define NOF_THREADS 1
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int i = 1;

void *routine(void *a) {
    pthread_t tid = pthread_self();
    
    while(1){
    pthread_mutex_lock(&mutex);
    if (i == 2){
    printf("%s %ld\n", (char*)a, tid);
    i = 1;
    }
    pthread_mutex_unlock(&mutex);
    }
    


        

    return NULL;
}

int main(void) {



    pthread_t tids[NOF_THREADS];

    int sort[12] = {9, 7 ,2, 6, 10, 35, 48, 91, 32, 67, 23, 96};
        pthread_create(&tids[i], NULL, routine, "PAPPAPAPA");

    while(1){
        pthread_mutex_lock(&mutex);
        if (i == 1){
        i = 2;
        printf("hello from main thread %ld\n", pthread_self());
        }

        pthread_mutex_unlock(&mutex);
        

        
    }



        // sleep(5);

    // for (int i = 0; i < NOF_THREADS; i++) {
    //     pthread_cancel(tids[i]);
    // }

    for (int i = 0; i < NOF_THREADS; i++) {
        pthread_join(tids[i], NULL);
    }
    return 0;

}