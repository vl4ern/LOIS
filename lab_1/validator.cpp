/////////////////////////////////////////////////////////////////////////////////////////
// Лабораторная работа №1 по дисциплине ЛОИС
// Выполнена студентом группы 421701 БГУИР Бибко Владислав Викторович
// 
// НАЗНАЧЕНИЕ: Файл реализует проверку корректности введённой логической формулы:
//              проверку пустого ввода, допустимости символов, структуры формулы,
//              правильности использования скобок, отрицания, бинарных логических
//              связок и отсутствия лишних символов после конца формулы.
// 
//         
// 
// ДАТА: 12.05.2026
// ВЕРСИЯ: 1

#include "validator.h"

// Проверяет, что символ вообще принадлежит алфавиту языка.
bool is_allowed_symbol(char symbol) {
    return is_variable(symbol) ||
           is_constant(symbol) ||
           is_service_symbol(symbol);
}

// Проверяет, что строка не пустая и не слишком длинная.
bool validate_basic_text(const char formula[], char errorMessage[]) {
    int length = get_text_length(formula);

    if (length == 0) {
        copy_text(errorMessage, "формула не должна быть пустой");
        return false;
    }

    if (length >= MAX_FORMULA_LENGTH - 1) {
        copy_text(errorMessage, "формула слишком длинная");
        return false;
    }

    return true;
}

// Проверяет, что в формуле нет символов вне алфавита.
bool validate_alphabet(const char formula[], char errorMessage[]) {
    for (int i = 0; formula[i] != '\0'; i++) {
        if (!is_allowed_symbol(formula[i])) {
            copy_text(errorMessage, "формула содержит символ вне алфавита");
            return false;
        }
    }

    return true;
}

// Рекурсивно разбирает формулу, начиная с позиции position.
// После успешного разбора position указывает на первый символ после формулы.
bool parse_formula(const char formula[], int& position, char errorMessage[]) {
    char current = formula[position];

    // Если дошли до конца строки, а формулу ещё ждали — это ошибка.
    if (current == '\0') {
        copy_text(errorMessage, "неожиданный конец формулы");
        return false;
    }

    // Атомарная формула: переменная или логическая константа.
    if (is_variable(current) || is_constant(current)) {
        position++;
        return true;
    }

    // Любая сложная формула должна начинаться с открывающей скобки.
    if (current != '(') {
        copy_text(errorMessage, "ожидалась переменная, константа или открывающая скобка");
        return false;
    }

    // Пропускаем '('.
    position++;

    // Случай отрицания: (-F)
    if (formula[position] == '!') {
        position++;

        if (!parse_formula(formula, position, errorMessage)) {
            return false;
        }

        if (formula[position] != ')') {
            copy_text(errorMessage, "после отрицания ожидалась закрывающая скобка");
            return false;
        }

        position++;
        return true;
    }

    // Случай бинарной формулы: (F op G)
    if (!parse_formula(formula, position, errorMessage)) {
        return false;
    }

    if (!is_binary_operator(formula, position)) {
        copy_text(errorMessage, "ожидалась бинарная логическая связка");
        return false;
    }

    int operatorLength = get_operator_length(formula, position);
    position += operatorLength;

    if (!parse_formula(formula, position, errorMessage)) {
        return false;
    }

    if (formula[position] != ')') {
        copy_text(errorMessage, "ожидалась закрывающая скобка");
        return false;
    }

    position++;
    return true;
}

bool validate_formula(const char formula[], char errorMessage[]) {
    if (!validate_basic_text(formula, errorMessage)) {
        return false;
    }

    if (!validate_alphabet(formula, errorMessage)) {
        return false;
    }

    int position = 0;

    if (!parse_formula(formula, position, errorMessage)) {
        return false;
    }

    // После разбора корректной формулы не должно оставаться лишних символов.
    if (formula[position] != '\0') {
        copy_text(errorMessage, "после конца формулы найдены лишние символы");
        return false;
    }

    return true;
}