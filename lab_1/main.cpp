/////////////////////////////////////////////////////////////////////////////////////////
// Лабораторная работа №1 по дисциплине ЛОИС
// Выполнена студентом группы 421701 БГУИР Бибко Владислав Викторович
// 
/// НАЗНАЧЕНИЕ: Файл содержит точку входа в программу, реализует пользовательский
//              интерфейс, вывод справочной информации, ввод формул F и G,
//              повторный ввод при ошибках, запуск проверки логического следования
//              и управление циклом работы программы.
// 
// ССЫЛКИ: https://learn.microsoft.com/ru-ru/cpp/standard-library/iostream?view=msvc-170
//         
// 
// ДАТА: 12.05.2026
// ВЕРСИЯ: 1


#include <iostream>
#include "formula.h"
#include "validator.h"
#include "solver.h"

using namespace std;


// Выводит подсказку по синтаксису формул.
void print_help() {
}

// Считывает корректную формулу.
// Если пользователь ошибся, программа не завершается, а просит повторить ввод.
void read_valid_formula(char formula[], const char formulaName[]) {
    char errorMessage[MAX_ERROR_LENGTH];
    bool isCorrect = false;

    while (!isCorrect) {
        cout << "Введите формулу " << formulaName << ": ";
        cin.getline(formula, MAX_FORMULA_LENGTH);

        if (validate_formula(formula, errorMessage)) {
            isCorrect = true;
        } else {
            cout << "Ошибка в формуле " << formulaName << ": "
                 << errorMessage << endl;
            cout << "Введите формулу повторно." << endl;
            cout << endl;
        }
    }
}

// Запрашивает у пользователя желание продолжить работу.
bool ask_continue() {
    char answer;

    cout << endl;
    cout << "Проверить ещё одну пару формул? (y/n): ";
    cin >> answer;
    cin.ignore(10000, '\n');

    return answer == 'y' || answer == 'Y';
}

int main() {
    bool isRunning = true;

    cout << "Лабораторная работа №1. Вариант 5." << endl;
    cout << "Проверка логического следования F |= G." << endl;
    cout << endl;

    print_help();

    while (isRunning) {
        char formulaF[MAX_FORMULA_LENGTH];
        char formulaG[MAX_FORMULA_LENGTH];

        char variables[MAX_VARIABLES];
        int variableCount = 0;

        read_valid_formula(formulaF, "F");
        read_valid_formula(formulaG, "G");

        if (!collect_variables(formulaF, formulaG, variables, variableCount)) {
            cout << "Ошибка: в формулах слишком много переменных." << endl;
            cout << "Максимальное количество переменных: "
                 << MAX_VARIABLES << endl;
        } else {
            cout << endl;
            check_following(formulaF, formulaG, variables, variableCount);
        }

        isRunning = ask_continue();

        cout << endl;
    }

    cout << "Работа программы завершена." << endl;

    return 0;
}