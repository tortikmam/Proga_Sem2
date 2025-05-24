#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 2048

// Функция проверки на пробельный символ (без ctype.h)
int simvoly(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

// Функция для поиска самой длинной строки в файле
int longestLine(FILE *file, char *longest_line) {
    char line[MAX_LINE_LENGTH];
    int max_length = 0;
    int current_line = 0;
    int longest_line_num = -1;

    rewind(file);

    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);
        if (length > max_length) {
            max_length = length;
            strcpy(longest_line, line);
            longest_line_num = current_line;
        }
        current_line++;
    }

    return longest_line_num;
}

// Функция для замены первого и последнего слова
void swap_first_last_words(char *str) {
    char first_word[MAX_LINE_LENGTH] = {0};
    char last_word[MAX_LINE_LENGTH] = {0};
    char middle_part[MAX_LINE_LENGTH] = {0};
    char result[MAX_LINE_LENGTH] = {0};

    // Удаляем символы новой строки
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
        len--;
    }

    // Находим первое слово
    int first_start = 0;

    while (first_start < len && simvoly(str[first_start])){
         first_start++;
         }

    int first_end = first_start;

    while (first_end < len && !simvoly(str[first_end])){
        first_end++;
        }

    strncpy(first_word, str + first_start, first_end - first_start);

    first_word[first_end - first_start] = '\0';

    // Находим последнее слово
    int last_end = len;

    while (last_end > 0 && simvoly(str[last_end-1])){ 
        last_end--;
        }

    int last_start = last_end;

    while (last_start > 0 && !simvoly(str[last_start-1])){ 
        last_start--;
        }

    strncpy(last_word, str + last_start, last_end - last_start);

    last_word[last_end - last_start] = '\0';

    // Копируем среднюю часть
    if (first_end < last_start) {
        strncpy(middle_part, str + first_end, last_start - first_end);
        middle_part[last_start - first_end] = '\0';
    }

    // Формируем результат
    if (last_start > first_end) {
        sprintf(result, "%s%s%s", last_word, middle_part, first_word);
    } else {
        // Если только одно слово
        strcpy(result, str);
    }

    strcpy(str, result);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r+");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char longest_line[MAX_LINE_LENGTH] = {0};
    int line_number = longestLine(file, longest_line);

    if (line_number == -1) {
        fprintf(stderr, "File is empty\n");
        fclose(file);
        return 1;
    }

    swap_first_last_words(longest_line);

    // Записываем измененную строку обратно в файл
    rewind(file);
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int current_line = 0;
    rewind(file);

    while (fgets(line, sizeof(line), file) != NULL) {
        if (current_line == line_number) {
            fputs(longest_line, temp_file);
            fputc('\n', temp_file);
        } else {
            fputs(line, temp_file);
        }
        current_line++;
    }

    // Копируем содержимое временного файла обратно в исходный
    rewind(temp_file);
    freopen(argv[1], "w", file);

    while (fgets(line, sizeof(line), temp_file) != NULL) {
        fputs(line, file);
    }

    fclose(temp_file);
    fclose(file);

    printf("Successfully swapped first and last words in the longest line\n");
    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>

// // gcc text.c -o text
// // ./text file.txt out.txt

// int main(int argc, char *argv[]) {

//     if (argc < 3) {
//         printf("Usage: ./a.out file.txt out.txt\n");
//         exit(1);
//     }
//     short re, im;

//     FILE *file = fopen(argv[1], "r");
//     if (file == NULL) {
//         perror("Error opening file");
//         exit(1);
//     }

//     FILE *file_w = fopen(argv[2], "w");
//     if (file_w == NULL) {
//         printf("In %s:%d Error opening file\n", __FILE__, __LINE__); // или perror()
//         exit(1);
//     }

//     fscanf(file, "array = ");

//     while (!feof(file)) {
//         fscanf(file, "%hd + j*(%hd)\n", &re, &im);
//         printf("%hd + j*(%hd)\n", re, im);
//         fprintf(file_w, "%hd + j*(%hd)\n", re, im);
//     }


//     fclose(file);

