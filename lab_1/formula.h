/////////////////////////////////////////////////////////////////////////////////////////
// Лабораторная работа №1 по дисциплине ЛОИС
// Выполнена студентом группы 421701 БГУИР Бибко Владислав Викторович
// 
// НАЗНАЧЕНИЕ: Файл содержит объявления констант и функций для базовой работы
//              с формулами сокращённого языка логики высказываний: проверки
//              символов, определения логических связок, сбора переменных,
//              поиска переменной и работы с C-строками.
// 
//         
// 
// ДАТА: 12.05.2026
// ВЕРСИЯ: 1

#ifndef FORMULA_H
#define FORMULA_H

const int MAX_FORMULA_LENGTH = 256;
const int MAX_VARIABLES = 10;
const int MAX_ERROR_LENGTH = 256;

// Проверяет, является ли символ пропозициональной переменной.
// В данной лабораторной используются только большие латинские буквы: A-Z.
bool is_variable(char symbol);

// Проверяет, является ли символ логической константой.
bool is_constant(char symbol);

// Проверяет, является ли символ допустимым служебным символом языка.
bool is_service_symbol(char symbol);

// Проверяет, начинается ли с текущей позиции бинарная связка.
bool is_binary_operator(const char formula[], int position);

// Возвращает длину оператора, который начинается с текущей позиции.
// Для /\ , \/ , -> длина равна 2.
// Для ~ длина равна 1.
int get_operator_length(const char formula[], int position);

// Добавляет переменную в массив, если её там ещё нет.
bool add_variable(char variables[], int& variableCount, char variable);

// Собирает все переменные из двух формул.
bool collect_variables(
    const char formulaF[],
    const char formulaG[],
    char variables[],
    int& variableCount
);

// Возвращает индекс переменной в массиве variables.
int get_variable_index(const char variables[], int variableCount, char variable);

// Копирует одну C-строку в другую.
void copy_text(char target[], const char source[]);

// Возвращает длину C-строки.
int get_text_length(const char text[]);

#endif