#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define n 10
#define N 10000

int counter = 0;

struct Student{
    char nameStudent[64];
    int math;
    int phys;
    int inf;
    int total;
};

struct Student addStudent(char name[], int mat, int ph, int in){

    struct Student newStudent;

    for (int i = 0; i < n+1; i++){
        newStudent.nameStudent[i] = name[i];
    }
    newStudent.math = mat;
    newStudent.phys = ph;
    newStudent.inf = in;
    newStudent.total = in + ph + mat;

    //allStudent[counter] = newStudent;

    return newStudent;
    
};

void RadixSort(struct Student studentik[]) {
    int max = studentik[0].total;
    int raz;

    for(int i = 0; i<N; i++) {
        if (studentik[i].total > max) {
            max = studentik[i].total;
        }
    }

    struct Student* output = (struct Student*)malloc(N * sizeof(struct Student)); //массив под цифирки

    for(int exp = 1; max/exp > 0; exp*=10) { 
        int count[10] = {0};

        for(int i = 0; i < N; i++) {//подсчет сколько раз цифра в разряде
            count[(studentik[i].total / exp) % 10]++; // Извлекаем текущюю цифру и увеличиваем счётчик этой цифры
        }
        // Преобразуем массив для подсчёта частоты цифр, чтобы он хранил индекс последнего элемента с данной цифрой
        for(int i = 1; i <10; i++) {
            count[i] += count[i-1];
        }
        // Строим временный массив для отсортированных данных, размещая элементы в правильном порядке
        for(int i = N - 1; i >=0; i--) {

            output[count[(studentik[i].total / exp)% 10] - 1] = studentik[i]; // Вычисляем текущую цифру и её позицию в output, размещаем элемент в массив
            count[(studentik[i].total / exp)% 10]--; // Уменьшаем счётчик для этой цифры
        }
    // Копируем временный массив для отсортированных данных обратно в массив студентов
    for (int i = 0; i<N; i++) {
        studentik[i] = output[i];
    }
    }
    free(output);
}

struct Student SelectSort(struct Student allStudent[]){

    int k;

    for (int i = 0; i < N - 1; i++){//n=5, 0 1 2 3 4

        k = i;

        for (int j = i + 1; j < N; j++){

            if (allStudent[j].total > allStudent[k].total){

                k = j;

            }

        }

        struct Student temp = allStudent[k];
        allStudent[k] = allStudent[i];
        allStudent[i] = temp;

    }

}

void printStudentInfo(struct Student allStudent[]){

    for (int j = 0; j < N; j++){//n=5, 0 1 2 3 4

        printf("%s\n", allStudent[j].nameStudent);
        printf("%d\n", allStudent[j].math);
        printf("%d\n", allStudent[j].phys);
        printf("%d\n", allStudent[j].inf);
        printf("%d\n", allStudent[j].total);

    }

}

void main(){

    //int colStudent;

    //scanf("%d", &colStudent);

    struct Student allStudent[N];
    struct Student sortAllStudent[N];

    srand(time(NULL));

    for (int x = 0; x  < N; x++){//Заполнение 100 студентов

        char name[n + 1];

        for (int i = 0; i < n; ++i) name[i] = rand() % 26 + 'A'; name[n] = '\0'; 

            int m = rand() % 101;
            int p = rand() % 101;
            int i = rand() % 101;

            allStudent[x] = addStudent(name, m, p, i);


    }
    

    //printStudentInfo(allStudent);

    //SelectSort(allStudent);

     printStudentInfo(allStudent);

    clock_t s = clock();

    RadixSort(allStudent);

    clock_t e = clock();

    double time = e - s;



    printStudentInfo(allStudent);

    printf("Время работы: %lf\n", time / CLOCKS_PER_SEC);
    

    system("cat /proc/cpuinfo | grep 'model name' | head -1");
    system("cat /proc/cpuinfo | grep 'cpu MHz' | head -1");

}