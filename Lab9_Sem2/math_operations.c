#include "math_operations.h"

float add(int a, int b) {
    return (float)(a + b);
}

float subtract(int a, int b) {
    return (float)(a - b);
}

float multiply(int a, int b) {
    return (float)(a * b);
}

float divide(int a, int b) {
    if (b == 0) {
        return -1.0f; // Возвращаем -1.0f вместо -1 для согласованности с типом float
    }
    return (float)a / b;
}
