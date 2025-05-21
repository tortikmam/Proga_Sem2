#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

int N;
int num_threads;
int **A, **B, **C;

typedef struct {
    int start_row;
    int end_row;
} thread_data;

// Функция для получения текущего времени в миллисекундах
long long get_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000LL + tv.tv_usec / 1000;
}

int** create_matrix(int size) {
    int **matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }
    return matrix;
}

void fill_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = 1;
        }
    }
}

void free_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void* multiply(void* arg) {
    thread_data* data = (thread_data*)arg;
    
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    pthread_exit(NULL);
}

void run_test(int matrix_size, int threads_count) {
    N = matrix_size;
    num_threads = threads_count;
    
    // Создаем матрицы
    A = create_matrix(N);
    B = create_matrix(N);
    C = create_matrix(N);
    
    // Заполняем матрицы
    fill_matrix(A, N);
    fill_matrix(B, N);
    
    pthread_t threads[num_threads];
    thread_data thread_args[num_threads];
    
    int rows_per_thread = N / num_threads;
    int extra_rows = N % num_threads;
    int current_row = 0;
    
    long long start_time = get_time_ms();
    
    // Создание потоков
    for (int i = 0; i < num_threads; i++) {
        thread_args[i].start_row = current_row;
        thread_args[i].end_row = current_row + rows_per_thread + (i < extra_rows ? 1 : 0);
        current_row = thread_args[i].end_row;
        
        pthread_create(&threads[i], NULL, multiply, (void*)&thread_args[i]);
    }
    
    // Ожидание завершения потоков
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    long long end_time = get_time_ms();
    long long execution_time = end_time - start_time;
    
    // Вывод результатов в CSV формате
    printf("%d,%d,%lld\n", N, num_threads, execution_time);
    
    // Освобождение памяти
    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);
}

int main() {
    // Размеры матриц для тестирования
    int matrix_sizes[] = {100, 300, 500, 700, 900};
    int num_sizes = sizeof(matrix_sizes) / sizeof(matrix_sizes[0]);
    
    // Количество потоков для тестирования
    int threads_counts[] = {1, 2, 4, 8, 16, 32, 64, 128};
    int num_threads_counts = sizeof(threads_counts) / sizeof(threads_counts[0]);
    
    // Заголовок CSV
    printf("matrix_size,threads_count,execution_time_ms\n");
    
    // Запуск всех тестов
    for (int i = 0; i < num_sizes; i++) {
        for (int j = 0; j < num_threads_counts; j++) {
            run_test(matrix_sizes[i], threads_counts[j]);
        }
    }
    
    return 0;
}