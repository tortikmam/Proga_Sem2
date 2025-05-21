#ifndef TEST_CEZAR_H
#define TEST_CEZAR_H

#include <wchar.h> // Для wchar_t

// Объявления тестовых функций
void test_cezar_russian_uppercase_encrypt(void);
void test_cezar_russian_lowercase_encrypt(void);
void test_cezar_english_uppercase_encrypt(void);
void test_cezar_english_lowercase_encrypt(void);
void test_cezar_mixed_encrypt(void);
void test_cezar_non_alpha_chars_encrypt(void);

void test_cezar_russian_uppercase_decrypt(void);
void test_cezar_russian_lowercase_decrypt(void);
void test_cezar_english_uppercase_decrypt(void);
void test_cezar_english_lowercase_decrypt(void);
void test_cezar_mixed_decrypt(void); // Добавляем тест для дешифрования смешанного текста

// Глобальные счетчики для результатов тестов
extern int test_successes;
extern int test_failures;

#endif // TEST_CEZAR_H