#include "main.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h> //isdigit
#include <stdlib.h> //atoi
#include <unistd.h> //ftruncate
#include <math.h> //rint

#define var 2

size_t count = 0;

float check1() { //проверка на корректный ввод чисел
    char s[max_size];
    int flag = 0;
    float dt;
    while (1) {
        fgets(s, sizeof(s), stdin);
        if (s[0] == '-') { //проверка на неотрицательные числа
            printf("Value mast be grater than zero. Try again:\n");
            continue;
        }
        for (int i = 0; i < strlen(s) - 1; i += 1) { //цикл для проверки каждого символа на цифру
            if (!isdigit(s[i]) && (s[i] != '.')) { //если символ цифра, то ничего
                flag += 1; //иначе меняется флаг
                break;
            }
        }
        if (flag == 0) { //проверка флага: если 0, значит строка это число
            dt = atoi(s);
            if (dt == 0) { //если равно нулю, то меняется флаг
                printf("Value mast be grater than zero. Try again:\n");
                continue;
            }
            break;
        }
        else if (flag != 100) { //проверка на равенство нулю
            printf("Value must include only numbers. Try again:\n");
        }
        flag = 0; //обнуление флага
    }
    return dt; //возращаемое значение - значение возраста/роста/веса
}

int check_c(char* s) {
    for (int i = 0; i < (strlen(s) - 1); i += 1) { //проверка на корректный ввод символов
        if (!isalpha(s[i]) && (s[i] != ' ')) {
            return 0;
        }
    }
    return 1;
}
char *check2(char *s) { //проверка на корректный ввод имени/спорта/звания
    if (((s[strlen(s)-1] != '\n') && (s[strlen(s)-1] != '\0')) || (!check_c(s))) { //перед "или" условие отвечает за корректную длину, после за корректные символы
        if (!check_c(s)) {
            printf("There must be only letters and numbers in the string. Try again:\n");
        }
        else {
            printf("Size of string must be less than 30. Try again:\n");
        }
        fflush(stdin); //очистка буфера
        while (1) {
            fgets(s, 30, stdin); //чтение новой (возможно правильной) строки
            if ((s[strlen(s)-1] != '\n') && (s[strlen(s)-1] != '\0')) { //проверка на количество символов
                fflush(stdin);
                printf("Size of string must be less than 30. Try again:\n");
            }
            else {
                if (check_c(s)) { //проверка на символы
                    s[strlen(s)-1] = '\0'; //если в конце строки \n заменится на \0
                    return s;
                }
                else {
                    printf("There must be only letters and numbers in the string. Try again:\n");
                }
            }
        }
    }
    else {
        s[strlen(s)-1] = '\0'; //если в конце строки \n заменится на \0
        return s;
    }
}

void add_in_file(FILE* file);

void delete_from_file(FILE* file);

void get_file(FILE* file);

void search_in_file(FILE*); //функция поиска по заданному параметру в файле

void edit_file(FILE*); //функция изменения параметра в файле

int main() {
    int num_case = 0; //переменная для выбора действия из меню
    FILE *file = fopen("data2.bin", "w+b"); //создание указателя для файла и открытие файла для чтения и записи

#if var == 2 //если вариант ввода исходный данных с клавиатуры, то сразу добавляем их в файл
    fseek(file, 0, SEEK_END);
    size_t k = fwrite(&base, sizeof(flw), sizeof(base) / sizeof(flw), file); //увеличение количества данных на величину, успешно записанных в файл
    count += k;
    printf("%llu objects out of %llu were uploaded to the file\n", k, sizeof(base) / sizeof(flw));
    printf("The amount of data in the file: %llu\n\n", count);
#endif

    while (num_case != 6) {
        printf("Choose what type of action do you want to do:\n"
               "1 - add data in the file\n"
               "2 - delete data from the file\n"
               "3 - search data in the file\n"
               "4 - edite data in the file\n"
               "5 - look at the whole the file\n"
               "6 - end program\n"
               "Enter the number of action:\n");
        scanf("%d", &num_case);
        fflush(stdin); //сброс данных из буфера
        switch (num_case) {
            case 1:
                add_in_file(file);
                break;
            case 2:
                delete_from_file(file);
                break;
            case 3:
                search_in_file(file);
                break;
            case 4:
                edit_file(file);
                break;
            case 5:
                get_file(file);
                break;
            case 6:
                break;
            default: //проверка на корректный ввод
                printf("The vaLue must be from 1 to 6. Try again\n\n");
        }
    }

    printf("You have finished work!");
    fclose(file);
    return 0;
}

