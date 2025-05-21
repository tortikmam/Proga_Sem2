#include "CEZAR.h" // Включаем наш собственный заголовочный файл
#include <math.h>   // Необходим для некоторых математических операций, если они есть
#include <string.h> // Для wcslen, mbstowcs
#include <ctype.h>  // Для iswalpha, iswupper (хотя wctype.h предпочтительнее для wchar_t)
#include <locale.h> // Для setlocale
#include <wctype.h> // Для iswalpha, iswupper, iswlower и т.д.

// Читает содержимое файла в строку широких символов.
wchar_t* readFileToString(FILE* file) {
    // Убедимся, что указатель на файл не NULL
    if (file == NULL) {
        printf("Ошибка: Указатель на входной файл NULL.\n");
        return NULL;
    }

    // Получаем размер файла в байтах
    if (fseek(file, 0, SEEK_END) != 0) {
        printf("Ошибка: fseek не удался.\n");
        return NULL;
    }
    long fileSize = ftell(file);
    if (fileSize == -1) {
        printf("Ошибка: ftell не удался.\n");
        return NULL;
    }
    if (fileSize == 0) {
        printf("file1: Файл не должен быть пустым.\n");
        return NULL;
    }

    // Возвращаемся в начало файла
    if (fseek(file, 0, SEEK_SET) != 0) {
        printf("Ошибка: fseek не удался.\n");
        return NULL;
    }

    // Выделяем буфер для байтов, затем конвертируем в широкие символы
    char* byteBuffer = (char*)malloc(fileSize + 1);
    if (byteBuffer == NULL) {
        printf("Ошибка: Выделение памяти для байтового буфера не удалось.\n");
        return NULL;
    }

    size_t bytesRead = fread(byteBuffer, 1, fileSize, file);
    if (bytesRead != (size_t)fileSize) {
        printf("Предупреждение: fread прочитал не все байты. Ожидалось %ld, получено %zu.\n", fileSize, bytesRead);
    }
    byteBuffer[bytesRead] = '\0'; // Добавляем нуль-терминатор к байтовому буферу

    // Определяем необходимый размер для wchar_t буфера
    size_t wc_len = mbstowcs(NULL, byteBuffer, 0); // Получаем необходимую длину для строки широких символов
    if (wc_len == (size_t)-1) {
        printf("Ошибка: Не удалось преобразовать многобайтовую строку в широкую строку. Проверьте настройки локали или кодировку файла.\n");
        free(byteBuffer);
        return NULL;
    }

    wchar_t* wideBuffer = (wchar_t*)malloc((wc_len + 1) * sizeof(wchar_t));
    if (wideBuffer == NULL) {
        printf("Ошибка: Выделение памяти для широкого буфера не удалось.\n");
        free(byteBuffer);
        return NULL;
    }

    // Конвертируем многобайтовую строку в строку широких символов
    mbstowcs(wideBuffer, byteBuffer, wc_len + 1);
    wideBuffer[wc_len] = L'\0'; // Убедимся в наличии широкого нуль-терминатора

    free(byteBuffer); // Освобождаем временный байтовый буфер
    return wideBuffer;
}

// Проверяет входные аргументы и читает файл.
wchar_t* checkInput(int c, FILE* file1) {
    if (c != 3) {
        printf("Использование: ./CEZAR file1 file2\n");
        if (file1) fclose(file1);
        exit(1);
    }

    wchar_t* s = readFileToString(file1);
    if (s != NULL) {
        return s;
    } else {
        if (file1) fclose(file1);
        exit(1);
    }
}

// Выводит строку широких символов.
void printStr(wchar_t* s) {
    if (s == NULL) return;
    wprintf(L"%ls\n", s);
}

// Реализует шифр Цезаря для широких символов, поддерживая русский и английский алфавиты.
// Эта функция работает как дешифратор, вычитая ключ 'k'.
wchar_t* CEZAR(wchar_t* s, int k) {
    if (s == NULL) return NULL; // Обрабатываем NULL строку
    int str_len = wcslen(s);
    for (int i = 0; i < str_len; i++) {
        if (iswalpha(s[i])) { // Проверяем, является ли символ алфавитным широким символом
            if (iswupper(s[i])) { // Если заглавная буква
                // Русские заглавные
                if (s[i] >= L'А' && s[i] <= L'Я') { // перед символом: Когда вы пишете L'А', вы создаете литерал широкого символа. Это означает, что компилятор интерпретирует А не как обычный однобайтовый char, а как wchar_t.
                    s[i] = L'А' + (s[i] - L'А' + k) % 33;
                }
                // Английские заглавные
                else if (s[i] >= L'A' && s[i] <= L'Z') {
                    s[i] = (wchar_t)(((s[i] - L'A' + k) % 26) + L'A');
                }
                // Обработка 'Ё' при необходимости (отдельно от 'Е' в некоторых кодировках)
                else if (s[i] == L'Ё') {
                    // Решите, как сдвигать 'Ё'. Для простоты, можно считать ее отдельным символом
                    // или при необходимости отображать ее на 'Е' перед сдвигом.
                    // Пока она не будет затронута общей логикой, если не обработана явно.
                }

            } else { // Если строчная буква
                // Русские строчные
                if (s[i] >= L'а' && s[i] <= L'я') {
                    s[i] = L'а' + (s[i] - L'а' + k) % 33;
                }
                // Английские строчные
                else if (s[i] >= L'a' && s[i] <= L'z') {
                    s[i] = (wchar_t)(((s[i] - L'a' + k) % 26) + L'a');
                }
                // Обработка 'ё' при необходимости
                else if (s[i] == L'ё') {
                    // Аналогично 'Ё'
                }
            }
        }
    }
    return s;
}

wchar_t* DECEZAR(wchar_t* s, int k) {
    if (s == NULL) return NULL; // Обрабатываем NULL строку
    int str_len = wcslen(s);
    for (int i = 0; i < str_len; i++) {
        if (iswalpha(s[i])) { // Проверяем, является ли символ алфавитным широким символом
            if (iswupper(s[i])) { // Если заглавная буква
                // Русские заглавные
                if (s[i] >= L'А' && s[i] <= L'Я') { // перед символом: Когда вы пишете L'А', вы создаете литерал широкого символа. Это означает, что компилятор интерпретирует А не как обычный однобайтовый char, а как wchar_t.
                    s[i] = L'А' + (s[i] - L'А' - k) % 33;
                }
                // Английские заглавные
                else if (s[i] >= L'A' && s[i] <= L'Z') {
                    s[i] = (wchar_t)(((s[i] - L'A' - k) % 26) + L'A');
                }
                // Обработка 'Ё' при необходимости (отдельно от 'Е' в некоторых кодировках)
                else if (s[i] == L'Ё') {
                    // Решите, как сдвигать 'Ё'. Для простоты, можно считать ее отдельным символом
                    // или при необходимости отображать ее на 'Е' перед сдвигом.
                    // Пока она не будет затронута общей логикой, если не обработана явно.
                }

            } else { // Если строчная буква
                // Русские строчные
                if (s[i] >= L'а' && s[i] <= L'я') {
                    s[i] = L'а' + (s[i] - L'а' - k) % 33;
                }
                // Английские строчные
                else if (s[i] >= L'a' && s[i] <= L'z') {
                    s[i] = (wchar_t)(((s[i] - L'a' - k) % 26) + L'a');
                }
                // Обработка 'ё' при необходимости
                else if (s[i] == L'ё') {
                    // Аналогично 'Ё'
                }
            }
        }
    }
    return s;
}