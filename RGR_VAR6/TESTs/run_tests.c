#include "test_cezar.h" // Включаем заголовок с объявлениями тестов
#include <stdio.h>
#include <stdlib.h> // Для EXIT_SUCCESS, EXIT_FAILURE
#include <locale.h> // Для setlocale

// Внешние счетчики из test_cezar.c
extern int test_successes;
extern int test_failures;

int main(void) {
    // Устанавливаем локаль для обработки широких символов
    if (setlocale(LC_ALL, "ru_RU.UTF-8") == NULL && setlocale(LC_ALL, "Russian") == NULL) {
        fprintf(stderr, "Предупреждение: Не удалось установить локаль для обработки русских символов в тестовом окружении.\n");
        setlocale(LC_ALL, ""); // Попытка установить локаль по умолчанию
    }

    wprintf(L"Запуск тестов CEZAR и DECEZAR...\n");

    // Запуск всех тестовых функций ШИФРОВАНИЯ
    test_cezar_russian_uppercase_encrypt();
    test_cezar_russian_lowercase_encrypt();
    test_cezar_english_uppercase_encrypt();
    test_cezar_english_lowercase_encrypt();
    test_cezar_mixed_encrypt();
    test_cezar_non_alpha_chars_encrypt();

    // Запуск всех тестовых функций ДЕШИФРОВАНИЯ
    test_cezar_russian_uppercase_decrypt();
    test_cezar_russian_lowercase_decrypt();
    test_cezar_english_uppercase_decrypt();
    test_cezar_english_lowercase_decrypt();
    test_cezar_mixed_decrypt();

    wprintf(L"\n--- Результаты тестов ---\n");
    wprintf(L"Успешно пройдено: %d\n", test_successes);
    wprintf(L"Неудач: %d\n", test_failures);

    return (test_failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}