#include "validator.h"

/****************************************************************************************
 * Реализация проверки формулы.
 *
 * Проверка сделана через рекурсивный разбор:
 * - атомарная формула: A, 0, 1;
 * - отрицание: (-F);
 * - бинарная формула: (F/\G), (F\/G), (F->G), (F~G).
 *
 * Такой способ удобен, потому что он проверяет не только символы,
 * но и правильную структуру формулы.
 ****************************************************************************************/

// Проверяет, что символ вообще принадлежит алфавиту языка.
bool isAllowedSymbol(char symbol) {
    return isVariable(symbol) ||
           isConstant(symbol) ||
           isServiceSymbol(symbol);
}

// Проверяет, что строка не пустая и не слишком длинная.
bool validateBasicText(const char formula[], char errorMessage[]) {
    int length = getTextLength(formula);

    if (length == 0) {
        copyText(errorMessage, "формула не должна быть пустой");
        return false;
    }

    if (length >= MAX_FORMULA_LENGTH - 1) {
        copyText(errorMessage, "формула слишком длинная");
        return false;
    }

    return true;
}

// Проверяет, что в формуле нет символов вне алфавита.
bool validateAlphabet(const char formula[], char errorMessage[]) {
    for (int i = 0; formula[i] != '\0'; i++) {
        if (!isAllowedSymbol(formula[i])) {
            copyText(errorMessage, "формула содержит символ вне алфавита");
            return false;
        }
    }

    return true;
}

// Рекурсивно разбирает формулу, начиная с позиции position.
// После успешного разбора position указывает на первый символ после формулы.
bool parseFormula(const char formula[], int& position, char errorMessage[]) {
    char current = formula[position];

    // Если дошли до конца строки, а формулу ещё ждали — это ошибка.
    if (current == '\0') {
        copyText(errorMessage, "неожиданный конец формулы");
        return false;
    }

    // Атомарная формула: переменная или логическая константа.
    if (isVariable(current) || isConstant(current)) {
        position++;
        return true;
    }

    // Любая сложная формула должна начинаться с открывающей скобки.
    if (current != '(') {
        copyText(errorMessage, "ожидалась переменная, константа или открывающая скобка");
        return false;
    }

    // Пропускаем '('.
    position++;

    // Случай отрицания: (-F)
    if (formula[position] == '-') {
        position++;

        if (!parseFormula(formula, position, errorMessage)) {
            return false;
        }

        if (formula[position] != ')') {
            copyText(errorMessage, "после отрицания ожидалась закрывающая скобка");
            return false;
        }

        position++;
        return true;
    }

    // Случай бинарной формулы: (F op G)
    if (!parseFormula(formula, position, errorMessage)) {
        return false;
    }

    if (!isBinaryOperatorAt(formula, position)) {
        copyText(errorMessage, "ожидалась бинарная логическая связка");
        return false;
    }

    int operatorLength = getOperatorLength(formula, position);
    position += operatorLength;

    if (!parseFormula(formula, position, errorMessage)) {
        return false;
    }

    if (formula[position] != ')') {
        copyText(errorMessage, "ожидалась закрывающая скобка");
        return false;
    }

    position++;
    return true;
}

bool validateFormula(const char formula[], char errorMessage[]) {
    if (!validateBasicText(formula, errorMessage)) {
        return false;
    }

    if (!validateAlphabet(formula, errorMessage)) {
        return false;
    }

    int position = 0;

    if (!parseFormula(formula, position, errorMessage)) {
        return false;
    }

    // После разбора корректной формулы не должно оставаться лишних символов.
    if (formula[position] != '\0') {
        copyText(errorMessage, "после конца формулы найдены лишние символы");
        return false;
    }

    return true;
}