void add_in_file(FILE *file) { //функция добавления одной записи в файл
    float fcount;
    flw data[1];
    printf("Enter name of flower:\n");
    fgets(data->name, sizeof(data->name), stdin);
    strcpy(data->name, check2(data->name));
    printf("Enter color of flower:\n");
    fgets(data->color, sizeof(data->color), stdin);
    strcpy(data->color, check2(data->color));
    printf("Enter country of flower:\n");
    fgets(data->country, sizeof(data->country), stdin);
    strcpy(data->country, check2(data->country));
    printf("Enter count of flowers:\n");
    while (1) { //проверка на целое число
        fcount = check1();
        if (fcount != rint(fcount)) {
            printf("Value must be integer. Try again:\n");
        } else {
            data->count = rint(fcount);
            break;
        }
    }

    printf("The result: %s | %s | %s |  %d  |\n", data->name, data->color, data->country, data->count);

    fseek(file, 0, SEEK_END); //смещение каретки в конец
    size_t k = fwrite(&data, sizeof(flw), 1, file); //запись данных в файл из структуры
    count += k; //увеличение счетчика количества данных
    printf("%llu objects out of %d were uploaded to the file\n", k, 1);
    printf("The amount of data in the file: %llu\n\n", count);

}

void delete_from_file(FILE *file) {
    if (count == 0) { //проверка на наличие данных в файле
        printf("There is no data to delete\n\n");
    }
    int num_line;
    float fnum;
    get_file(file); //вывод данных для удобства
    printf("Choose the number of line which you want to delete:\n");
    while (1) {
        fnum = check1();
        if (fnum != rint(fnum)) { //проверка на целое число
            printf("Value must be integer. Try again:\n");
            continue;
        }
        num_line = rint(fnum); //выбор строки
        int flag = 0;
        for (int i = 1; i <= count; i += 1) { //проверка на ввод нужного числа
            if (num_line != i) {
                flag += 1;
                continue;
            }
            else {
                break;
            }
        }
        if (flag == count) {
            printf("Value must be from 1 to %llu. Try again:\n", count);
        }
        else {
            break;
        }
    }

    flw del[1];

    for (int i = num_line; i < count; i += 1) { //цикл, в котором данные смещаются на одну позицию в начало, тем самым удаляя нужные данные
        fseek(file, sizeof(flw)*i, SEEK_SET);
        fread(&del, sizeof(flw), 1, file);
        fseek(file, sizeof(flw)*(i - 1), SEEK_SET);
        fwrite(&del, sizeof(flw), 1, file);
    }

    count -= 1;
    ftruncate(fileno(file), sizeof(flw)*count); //уменьшение размера файла

}

void search_in_file(FILE* file) {
    if (count == 0) { //проверка на наличие данных в файле
        printf("There is no data to search\n\n");
        return;
    }
    int num_field, item_d, flag, flag2 = 0;
    char item_s[max_size];
    flw line;
    float fnum;

    printf("1 - name; 2 - color; 3 - country; 4 - count\n");
    printf("Choose the number of field which you want to find:\n");
    while (1) {
        fnum = check1();
        if (fnum != rint(fnum)) { //проверка на целое значение
            printf("Value must be integer. Try again:\n");
            continue;
        }
        num_field = fnum; //выбор поля
        if ((num_field != 1) && (num_field != 2) && (num_field != 3) && (num_field != 4)) {
            printf("Value must be from 1 to 4. Try again:\n");
        }
        else {
            break;
        }
    }
    fflush(stdin);
    printf("Enter the value:\n");

    if ( (num_field == 1) || (num_field == 2) || (num_field == 3) ) { //если выбор 1/2/3, то значение для поиска записываем в строку
        fgets(item_s, sizeof(item_s), stdin);
        item_s[strlen(item_s)-1] = '\0';
    }
    else { //если выбор 4, то значение для поиска это число, записываем в переменную
        item_d = check1();
    }

    printf("Matching:\n");
    for (int i = 0; i < count; i += 1) { //поиск совпадения по данным
        flag = 0;
        fseek(file, sizeof(flw)*i, SEEK_SET); //смещение каретки на одну структуру
        fread(&line, sizeof(flw), 1, file); //чтение одной структуры

        switch (num_field) {
            case 1:
                if (!strcmp(item_s, line.name)) {
                    flag += 1; //флаг на совпадение
                }
                break;
            case 2:
                if (!strcmp(item_s, line.color)) {
                    flag += 1; //флаг на совпадение
                }
                break;
            case 3:
                if (!strcmp(item_s, line.country)) {
                    flag += 1; //флаг на совпадение
                }
                break;
            case 4:
                if (item_d == line.count) {
                    flag += 1;
                }
                break;
        }
        if (flag != 0) { //вывод данных если совпадение было
            flag2 = 1;
            printf("%s | %s | %s | %d \n", line.name, line.color, line.country, line.count);
        }
    }
    if (flag2 == 0) { //если совпадений не было
        printf("There is no match\n");
    }
    printf("\n");
}

