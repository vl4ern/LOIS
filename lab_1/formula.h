#ifndef FORMULA_H
#define FORMULA_H

/****************************************************************************************
 * Модуль formula
 *
 * НАЗНАЧЕНИЕ:
 * Содержит функции для работы с формулами сокращённого языка логики высказываний:
 * - проверка типов символов;
 * - работа с переменными;
 * - вычисление формулы при заданных значениях переменных.
 *
 * ВАЖНО:
 * В программе не используются string, vector, stack, map и регулярные выражения.
 * Все строки и структуры данных реализованы через обычные массивы.
 ****************************************************************************************/

const int MAX_FORMULA_LENGTH = 256;
const int MAX_VARIABLES = 10;
const int MAX_ERROR_LENGTH = 256;

// Проверяет, является ли символ пропозициональной переменной.
// В данной лабораторной используются только большие латинские буквы: A-Z.
bool isVariable(char symbol);

// Проверяет, является ли символ логической константой.
bool isConstant(char symbol);

// Проверяет, является ли символ допустимым служебным символом языка.
bool isServiceSymbol(char symbol);

// Проверяет, начинается ли с текущей позиции бинарная связка.
bool isBinaryOperatorAt(const char formula[], int position);

// Возвращает длину оператора, который начинается с текущей позиции.
// Для /\ , \/ , -> длина равна 2.
// Для ~ длина равна 1.
int getOperatorLength(const char formula[], int position);

// Добавляет переменную в массив, если её там ещё нет.
bool addVariable(char variables[], int& variableCount, char variable);

// Собирает все переменные из двух формул.
bool collectVariables(
    const char formulaF[],
    const char formulaG[],
    char variables[],
    int& variableCount
);

// Возвращает индекс переменной в массиве variables.
int getVariableIndex(const char variables[], int variableCount, char variable);

// Копирует одну C-строку в другую.
void copyText(char target[], const char source[]);

// Возвращает длину C-строки.
int getTextLength(const char text[]);

#endif