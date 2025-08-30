#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int n;
    cout << "Ingrese el numero de puntos: ";
    cin >> n;

    //Ingreso de datos separados por un espacio
    vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cout << "Ingrese x[" << i << "] y y[" << i << "]: ";
        cin >> x[i] >> y[i];
    }

    // Calcular sumatorias
    double sum_x = 0, sum_y = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0;
    double sum_xy = 0, sum_x2y = 0;
    for (int i = 0; i < n; ++i) {
        sum_x += x[i];
        sum_y += y[i];
        sum_x2 += pow(x[i], 2);
        sum_x3 += pow(x[i], 3);
        sum_x4 += pow(x[i], 4);
        sum_xy += x[i] * y[i];
        sum_x2y += pow(x[i], 2) * y[i];
    }

    // Matriz del sistema (3x3) y vector b
    double mat[3][3] = {
        {static_cast<double>(n), sum_x, sum_x2},
        {sum_x, sum_x2, sum_x3},
        {sum_x2, sum_x3, sum_x4}
    };
    double b[3] = {sum_y, sum_xy, sum_x2y};

    // Eliminación de Gauss simple (sin pivoteo)
    for (int i = 0; i < 3; ++i) {
        for (int k = i + 1; k < 3; ++k) {
            double factor = mat[k][i] / mat[i][i];
            for (int j = i; j < 3; ++j) {
                mat[k][j] -= factor * mat[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    // Sustitución hacia atrás
    double sol[3]; // c, b, a
    for (int i = 2; i >= 0; --i) {
        sol[i] = b[i];
        for (int j = i + 1; j < 3; ++j) {
            sol[i] -= mat[i][j] * sol[j];
        }
        sol[i] /= mat[i][i];
    }

    cout << "La funcion cuadratica es: y = " << sol[2] << " x^2 + " << sol[1] << " x + " << sol[0] << std::endl;

    return 0;
}
