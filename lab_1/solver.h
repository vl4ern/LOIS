/////////////////////////////////////////////////////////////////////////////////////////
// Лабораторная работа №1 по дисциплине ЛОИС
// Выполнена студентом группы 421701 БГУИР Бибко Владислав Викторович
// 
// НАЗНАЧЕНИЕ: Файл содержит объявления функций, необходимых для вычисления
//              логических формул при заданных значениях переменных и проверки
//              логического следования формулы G из формулы F.
//
//         
// 
// ДАТА: 12.05.2026
// ВЕРСИЯ: 1

#ifndef SOLVER_H
#define SOLVER_H

#include "formula.h"

// Вычисляет значение формулы при заданных значениях переменных.
bool evaluate_formula(
    const char formula[],
    int& position,
    const char variables[],
    const int values[],
    int variableCount,
    int& result
);

// Строит таблицу истинности и проверяет логическое следование.
bool check_following(
    const char formulaF[],
    const char formulaG[],
    const char variables[],
    int variableCount
);

#endif