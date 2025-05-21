#include <stdio.h>
#include <string.h>

typedef struct {
    char name[100];
    char number[20];
    int date[3];
} Employee;

void add_employees() {
    FILE *f = fopen("Worker.dat", "wb");
    if (!f) {
        printf("Ошибка создания файла\n");
        return;
    }

    int count;
    printf("Сколько сотрудников добавить? ");
    scanf("%d", &count);

    for (int i = 0; i < count; i++) {
        Employee e;
        printf("\nСотрудник %d:\n", i+1);
        printf("ФИО: "); 
        getchar();
        fgets(e.name, 100, stdin);
        e.name[strlen(e.name)-1] = '\0';

        for(int j = 0; j < 3; j++){
            int n = 0;
            if (j == 0){
                printf("Введите число когда родились: ");
                scanf("%d", &n);
                e.date[j] = n;
            }else if(j == 1){
                printf("Введите месяц когда родились: ");
                scanf("%d", &n);
                e.date[j] = n;
            }else if(j == 2){
                printf("Введите год когда родились: ");
                scanf("%d", &n);
                e.date[j] = n;
            }
        }
        
        printf("Телефон: ");
        getchar();
        fgets(e.number, 20, stdin);
        e.number[strlen(e.number)-1] = '\0';
        
        fwrite(&e, sizeof(Employee), 1, f);
    }
    
    fclose(f);
    printf("\nДанные сохранены в Worker.dat\n");
}

void search_employee() {
    FILE *f = fopen("Worker.dat", "rb");
    if (!f) {
        printf("Файл не найден\n");
        return;
    }

    printf("\nПоиск по:\n1. ФИО\n2. Номеру\n3. Дате рождения\nВыбор: ");
    int choice;
    scanf("%d", &choice);

    Employee e;
    int found = 0;
    
    if (choice == 1) {
        char name[100];
        printf("Введите ФИО: ");
        getchar();
        fgets(name, 100, stdin);
        name[strlen(name)-1] = '\0';
        
        while (fread(&e, sizeof(Employee), 1, f)) {
            if (strcmp(e.name, name) == 0) {
                printf("\nНайдено:\nФИО: %s\nномер: %s\n", 
                      e.name, e.number);
                
                printf("Дата рождения: %d.%d.%d", e.date[0], e.date[1], e.date[2]);
                found = 1;
            }
        }
    }
    else if (choice == 2) {
        char number[20];
        printf("Введите Номер: ");
        getchar();
        fgets(number, 20, stdin);
        number[strlen(number)-1] = '\0';
        
        while (fread(&e, sizeof(Employee), 1, f)) {
            if (strcmp(e.number, number) == 0) {
                 printf("\nНайдено:\nФИО: %s\nНомер: %s\n", 
                      e.name, e.number);
                
                printf("Дата рождения: %d.%d.%d", e.date[0], e.date[1], e.date[2]);
                found = 1;
            }
        }
    }
    else if (choice == 3) {
        int day;
        int month;
        int year;

        printf("Введите день рождения: ");
        scanf("%d", &day);
        printf("Введите месяц рождения: ");
        scanf("%d", &month);
        printf("Введите год рождения: ");
        scanf("%d", &year);
        
        while (fread(&e, sizeof(Employee), 1, f)) {
            if (e.date[0] == day && e.date[1] == month && e.date[2] == year) {
                printf("\nНайдено:\nФИО: %s\nномер: %s\n", 
                      e.name, e.number);
                
                printf("Дата рождения: %d.%d.%d", e.date[0], e.date[1], e.date[2]);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("Ничего не найдено\n");  
    }

    fclose(f);
}

int main() {
    add_employees();
    search_employee();
    return 0;
}