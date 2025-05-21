#include "test_cezar.h"
#include "../CEZAR/CEZAR.h" // Включаем наш заголовочный файл с функцией CEZAR и DECEZAR

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Для wcscpy и wcslen
#include <locale.h> // Для setlocale

// Простая макросная обертка для ассертов
#define ASSERT_WCS_EQUAL(expected, actual, message) \
    do { \
        if (actual == NULL || wcscmp(expected, actual) != 0) { \
            wprintf(L"НЕУДАЧА: %s\n", message); \
            wprintf(L"  Ожидалось: \"%ls\"\n", expected); \
            wprintf(L"  Получено:  \"%ls\"\n", actual ? actual : L"(NULL)"); \
            test_failures++; \
        } else { \
            /* wprintf(L"УСПЕХ: %s\n", message); */ \
            test_successes++; \
        } \
    } while (0)

// Глобальные счетчики для результатов тестов
int test_successes = 0;
int test_failures = 0;

// Вспомогательная функция для копирования wide string
wchar_t* wcsdup_custom(const wchar_t* s) {
    if (s == NULL) return NULL;
    size_t len = wcslen(s) + 1;
    wchar_t* new_s = (wchar_t*)malloc(len * sizeof(wchar_t));
    if (new_s == NULL) {
        perror("Failed to allocate memory for wcsdup_custom");
        exit(EXIT_FAILURE);
    }
    wcscpy(new_s, s);
    return new_s;
}

// --- Тесты на ШИФРОВАНИЕ (функция CEZAR) ---

void test_cezar_russian_uppercase_encrypt(void) {
    wchar_t* original = wcsdup_custom(L"ПРИВЕТ");
    wchar_t* expected = L"ТУЛЕИХ";
    wchar_t* encrypted = CEZAR(original, 3);
    ASSERT_WCS_EQUAL(expected, encrypted, L"Шифрование русских заглавных");
    free(original);
}

void test_cezar_russian_lowercase_encrypt(void) {
    wchar_t* original = wcsdup_custom(L"привет");
    wchar_t* expected = L"тулеих";
    wchar_t* encrypted = CEZAR(original, 3);
    ASSERT_WCS_EQUAL(expected, encrypted, L"Шифрование русских строчных");
    free(original);
}

void test_cezar_english_uppercase_encrypt(void) {
    wchar_t* original = wcsdup_custom(L"HELLO");
    wchar_t* expected = L"KHOOR";
    wchar_t* encrypted = CEZAR(original, 3);
    ASSERT_WCS_EQUAL(expected, encrypted, L"Шифрование английских заглавных");
    free(original);
}

void test_cezar_english_lowercase_encrypt(void) {
    wchar_t* original = wcsdup_custom(L"hello");
    wchar_t* expected = L"khoor";
    wchar_t* encrypted = CEZAR(original, 3);
    ASSERT_WCS_EQUAL(expected, encrypted, L"Шифрование английских строчных");
    free(original);
}

void test_cezar_mixed_encrypt(void) {
    wchar_t* original = wcsdup_custom(L"Привет, World!");
    wchar_t* expected = L"Тулеих, Zruog!";
    wchar_t* encrypted = CEZAR(original, 3);
    ASSERT_WCS_EQUAL(expected, encrypted, L"Шифрование смешанного текста");
    free(original);
}

void test_cezar_non_alpha_chars_encrypt(void) {
    wchar_t* original = wcsdup_custom(L"123!@#$ %^&*()");
    wchar_t* expected = L"123!@#$ %^&*()";
    wchar_t* encrypted = CEZAR(original, 3);
    ASSERT_WCS_EQUAL(expected, encrypted, L"Неалфавитные символы при шифровании");
    free(original);
}

// --- Тесты на ДЕШИФРОВАНИЕ (функция DECEZAR) ---

void test_cezar_russian_uppercase_decrypt(void) {
    wchar_t* original = wcsdup_custom(L"ТУЛЕИХ"); // Зашифрованный текст
    wchar_t* expected = L"ПРИВЕТ"; // Ожидаемый дешифрованный текст
    wchar_t* decrypted = DECEZAR(original, 3); // Используем DECEZAR
    ASSERT_WCS_EQUAL(expected, decrypted, L"Дешифрование русских заглавных");
    free(original);
}

void test_cezar_russian_lowercase_decrypt(void) {
    wchar_t* original = wcsdup_custom(L"тулеих");
    wchar_t* expected = L"привет";
    wchar_t* decrypted = DECEZAR(original, 3);
    ASSERT_WCS_EQUAL(expected, decrypted, L"Дешифрование русских строчных");
    free(original);
}

void test_cezar_english_uppercase_decrypt(void) {
    wchar_t* original = wcsdup_custom(L"KHOOR");
    wchar_t* expected = L"HELLO";
    wchar_t* decrypted = DECEZAR(original, 3);
    ASSERT_WCS_EQUAL(expected, decrypted, L"Дешифрование английских заглавных");
    free(original);
}

void test_cezar_english_lowercase_decrypt(void) {
    wchar_t* original = wcsdup_custom(L"khoor");
    wchar_t* expected = L"hello";
    wchar_t* decrypted = DECEZAR(original, 3);
    ASSERT_WCS_EQUAL(expected, decrypted, L"Дешифрование английских строчных");
    free(original);
}

void test_cezar_mixed_decrypt(void) {
    wchar_t* original = wcsdup_custom(L"Тулеих, Zruog!"); // Зашифрованный смешанный текст
    wchar_t* expected = L"Привет, World!"; // Ожидаемый дешифрованный текст
    wchar_t* decrypted = DECEZAR(original, 3);
    ASSERT_WCS_EQUAL(expected, decrypted, L"Дешифрование смешанного текста");
    free(original);
}