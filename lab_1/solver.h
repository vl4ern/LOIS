#ifndef SOLVER_H
#define SOLVER_H

#include "formula.h"

/****************************************************************************************
 * Модуль solver
 *
 * НАЗНАЧЕНИЕ:
 * Содержит основную логику варианта 5:
 * проверку, следует ли формула G из формулы F.
 *
 * Логическое следование F |= G нарушается только в одном случае:
 * F = 1, G = 0.
 ****************************************************************************************/

// Вычисляет значение формулы при заданных значениях переменных.
bool evaluateFormula(
    const char formula[],
    int& position,
    const char variables[],
    const int values[],
    int variableCount,
    int& result
);

// Строит таблицу истинности и проверяет логическое следование.
bool checkEntailment(
    const char formulaF[],
    const char formulaG[],
    const char variables[],
    int variableCount
);

#endif