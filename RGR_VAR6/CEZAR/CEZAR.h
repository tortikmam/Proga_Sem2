#ifndef CEZAR_H
#define CEZAR_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h> // Для wchar_t и связанных функций

// Объявление функций
wchar_t* readFileToString(FILE* file);
wchar_t* checkInput(int c, FILE* file1);
void printStr(wchar_t* s);
wchar_t* CEZAR(wchar_t* s, int k); 
wchar_t* DECEZAR(wchar_t* s, int k);

#endif // CEZAR_H