/////////////////////////////////////////////////////////////////////////////////////////
// Лабораторная работа №1 по дисциплине ЛОИС
// Выполнена студентом группы 421701 БГУИР Бибко Владислав Викторович
// 
// НАЗНАЧЕНИЕ: Файл реализует функции вычисления логических формул, построения
//              таблицы истинности, перебора всех наборов значений переменных,
//              проверки логического следования одной формулы из другой и вывода
//              контрпримера при нарушении следования.
// 
// ССЫЛКИ: https://learn.microsoft.com/ru-ru/cpp/standard-library/iostream?view=msvc-170
//         
// 
// ДАТА: 12.05.2026
// ВЕРСИЯ: 1

#include <iostream>
#include "solver.h"

using namespace std;

// Применяет бинарную логическую операцию.
int use_binary_operator(char firstSymbol, char secondSymbol, int left, int right) {
    // Конъюнкция: (/\)
    if (firstSymbol == '/' && secondSymbol == '\\') {
        return left && right;
    }

    // Дизъюнкция: \/
    if (firstSymbol == '\\' && secondSymbol == '/') {
        return left || right;
    }

    // Импликация: ->
    if (firstSymbol == '-' && secondSymbol == '>') {
        return (!left) || right;
    }

    // Эквивалентность: ~
    if (firstSymbol == '~') {
        return left == right;
    }

    // До этого места программа не должна доходить,
    // если формула была предварительно проверена валидатором.
    return 0;
}

// Выводит значения переменных в одной строке таблицы.
void print_variable_values(const int values[], int variableCount) {
    for (int i = 0; i < variableCount; i++) {
        cout << values[i] << " ";
    }
}

// Выводит конкретный контрпример, при котором следование нарушается.
void print_counterexample(
    const char variables[],
    const int values[],
    int variableCount
) {
    cout << "Контрпример: ";

    for (int i = 0; i < variableCount; i++) {
        cout << variables[i] << " = " << values[i];

        if (i < variableCount - 1) {
            cout << ", ";
        }
    }

    cout << endl;
}

// Рекурсивно вычисляет значение формулы.
// position после вычисления указывает на первый символ после разобранной формулы.
bool evaluate_formula(
    const char formula[],
    int& position,
    const char variables[],
    const int values[],
    int variableCount,
    int& result
) {
    char current = formula[position];

    // Логическая константа 0 или 1.
    if (is_constant(current)) {
        result = current - '0';
        position++;
        return true;
    }

    // Пропозициональная переменная.
    if (is_variable(current)) {
        int index = get_variable_index(variables, variableCount, current);

        if (index == -1) {
            return false;
        }

        result = values[index];
        position++;
        return true;
    }

    // Сложная формула должна начинаться со скобки.
    if (current != '(') {
        return false;
    }

    position++;

    // Случай отрицания: (-F)
    if (formula[position] == '!') {
        position++;

        int innerResult = 0;

        if (!evaluate_formula(formula, position, variables, values, variableCount, innerResult)) {
            return false;
        }

        if (formula[position] != ')') {
            return false;
        }

        position++;
        result = !innerResult;
        return true;
    }

    // Случай бинарной формулы: (F op G)
    int leftResult = 0;
    int rightResult = 0;

    if (!evaluate_formula(formula, position, variables, values, variableCount, leftResult)) {
        return false;
    }

    char firstOperatorSymbol = formula[position];
    char secondOperatorSymbol = '\0';

    int operatorLength = get_operator_length(formula, position);

    if (operatorLength == 0) {
        return false;
    }

    if (operatorLength == 2) {
        secondOperatorSymbol = formula[position + 1];
    }

    position += operatorLength;

    if (!evaluate_formula(formula, position, variables, values, variableCount, rightResult)) {
        return false;
    }

    if (formula[position] != ')') {
        return false;
    }

    position++;

    result = use_binary_operator(
        firstOperatorSymbol,
        secondOperatorSymbol,
        leftResult,
        rightResult
    );

    return true;
}

// Заполняет массив значений переменных по номеру строки таблицы истинности.
void fill_values_by_row_number(int rowNumber, int values[], int variableCount) {
    for (int i = variableCount - 1; i >= 0; i--) {
        values[i] = rowNumber % 2;
        rowNumber = rowNumber / 2;
    }
}

// Печатает заголовок таблицы истинности.
void print_table_header(const char variables[], int variableCount) {
    for (int i = 0; i < variableCount; i++) {
        cout << variables[i] << " ";
    }

    cout << "| F | G | F->G" << endl;

    for (int i = 0; i < variableCount; i++) {
        cout << "--";
    }

    cout << "----------" << endl;
}

// Строит таблицу истинности и проверяет следование G из F.
bool check_following(
    const char formulaF[],
    const char formulaG[],
    const char variables[],
    int variableCount
) {
    int values[MAX_VARIABLES];
    int rowCount = 1;

    for (int i = 0; i < variableCount; i++) {
        rowCount = rowCount * 2;
    }

    bool follows = true;
    bool counterexampleFound = false;
    int counterexampleValues[MAX_VARIABLES];

    print_table_header(variables, variableCount);

    for (int row = 0; row < rowCount; row++) {
        fill_values_by_row_number(row, values, variableCount);

        int positionF = 0;
        int positionG = 0;

        int resultF = 0;
        int resultG = 0;

        bool correctF = evaluate_formula(
            formulaF,
            positionF,
            variables,
            values,
            variableCount,
            resultF
        );

        bool correctG = evaluate_formula(
            formulaG,
            positionG,
            variables,
            values,
            variableCount,
            resultG
        );

        if (!correctF || !correctG) {
            cout << "Ошибка вычисления формулы." << endl;
            return false;
        }

        int implicationResult = (!resultF) || resultG;

        print_variable_values(values, variableCount);
        cout << "| " << resultF << " | " << resultG << " | " << implicationResult << endl;

        // Главное условие варианта 5:
        // если F истинна, а G ложна, то G не следует из F.
        if (resultF == 1 && resultG == 0) {
            follows = false;

            if (!counterexampleFound) {
                counterexampleFound = true;

                for (int i = 0; i < variableCount; i++) {
                    counterexampleValues[i] = values[i];
                }
            }
        }
    }

    cout << endl;

    if (follows) {
        cout << "Вывод: формула G следует из формулы F." << endl;
    } else {
        cout << "Вывод: формула G не следует из формулы F." << endl;
        print_counterexample(variables, counterexampleValues, variableCount);
    }

    return follows;
}