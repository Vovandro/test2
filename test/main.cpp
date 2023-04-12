#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include "../lib/main.h"

void drawGraph(const std::vector<std::pair<double, double>> &points) {
    // определяем размеры графика
    const int height = 10, width = 100;
    const char blank = ' ';

    // определяем максимальные и минимальные значения по осям x и y
    double xMin = points.front().first, xMax = points.front().first, yMin = points.front().second, yMax = points.front().second;
    for (const auto &point: points) {
        xMin = std::min(xMin, point.first);
        xMax = std::max(xMax, point.first);
        yMin = std::min(yMin, point.second);
        yMax = std::max(yMax, point.second);
    }

    // определяем масштаб по осям x и y
    const double xScale = width / (xMax - xMin), yScale = height / (yMax - yMin);

    // создаем массив для хранения точек графика
    std::vector<std::vector<char>> graph(height + 1, std::vector<char>(width + 1, blank));

    // отмечаем точки на графике
    for (const auto &point: points) {
        int x = std::round((point.first - xMin) * xScale), y = std::round((point.second - yMin) * yScale);
        graph[height - y][x] = 'o';
    }

    // выводим график в консоль
    for (int i = 0; i <= height + 1; ++i) {
        for (int j = 0; j <= width + 1; ++j) {
            if (i == height + 1)
                std::cout << "_";
            else if (j == 0)
                std::cout << "|";
            else
                std::cout << graph[i][j - 1];
        }
        std::cout << '\n';
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Invalid arguments count" << endl;
        return 1;
    }

    cout << "Select algorithm:" << endl;
    cout << "\t1: Linear interpolation" << endl;
    cout << "\t2: Canonical polynomial" << endl;
    cout << "\t3: Lagrange polynomial" << endl;
    cout << "\t4: Newton polynomial" << endl;

    int alg;

    cin >> alg;
    cout << endl;

    if (alg < 1 || alg > 4) {
        cout << "Invalid selected algorithm" << endl;
        return 1;
    }

    ifstream file(argv[1], ios::in | ios::binary);

    if (!file.is_open()) {
        cout << "Could not open file" << endl;
        return 1;
    }

    string line;
    vector<double> numbers;

    while (std::getline(file, line)) {
        double number;
        istringstream iss(line);
        iss >> number;
        numbers.push_back(number);
    }

    file.close();

    switch (alg) {
        case 1: {
            vector<pair<double, double>> data;

            if (numbers.size() % 2 != 0) {
                cout << "Invalid count numbers" << endl;
                return 1;
            }

            int j;
            double xLast, yLast;

            for (int i = 0; i < numbers.size() % 2; ++i) {
                double x1, y1;

                x1 = numbers[i];
                y1 = numbers[i + 1];

                if (i == 0) {
                    data.emplace_back(x1, y1);
                    j = x1;
                    xLast = x1;
                    yLast = y1;
                } else {
                    for (; j < x1; ++j) {
                        data.emplace_back(j, linearInterpolation(j, pair{xLast, yLast}, pair{x1, y1}));
                    }

                    xLast = x1;
                    yLast = y1;
                }
            }

            drawGraph(data);
        }
            break;

        case 2: {
            auto data = canonicalPolynomial(numbers);

            for (int i = 0; i < data.size(); ++i) {
                if (i != 0)
                    cout << ", ";

                cout << data[i];
            }
        }
            break;

        case 3: {
            vector<pair<double, double>> pointsAll;

            if (numbers.size() % 2 != 0) {
                cout << "Invalid count numbers" << endl;
                return 1;
            }

            double minX, maxX;

            for (int i = 0; i < numbers.size() % 2; ++i) {
                double x1, y1;

                x1 = numbers[i];
                y1 = numbers[i + 1];

                minX = min(x1, minX);
                maxX = max(x1, maxX);

                pointsAll.emplace_back(x1, y1);
            }

            vector<pair<double, double>> data;

            for (int j = minX; j < maxX; ++j) {
                data.emplace_back(j, lagrangePolynomial(pointsAll, j));
            }

            drawGraph(data);
        }
            break;

        case 4: {
            vector<pair<double, double>> pointsAll;

            if (numbers.size() % 2 != 0) {
                cout << "Invalid count numbers" << endl;
                return 1;
            }

            double minX, maxX;

            for (int i = 0; i < numbers.size() % 2; ++i) {
                double x1, y1;

                x1 = numbers[i];
                y1 = numbers[i + 1];

                minX = min(x1, minX);
                maxX = max(x1, maxX);

                pointsAll.emplace_back(x1, y1);
            }

            vector<pair<double, double>> data;

            for (int j = minX; j < maxX; ++j) {
                data.emplace_back(j, newtonPolynomial(pointsAll, j));
            }

            drawGraph(data);
        }
            break;

        default:
            break;
    }

    std::vector<std::pair<double, double>> data;

    for (int i = 0; i < 20; ++i) {
        double y = std::rand() % (i + 1);

        data.emplace_back(i, y);
    }

    drawGraph(data);

    return 0;
}
