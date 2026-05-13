/////////////////////////////////////////////////////////////////////////////////////////
// Лабораторная работа №1 по дисциплине ЛОИС
// Выполнена студентом группы 421701 БГУИР Бибко Владислав Викторович
// 
// НАЗНАЧЕНИЕ: Файл реализует функции для базовой обработки формул сокращённого
//              языка логики высказываний: распознавание переменных, констант,
//              служебных символов и логических связок, сбор переменных из формул,
//              поиск переменной в массиве, копирование текста и вычисление длины
//              C-строки.
//
//         
// 
// ДАТА: 12.05.2026
// ВЕРСИЯ: 1

#include "formula.h"

bool is_variable(char symbol) {
    return symbol >= 'A' && symbol <= 'Z';
}

bool is_constant(char symbol) {
    return symbol == '0' || symbol == '1';
}

bool is_service_symbol(char symbol) {
    return symbol == '(' || symbol == ')' || symbol == '!' ||
           symbol == '/' || symbol == '\\' || symbol == '-' ||
           symbol == '>' || symbol == '~';
}

bool is_binary_operator(const char formula[], int position) {
    if (formula[position] == '/' && formula[position + 1] == '\\') {
        return true;
    }

    if (formula[position] == '\\' && formula[position + 1] == '/') {
        return true;
    }

    if (formula[position] == '-' && formula[position + 1] == '>') {
        return true;
    }

    if (formula[position] == '~') {
        return true;
    }

    return false;
}

int get_operator_length(const char formula[], int position) {
    if (formula[position] == '~') {
        return 1;
    }

    if (is_binary_operator(formula, position)) {
        return 2;
    }

    return 0;
}

bool add_variable(char variables[], int& variableCount, char variable) {
    for (int i = 0; i < variableCount; i++) {
        if (variables[i] == variable) {
            return true;
        }
    }

    if (variableCount >= MAX_VARIABLES) {
        return false;
    }

    variables[variableCount] = variable;
    variableCount++;

    return true;
}

bool collect_variables(
    const char formulaF[],
    const char formulaG[],
    char variables[],
    int& variableCount
) {
    variableCount = 0;

    for (int i = 0; formulaF[i] != '\0'; i++) {
        if (is_variable(formulaF[i])) {
            if (!add_variable(variables, variableCount, formulaF[i])) {
                return false;
            }
        }
    }

    for (int i = 0; formulaG[i] != '\0'; i++) {
        if (is_variable(formulaG[i])) {
            if (!add_variable(variables, variableCount, formulaG[i])) {
                return false;
            }
        }
    }

    return true;
}

int get_variable_index(const char variables[], int variableCount, char variable) {
    for (int i = 0; i < variableCount; i++) {
        if (variables[i] == variable) {
            return i;
        }
    }

    return -1;
}

void copy_text(char target[], const char source[]) {
    int i = 0;

    while (source[i] != '\0') {
        target[i] = source[i];
        i++;
    }

    target[i] = '\0';
}

int get_text_length(const char text[]) {
    int length = 0;

    while (text[length] != '\0') {
        length++;
    }

    return length;
}