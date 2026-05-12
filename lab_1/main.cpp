    /////////////////////////////////////////////////////////////////////////////////////////
    // Лабораторная работа №1 по дисциплине ЛОИС
    // Выполнена студентом группы 421701 БГУИР Бибко Владислав Викторович
    // 
    // НАЗНАЧЕНИЕ: Файл реализует функции необходимые для вычисления (построения)
    //            таблицы истинности логической формулы (заданной в виде дерева), 
    //            проверки логического следования одной формулы из другой, сбора переменных
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
void printHelp() {
    cout << "Допустимый синтаксис формул:" << endl;
    cout << "A" << endl;
    cout << "0" << endl;
    cout << "1" << endl;
    cout << "(-A)" << endl;
    cout << "(A/\\B)" << endl;
    cout << "(A\\/B)" << endl;
    cout << "(A->B)" << endl;
    cout << "(A~B)" << endl;
    cout << "((A/\\B)->C)" << endl;
    cout << endl;
    cout << "Важно: используются только большие латинские буквы A-Z." << endl;
    cout << "Пробелы в формулах не используются." << endl;
    cout << endl;
}

// Считывает корректную формулу.
// Если пользователь ошибся, программа не завершается, а просит повторить ввод.
void readValidFormula(char formula[], const char formulaName[]) {
    char errorMessage[MAX_ERROR_LENGTH];
    bool isCorrect = false;

    while (!isCorrect) {
        cout << "Введите формулу " << formulaName << ": ";
        cin.getline(formula, MAX_FORMULA_LENGTH);

        if (validateFormula(formula, errorMessage)) {
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
bool askContinue() {
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

    printHelp();

    while (isRunning) {
        char formulaF[MAX_FORMULA_LENGTH];
        char formulaG[MAX_FORMULA_LENGTH];

        char variables[MAX_VARIABLES];
        int variableCount = 0;

        readValidFormula(formulaF, "F");
        readValidFormula(formulaG, "G");

        if (!collectVariables(formulaF, formulaG, variables, variableCount)) {
            cout << "Ошибка: в формулах слишком много переменных." << endl;
            cout << "Максимальное количество переменных: "
                 << MAX_VARIABLES << endl;
        } else {
            cout << endl;
            checkEntailment(formulaF, formulaG, variables, variableCount);
        }

        isRunning = askContinue();

        cout << endl;
    }

    cout << "Работа программы завершена." << endl;

    return 0;
}