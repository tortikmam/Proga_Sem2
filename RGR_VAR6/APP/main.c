#include "../CEZAR/CEZAR.h" // Включаем наш собственный заголовочный файл
#include <locale.h> // Для setlocale

int main(int argc, char* argv[]) {
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
        return 1;
    }
    int k ;
    wprintf(L"Ввведите значение k: ");
    scanf("%d",&k);
    wprintf(L"Изначальный  текст: \n");
    printStr(s);
    wprintf(L"0 - шифровка / 1 - дешифрровка  : \n");
    int select = 0;
    scanf("%d",&select);
    if (select == 0){
        wprintf(L"Зашифрованный текст: \n");
        s = CEZAR(s, k); // Вызываем CEZAR для дешифровки (ключ 3)
        printStr(s);

    }
    else if(select == 1){
        wprintf(L"Дешифрованный текст: \n");
        s = DECEZAR(s, k); // Вызываем CEZAR для дешифровки (ключ 3)
        printStr(s);

    }
    else{
        wprintf(L"Такого варианта нет \n");
    }


    // Открываем file2 для записи дешифрованного текста
    file2 = fopen(argv[2], "w");
    if (file2 == NULL) {
        printf("file2: Не удалось открыть для записи.\n");
        free(s);
        return 1;
    }

    fwprintf(file2, L"%ls", s);

    fclose(file2);
    free(s);
    return 0;
}