#ifndef TASK2_MAIN_H
#define TASK2_MAIN_H

#include <vector>

using namespace std;

/**
 * Линейная интерполяция
 * x: значение x для которого нужно вычислить интерполированное значение y.
 * point1: координаты первой точки на кривой.
 * point2: координаты второй точки на кривой.
 */
double linearInterpolation(double x, pair<double, double> point1, pair<double, double> point2);

/**
 * Канонической полином
 * p: многочлен, представленный в виде вектора коэффициентов, начиная со старшего
 */
vector<double> canonicalPolynomial(const vector<double>& p);

/**
 * Полином Лагранджа
 * points: набор точек, представленный в виде вектора пар значений x и y.
 * x: значение x, для которого необходимо рассчитать значение интерполяционного многочлена.
 */
double lagrangePolynomial(const vector<pair<double, double>>& points, double x);

/**
 * Полином Ньютона
 * points: набор точек, представленный в виде вектора пар значений x и y.
 * x: значение x, для которого необходимо рассчитать значение интерполяционного многочлена.
 */
double newtonPolynomial(const vector<pair<double, double>>& points, double x);

#endif //TASK2_MAIN_H