void edit_file(FILE* file) {
    if (count == 0) { //проверка на наличие данных в файле
        printf("There is no data to edit\n\n");
        return;
    }
    flw line;
    int num_line, num_field;
    float fnum;

    get_file(file); //вывод данных для удобства
    printf("Choose the number of line which you want to edit:\n");
    while (1) {
        fnum = check1(); //проверка на целое число
        if (fnum != rint(fnum)) {
            printf("Value must be integer. Try again:\n");
            continue;
        }
        num_line = fnum;
        int flag = 0;
        for (int i = 1; i <= count; i += 1) { //проверка на нужное число
            if (num_line != i) {
                flag += 1; //количество несовпадений
                continue;
            } else {
                break;
            }
        }
        if (flag == count) {
            printf("Value must be from 1 to %llu. Try again:\n", count);
        }
        else {
            break;
        }
    }
    fseek(file, sizeof(flw)*(num_line - 1), SEEK_SET); //перемещение картеки на место перед нужной строкой
    fread(&line, sizeof(flw), 1, file); //чтение этой строки

    printf("1 - name; 2 - color; 3 - country; 4 - count\n");
    printf("Choose the number of field which you want to edit:\n");
    while (1) {
        fnum = check1(); //проверка на целое число
        if (fnum != rint(fnum)) {
            printf("Value must be integer. Try again:\n");
            continue;
        }
        num_field = fnum;
        if ((num_field != 1) && (num_field != 2) && (num_field != 3) && (num_field != 4)) {
            printf("Value must be from 1 to 4. Try again:\n");
        }
        else {
            break;
        }
    }
    printf("Enter what you want to replace it with:\n");
    fflush(stdin);

    switch (num_field) {
        case 1:
            fgets(line.name, sizeof(line.name), stdin); //получение нового значения для поля
            line.name[strlen(line.name) - 1] = '\0';
            break;
        case 2:
            fgets(line.color, sizeof(line.color), stdin); //получение нового значения для поля
            line.color[strlen(line.color) - 1] = '\0';
            break;
        case 3:
            fgets(line.country, sizeof(line.country), stdin); //получение нового значения для поля
            line.country[strlen(line.country) - 1] = '\0';
            break;
        case 4:
            line.count = check1(); //получение нового значения для поля
            break;
    }
    printf("The result: %s | %s | %s | %d \n\n", line.name, line.color, line.country, line.count); //вывод новой строки

    fseek(file, sizeof(flw)*(num_line - 1), SEEK_SET); //перемещение каретки на место перед нужной строкой
    fwrite(&line, sizeof(flw), 1, file);
}

void get_file(FILE *file) {
    if (count == 0) {
        printf("There is no data in the file\n\n");
    }
    flw data[count];
    fseek(file, 0, SEEK_SET); //перемещение каретки в начало
    fread(&data, sizeof(flw), count, file); //чтение всего файла

    char p = '\0';
    printf("N  Name | Color | Country | Count \n\n");
    for (int i = 0; i < count; i += 1) { //построчный вывод
        printf("%d: %s | %s | %s | %d \n", i+1, data[i].name, data[i].color, data[i].country, data[i].count);
    }
    printf("\n");
}


