#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class Matrix {
private:
    T** data; 
    size_t rows; 
    size_t cols; 

public:
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
        data = new T * [rows];
        for (size_t i = 0; i < rows; ++i) {
            data[i] = new T[cols];
        }
    }

    ~Matrix() {
        for (size_t i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    void fillFromKeyboard() {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                cout << "Enter element at position (" << i << ", " << j << "): ";
                cin >> data[i][j];
            }
        }
    }

    void fillRandom() {
        srand(static_cast<unsigned>(time(0)));
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = static_cast<T>(rand() % 100);
            }
        }
    }

    void display() const {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                cout << setw(4) << data[i][j] << " ";
            }
            cout << '\n';
        }
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            cout << "Error: Matrix dimensions do not match for addition.\n";
            exit(EXIT_FAILURE);
        }

        Matrix result(rows, cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            cout << "Error: Matrix dimensions do not match for subtraction.\n";
            exit(EXIT_FAILURE);
        }

        Matrix result(rows, cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }

        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            cout << "Error: Incompatible matrix dimensions for multiplication.\n";
            exit(EXIT_FAILURE);
        }

        Matrix result(rows, other.cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0;
                for (size_t k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    Matrix operator/(const T& scalar) const {
        if (scalar == 0) {
            cout << "Error: Division by zero.\n";
            exit(EXIT_FAILURE);
        }

        Matrix result(rows, cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] / scalar;
            }
        }

        return result;
    }

    T findMax() const {
        T maxVal = data[0][0];
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (data[i][j] > maxVal) {
                    maxVal = data[i][j];
                }
            }
        }
        return maxVal;
    }

    T findMin() const {
        T minVal = data[0][0];
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (data[i][j] < minVal) {
                    minVal = data[i][j];
                }
            }
        }
        return minVal;
    }
};

int main() {
    Matrix<int> matrix1(3, 3);
    matrix1.fillRandom();
    cout << "Matrix 1:\n";
    matrix1.display();

    Matrix<int> matrix2(3, 3);
    matrix2.fillRandom();
    cout << "\nMatrix 2:\n";
    matrix2.display();

    Matrix<int> sumMatrix = matrix1 + matrix2;
    cout << "\nMatrix Sum:\n";
    sumMatrix.display();

    Matrix<int> diffMatrix = matrix1 - matrix2;
    cout << "\nMatrix Difference:\n";
    diffMatrix.display();

    Matrix<int> productMatrix = matrix1 * matrix2;
    cout << "\nMatrix Product:\n";
    productMatrix.display();

    Matrix<int> scaledMatrix = matrix1 / 2;
    cout << "\nMatrix Scaled by 2:\n";
    scaledMatrix.display();

    cout << "\nMaximum element in Matrix 1: " << matrix1.findMax() << '\n';
    cout << "Minimum element in Matrix 2: " << matrix2.findMin() << '\n';

    return 0;
}
