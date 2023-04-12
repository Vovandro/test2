#include "./main.h"


double linearInterpolation(double x, pair<double, double> point1, pair<double, double> point2) {
    double y;
    y = point1.second + ((point2.second - point1.second) / (point2.first - point1.first)) * (x - point1.first);
    return y;
}

// функция для деления многочленов
vector<double> dividePolynomials(vector<double>& A, const vector<double>& B) {
    int n = A.size() - 1, m = B.size() - 1;
    vector<double> R(n + 1), Q(n - m + 1, 0.0);

    for (int k = n - m; k >= 0; --k) {
        Q[k] = A[m + k] / B[m];
        for (int j = m + k - 1; j >= k; --j) {
            A[j] -= Q[k] * B[j - k];
        }
    }

    for (int i = 0; i <= n; ++i) {
        R[i] = A[i];
    }

    return R;
}

vector<double> canonicalPolynomial(const vector<double>& p) {
    vector<double> q = p;
    double leading_coefficient = q.front();
    for (double& c : q) {
        c /= leading_coefficient;
    }
    q = dividePolynomials(q, {1.0, -1.0});
    q.insert(q.begin(), 1.0);
    return q;
}

double lagrangePolynomial(const vector<std::pair<double, double>>& points, double x) {
    int n = points.size();
    double result = 0.0;

    for (int i = 0; i < n; ++i) {
        double term = points[i].second;

        for (int j = 0; j < n; ++j) {
            if (j != i) {
                term *= (x - points[j].first) / (points[i].first - points[j].first);
            }
        }

        result += term;
    }

    return result;
}

double newtonPolynomial(const vector<std::pair<double, double>>& points, double x) {
    int n = points.size();

   vector<std::vector<double>> divided_differences(n,vector<double>(n));
    for (int i = 0; i < n; ++i) {
        divided_differences[i][0] = points[i].second;
    }

    for (int j = 1; j < n; ++j) {
        for (int i = j; i < n; ++i) {
            divided_differences[i][j] = (divided_differences[i][j - 1] - divided_differences[i - 1][j - 1]) / (points[i].first - points[i - j].first);
        }
    }

    double result = divided_differences[0][0];
    double product = 1.0;
    for (int i = 1; i < n; ++i) {
        product *= (x - points[i - 1].first);
        result += divided_differences[i][i] * product;
    }

    return result;
}