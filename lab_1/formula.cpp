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

bool isVariable(char symbol) {
    return symbol >= 'A' && symbol <= 'Z';
}

bool isConstant(char symbol) {
    return symbol == '0' || symbol == '1';
}

bool isServiceSymbol(char symbol) {
    return symbol == '(' || symbol == ')' || symbol == '-' ||
           symbol == '/' || symbol == '\\' || symbol == '>' ||
           symbol == '~';
}

bool isBinaryOperatorAt(const char formula[], int position) {
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

int getOperatorLength(const char formula[], int position) {
    if (formula[position] == '~') {
        return 1;
    }

    if (isBinaryOperatorAt(formula, position)) {
        return 2;
    }

    return 0;
}

bool addVariable(char variables[], int& variableCount, char variable) {
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

bool collectVariables(
    const char formulaF[],
    const char formulaG[],
    char variables[],
    int& variableCount
) {
    variableCount = 0;

    for (int i = 0; formulaF[i] != '\0'; i++) {
        if (isVariable(formulaF[i])) {
            if (!addVariable(variables, variableCount, formulaF[i])) {
                return false;
            }
        }
    }

    for (int i = 0; formulaG[i] != '\0'; i++) {
        if (isVariable(formulaG[i])) {
            if (!addVariable(variables, variableCount, formulaG[i])) {
                return false;
            }
        }
    }

    return true;
}

int getVariableIndex(const char variables[], int variableCount, char variable) {
    for (int i = 0; i < variableCount; i++) {
        if (variables[i] == variable) {
            return i;
        }
    }

    return -1;
}

void copyText(char target[], const char source[]) {
    int i = 0;

    while (source[i] != '\0') {
        target[i] = source[i];
        i++;
    }

    target[i] = '\0';
}

int getTextLength(const char text[]) {
    int length = 0;

    while (text[length] != '\0') {
        length++;
    }

    return length;
}