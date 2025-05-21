#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>  // Для setlocale
#include <wchar.h>   // Для работы с широкими символами (wchar_t, wprintf, wcslen и т.д.)
#include <wctype.h>  // Для функций типа iswalpha, iswupper и т.д.

#define DEBUG 1

// Читает содержимое файла в строку широких символов.
wchar_t* readFileToString(FILE* file) {
  

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
    if (bytesRead != fileSize ) {
        printf("Предупреждение: fread прочитал не все байты. Ожидалось %ld, получено %zu.\n", fileSize, bytesRead);
    }
    byteBuffer[bytesRead] = '\0'; // Добавляем нуль-терминатор к байтовому буферу

    // Определяем необходимый размер для wchar_t буфера
    // Предполагается, что входной файл закодирован так, что соответствует кодировке текущей локали
    // (часто UTF-8 для Linux/macOS и иногда Windows).
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
        if (file1) fclose(file1); // Закрываем файл, если он был открыт
        exit(1);
    }
    // Проверка существования file1 уже делается функцией fopen,
    // которая возвращает NULL, если файл не найден.
    // Если fopen возвращает NULL, file1 уже NULL, нет необходимости повторно fclose(file1).

    wchar_t* s = readFileToString(file1);
    if (s != NULL) {
        return s;
    } else {
        // readFileToString уже выводит ошибку, просто выходим.
        if (file1) fclose(file1); // Закрываем только если он был успешно открыт
        exit(1);
    }
}

// Выводит строку широких символов.
void printStr(wchar_t* s) { // Изменен тип возвращаемого значения на void, так как функция ничего не возвращает
    if (s == NULL) return; // Обрабатываем NULL строку
    wprintf(L"%ls\n", s); // Используем wprintf со спецификатором %ls для широких строк
}

// Реализует шифр Цезаря для широких символов, поддерживая русский и английский алфавиты.
wchar_t* CEZAR(wchar_t* s, int k) {
    if (s == NULL) return NULL; // Обрабатываем NULL строку
    int str_len = wcslen(s);
    for (int i = 0; i < str_len; i++) {
        if (iswalpha(s[i])) { // Проверяем, является ли символ алфавитным широким символом
            if (iswupper(s[i])) { // Если заглавная буква
                // Русские заглавные
                if (s[i] >= L'А' && s[i] <= L'Я') { // перед символом: Когда вы пишете L'А', вы создаете литерал широкого символа. Это означает, что компилятор интерпретирует А не как обычный однобайтовый char, а как wchar_t.
                    s[i] = L'А' + (s[i] - L'А' + k) % 32;
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
                    s[i] = L'а' + (s[i] - L'а' + k) % 32;
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

int main(int argc, char* argv[]) {
    // Устанавливаем локаль для обработки широких символов, особенно русских.
    // "Rus" может работать на некоторых системах, но "ru_RU.UTF-8" более стандартен для Linux/macOS.
    // На Windows может использоваться "Russian" или ".ACP" (для ANSI кодовой страницы) или ".UTF8".
    // Более надежный способ для UTF-8 - это setlocale(LC_ALL, ""); а затем проверить, является ли фактическая кодировка UTF-8.
    if (setlocale(LC_ALL, "ru_RU.UTF-8") == NULL && setlocale(LC_ALL, "Russian") == NULL) {
        fprintf(stderr, "Предупреждение: Не удалось установить локаль для обработки русских символов. Операции с широкими символами могут завершиться неудачей.\n");
        // Запасной вариант для систем, которые не распознают "ru_RU.UTF-8" или "Russian"
        setlocale(LC_ALL, ""); // Попытка установить локаль по умолчанию
    }

    FILE* file1 = NULL;
    FILE* file2 = NULL;

    // Проверяем, достаточно ли аргументов, прежде чем пытаться получить доступ к argv[1] и argv[2]
    if (argc < 3) {
        printf("Использование: %s file1 file2\n", argv[0]);
        exit(1);
    }

    file1 = fopen(argv[1], "r");
    if (file1 == NULL) {
        printf("file1: Файл с таким именем должен существовать или не может быть открыт для чтения.\n");
        exit(1);
    }

    wchar_t* s = checkInput(argc, file1);
    fclose(file1); // Закрываем file1 после чтения его содержимого

    if (s == NULL) {
        // Ошибка уже обработана в checkInput/readFileToString, просто выходим
        return 1;
    }

    wprintf(L"Зашифрованый текст: \n"); // Используем wprintf для широких строковых литералов
    printStr(s);

    wprintf(L"Дешифрованный текст: \n"); // Используем wprintf для широких строковых литералов
    s = CEZAR(s, 3);
    printStr(s);

    // Открываем file2 для записи зашифрованного текста
    file2 = fopen(argv[2], "w");
    if (file2 == NULL) {
        printf("file2: Не удалось открыть для записи.\n");
        free(s); // Освобождаем выделенную память перед выходом
        return 1;
    }

    // Записываем строку широких символов в file2.
    // fwprintf необходима для записи широких символов в файл.
    // Убедитесь, что файл открыт в режиме "wb", если вы хотите записывать необработанные широкие символы,
    // или если вы хотите многобайтовый вывод с учетом локали, используйте режим "w" и fwprintf.
    // Для общей переносимости и UTF-8, часто лучше преобразовать обратно в UTF-8
    // при записи или убедиться, что выходной поток обрабатывает широкие символы.
    // Использование `wprintf` и `fwprintf` зависит от `setlocale` для управления кодировкой.
    fwprintf(file2, L"%ls", s);

    fclose(file2); // Закрываем file2
    free(s); // Освобождаем динамически выделенную широкую строку
    return 0;
}